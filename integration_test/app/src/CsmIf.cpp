/**
 * @file CsmIf.cpp
 * @author Steven Le (sonlq@vingroup.net)
 * @brief
 * @version 0.1
 * @date 2021-12-09
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "spdlog/spdlog.h"

#include "CsmIf.h"
#include "platform/core/ipc/Publisher.h"
#include "platform/core/ipc/SubscribingTaskEventQueue.h"

#include <list>
#include <utility>

#include <json/json.h>
#include <json/reader.h>
#include <ss_helper.h>

#define CSM_OK      1
#define CSM_FAILURE 0
#define OBJECT_ID_MP_AUTHEN_LIST "mp_authen_list"
#define OBJECT_ID_MP_AUTHEN_LIST_LEN "mp_authen_list"
#define OBJECT_ID_CCS_CLIENT_CERT "ccs_client_cert"
#define OBJECT_ID_CCS_CLIENT_KEY "ccs_client_key"
#define OBJECT_ID_CCS_CA_CERT "ccs_ca_cert"
#define OBJECT_ID_TEMPO_CS_PKEY "tempo_cs_pkey"

using namespace platform::core::ipc;
using namespace platform::core::timer;
using namespace std::chrono;

const int CSM_JOB_LIFETIME_TIMER_ID     = 1;
static constexpr const char* csm_if_tag = "CsmIf";

namespace rb::csm {
CsmIf::CsmIf(const std::string& interface_id, uint32_t stack_size, uint32_t priority,
             std::weak_ptr<platform::core::ipc::TaskEventQueue<std::shared_ptr<rb::csm::CsmEventData>>> app_event_queue)
    : Task(interface_id, stack_size, priority, std::chrono::milliseconds(10000)),
      m_csmEventQueue(std::move(app_event_queue)),
      m_JobQueue(CsmJobQueue::create(10, *this, *this)),
      m_timerEvents(TimerQueue::create(5, *this, *this)),
      m_interfaceId(interface_id),
      m_keepAliveTimer(CSM_JOB_LIFETIME_TIMER_ID, m_timerEvents, false, std::chrono::seconds(1))
{
    SPDLOG_INFO("{}: ctor()", csm_if_tag);
}

CsmIf::~CsmIf()
{
    SPDLOG_INFO("{}: dtor()", csm_if_tag);
}

void CsmIf::tick() {}

void CsmIf::init() { SPDLOG_INFO("{}: init()", csm_if_tag); }

void CsmIf::event(const platform::core::timer::TimerExpiredEvent& event)
{
    if (CSM_JOB_LIFETIME_TIMER_ID == event.getId()) {}
}

void CsmIf::event(const std::shared_ptr<rb::csm::CsmEventData>& event)
{
    SPDLOG_INFO("{}: event for job_id: {}", csm_if_tag, event->jobId());
    switch (event->jobId()) {
    case rb::csm::CsmEventData::kCsmJobGenerateCsr: {
        onPrepareCSR();
        break;
    }
    case rb::csm::CsmEventData::kCsmJobUpdateCert: {
        onUpdateCert(event->data());
        break;
    }

    default:
        break;
    }
}

void CsmIf::publish(const std::shared_ptr<rb::csm::CsmEventData>& event) { m_JobQueue->push(event); }

// Implementation methods

int CsmIf::generateCSR(EVP_PKEY** privkey, X509_REQ** req)
{
    FILE* fp                   = nullptr;
    char pathname[PATH_MAX]    = {0};
    char stationId[50]         = {0};
    fp                         = popen("fw_printenv stationId", "r");
    if (fp == nullptr) {
        SPDLOG_INFO("popen() failed");
    }
    /* Read resulting list of pathnames until EOF */
    while (fgets(pathname, PATH_MAX, fp) != nullptr) {
        sscanf(pathname, "stationId=%49s", stationId);
        SPDLOG_ERROR("{}", stationId);
    }
    /* Close pipe, fetch and display termination status */
    pclose(fp);
    *privkey  = nullptr;
    *req      = nullptr;
    RSA* rsa  = nullptr;
    BIGNUM* e = nullptr;

    *privkey = EVP_PKEY_new();
    if (!*privkey) {
        EVP_PKEY_free(*privkey);
        X509_REQ_free(*req);
        RSA_free(rsa);
        BN_free(e);
        return CSM_FAILURE;
    }
    *req = X509_REQ_new();
    if (!*req) {
        EVP_PKEY_free(*privkey);
        X509_REQ_free(*req);
        RSA_free(rsa);
        BN_free(e);
        return CSM_FAILURE;
    }
    rsa = RSA_new();
    if (!rsa) {
        EVP_PKEY_free(*privkey);
        X509_REQ_free(*req);
        RSA_free(rsa);
        BN_free(e);
        return CSM_FAILURE;
    }
    e = BN_new();
    if (!e) {
        EVP_PKEY_free(*privkey);
        X509_REQ_free(*req);
        RSA_free(rsa);
        BN_free(e);
        return CSM_FAILURE;
    }
    BN_set_word(e, 65537);
    if (!RSA_generate_key_ex(rsa, RSA_KEY_BITS, e, nullptr)) {
        EVP_PKEY_free(*privkey);
        X509_REQ_free(*req);
        RSA_free(rsa);
        BN_free(e);
        return CSM_FAILURE;
    }
    if (!EVP_PKEY_assign_RSA(*privkey, rsa)) {
        EVP_PKEY_free(*privkey);
        X509_REQ_free(*req);
        RSA_free(rsa);
        BN_free(e);
        return CSM_FAILURE;
    }

    X509_REQ_set_pubkey(*req, *privkey);

    /* Set the DN of the request. */
    X509_NAME* name = X509_REQ_get_subject_name(*req);
    X509_NAME_add_entry_by_txt(name, "C", MBSTRING_ASC, (const unsigned char*)REQ_DN_C, -1, -1, 0);
    X509_NAME_add_entry_by_txt(name, "ST", MBSTRING_ASC, (const unsigned char*)REQ_DN_ST, -1, -1, 0);
    X509_NAME_add_entry_by_txt(name, "L", MBSTRING_ASC, (const unsigned char*)REQ_DN_L, -1, -1, 0);
    X509_NAME_add_entry_by_txt(name, "O", MBSTRING_ASC, (const unsigned char*)REQ_DN_O, -1, -1, 0);
    X509_NAME_add_entry_by_txt(name, "OU", MBSTRING_ASC, (const unsigned char*)REQ_DN_OU, -1, -1, 0);
    X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_ASC, (const unsigned char*)stationId, -1, -1, 0);

    /* Self-sign the request to prove that we possess the key. */
    if (!X509_REQ_sign(*req, *privkey, EVP_sha256())) {
        EVP_PKEY_free(*privkey);
        X509_REQ_free(*req);
        RSA_free(rsa);
        BN_free(e);
        return CSM_FAILURE;
    }

    BN_free(e);

    return CSM_OK;
}

