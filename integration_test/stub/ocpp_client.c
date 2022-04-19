/**
 * @file ocpp_client.c
 * @author Steven Le (sonlq@vingroup.net)
 * @brief
 * @version 0.1
 * @date 2021-11-15
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <stdio.h>
#include <string.h>
#include "ocpp_if.h"
#include "ocpp_types.h"
#include "ocpp_types_internal.h"

typedef struct _message_info_type_ {
    ocpp_event_t event;
    ocpp_func_ptr_t func;
    event_status status;
    void* ctx;
} event_callback_info_t;

typedef struct _message_mapping_info_t_ {
    const char* name;
    ocpp_message_dir_t dir;
    ocpp_event_t event;
    message_type_id pairType;
} message_mapping_info_t;

typedef struct _registered_server_event_t_ {
    bool isRegistered;
    int eventNo;
    int eventList[OCPP_EVENT_ALL];
} registered_server_event_t;

static volatile bool is_connected   = false;
static volatile bool is_wbuff_empty = true;
static bool wait_resp               = false;
// static pthread_mutex_t wbuff_lock;
static ocpp_connect_cb_t connect_callback = NULL;
static void* connect_context              = NULL;
static bool is_initialized                = false;
static event_callback_info_t callbacks[OCPP_EVENT_NUM];
static registered_server_event_t registeredEvt;

/** @brief OCPP Message info  */
const message_mapping_info_t event_mapping_table[MESSAGE_TYPE_MAX] = {
    /*   messageName,  Direction,  Ocpp Event,  Coresponding Mesg*/
    {"Authorize", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, AUTHORIZE_RESPONSE},
    {"Authorize", RES_FROM_SERVER_TO_CS, OCPP_EVENT_AUTHORIZE_RESPONSE, AUTHORIZE_REQUEST},
    {"BootNotification", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, BOOT_NOTIFICATION_RESPONSE},
    {"BootNotification", RES_FROM_SERVER_TO_CS, OCPP_EVENT_BOOT_NOTIFICATION_RESPONSE, BOOT_NOTIFICATION_REQUEST},
    {"CancelReservation", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_CANCEL_RESERVATION_REQUEST, CANCEL_RESERVATION_RESPONSE},
    {"CancelReservation", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, CANCEL_RESERVATION_REQUEST},
    {"CertificateSigned", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_CERTIFICATE_SIGNED_REQUEST, CERTIFICATE_SIGNED_RESPONSE},
    {"CertificateSigned", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, CERTIFICATE_SIGNED_REQUEST},
    {"ChangeAvailability", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_CHANGE_AVAILABILITY_REQUEST, CHANGE_AVAILABILITY_RESPONSE},
    {"ChangeAvailability", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, CHANGE_AVAILABILITY_REQUEST},
    {"ClearCache", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_CLEAR_CACHE_REQUEST, CLEAR_CACHE_RESPONSE},
    {"ClearCache", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, CLEAR_CACHE_REQUEST},
    {"ClearChargingProfile", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_CLEAR_CHARGING_PROFILE_REQUEST,
     CLEAR_CHARGING_PROFILE_RESPONSE},
    {"ClearChargingProfile", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, CLEAR_CHARGING_PROFILE_REQUEST},
    {"ClearDisplayMessage", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_CLEAR_DISPLAY_MESSAGE_REQUEST,
     CLEAR_DISPLAY_MESSAGE_RESPONSE},
    {"ClearDisplayMessage", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, CLEAR_DISPLAY_MESSAGE_REQUEST},
    {"ClearVariableMonitoring", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_CLEAR_VARIABLE_MONITORING_REQUEST,
     CLEAR_VARIABLE_MONITORING_RESPONSE},
    {"ClearVariableMonitoring", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, CLEAR_VARIABLE_MONITORING_REQUEST},
    {"ClearedChargingLimit", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, CLEARED_CHARGING_LIMIT_RESPONSE},
    {"ClearedChargingLimit", RES_FROM_SERVER_TO_CS, OCPP_EVENT_CLEARED_CHARGING_LIMIT_RESPONSE,
     CLEARED_CHARGING_LIMIT_REQUEST},
    {"CostUpdated", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_COST_UPDATED_REQUEST, COST_UPDATED_RESPONSE},
    {"CostUpdated", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, COST_UPDATED_REQUEST},
    {"CustomerInformation", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_CUSTOMER_INFORMATION_REQUEST,
     CUSTOMER_INFORMATION_RESPONSE},
    {"CustomerInformation", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, CUSTOMER_INFORMATION_REQUEST},
    {"DataTransfer", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, DATA_TRANSFER_RESPONSE},
    {"DataTransfer", RES_FROM_SERVER_TO_CS, OCPP_EVENT_DATA_TRANSFER_RESPONSE, DATA_TRANSFER_REQUEST},
    {"DeleteCertificate", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_DELETE_CERTIFICATE_REQUEST, DELETE_CERTIFICATE_RESPONSE},
    {"DeleteCertificate", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, DELETE_CERTIFICATE_REQUEST},
    {"FirmwareStatusNotification", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, FIRMWARE_STATUS_NOTIFICATION_RESPONSE},
    {"FirmwareStatusNotification", RES_FROM_SERVER_TO_CS, OCPP_EVENT_FIRMWARE_STATUS_NOTIFICATION_RESPONSE,
     FIRMWARE_STATUS_NOTIFICATION_REQUEST},
    {"Get15118EVCertificate", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, GET15118_EV_CERTIFICATE_RESPONSE},
    {"Get15118EVCertificate", RES_FROM_SERVER_TO_CS, OCPP_EVENT_GET15118_EV_CERTIFICATE_RESPONSE,
     GET15118_EV_CERTIFICATE_REQUEST},
    {"GetBaseReport", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_GET_BASE_REPORT_REQUEST, GET_BASE_REPORT_RESPONSE},
    {"GetBaseReport", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, GET_BASE_REPORT_REQUEST},
    {"GetCertificateStatus", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, GET_CERTIFICATE_STATUS_RESPONSE},
    {"GetCertificateStatus", RES_FROM_SERVER_TO_CS, OCPP_EVENT_GET_CERTIFICATE_STATUS_RESPONSE,
     GET_CERTIFICATE_STATUS_REQUEST},
    {"GetChargingProfiles", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_GET_CHARGING_PROFILES_REQUEST,
     GET_CHARGING_PROFILES_RESPONSE},
    {"GetChargingProfiles", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, GET_CHARGING_PROFILES_REQUEST},
    {"GetCompositeSchedule", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_GET_COMPOSITE_SCHEDULE_REQUEST,
     GET_COMPOSITE_SCHEDULE_RESPONSE},
    {"GetCompositeSchedule", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, GET_COMPOSITE_SCHEDULE_REQUEST},
    {"GetDisplayMessages", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_GET_DISPLAY_MESSAGES_REQUEST,
     GET_DISPLAY_MESSAGES_RESPONSE},
    {"GetDisplayMessages", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, GET_DISPLAY_MESSAGES_REQUEST},
    {"GetInstalledCertificateIds", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_GET_INSTALLED_CERTIFICATE_IDS_REQUEST,
     GET_INSTALLED_CERTIFICATE_IDS_RESPONSE},
    {"GetInstalledCertificateIds", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, GET_INSTALLED_CERTIFICATE_IDS_REQUEST},
    {"GetLocalListVersion", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_GET_LOCAL_LIST_VERSION_REQUEST,
     GET_LOCAL_LIST_VERSION_RESPONSE},
    {"GetLocalListVersion", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, GET_LOCAL_LIST_VERSION_REQUEST},
    {"GetLog", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_GET_LOG_REQUEST, GET_LOG_RESPONSE},
    {"GetLog", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, GET_LOG_REQUEST},
    {"GetMonitoringReport", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_GET_MONITORING_REPORT_REQUEST,
     GET_MONITORING_REPORT_RESPONSE},
    {"GetMonitoringReport", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, GET_MONITORING_REPORT_REQUEST},
    {"GetReport", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_GET_REPORT_REQUEST, GET_REPORT_RESPONSE},
    {"GetReport", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, GET_REPORT_REQUEST},
    {"GetTransactionStatus", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_GET_TRANSACTION_STATUS_REQUEST,
     GET_TRANSACTION_STATUS_RESPONSE},
    {"GetTransactionStatus", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, GET_TRANSACTION_STATUS_REQUEST},
    {"GetVariables", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_GET_VARIABLES_REQUEST, GET_VARIABLES_RESPONSE},
    {"GetVariables", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, GET_VARIABLES_REQUEST},
    {"Heartbeat", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, HEARTBEAT_RESPONSE},
    {"Heartbeat", RES_FROM_SERVER_TO_CS, OCPP_EVENT_HEARTBEAT_RESPONSE, HEARTBEAT_REQUEST},
    {"InstallCertificate", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_INSTALL_CERTIFICATE_REQUEST, INSTALL_CERTIFICATE_RESPONSE},
    {"InstallCertificate", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, INSTALL_CERTIFICATE_REQUEST},
    {"LogStatusNotification", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, LOG_STATUS_NOTIFICATION_RESPONSE},
    {"LogStatusNotification", RES_FROM_SERVER_TO_CS, OCPP_EVENT_LOG_STATUS_NOTIFICATION_RESPONSE,
     LOG_STATUS_NOTIFICATION_REQUEST},
    {"MeterValues", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, METER_VALUES_RESPONSE},
    {"MeterValues", RES_FROM_SERVER_TO_CS, OCPP_EVENT_METER_VALUES_RESPONSE, METER_VALUES_REQUEST},
    {"NotifyChargingLimit", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, NOTIFY_CHARGING_LIMIT_RESPONSE},
    {"NotifyChargingLimit", RES_FROM_SERVER_TO_CS, OCPP_EVENT_NOTIFY_CHARGING_LIMIT_RESPONSE,
     NOTIFY_CHARGING_LIMIT_REQUEST},
    {"NotifyCustomerInformation", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, NOTIFY_CUSTOMER_INFORMATION_RESPONSE},
    {"NotifyCustomerInformation", RES_FROM_SERVER_TO_CS, OCPP_EVENT_NOTIFY_CUSTOMER_INFORMATION_RESPONSE,
     NOTIFY_CUSTOMER_INFORMATION_REQUEST},
    {"NotifyDisplayMessages", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, NOTIFY_DISPLAY_MESSAGES_RESPONSE},
    {"NotifyDisplayMessages", RES_FROM_SERVER_TO_CS, OCPP_EVENT_NOTIFY_DISPLAY_MESSAGES_RESPONSE,
     NOTIFY_DISPLAY_MESSAGES_REQUEST},
    {"NotifyEVChargingNeeds", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, NOTIFY_EV_CHARGING_NEEDS_RESPONSE},
    {"NotifyEVChargingNeeds", RES_FROM_SERVER_TO_CS, OCPP_EVENT_NOTIFY_EV_CHARGING_NEEDS_RESPONSE,
     NOTIFY_EV_CHARGING_NEEDS_REQUEST},
    {"NotifyEVChargingSchedule", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, NOTIFY_EV_CHARGING_SCHEDULE_RESPONSE},
    {"NotifyEVChargingSchedule", RES_FROM_SERVER_TO_CS, OCPP_EVENT_NOTIFY_EV_CHARGING_SCHEDULE_RESPONSE,
     NOTIFY_EV_CHARGING_SCHEDULE_REQUEST},
    {"NotifyEvent", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, NOTIFY_EVENT_RESPONSE},
    {"NotifyEvent", RES_FROM_SERVER_TO_CS, OCPP_EVENT_NOTIFY_EVENT_RESPONSE, NOTIFY_EVENT_REQUEST},
    {"NotifyMonitoringReport", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, NOTIFY_MONITORING_REPORT_RESPONSE},
    {"NotifyMonitoringReport", RES_FROM_SERVER_TO_CS, OCPP_EVENT_NOTIFY_MONITORING_REPORT_RESPONSE,
     NOTIFY_MONITORING_REPORT_REQUEST},
    {"NotifyReport", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, NOTIFY_REPORT_RESPONSE},
    {"NotifyReport", RES_FROM_SERVER_TO_CS, OCPP_EVENT_NOTIFY_REPORT_RESPONSE, NOTIFY_REPORT_REQUEST},
    {"PublishFirmware", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_PUBLISH_FIRMWARE_REQUEST, PUBLISH_FIRMWARE_RESPONSE},
    {"PublishFirmware", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, PUBLISH_FIRMWARE_REQUEST},
    {"PublishFirmwareStatusNotification", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM,
     PUBLISH_FIRMWARE_STATUS_NOTIFICATION_RESPONSE},
    {"PublishFirmwareStatusNotification", RES_FROM_SERVER_TO_CS,
     OCPP_EVENT_PUBLISH_FIRMWARE_STATUS_NOTIFICATION_RESPONSE, PUBLISH_FIRMWARE_STATUS_NOTIFICATION_REQUEST},
    {"ReportChargingProfiles", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, REPORT_CHARGING_PROFILES_RESPONSE},
    {"ReportChargingProfiles", RES_FROM_SERVER_TO_CS, OCPP_EVENT_REPORT_CHARGING_PROFILES_RESPONSE,
     REPORT_CHARGING_PROFILES_REQUEST},
    {"RequestStartTransaction", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_REQUEST_START_TRANSACTION_REQUEST,
     REQUEST_START_TRANSACTION_RESPONSE},
    {"RequestStartTransaction", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, REQUEST_START_TRANSACTION_REQUEST},
    {"RequestStopTransaction", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_REQUEST_STOP_TRANSACTION_REQUEST,
     REQUEST_STOP_TRANSACTION_RESPONSE},
    {"RequestStopTransaction", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, REQUEST_STOP_TRANSACTION_REQUEST},
    {"ReservationStatusUpdate", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, RESERVATION_STATUS_UPDATE_RESPONSE},
    {"ReservationStatusUpdate", RES_FROM_SERVER_TO_CS, OCPP_EVENT_RESERVATION_STATUS_UPDATE_RESPONSE,
     RESERVATION_STATUS_UPDATE_REQUEST},
    {"ReserveNow", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_RESERVE_NOW_REQUEST, RESERVE_NOW_RESPONSE},
    {"ReserveNow", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, RESERVE_NOW_REQUEST},
    {"Reset", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_RESET_REQUEST, RESET_RESPONSE},
    {"Reset", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, RESET_REQUEST},
    {"SecurityEventNotification", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, SECURITY_EVENT_NOTIFICATION_RESPONSE},
    {"SecurityEventNotification", RES_FROM_SERVER_TO_CS, OCPP_EVENT_SECURITY_EVENT_NOTIFICATION_RESPONSE,
     SECURITY_EVENT_NOTIFICATION_REQUEST},
    {"SendLocalList", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_SEND_LOCAL_LIST_REQUEST, SEND_LOCAL_LIST_RESPONSE},
    {"SendLocalList", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, SEND_LOCAL_LIST_REQUEST},
    {"SetChargingProfile", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_SET_CHARGING_PROFILE_REQUEST,
     SET_CHARGING_PROFILE_RESPONSE},
    {"SetChargingProfile", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, SET_CHARGING_PROFILE_REQUEST},
    {"SetDisplayMessage", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_SET_DISPLAY_MESSAGE_REQUEST, SET_DISPLAY_MESSAGE_RESPONSE},
    {"SetDisplayMessage", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, SET_DISPLAY_MESSAGE_REQUEST},
    {"SetMonitoringBase", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_SET_MONITORING_BASE_REQUEST, SET_MONITORING_BASE_RESPONSE},
    {"SetMonitoringBase", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, SET_MONITORING_BASE_REQUEST},
    {"SetMonitoringLevel", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_SET_MONITORING_LEVEL_REQUEST,
     SET_MONITORING_LEVEL_RESPONSE},
    {"SetMonitoringLevel", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, SET_MONITORING_LEVEL_REQUEST},
    {"SetNetworkProfile", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_SET_NETWORK_PROFILE_REQUEST, SET_NETWORK_PROFILE_RESPONSE},
    {"SetNetworkProfile", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, SET_NETWORK_PROFILE_REQUEST},
    {"SetVariableMonitoring", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_SET_VARIABLE_MONITORING_REQUEST,
     SET_VARIABLE_MONITORING_RESPONSE},
    {"SetVariableMonitoring", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, SET_VARIABLE_MONITORING_REQUEST},
    {"SetVariables", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_SET_VARIABLES_REQUEST, SET_VARIABLES_RESPONSE},
    {"SetVariables", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, SET_VARIABLES_REQUEST},
    {"SignCertificate", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, SIGN_CERTIFICATE_RESPONSE},
    {"SignCertificate", RES_FROM_SERVER_TO_CS, OCPP_EVENT_SIGN_CERTIFICATE_RESPONSE, SIGN_CERTIFICATE_REQUEST},
    {"StatusNotification", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, STATUS_NOTIFICATION_RESPONSE},
    {"StatusNotification", RES_FROM_SERVER_TO_CS, OCPP_EVENT_STATUS_NOTIFICATION_RESPONSE, STATUS_NOTIFICATION_REQUEST},
    {"TransactionEvent", REQ_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, TRANSACTION_EVENT_RESPONSE},
    {"TransactionEvent", RES_FROM_SERVER_TO_CS, OCPP_EVENT_TRANSACTION_EVENT_RESPONSE, TRANSACTION_EVENT_REQUEST},
    {"TriggerMessage", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_TRIGGER_MESSAGE_REQUEST, TRIGGER_MESSAGE_RESPONSE},
    {"TriggerMessage", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, TRIGGER_MESSAGE_REQUEST},
    {"UnlockConnector", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_UNLOCK_CONNECTOR_REQUEST, UNLOCK_CONNECTOR_RESPONSE},
    {"UnlockConnector", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, UNLOCK_CONNECTOR_REQUEST},
    {"UnpublishFirmware", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_UNPUBLISH_FIRMWARE_REQUEST, UNPUBLISH_FIRMWARE_RESPONSE},
    {"UnpublishFirmware", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, UNPUBLISH_FIRMWARE_REQUEST},
    {"UpdateFirmware", REQ_FROM_SERVER_TO_CS, OCPP_EVENT_UPDATE_FIRMWARE_REQUEST, UPDATE_FIRMWARE_RESPONSE},
    {"UpdateFirmware", RES_FROM_CS_TO_SERVER, OCPP_EVENT_NUM, UPDATE_FIRMWARE_REQUEST}};

