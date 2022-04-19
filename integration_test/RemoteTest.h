/**
 * @file RemoteTest.h
 * @author Steven Le (sonlq@vingroup.net)
 * @brief
 * @version 0.1
 * @date 2021-11-15
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include "AppItemData.h"
#include "NvmIf.h"
#include "CsmIf.h"

#include "platform/core/Application.h"
#include "platform/core/timer/Timer.h"
#include <vector>

#include <protocol/sign_certificate_request.hpp>
#include <protocol/heartbeat_request.hpp>

const int RM_FSM_BOOTUP_TIMER_ID    = 1;
const int RM_FSM_HEARTBEAT_TIMER_ID = 2;
const int RM_FSM_NOTIFY_EVENT_TIMER_ID = 3;
const int RM_FSM_NOTIFY_REPORT_TIMER_ID = 4;

#define DEFAULT_BOOTUP_TIMEOUT            30
#define DEFAULT_HEARTBEAT_TIMEOUT         60
#define DEFAULT_NBR_OF_GUN                1
#define MAX_NBR_OF_GUN                    2
#define FW_INFO_MAX_SIZE                  25
#define EVSE_CONNECTOR_ID                 1
#define CS_DEFAULT_COMPONENT_INSTANCE     "1"
#define CS_DEFAULT_VARIABLE_INSTANCE      "1"
#define CS_COMPONENT_NAME                 "ChargingStation"
#define CS_COMPONENT_INSTANCE             CS_DEFAULT_COMPONENT_INSTANCE
#define CS_AVAILABILITY_VARIABLE_NAME     "StationAvailability"
#define CS_AVAILABILITY_VARIABLE_INSTANCE CS_DEFAULT_COMPONENT_INSTANCE
#define DEFAULT_MONITORING_PERIODIC_S     1
#define ENUM_TO_STRING(x)                 #x
#define HISTORY_PAIR                      2
#define HISTORY_PAIR_OLD_IDX              0
#define HISTORY_PAIR_NEW_IDX              1

namespace rb {
class RemoteTest : public platform::core::Application,
                      private platform::core::ipc::IEventListener<std::shared_ptr<rb::AppItemData>>,
                      private platform::core::ipc::IEventListener<std::shared_ptr<rb::csm::CsmEventData>>,
                      private platform::core::ipc::IEventListener<platform::core::timer::TimerExpiredEvent> {
public:
    using AppMessageQueue   = platform::core::ipc::TaskEventQueue<std::shared_ptr<rb::AppItemData>>;
    using TimerQueue        = platform::core::ipc::TaskEventQueue<platform::core::timer::TimerExpiredEvent>;
    using CsmEventQueue     = platform::core::ipc::TaskEventQueue<std::shared_ptr<rb::csm::CsmEventData>>;

    struct Config {
        std::string app_name;
        bool bypass_auth;
        bool bypass_rfid;

        uint8_t nbr_of_gun;
        std::string mp_authen_list;
        std::string serial_number;
        std::string station_id;
        std::string qr_code;
        std::string eth_addr;
        std::string model;
        std::string fw_info;
    };
    RemoteTest();

    void init() override;

    void tick() override;

    void event(const std::shared_ptr<rb::AppItemData>&) override;

    void event(const platform::core::timer::TimerExpiredEvent&) override;

    void event(const std::shared_ptr<rb::csm::CsmEventData>&) override;

    const std::shared_ptr<CsmEventQueue> csmQueue(void) const { return m_csmEventQueue; }

    void prepare(void);

    int getCurrentMode(void);

    int getWorkingMode(void);

    void setWorkingMode(int);

    void onModeChange(int mode, int prev);

    void onActivateSource(bool is_online);

    std::string updateAvailability();

    void onReloadMonitoring(void);

    bool changeAvailability(std::string availability);

    void onTriggerEvent(int id, std::string& actual_value);

    bool interfaceCheck() const;
    /*========================== Declaration of implementation Function ====================================*/
    bool getEnvFwInfo(std::string list_file);
    bool getEnvFileInfo(std::string list_file);
    void getConfig(const char* config_file);

    // void onBootNotificationRequest();
    void onHeartbeatRequest();
    // void onNotifyReportRequest(int);
    // void onStatusNotificationRequest(int evseId, std::string status);
    void onSignCertificateRequest(const std::string& csr);

private:
    // std::mutex m_currentModeMtx;
    // std::mutex m_workingModeMtx;
    std::shared_ptr<rb::csm::CsmIf> csm_job;
    bool m_serverConnection = false;
    Config m_config{};

    std::shared_ptr<AppMessageQueue> m_csQueue;
    std::vector<std::shared_ptr<rb::csm::CsmIf>> m_csmJobQueue;
    std::shared_ptr<TimerQueue> m_timerEventQueue;
    std::shared_ptr<CsmEventQueue> m_csmEventQueue;
    platform::core::timer::TimerOwner m_bootNotificationTimer;
    platform::core::timer::TimerOwner m_heartbeatTimer;
    platform::core::timer::TimerOwner m_notifyEventTimer;
    platform::core::timer::TimerOwner m_notifyReportTimer;
    int m_bootNotificationInterval;
    int m_heartbeatInterval;
    std::string m_availability;
    std::array<uint32_t, HISTORY_PAIR> m_monitorTick;
    std::array<uint32_t, HISTORY_PAIR> m_ocppTick;
    std::array<uint32_t, HISTORY_PAIR> m_brokerTick;
    std::array<uint32_t, HISTORY_PAIR> m_canTick;
    std::array<uint32_t, HISTORY_PAIR> m_csmTick;
    size_t m_heartBeatOutCount = 0;
    size_t m_heartBeatInCount = 0;
    size_t m_notifyEventOutCount = 0;
    size_t m_notifyEventInCount = 0;
    size_t m_notifyReportOutCount = 0;
    size_t m_notifyReportInCount = 0;
};
} // namespace rb