void CsmIf::csrToPem(X509_REQ* crt, uint8_t** csr_bytes, size_t* csr_size)
{
    /* Convert signed certificate to PEM format. */
    BIO* bio = BIO_new(BIO_s_mem());
    PEM_write_bio_X509_REQ(bio, crt);
    *csr_size  = BIO_pending(bio);
    *csr_bytes = (uint8_t*)malloc(*csr_size + 1);
    BIO_read(bio, *csr_bytes, *csr_size);
    BIO_free_all(bio);
}

void CsmIf::crtToPem(X509* crt, uint8_t** csr_bytes, size_t* csr_size)
{
    /* Convert signed certificate to PEM format. */
    BIO* bio = BIO_new(BIO_s_mem());
    PEM_write_bio_X509(bio, crt);
    *csr_size  = BIO_pending(bio);
    *csr_bytes = (uint8_t*)malloc(*csr_size + 1);
    BIO_read(bio, *csr_bytes, *csr_size);
    BIO_free_all(bio);
}

void CsmIf::keyToPem(EVP_PKEY* key, uint8_t** key_bytes, size_t* key_size)
{
    /* Convert private key to PEM format. */
    BIO* bio = BIO_new(BIO_s_mem());
    PEM_write_bio_PrivateKey(bio, key, nullptr, nullptr, 0, nullptr, nullptr);
    *key_size  = BIO_pending(bio);
    *key_bytes = (uint8_t*)malloc(*key_size + 1);
    BIO_read(bio, *key_bytes, *key_size);
    BIO_free_all(bio);
}

