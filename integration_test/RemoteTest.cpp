/**
 * @file RemoteTest.cpp
 * @author Steven Le (sonlq@vingroup.net)
 * @brief
 * @version 0.1
 * @date 2021-11-15
 *
 * @copyright Copyright (c) 2021
 *
 */

// #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#include "spdlog/spdlog.h"

#include "RemoteTest.h"
#include "platform/core/SystemStatistics.h"
#include "platform/core/Task.h"
#include "platform/core/ipc/IEventListener.h"
#include "platform/core/ipc/Publisher.h"
#include "platform/core/ipc/SubscribingTaskEventQueue.h"
#include "platform/core/task_priorities.h"

#include <fstream>
#include <iostream>
#include <random>

#include <json/json.h>
#include <json/reader.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wterminate"
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough="
#include "config_manager_if.hpp"
#pragma GCC diagnostic pop

using namespace platform::core;

namespace rb {
using namespace platform::core::ipc;

static constexpr const char* remote_basic_tag = "RemoteTest";

RemoteTest::RemoteTest()
    : Application(platform::core::APPLICATION_BASE_PRIO, std::chrono::seconds(10)),
      m_csQueue(AppMessageQueue::create(100, *this, *this)),
      m_timerEventQueue(TimerQueue::create(30, *this, *this)),
      m_csmEventQueue(CsmEventQueue::create(20, *this, *this)),
      m_bootNotificationTimer(RM_FSM_BOOTUP_TIMER_ID, m_timerEventQueue, false,
                              std::chrono::seconds(DEFAULT_BOOTUP_TIMEOUT)),
      m_heartbeatTimer(RM_FSM_HEARTBEAT_TIMER_ID, m_timerEventQueue, true,
                       std::chrono::seconds(DEFAULT_HEARTBEAT_TIMEOUT)),
      m_notifyEventTimer(RM_FSM_NOTIFY_EVENT_TIMER_ID, m_timerEventQueue, false,
                         std::chrono::seconds(DEFAULT_HEARTBEAT_TIMEOUT)),
      m_notifyReportTimer(RM_FSM_NOTIFY_REPORT_TIMER_ID, m_timerEventQueue, false,
                          std::chrono::seconds(DEFAULT_HEARTBEAT_TIMEOUT)),
      m_bootNotificationInterval(DEFAULT_BOOTUP_TIMEOUT),
      m_heartbeatInterval(DEFAULT_HEARTBEAT_TIMEOUT),
      m_availability("Inoperative")
{
    // Initialize error code to 0
    m_monitorTick.fill(0);
    m_ocppTick.fill(0);
    m_canTick.fill(0);
    m_brokerTick.fill(0);
}

void RemoteTest::init()
{
    Application::init();

    csm_job = std::make_shared<rb::csm::CsmIf>("SignChargingStationCertificate", 8192, 10, csmQueue());
    m_csmJobQueue.push_back(csm_job);
    csm_job->start();

    SPDLOG_INFO("{}: Starting ...", remote_basic_tag);
    // std::lock_guard<std::mutex> lock(m_currentModeMtx);
    {
    // Start BootUp Timer if App bootup at the middle of INACTIVATE mode
        m_bootNotificationTimer->start();
    }
    {
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_int_distribution<int> distr(10, 15);
        auto set_time = distr(eng);
        m_heartbeatTimer->start(std::chrono::seconds(set_time));
    }
    {
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_int_distribution<int> distr(20, 30);
        auto set_time = distr(eng);
        m_notifyEventTimer->start(std::chrono::seconds(set_time));
    }
    {
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_int_distribution<int> distr(10, 15);
        auto set_time = distr(eng);
        m_notifyReportTimer->start(std::chrono::seconds(set_time));
    }
}

void RemoteTest::tick()
{
    std::cout << "Tick!" << std::endl;
}

void RemoteTest::event(const std::shared_ptr<rb::AppItemData>& event)
{
    SPDLOG_INFO("{}: {} dispatch: {}", remote_basic_tag, "AppMessageQueue", event->signal());
    switch (event->signal()) {
    case rb::AppItemData::kSysMsgOpModeChanged: {
        SPDLOG_INFO("kSysMsgOpModeChanged");
        break;
    }
    case rb::AppItemData::kSysMsgWokingModeSignal: {
        SPDLOG_INFO("{}: kSysMsgWokingModeSignal", remote_basic_tag);

        break;
    }
    default:
        break;
    }
}


void RemoteTest::event(const platform::core::timer::TimerExpiredEvent& event)
{
    if (event.getId() == RM_FSM_BOOTUP_TIMER_ID) {
        SPDLOG_INFO("onBootNotificationRequest");
        // onBootNotificationRequest();
    }
    else if (event.getId() == RM_FSM_HEARTBEAT_TIMER_ID) {
        SPDLOG_INFO("Heartbeat Out/In: [{}]/[{}]", m_heartBeatOutCount, m_heartBeatInCount);

        onHeartbeatRequest();
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_int_distribution<int> distr(10, 15);
        auto set_time = distr(eng);
        m_heartbeatTimer->start(std::chrono::seconds(set_time));
    }
    else if (event.getId() == RM_FSM_NOTIFY_EVENT_TIMER_ID) {
        SPDLOG_INFO("NotifyEvent Out/In: [{}]/[{}]", m_notifyEventOutCount, m_notifyEventInCount);

        // onNotifyEventRequest(event);
        auto request = std::make_shared<rb::csm::CsmEventData>(rb::csm::CsmEventData::kCsmJobGenerateCsr);
        csm_job->publish(request);
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_int_distribution<int> distr(10, 15);
        auto set_time = distr(eng);
        m_notifyEventTimer->start(std::chrono::seconds(set_time));
    }
    else if (event.getId() == RM_FSM_NOTIFY_REPORT_TIMER_ID) {
        SPDLOG_INFO("NotifyReport Out/In: [{}]/[{}]", m_notifyReportOutCount, m_notifyReportInCount);
        // onNotifyReportRequest(1);

        auto message  = std::make_shared<rb::AppItemData>(rb::AppItemData::kSysMsgOpModeChanged);
        m_csQueue->push(message);

        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_int_distribution<int> distr(10, 15);
        auto set_time = distr(eng);
        m_notifyReportTimer->start(std::chrono::seconds(set_time));
    }
}

void RemoteTest::event(const std::shared_ptr<rb::csm::CsmEventData>& event)
{
    SPDLOG_INFO("{}: {} dispatch: ", remote_basic_tag, "CsmEventData");
    switch (event->jobId()) {
    case rb::csm::CsmEventData::kCsmJobGenerateCsr: {
        for (auto it = m_csmJobQueue.begin(); it != m_csmJobQueue.end(); it++) {
            if ((*it)->jobId().compare("SignChargingStationCertificate") == 0) {
                SPDLOG_INFO("{}: Found {} element ", remote_basic_tag, "SignChargingStationCertificate");
                try {
                    m_csmJobQueue.erase(it--);
                }
                catch (...) {
                    SPDLOG_INFO("{}: m_csmJobQueue erase failed", remote_basic_tag);
                }
                break;
            }
        }
        SPDLOG_INFO("{}: m_csmJobQueue size: {}", remote_basic_tag, m_csmJobQueue.size());

        if (event->result() == rb::csm::CsmEventData::kCsmResultOk) {
            auto csr_payload = event->data();
            onSignCertificateRequest(csr_payload);
        }

        break;
    }
    case rb::csm::CsmEventData::kCsmJobUpdateCert: {
        for (auto it = m_csmJobQueue.begin(); it != m_csmJobQueue.end(); it++) {
            if ((*it)->jobId().compare("ChargingStationCertificate") == 0) {
                SPDLOG_INFO("{}: Found {} element ", remote_basic_tag, "ChargingStationCertificate");
                try {
                    m_csmJobQueue.erase(it--);
                }
                catch (...) {
                    SPDLOG_INFO("{}: m_csmJobQueue erase failed", remote_basic_tag);
                }
                break;
            }
        }
        SPDLOG_INFO("{}: m_csmJobQueue size: {}", remote_basic_tag, m_csmJobQueue.size());

        if (event->result() == rb::csm::CsmEventData::kCsmResultOk) {
        }
        break;
    }
    default:
        break;
    }
}


void RemoteTest::prepare(void)
{
    int rc = ConfigManager::init();
    if (rc != EXIT_SUCCESS) {
        SPDLOG_INFO("{}: Config Manager init failed", remote_basic_tag);
    }
}

// int RemoteTest::getCurrentMode(void)
// {
//     std::lock_guard<std::mutex> lock(m_currentModeMtx);
//     return 1;
// }

// int RemoteTest::getWorkingMode(void)
// {
//     std::lock_guard<std::mutex> lock(m_workingModeMtx);
//     return 1;
// }

// void RemoteTest::setWorkingMode(int mode)
// {
//     std::lock_guard<std::mutex> lock(m_workingModeMtx);
//     // m_workingMode = mode;
// }

// void RemoteTest::onModeChange(int mode, int prev)
// {
//     SPDLOG_INFO("{}: OpMode change from {} to {}", remote_basic_tag, prev, mode);
//     std::lock_guard<std::mutex> lock(m_currentModeMtx);
//     m_currentMode = mode;
//     m_prevMode    = prev;
//     auto message  = std::make_shared<rb::AppItemData>(rb::AppItemData::kSysMsgOpModeChanged);
//     m_csQueue->push(message);
// }

void RemoteTest::onActivateSource(bool is_online)
{
    SPDLOG_INFO("{}: Activate source is {}", remote_basic_tag, is_online);
    // std::lock_guard<std::mutex> lock(m_workingModeMtx);
    // m_workingMode = is_online;
    auto message  = std::make_shared<rb::AppItemData>(rb::AppItemData::kSysMsgWokingModeSignal);
    m_csQueue->push(message);
}


// void RemoteTest::onReloadMonitoring(void)
// {
//     m_monitorIf->onStopMonitoringTimer();
//     m_monitorIf->onStartMonitoringTimer(DEFAULT_MONITORING_PERIODIC_S);
// }

// bool RemoteTest::interfaceCheck() const
// {
//     return m_opmodeIf == nullptr || m_ocppIf == nullptr || m_canIf == nullptr || m_brokerIf == nullptr;
// }

/*===================================== Implementation Functions =============================================*/

bool RemoteTest::getEnvFwInfo(std::string list_file)
{
    bool ret = false;
    SPDLOG_INFO("Parsing fw_into file {}", list_file.c_str());

    std::ifstream ifs(list_file.c_str());
    if (ifs.good()) {
        SPDLOG_INFO("{}", "fw_into file found. Parsing now");
        std::string fw_info = {};
        if (std::getline(ifs, fw_info)) {
            if (fw_info.length() > FW_INFO_MAX_SIZE) {
                return ret;
            }
            m_config.fw_info = fw_info;
        }
        else {
            return ret;
        }
        ret = true;
    }
    else {
        SPDLOG_INFO("{}", "fw_into not found. Applying default fw_into");
        m_config.fw_info = std::string("x.x.x");
    }
    ifs.close();
    return ret;
}

bool RemoteTest::getEnvFileInfo(std::string list_file)
{
    bool ret = false;
    SPDLOG_INFO("Parsing env file {}", list_file.c_str());

    Json::Value obj;
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;

    std::ifstream ifs(list_file.c_str());
    // std::ifstream ifs("/etc/remote-basic/mp_authen_list_clone.json");
    if (ifs.good()) {
        SPDLOG_INFO("{}", "Env file found. Parsing now");
        if (!parseFromStream(builder, ifs, &obj, &errs)) {
            SPDLOG_INFO("{}", errs);
        }
        m_config.serial_number = obj["serialnumber"].asString();
        m_config.qr_code       = obj["qrCodeSn"].asString();
        m_config.eth_addr      = obj["ethaddr"].asString();
        m_config.station_id    = obj["stationId"].asString();
        ret                    = true;
    }
    else {
        SPDLOG_INFO("{}", "Env file not found. Applying default Env");
        m_config.serial_number = std::string("xxxxxx");
        m_config.qr_code       = std::string("xxxxxx");
        m_config.eth_addr      = std::string("xxxxxx");
        m_config.station_id    = std::string("xxxxxx");
    }
    ifs.close();
    return ret;
}

void RemoteTest::getConfig(const char* config_file)
{
    SPDLOG_INFO("Parsing config file {}", config_file);

    Json::Value obj;
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;

    std::ifstream ifs(config_file);
    if (ifs.good()) {
        SPDLOG_INFO("{}", "Config file found. Parsing now");
        if (!parseFromStream(builder, ifs, &obj, &errs)) {
            SPDLOG_INFO("{}", errs);
        }

        m_config.app_name         = obj["name"].asString();
        m_config.bypass_auth      = obj["bypass_auth"].asBool();
        m_config.bypass_rfid      = obj["bypass_rfid"].asBool();
        m_config.nbr_of_gun       = obj["nbr_of_gun"].asUInt();
        m_config.mp_authen_list   = obj["mp_authen_list_dir"].asString();
        std::string env_list_file = obj["env_file_dir"].asString();
        std::string fw_info_file  = obj["fw_info_dir"].asString();
        bool is_fw_info_ok        = getEnvFwInfo(fw_info_file);
        if (is_fw_info_ok) {
            SPDLOG_INFO("{}", "Get fw_info OK");
        }
        else {
            SPDLOG_INFO("{}", "Get fw_info fail");
        }

        bool is_env_list_ok = getEnvFileInfo(env_list_file);
        if (is_env_list_ok) {
            SPDLOG_INFO("{}", "Get env info OK");
        }
        else {
            SPDLOG_INFO("{}", "Get env info fail");
        }

        if (m_config.nbr_of_gun > MAX_NBR_OF_GUN) {
            SPDLOG_INFO("Number of gun config incorrectly: {}", m_config.nbr_of_gun);
            m_config.nbr_of_gun = MAX_NBR_OF_GUN;
        }
    }
    else {
        SPDLOG_INFO("{}", "Config file not found. Applying default config");
        m_config.app_name    = std::string(remote_basic_tag);
        m_config.bypass_auth = false;
        m_config.bypass_rfid = false;
        m_config.nbr_of_gun  = DEFAULT_NBR_OF_GUN;
    }
    if (m_config.nbr_of_gun == 1) {
        m_config.model = std::string("AutoCS-DC-30KW");
    }
    else {
        m_config.model = std::string("AutoCS-DC-60KW");
    }

    if (m_config.bypass_rfid && m_config.bypass_auth) {
        SPDLOG_INFO("{}", "Bypass authen disabled");
        m_config.bypass_auth = false;
    }
    ifs.close();

    SPDLOG_INFO("{}", "Parsing config done");
    SPDLOG_INFO(" - App name: {}", m_config.app_name.c_str());
    SPDLOG_INFO(" - Bypass auth: {}", m_config.bypass_auth);
    SPDLOG_INFO(" - Bypass RFID: {}", m_config.bypass_rfid);
    SPDLOG_INFO(" - Nbr of gun: {}", m_config.nbr_of_gun);
    SPDLOG_INFO(" - Serial Number: {}", m_config.serial_number.c_str());
    SPDLOG_INFO(" - Station Id: {}", m_config.station_id.c_str());
    SPDLOG_INFO(" - Model: {}", m_config.model.c_str());
    SPDLOG_INFO(" - FW Version: {}", m_config.fw_info.c_str());
}

void RemoteTest::onSignCertificateRequest(const std::string& csr)
{
    SignCertificateRequest request{};
    request.certificateType = CertificateSigningUseEnumType::from_string("ChargingStationCertificate");
    request.csr             = csr;
    try {
        std::stringstream ss;
        {
            cereal::JSONOutputArchive archive(ss);
            request.serialize(archive);
        }
        SPDLOG_INFO("onSignCertificateRequest {}", ss.str());
        // auto message = std::make_shared<rb::ocpp::OcppItemData>(rb::ocpp::message::OcppMessage::kOcppMsgSignCertificate,
        //                                                         rb::ocpp::OcppItemData::kOcppEventToServer, ss.str());
        // if (true == m_serverConnection) {
        //     m_ocppIf->publish(message);
        // }
    }
    catch (...) {
        SPDLOG_INFO("{}", "Parse message failed!");
    }
}
// void RemoteTest::onBootNotificationRequest()
// {
//     BootNotificationRequest request{};
//     ChargingStationType csType = {};
//     csType.vendorName          = "Vinfast";
//     if (m_config.model.empty() != true) {
//         csType.model = m_config.model;
//     }
//     else {
//         csType.model = std::string("xxxxxx");
//     }
//     if (m_config.serial_number.empty() != true) {
//         csType.serialNumber = m_config.serial_number;
//     }
//     else {
//         csType.serialNumber = std::string("xxxxxx");
//     }
//     if (m_config.fw_info.empty() != true) {
//         csType.firmwareVersion = m_config.fw_info;
//     }
//     else {
//         csType.firmwareVersion = std::string("x.x.x");
//     }
//     request.chargingStation = csType;
//     request.reason          = "PowerUp";

//     try {
//         std::stringstream ss;
//         {
//             cereal::JSONOutputArchive archive(ss);
//             request.serialize(archive);
//         }
//         SPDLOG_INFO("onBootNotificationRequest {}",  ss.str());
//     }
//     catch (...) {
//         SPDLOG_INFO("{}", "Parse message failed!");
//     }
// }

void RemoteTest::onHeartbeatRequest()
{
    HeartbeatRequest request{};
    try {
        std::stringstream ss;
        {
            cereal::JSONOutputArchive archive(ss);
            request.serialize(archive);
        }
        SPDLOG_INFO("Heart beat {}", ss.str());

        m_heartBeatOutCount++;
    }
    catch (...) {
        SPDLOG_INFO("{}", "Parse message failed!");
    }
}

// void RemoteTest::onNotifyReportRequest(int request_id)
// {
//     std::stringstream ss;
//     {
//         cereal::JSONOutputArchive archive(ss);
//         request.serialize(archive);
//     }
//     SPDLOG_INFO("request Size: {}", ss.str().size());
//     SPDLOG_DEBUG("[request]: {}", ss.str());

//     m_notifyReportOutCount++;
// }

// void RemoteTest::onStatusNotificationRequest(int evseId, std::string status)
// {
//     // Update StatusNotification
//     StatusNotificationRequest request{};

//     request.evseId          = evseId + 1;
//     request.connectorId     = EVSE_CONNECTOR_ID;
//     request.connectorStatus = status;
//     try {
//         std::stringstream ss;
//         {
//             cereal::JSONOutputArchive archive(ss);
//             request.serialize(archive);
//         }
//         SPDLOG_INFO("onStatusNotificationRequest {}", ss.str());
//     }
//     catch (...) {
//         SPDLOG_INFO("{}", "Parse message failed!");
//     }
// }

} // namespace rb