static void onEventBootNotificationResponse();
static void onEventGetBaseReportRequest();

ocpp_status_t ocpp_init(ocpp_connect_cb_t connect_cb, void* connect_ctx)
{
    int error = E_NG_OCPP;
    if (!is_initialized) {
        printf("%s\n", "Not initialize yet");
        connect_callback = connect_cb;
        connect_context  = connect_ctx;
        memset(callbacks, 0, sizeof(callbacks));

        // pthread_mutex_init(&client_mtx, NULL);
        // pthread_mutex_init(&resp_data_lock, NULL);
        // pthread_mutex_init(&event_lock, NULL);
        // evthread_use_pthreads();
        // pthread_create(&client_tid, NULL, client_thread, NULL);

        is_initialized             = true;
        is_connected               = true; // set CONNECT state to mock service
        wait_resp                  = false;
        is_wbuff_empty             = true;
        registeredEvt.isRegistered = false;
        registeredEvt.eventNo      = 0;
        for (uint16_t i = 0; i < OCPP_EVENT_ALL; i++) {
            registeredEvt.eventList[i] = 0;
        }
        connect_callback(is_connected, connect_context);

        error = E_OK_OCPP;
    }
    else {
        printf("%s\n", "initialized");
        error = E_ALREADY_INITIALIZED_OCPP;
    }
    return error;
}