void CsmIf::printBytes(uint8_t* data, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        printf("%c", data[i]);
    }
}

void CsmIf::onPrepareCSR(void)
{
    EVP_PKEY* key     = nullptr;
    X509_REQ* rsa     = nullptr;
    char objectId[64] = {0};
    int result        = CSM_FAILURE;

    SPDLOG_ERROR("{}: Genterating CSR...", csm_if_tag);

    result = generateCSR(&key, &rsa);
    if (result == CSM_FAILURE) {
        SPDLOG_ERROR("{}: Failed to generate key pair!", csm_if_tag);
        auto queue = m_csmEventQueue.lock();
        if (queue) {
            auto message = std::make_shared<rb::csm::CsmEventData>(rb::csm::CsmEventData::kCsmJobGenerateCsr,
                                                                   rb::csm::CsmEventData::kCsmResultFailure);
            queue->push(message);
        }
        else {
            SPDLOG_ERROR("{}: Null spt of {}", csm_if_tag, "m_csmEventQueue");
        }
    }
    else {
        SPDLOG_ERROR("{}: Genterate CSR Done", csm_if_tag);
        /* Convert key and certificate to PEM format. */
        uint8_t* key_bytes = nullptr;
        uint8_t* csr_bytes = nullptr;
        size_t key_size    = 0;
        size_t csr_size    = 0;

        keyToPem(key, &key_bytes, &key_size);
        SPDLOG_ERROR("{}: keyToPem Done", csm_if_tag);
        csrToPem(rsa, &csr_bytes, &csr_size);
        SPDLOG_ERROR("{}: csrToPem Done", csm_if_tag);

        // std::string destKeyfile = "/etc/ocpp/new_key.pem";
        // // prepare a file to write
        // std::ofstream outfile_key(destKeyfile, std::ofstream::binary);
        // // write to outfile
        // outfile_key.write(reinterpret_cast<char*>(key_bytes), key_size);
        // outfile_key.close();

        /* Write new tempo private key to secure storage */
        memset(objectId, 0, sizeof(objectId));
        strncpy(objectId, OBJECT_ID_TEMPO_CS_PKEY, strlen(OBJECT_ID_TEMPO_CS_PKEY));
        if (SSHelper_Write(objectId, reinterpret_cast<char*>(key_bytes), key_size)) {
            SPDLOG_INFO("{}", "write new key done");
            result = CSM_OK;
        }
        else {
            SPDLOG_ERROR("{}", "write new key fail");
        }
        auto queue = m_csmEventQueue.lock();
        if (queue) {
            if (result == CSM_OK) {
                auto message = std::make_shared<rb::csm::CsmEventData>(
                    rb::csm::CsmEventData::kCsmJobGenerateCsr, rb::csm::CsmEventData::kCsmResultOk,
                    std::string(reinterpret_cast<const char*>(csr_bytes), csr_size));
                queue->push(message);
            }
            else {
                auto message = std::make_shared<rb::csm::CsmEventData>(rb::csm::CsmEventData::kCsmJobGenerateCsr,
                                                                       rb::csm::CsmEventData::kCsmResultFailure);
                queue->push(message);
            }
        }
        else {
            SPDLOG_ERROR("{}: Null spt of {}", csm_if_tag, "m_csmEventQueue");
        }

        /* Print key and certificate. */
        // printBytes(key_bytes, key_size);
        // printBytes(csr_bytes, csr_size);

        // std::string destCSRfile = "/etc/ocpp/csr.pem";
        // // prepare a file to write
        // std::ofstream outfile_csr(destCSRfile, std::ofstream::binary);
        // // write to outfile
        // outfile_csr.write(reinterpret_cast<char*>(csr_bytes), csr_size);
        // outfile_csr.close();
        /* Free stuff. */
        EVP_PKEY_free(key);
        X509_REQ_free(rsa);
        free(key_bytes);
        free(csr_bytes);
    }
}

