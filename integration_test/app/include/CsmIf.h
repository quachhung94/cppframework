/**
 * @file CsmIf.h
 * @author Steven Le (sonlq@vingroup.net)
 * @brief
 * @version 0.1
 * @date 2021-12-09
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include "platform/core/Task.h"
#include "platform/core/ipc/SubscribingTaskEventQueue.h"
#include "platform/core/ipc/TaskEventQueue.h"
#include "platform/core/timer/Timer.h"
#include <chrono>
#include <deque>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <regex>
#include <string>
#include <unordered_map>

#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/x509_vfy.h>
#include <openssl/x509v3.h>

#define RSA_KEY_BITS (2048)
#define REQ_DN_C     "VN"
#define REQ_DN_ST    "HN"
#define REQ_DN_L     ""
#define REQ_DN_O     "Vingroup"
#define REQ_DN_OU    ""
#define REQ_DN_CN    "scooter.ca-vinfast.vingroup.net"

namespace rb::csm {
class CsmEventData {
public:
    enum csmJobId { kCsmJobGenerateCsr = 0, kCsmJobUpdateCert };
    enum csmResultType { kCsmResultFailure = 0, kCsmResultOk = 1, kCsmResultIgnore };
    CsmEventData(int jobId) : m_jobId(jobId), m_result(0), m_data() {}
    CsmEventData(int jobId, int result) : m_jobId(jobId), m_result(result), m_data() {}
    CsmEventData(int jobId, int result, std::string data) : m_jobId(jobId), m_result(result), m_data(data) {}
    int jobId() { return m_jobId; }
    int result() { return m_result; }
    std::string data() { return m_data; }

private:
    int m_jobId;
    int m_result;
    std::string m_data;
};
/**
 * @brief Can Interface
 *
 */
class CsmIf : public platform::core::Task,
              public std::enable_shared_from_this<CsmIf>,
              public platform::core::ipc::IEventListener<std::shared_ptr<rb::csm::CsmEventData>>,
              private platform::core::ipc::IEventListener<platform::core::timer::TimerExpiredEvent> {
    using CsmJobQueue = platform::core::ipc::TaskEventQueue<std::shared_ptr<rb::csm::CsmEventData>>;

public:
    /**
     * @brief Construct a new Can If object
     *
     * @param interface_id
     * @param stack_size
     * @param priority
     */
    CsmIf(const std::string& interface_id, uint32_t stack_size, uint32_t priority,
          std::weak_ptr<platform::core::ipc::TaskEventQueue<std::shared_ptr<rb::csm::CsmEventData>>> app_event_queue);
    ~CsmIf();
    void publish(const std::shared_ptr<rb::csm::CsmEventData>&);

    const std::string jobId() const { return m_interfaceId; }
    bool checkLocalAuthenList();
    bool deleteLocalAuthenList();

private:
    int generateCSR(EVP_PKEY** privkey, X509_REQ** req);
    void csrToPem(X509_REQ* crt, uint8_t** crt_bytes, size_t* crt_size);
    void crtToPem(X509* crt, uint8_t** crt_bytes, size_t* crt_size);
    void keyToPem(EVP_PKEY* key, uint8_t** key_bytes, size_t* key_size);
    void printBytes(uint8_t* data, size_t size);
    void onPrepareCSR(void);
    void onUpdateCert(const std::string& cert);
    int verifyCert(const std::string& cert);

    void event(const std::shared_ptr<rb::csm::CsmEventData>&) override;

    void event(const platform::core::timer::TimerExpiredEvent&) override;

    void init() override;

    void tick() override;

    using TimerQueue = platform::core::ipc::TaskEventQueue<platform::core::timer::TimerExpiredEvent>;

    std::weak_ptr<platform::core::ipc::TaskEventQueue<std::shared_ptr<rb::csm::CsmEventData>>> m_csmEventQueue;
    std::shared_ptr<CsmJobQueue> m_JobQueue;
    std::shared_ptr<TimerQueue> m_timerEvents;
    std::mutex m_guard;
    std::string m_interfaceId;
    platform::core::timer::TimerOwner m_keepAliveTimer;
    std::mutex m_mutex;
    std::condition_variable m_cv;
};
} // namespace rb::csm