ocpp_status_t ocpp_register_event(ocpp_event_t event, ocpp_func_ptr_t func_ptr, void* context)
{
    if (func_ptr != NULL) {
        if (event < OCPP_EVENT_NUM) {
            callbacks[event].func = func_ptr;
            callbacks[event].ctx  = context;
        }
        else if (event == OCPP_EVENT_ALL) {
            printf("%s\n","ocpp_register_event");
            for (int i = 0; i < OCPP_EVENT_ALL; i++) {
                callbacks[i].func = func_ptr;
                callbacks[i].ctx  = context;
            }
        }
    }
    return E_OK_OCPP;
}
ocpp_status_t ocpp_intro_message_to_service(int32_t* events, size_t eventNo)
{
    (void)events;
    (void)eventNo;
    return E_OK_OCPP;
}
ocpp_status_t ocpp_alert_message_to_service(uint32_t len, uint8_t* p_data)
{
    (void)len;
    (void)p_data;
    return E_OK_OCPP;
}
ocpp_status_t ocpp_info_message_to_service(message_type_id cmd, bool bsync, uint32_t len, uint8_t* p_data)
{
    (void)bsync;
    printf("Message from APP, len = %d, payload =[%s]\n", len, p_data);
    switch (cmd) {
    case BOOT_NOTIFICATION_REQUEST:
        onEventBootNotificationResponse();
        break;

    default:
        break;
    }
    return E_OK_OCPP;
}
ocpp_status_t ocpp_config_message_to_service(config_type_id cmd, uint8_t* p_data, size_t len)
{
    (void)cmd;
    (void)p_data;
    (void)len;
    return E_OK_OCPP;
}
ocpp_status_t ocpp_set_reconnect_pararm(reconnect_param param, uint32_t options)
{
    (void)param;
    (void)options;
    return E_OK_OCPP;
}
void ocpp_deinit(void) {}
void onEventBootNotificationResponse()
{
    const char* response_payload
        = "{\"currentTime\":\"2021-11-23T09:08:58.031Z\",\"interval\":300,\"status\":\"Accepted\"}";
    event_status response_status = STATUS_NORMAL;
    int eventIdx                 = event_mapping_table[BOOT_NOTIFICATION_RESPONSE].event;
    ocpp_func_ptr_t func_ptr     = callbacks[eventIdx].func;
    // printf("onEventBootNotificationResponse: %d, %p\n", eventIdx, func_ptr);
    if (func_ptr != NULL) {
        func_ptr(eventIdx, (void*)response_payload, response_status, callbacks[eventIdx].ctx);
    }
    onEventGetBaseReportRequest();
}

void onEventGetBaseReportRequest()
{
    const char* request_payload =  NULL;
        // = "{\"reportBase\":\"FullInventory\",\"requestId\":1234}";
    event_status request_status = STATUS_NORMAL;
    int eventIdx                 = event_mapping_table[GET_BASE_REPORT_REQUEST].event;
    ocpp_func_ptr_t func_ptr     = callbacks[eventIdx].func;
    // printf("onEventBootNotificationResponse: %d, %p\n", eventIdx, func_ptr);
    if (func_ptr != NULL) {
        func_ptr(eventIdx, (void*)request_payload, request_status, callbacks[eventIdx].ctx);
    }
}