void CsmIf::onUpdateCert(const std::string& cert)
{
    auto queue = m_csmEventQueue.lock();
    if (queue) {
        if (CSM_FAILURE == verifyCert(cert)) {
            SPDLOG_ERROR("{}: Failed to verify certificate!", csm_if_tag);
            auto message = std::make_shared<rb::csm::CsmEventData>(rb::csm::CsmEventData::kCsmJobUpdateCert,
                                                                   rb::csm::CsmEventData::kCsmResultFailure);
            queue->push(message);
        }
        else {
            SPDLOG_INFO("{}: Verify certificate Done", csm_if_tag);
            char objectId[64]     = {0};
            std::string tempo_key = {};
            /* Read tempo key from secure storage */
            {
                /* Get data size */
                strncpy(objectId, OBJECT_ID_TEMPO_CS_PKEY, strlen(OBJECT_ID_TEMPO_CS_PKEY));
                auto size = SSHelper_GetSize(objectId);
                if (size)
                    SPDLOG_INFO("Get data size {}\r", size);
                else {
                    SPDLOG_INFO("get data size error ");
                    auto message = std::make_shared<rb::csm::CsmEventData>(rb::csm::CsmEventData::kCsmJobUpdateCert,
                                                                           rb::csm::CsmEventData::kCsmResultFailure);
                    queue->push(message);
                    return;
                }
                // allocate memory for file content
                char* buffer = new char[size + 1];
                memset(buffer, 0, (size + 1));

                // read content of objectId
                if (SSHelper_Read(objectId, buffer, size)) {
                    SPDLOG_INFO("read data done \r");
                }
                else {
                    SPDLOG_INFO("read data error \r");
                    delete[] buffer;
                    auto message = std::make_shared<rb::csm::CsmEventData>(rb::csm::CsmEventData::kCsmJobUpdateCert,
                                                                           rb::csm::CsmEventData::kCsmResultFailure);
                    queue->push(message);
                    return;
                }

                tempo_key = std::string(buffer);
                SPDLOG_DEBUG("Size of tempo_key: {}", tempo_key.size());
                delete[] buffer;
            }

            /* Replace old ccs_client_key object */
            memset(objectId, 0, sizeof(objectId));
            strncpy(objectId, OBJECT_ID_CCS_CLIENT_KEY, strlen(OBJECT_ID_CCS_CLIENT_KEY));

            if (SSHelper_Write(objectId, (char*)tempo_key.c_str(), tempo_key.size())) {
                SPDLOG_INFO("write data done ");
            }
            else {
                SPDLOG_INFO("write data error ");
                auto message = std::make_shared<rb::csm::CsmEventData>(rb::csm::CsmEventData::kCsmJobUpdateCert,
                                                                       rb::csm::CsmEventData::kCsmResultFailure);
                queue->push(message);
                return;
            }

            /* Replace old ccs_client_cert object */
            memset(objectId, 0, sizeof(objectId));
            strncpy(objectId, OBJECT_ID_CCS_CLIENT_CERT, strlen(OBJECT_ID_CCS_CLIENT_CERT));
            if (SSHelper_Write(objectId, (char*)cert.c_str(), cert.size())) {
                SPDLOG_INFO("write data done ");
            }
            else {
                SPDLOG_INFO("write data error ");
                auto message = std::make_shared<rb::csm::CsmEventData>(rb::csm::CsmEventData::kCsmJobUpdateCert,
                                                                       rb::csm::CsmEventData::kCsmResultFailure);
                queue->push(message);
                return;
            }
            SPDLOG_INFO("Succeed to update certificate");
            auto message = std::make_shared<rb::csm::CsmEventData>(rb::csm::CsmEventData::kCsmJobUpdateCert,
                                                                   rb::csm::CsmEventData::kCsmResultOk);
            queue->push(message);
            // If success to update certificate then delete LocalAuthenList if existed
            if (true == checkLocalAuthenList()) {
                bool ret = deleteLocalAuthenList();
                if (ret == true) {
                    SPDLOG_INFO("{}", "File deleted successfully");
                }
                else {
                    SPDLOG_ERROR("{}", "Error: unable to delete the file");
                }
            }
        }
    }
    else {
        SPDLOG_ERROR("{}: Null spt of {}", csm_if_tag, "m_csmEventQueue");
    }
}

