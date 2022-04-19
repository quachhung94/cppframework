//
// Created by hungnk8 on 23/11/2020.
//

#ifndef CONFIG_MANAGER_IF_HPP
#define CONFIG_MANAGER_IF_HPP

#include <cereal/no_pretty_json.hpp>
#include <protocol/clear_charging_profile_request.hpp>
#include <protocol/clear_charging_profile_response.hpp>
#include <protocol/clear_variable_monitoring_request.hpp>
#include <protocol/clear_variable_monitoring_response.hpp>
#include <protocol/get_charging_profiles_request.hpp>
#include <protocol/get_monitoring_report_request.hpp>
#include <protocol/get_variables_request.hpp>
#include <protocol/get_variables_response.hpp>
#include <protocol/notify_monitoring_report_request.hpp>
#include <protocol/notify_report_request.hpp>
#include <protocol/notify_report_response.hpp>
#include <protocol/report_charging_profiles_request.hpp>
#include <protocol/set_charging_profile_request.hpp>
#include <protocol/set_charging_profile_response.hpp>
#include <protocol/set_monitoring_base_request.hpp>
#include <protocol/set_monitoring_base_response.hpp>
#include <protocol/set_monitoring_level_request.hpp>
#include <protocol/set_monitoring_level_response.hpp>
#include <protocol/set_variable_monitoring_request.hpp>
#include <protocol/set_variable_monitoring_response.hpp>
#include <protocol/set_variables_request.hpp>
#include <protocol/set_variables_response.hpp>
using namespace lgpl3::ocpp201;

// #include "common.h"
#include <sys/epoll.h>

typedef struct {
    uint16_t sequence_number;
    std::string type;
    std::string payload;
} ResponseResult;

typedef struct MonitoringDataWrapper {
    bool is_enabled = false;
    MonitoringDataType monitoring_data_type;
} MonitoringDataWrapperType;

typedef struct ChargingProfileWrapper {
    ChargingProfileType charging_profile;
    int32_t evse_id = 0;
    ChargingLimitSourceEnumType charging_limit_source;
} ChargingProfileWrapperType;

class ConfigManager {
public:
    ConfigManager() = default;
    // API
    static int init() {}
    static int get_variable(const GetVariablesRequest &request, GetVariablesResponse &response) {}
    static int set_variable(const SetVariablesRequest &request, SetVariablesResponse &response) {}
    static int get_report(std::vector<ReportDataType> &result) {}

    static int get_monitoring_report(const GetMonitoringReportRequest &request, std::vector<MonitoringDataType> &response) {}
    static int get_monitoring_all_list(std::vector<MonitoringDataWrapperType> &result) {}
    static int set_monitoring_base(const SetMonitoringBaseRequest &request, SetMonitoringBaseResponse &response) {}
    static int set_variable_monitoring(const SetVariableMonitoringRequest &request, SetVariableMonitoringResponse &response) {}
    static int set_monitoring_level(const SetMonitoringLevelRequest &request, SetMonitoringLevelResponse &response) {}
    static int clear_variable_monitoring(const ClearVariableMonitoringRequest &request, ClearVariableMonitoringResponse &response) {}
    // Return a vector of all transaction id according to gun id 1 or 2.
    // If vector is empty, then no transaction id is recorded.
    static std::vector<std::string> get_all_transaction_id(uint8_t gun_id) {}
    // Return last transaction id according to gun id 1 or 2.
    // If string is empty, then error happened or no transaction id is recorded (brand-new database).
    static std::string get_last_transaction_id(uint8_t gun_id) {}
    // Return a vector of response message's payload according to gun id 1 or 2.
    // If vector is empty, then no response that matched transaction id is recorded.
    // If an element of vector is empty string, then that response message payload is empty.
    static std::vector<ResponseResult> get_all_message_response(uint8_t gun_id, const std::string &transaction_id) {}
    // Return a payload of request message that matched transaction id and sequence number (sequence number count from 1) according to gun id 1 or 2.
    // If string is empty, then request message that matched transaction id and sequence number is not available.
    static std::string get_request_message(uint8_t gun_id, const std::string &transaction_id, uint32_t sequence_number) {}
    // Append a new request message to database according to gun id 1 or 2.
    // Note that we only accept type with following values: start_req, update_req, end_req.
    // We also accept empty payload, but transaction id MUST not empty.
    // This API return -1 if error happened, else return sequence number of this request message.
    static int64_t append_request_message(uint8_t gun_id, const std::string &transaction_id, const std::string &type, const std::string &payload, bool is_fast_charge_enabled) {}
    // Update request message according to gun id 1 or 2, -1 if error happened, 0 is OK
    static int update_request_message(uint8_t gun_id, const std::string &transaction_id, uint32_t sequence_number, const std::string &payload) {}
    static int update_response_message(uint8_t gun_id, const std::string &transaction_id, uint32_t sequence_number, const std::string &payload) {}
    // Get fast charge status according to gun id 1 or 2.
    // This API return -1 if error happened, 0 is fast charge disable, 1 is fast charge enable.
    static int set_charging_profile(const SetChargingProfileRequest &request, SetChargingProfileResponse &response) {}
    static int get_charging_profiles(const GetChargingProfilesRequest &request, std::vector<ChargingProfileWrapperType> &response) {}
    static int get_fast_charge_status(uint8_t gun_id, const std::string &transaction_id, uint32_t sequence_number) {}
    static int clear_charging_profile(const ClearChargingProfileRequest &request, ClearChargingProfileResponse &response) {}
    static void release() {}
};

#endif//CONFIG_MANAGER_IF_HPP