int CsmIf::verifyCert(const std::string& cert)
{
    int result          = CSM_FAILURE;
    char objectId[64]   = {0};
    std::string ca_cert = {};
    auto untrusted_cert(cert);
    /* Read Trusted CA from secure storage */
    {
        /* Get data size */
        strncpy(objectId, OBJECT_ID_CCS_CA_CERT, strlen(OBJECT_ID_CCS_CA_CERT));
        auto size = SSHelper_GetSize(objectId);
        if (size)
            SPDLOG_INFO("Get data size {}\r", size);
        else {
            SPDLOG_INFO("get data size error ");
            return result;
        }
        // allocate memory for file content
        char* buffer = new char[size + 1];
        memset(buffer, 0, (size + 1));

        // read content of objectId
        if (SSHelper_Read(objectId, buffer, size)) {
            SPDLOG_INFO("read data done \r");
        }
        else {
            SPDLOG_INFO("read data error \r");
            delete[] buffer;
            return result;
        }

        ca_cert = std::string(buffer);
        SPDLOG_DEBUG("Size of ca_cert: {}", ca_cert.size());
        delete[] buffer;
    }

    /* Enable CRL checking of the server certificate */
    X509_STORE* store;
    // X509_STORE_CTX store_ctx; // X509_STORE_CTX_new();// store_ctx;

    BIO* bio = BIO_new(BIO_s_mem());

    /* Load Untrusted X509 from mem buffer */
    int written = BIO_write(bio, untrusted_cert.c_str(), untrusted_cert.size());
    if (written <= 0 || written != (signed int)untrusted_cert.size()) {
        SPDLOG_INFO("{}", "Failed to BIO_write ccs_client_cert");
        // goto exit_verification;
        if (bio != nullptr) {
            BIO_free_all(bio);
        }
        return result;
    }
    X509* vrfy_cert = PEM_read_bio_X509(bio, NULL, NULL, NULL);
    {
        SPDLOG_INFO("{}", "[Untrusted cert INFO]");
        X509_NAME* subj = X509_get_subject_name(vrfy_cert);

        for (int i = 0; i < X509_NAME_entry_count(subj); i++) {
            X509_NAME_ENTRY* e = X509_NAME_get_entry(subj, i);
            ASN1_STRING* d     = X509_NAME_ENTRY_get_data(e);
#if(0)
            const unsigned char* str = ASN1_STRING_get0_data(d);
#else
            unsigned char* str = ASN1_STRING_data(d);
#endif
            SPDLOG_INFO("{}", str);
        }
    }
    /* Load trusted X509 from mem buffer */
    int written2 = BIO_write(bio, ca_cert.c_str(), ca_cert.size());
    if (written2 <= 0 || written2 != (signed int)ca_cert.size()) {
        SPDLOG_INFO("{}", "Failed to BIO_write ccs_client_cert");
        // goto exit_verification;
        if (vrfy_cert != nullptr) {
            X509_free(vrfy_cert);
        }
        if (bio != nullptr) {
            BIO_free_all(bio);
        }
        return result;
    }
    X509* trusted_cert = PEM_read_bio_X509_AUX(bio, NULL, NULL, NULL);
    {
        SPDLOG_INFO("{}", "[Trusted CA INFO]");
        X509_NAME* subj = X509_get_subject_name(trusted_cert);

        for (int i = 0; i < X509_NAME_entry_count(subj); i++) {
            X509_NAME_ENTRY* e = X509_NAME_get_entry(subj, i);
            ASN1_STRING* d     = X509_NAME_ENTRY_get_data(e);
#if(0)
            const unsigned char* str = ASN1_STRING_get0_data(d);
#else
            unsigned char* str = ASN1_STRING_data(d);
#endif
            SPDLOG_INFO("{}", str);
        }
    }
    int n = 0;
    store = X509_STORE_new();
    if (store == NULL) {
        SPDLOG_INFO("{}", "Can't create X509_STORE");
        // goto exit_verification;
        if (store != nullptr) {
            X509_STORE_free(store);
        }
        if (trusted_cert != nullptr) {
            X509_free(trusted_cert);
        }
        if (vrfy_cert != nullptr) {
            X509_free(vrfy_cert);
        }
        if (bio != nullptr) {
            BIO_free_all(bio);
        }
        return result;
    }
    X509_STORE_add_cert(store, trusted_cert);

    X509_VERIFY_PARAM* param = X509_VERIFY_PARAM_new();
    n                        = X509_VERIFY_PARAM_set_flags(param, X509_V_FLAG_PARTIAL_CHAIN);
    if (n != 1) {
        SPDLOG_INFO("{}", "Failed to set X509_V_FLAG_PARTIAL_CHAIN");
        // goto exit_verification;
        if (store != nullptr) {
            X509_STORE_free(store);
        }
        if (param != nullptr) {
            X509_VERIFY_PARAM_free(param);
        }
        if (trusted_cert != nullptr) {
            X509_free(trusted_cert);
        }
        if (vrfy_cert != nullptr) {
            X509_free(vrfy_cert);
        }
        if (bio != nullptr) {
            BIO_free_all(bio);
        }
        return result;
    }
    else {
        SPDLOG_INFO("{}", "Succeed to set X509_V_FLAG_PARTIAL_CHAIN");
    }

    X509_STORE_set1_param(store, param);

    X509_STORE_CTX *store_ctx;
    store_ctx = X509_STORE_CTX_new();

    n = X509_STORE_CTX_init(store_ctx, store, vrfy_cert, NULL); //
    if (n != 1) {
        SPDLOG_ERROR("Failed to load trusted certificate!");
        // goto exit_verification;
        if (store != nullptr) {
            X509_STORE_free(store);
        }
        if (param != nullptr) {
            X509_VERIFY_PARAM_free(param);
        }
        if (trusted_cert != nullptr) {
            X509_free(trusted_cert);
        }
        if (vrfy_cert != nullptr) {
            X509_free(vrfy_cert);
        }
        if (bio != nullptr) {
            BIO_free_all(bio);
        }
        return result;
    }

    if (!X509_verify_cert(store_ctx)) {
        SPDLOG_INFO("{}", X509_verify_cert_error_string(X509_STORE_CTX_get_error(store_ctx)));
        SPDLOG_INFO("{}", X509_verify_cert_error_string(X509_STORE_CTX_get_error(store_ctx)));
        if (store != nullptr) {
            X509_STORE_free(store);
        }
        if (param != nullptr) {
            X509_VERIFY_PARAM_free(param);
        }
        if (trusted_cert != nullptr) {
            X509_free(trusted_cert);
        }
        if (vrfy_cert != nullptr) {
            X509_free(vrfy_cert);
        }
        if (bio != nullptr) {
            BIO_free_all(bio);
        }
        X509_STORE_CTX_cleanup(store_ctx);
        return result;
    }
    SPDLOG_INFO("{}", "Succeed to verify certificate");
    result = true;
    X509_STORE_CTX_cleanup(store_ctx);
    return result;
}

bool CsmIf::checkLocalAuthenList()
{
    char objectId[64]             = {0};
    std::string local_authen_list = {};
    bool ret                      = false;
    /* Read mp_authen_list from secure storage */
    {
        /* Get data size */
        strncpy(objectId, OBJECT_ID_MP_AUTHEN_LIST, strlen(OBJECT_ID_MP_AUTHEN_LIST));
        auto size = SSHelper_GetSize(objectId);
        if (size)
            SPDLOG_INFO("{}: Get data size {}\r", csm_if_tag, size);
        else {
            SPDLOG_INFO("{}: get data size error ", csm_if_tag);
            return ret;
        }
        // allocate memory for file content
        char* buffer = new char[size + 1];
        memset(buffer, 0, (size + 1));

        // read content of objectId
        if (SSHelper_Read(objectId, buffer, size)) {
            SPDLOG_INFO("{}: read data done", csm_if_tag);
        }
        else {
            SPDLOG_INFO("{}: read data error", csm_if_tag);
            return ret;
        }

        local_authen_list = std::string(buffer);
        SPDLOG_DEBUG("{}: Size of local_authen_list: {}", csm_if_tag, local_authen_list.size());
        delete[] buffer;
    }
    Json::CharReaderBuilder builder;
    Json::Value obj;
    JSONCPP_STRING errs;

    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());

    if (!reader->parse(local_authen_list.c_str(), local_authen_list.c_str() + local_authen_list.length(), &obj,
                       &errs)) {
        SPDLOG_ERROR("{}: Failed to parse list", csm_if_tag);
        return ret;
    }
    else {
        int sz = 0;
        sz     = obj["rfid_list"].size();
        for (int i = 0; i < sz; ++i) {
            SPDLOG_INFO("rfid {}: {}", (i + 1), obj["rfid_list"][i].asString());
        }
        sz = obj["mac_list"].size();
        for (int i = 0; i < sz; ++i) {
            SPDLOG_INFO("mac {}: {}", (i + 1), obj["mac_list"][i].asString());
        }
        ret = true;
    }
#if (0)
    std::string list_file = config_.mp_authen_list;
    SPDLOG_INFO("Parsing config file {}", list_file.c_str());

    Json::Value obj;
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;

    std::ifstream ifs(list_file.c_str());
    // std::ifstream ifs("/etc/remote-monitor/mp_authen_list_clone.json");
    if (ifs.good()) {
        SPDLOG_INFO("{}", "Config file found. Parsing now");
        if (!parseFromStream(builder, ifs, &obj, &errs)) {
            SPDLOG_INFO( errs << std::endl;
        }
        int sz = 0;
        sz     = obj["rfid_list"].size();
        for (int i = 0; i < sz; ++i) {
            SPDLOG_INFO( "rfid " << i + 1 << ": ";
            SPDLOG_INFO( obj["rfid_list"][i].asString() << std::endl;
        }
        sz = obj["mac_list"].size();
        for (int i = 0; i < sz; ++i) {
            SPDLOG_INFO( "mac " << i + 1 << ": ";
            SPDLOG_INFO( obj["mac_list"][i].asString() << std::endl;
        }
        ret = true;
    }
    else {
        SPDLOG_INFO("{}", "Config file not found. Applying default config");
    }
    ifs.close();
#endif
    return ret;
}

bool CsmIf::deleteLocalAuthenList()
{
    char objectId[64] = {0};
    bool ret          = false;
    /* Read mp_authen_list from secure storage */
    {
        /* Get data size */
        strncpy(objectId, OBJECT_ID_MP_AUTHEN_LIST, strlen(OBJECT_ID_MP_AUTHEN_LIST));
        auto result = SSHelper_Delete(objectId);
        if (true == result) {
            SPDLOG_INFO("{}: File deleted ", csm_if_tag);
            ret = true;
        }
        else {
            return ret;
        }
    }
    return ret;
}

} // namespace rb::csm