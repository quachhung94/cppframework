
#ifndef _LIBBROKER_MESSAGES_H_
#define _LIBBROKER_MESSAGES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#define LIBBROKER_PRODUCT_STRING_MAX 128
#define LIBBROKER_FAN_NUM 8
#define METER_COUNT_MAX 2
#define PLC_COUNT_MAX 2
#define UID_LEN_MAX 6
#define EV_MAC_LEN 6

typedef enum {
    kHmiScreenStateBoot = 0,
    kHmiScreenStateHome,
    kHmiScreenStateAuthen,
    kHmiScreenStateRfidPass,
    kHmiScreenStateRfidFailed,
    kHmiScreenStateSocketSelect,
    kHmiScreenStateGun,
    kHmiScreenState30kSocketHlc,
    kHmiScreenState30kSocketCharging,
    kHmiScreenState30kSocketInfo,
    kHmiScreenState30kSocket1Hlc,
    kHmiScreenState30kSocket1Charging,
    kHmiScreenState30kSocket1Info,
    kHmiScreenState30kSocket2Hlc,
    kHmiScreenState30kSocket2Charging,
    kHmiScreenState30kSocket2Info,
    kHmiScreenStateMaintenance,
    kHmiScreenStateThankYou,
    kHmiScreenCurrentMax
} DisplayCurrentScreens;

typedef enum {
    kHmiRequestCurrentScreen = 0,
    kHmiScreenActiveMax
} DisplayActiveScreens;

typedef enum {
    kPilotStateA = 0,
    kPilotStateB,
    kPilotStateC,
    kPilotStateD,
    kPilotStateE,
    kPilotStateF,
    kPilotStateMax
} ControlPilotStates;

typedef enum {
    kEnergyTransferStart = 0,
    kEnergyTransferStop,
    kEnergyTransferMax
} EnergyTransferStates;

typedef enum {
    kAuthenTypeQrCode = 0,
    kAuthenTypeRfId,
    kAuthenTypeEvMac,
    kAuthenTypeMax
} AuthenTypes;

typedef enum {
    kEvTypeVf = 0,
    kEvTypeOthers,
    kEvTypeMax
} EvTypes;

typedef enum {
    kNoErrorCode = 0,
    kHasErrorCode
} ErrorCodeStatus;

typedef enum {
    kHmiSystemStatusNone = 0,
    kHmiSystemStatusNormal,
    kHmiSystemStatusDiag,
    kHmiSystemStatusFota,
    kHmiSystemStatusError,
    kHmiSystemStatusMax,
} HmiSystemStatus;

typedef enum {
    kPostDetailStatusOk = 0,
    kPostDetailStatusNg,
    kPostDetailStatusMax,
} PostDetailStatus;

typedef struct _PostMainInfo_t_ {
    char swversion[LIBBROKER_PRODUCT_STRING_MAX];
    char hwversion[LIBBROKER_PRODUCT_STRING_MAX];
    char serialno[LIBBROKER_PRODUCT_STRING_MAX];
    PostDetailStatus ddr;
    PostDetailStatus emmc;
    PostDetailStatus i2c;
    PostDetailStatus can0;
    PostDetailStatus can1;
    PostDetailStatus eth0;
    PostDetailStatus eth1;
    PostDetailStatus usb;
} PostMainInfo_t;

typedef struct _PostPlcImxInfo_t_ {
    char swversion[LIBBROKER_PRODUCT_STRING_MAX];
    char hwversion[LIBBROKER_PRODUCT_STRING_MAX];
    char serialno[LIBBROKER_PRODUCT_STRING_MAX];
    PostDetailStatus ddr;
    PostDetailStatus emmc;
    PostDetailStatus i2c;
    PostDetailStatus can;
    PostDetailStatus eth;
} PostPlcImxInfo_t;

typedef struct _PostFanInfo_t_ {
    char swversion[LIBBROKER_PRODUCT_STRING_MAX];
    char hwversion[LIBBROKER_PRODUCT_STRING_MAX];
    char serialno[LIBBROKER_PRODUCT_STRING_MAX];
    PostDetailStatus fanstatus[LIBBROKER_FAN_NUM];
    PostDetailStatus allfanstatus;
    PostDetailStatus hightempstatus;
    PostDetailStatus temp0sensor;
    PostDetailStatus temp1sensor;
    PostDetailStatus temp2sensor;
    PostDetailStatus canconnectstatus;
} PostFanInfo_t;

typedef struct _PostIoInfo_t_ {
    char swversion[LIBBROKER_PRODUCT_STRING_MAX];
    char hwversion[LIBBROKER_PRODUCT_STRING_MAX];
    char serialno[LIBBROKER_PRODUCT_STRING_MAX];
    PostDetailStatus flashstatus;
    PostDetailStatus canconnectstatus;
    int metercount;
    PostDetailStatus meterconnectstatus[METER_COUNT_MAX];
    PostDetailStatus doorstatus;
    PostDetailStatus emergencybtnstatus;
    PostDetailStatus spdstatus;
} PostIoInfo_t;

typedef struct _PostHvInfo_t_ {
    char swversion[LIBBROKER_PRODUCT_STRING_MAX];
    char hwversion[LIBBROKER_PRODUCT_STRING_MAX];
    char serialno[LIBBROKER_PRODUCT_STRING_MAX];
    PostDetailStatus acrelaystatus;
    PostDetailStatus inputovervoltage;
    PostDetailStatus inputundervoltage;
    PostDetailStatus output0status;
    PostDetailStatus output1status;
    PostDetailStatus output0hvrelay;
    PostDetailStatus output0lvrelay;
    PostDetailStatus output1hvrelay;
    PostDetailStatus output1lvrelay;
    PostDetailStatus parallelhvrelay;
    PostDetailStatus parallellvrelay;
    PostDetailStatus flashstatus;
    PostDetailStatus canconnectstatus;
} PostHvInfo_t;

typedef struct _PostRfidInfo_t_ {
    char swversion[LIBBROKER_PRODUCT_STRING_MAX];
    char hwversion[LIBBROKER_PRODUCT_STRING_MAX];
    char serialno[LIBBROKER_PRODUCT_STRING_MAX];
    PostDetailStatus transceiverstatus;
} PostRfidInfo_t;

typedef struct _PostPlcXmcInfo_t_ {
    char swversion[LIBBROKER_PRODUCT_STRING_MAX];
    char hwversion[LIBBROKER_PRODUCT_STRING_MAX];
    char serialno[LIBBROKER_PRODUCT_STRING_MAX];
    PostDetailStatus canconnectstatus;
    PostDetailStatus adcPwmStatus;
} PostPlcXmcInfo_t;

typedef struct _PostDetailResult_t_ {
    PostMainInfo_t main;
    PostPlcImxInfo_t plcImx[PLC_COUNT_MAX];
    PostFanInfo_t fan;
    PostIoInfo_t io;
    PostHvInfo_t hv;
    PostRfidInfo_t rfid;
    PostPlcXmcInfo_t plcXmc[PLC_COUNT_MAX];
} PostDetailResult_t;

typedef enum {
    kOpModePost = 0,
    kOpModeNormal,
    kOpModeMaintain,
    kOpModeMax
} SystemOpModes;

/**
 * Get/set connection status, used to parse/manipulate message contents of these following topics:
 * - kBrokerTopic_Hmi_Rfid_ConnectionStatus
 * - kBrokerTopic_Hmi_Display_ConnectionStatus
 * - kBrokerTopic_Hmi_Ext_ConnectionStatus
 */
int32_t Libbroker_GetConnectionStatus(void* input_message,  uint32_t message_len, bool* is_connected);
int32_t Libbroker_SetConnectionStatus(void* output_message, uint32_t message_len, bool  is_connected);

/**
 * Get/set error code, used to parse/manipulate message contents of these following topics:
 * - kBrokerTopic_Hmi_Rfid_ErrorCode
 * - kBrokerTopic_Hmi_Display_ErrorCode
 * - kBrokerTopic_Hmi_Ext_ErrorCode
 * - kBrokerTopic_Hmi_App_ErrorCode
 */
int32_t Libbroker_GetErrorCode(void* input_message,  uint32_t message_len, uint32_t* error_code);
int32_t Libbroker_SetErrorCode(void* output_message, uint32_t message_len, uint32_t  error_code);

/**
 * Get/set UID of RFID card for kBrokerTopic_Hmi_Rfid_Uid topic
 */
int32_t Libbroker_GetCardUid(void* input_message,  uint32_t message_len, uint16_t* gun_id, uint8_t* uid, uint16_t* uid_len);
int32_t Libbroker_SetCardUid(void* output_message, uint32_t message_len, uint16_t  gun_id, uint8_t* uid, uint16_t  uid_len);

/**
 * Get/set current screen of HMI for kBrokerTopic_Hmi_Display_ScreenIdCurrent topic
 */
int32_t Libbroker_GetCurrentScreen(void* input_message,  uint32_t message_len, DisplayCurrentScreens* screen);
int32_t Libbroker_SetCurrentScreen(void* output_message, uint32_t message_len, DisplayCurrentScreens  screen);

/**
 * Get/set active screen of HMI for kBrokerTopic_Hmi_Display_ScreenIdActive topic
 */
int32_t Libbroker_GetActiveScreen(void* input_message,  uint32_t message_len, DisplayActiveScreens* screen);
int32_t Libbroker_SetActiveScreen(void* output_message, uint32_t message_len, DisplayActiveScreens  screen);

/**
 * Get/set connection status of modules for these following topics:
 * - kBrokerTopic_Hmi_App_GunStatus
 * - kBrokerTopic_Hmi_App_GunError
 * - kBrokerTopic_Hmi_App_HlcStatus
 */
int32_t Libbroker_GetModuleStatus(void* input_message,  uint32_t message_len, uint16_t* gun_id, bool* is_connected);
int32_t Libbroker_SetModuleStatus(void* output_message, uint32_t message_len, uint16_t  gun_id, bool  is_connected);

/**
 * Get/set status of icons for these following topics:
 * - kBrokerTopic_Hmi_App_Icon4g
 * - kBrokerTopic_Hmi_App_IconWifi
 * - kBrokerTopic_Hmi_App_IconLan
 * - kBrokerTopic_Hmi_App_Cloud
 */
int32_t Libbroker_GetIconStatus(void* input_message,  uint32_t message_len, bool* is_active);
int32_t Libbroker_SetIconStatus(void* output_message, uint32_t message_len, bool  is_active);

/**
 * Get/set battery percent for kBrokerTopic_Hmi_App_BattPercent topic
 */
int32_t Libbroker_GetBattPercent(void* input_message,  uint32_t message_len, uint16_t* gun_id, uint8_t* batt_percent);
int32_t Libbroker_SetBattPercent(void* output_message, uint32_t message_len, uint16_t  gun_id, uint8_t  batt_percent);

/**
 * Get/set charging time for kBrokerTopic_Hmi_App_ChargingTime topic
 */
int32_t Libbroker_GetChargingTime(void* input_message,  uint32_t message_len, uint16_t* gun_id, uint32_t* time);
int32_t Libbroker_SetChargingTime(void* output_message, uint32_t message_len, uint16_t  gun_id, uint32_t  time);

/**
 * Get/set charging power for kBrokerTopic_Hmi_App_ChargingPower topic
 */
int32_t Libbroker_GetChargingPower(void* input_message, uint32_t  message_len, uint16_t* gun_id, uint32_t* power);
int32_t Libbroker_SetChargingPower(void* output_message, uint32_t message_len, uint16_t  gun_id, uint32_t  power);

/**
 * Get/set charging energy for kBrokerTopic_Hmi_App_ChargingEnergy topic
 */
int32_t Libbroker_GetChargingEnergy(void* input_message,  uint32_t message_len, uint16_t* gun_id, uint32_t* energy);
int32_t Libbroker_SetChargingEnergy(void* output_message, uint32_t message_len, uint16_t  gun_id, uint32_t  energy);

/**
 * Get/set charging cash for kBrokerTopic_Hmi_App_ChargingCast topic
 */
int32_t Libbroker_GetChargingCash(void* input_message,  uint32_t message_len, uint16_t* gun_id, uint32_t* cash);
int32_t Libbroker_SetChargingCash(void* output_message, uint32_t message_len, uint16_t  gun_id, uint32_t  cash);

/**
 * Get/set active socket for:
 * - kBrokerTopic_Hmi_App_ActiveSocket
 * - kBrokerTopic_Hmi_App_GunCableCheck
 */
int32_t Libbroker_GetActiveSocket(void* input_message,  uint32_t message_len, uint16_t* gun_id);
int32_t Libbroker_SetActiveSocket(void* output_message, uint32_t message_len, uint16_t  gun_id);

/**
 * Get/set charging cash for kBrokerTopic_Hmi_App_SystemStatus topic
 */
int32_t Libbroker_GetChargingSystemStatus(void* input_message,  uint32_t message_len, HmiSystemStatus* status);
int32_t Libbroker_SetChargingSystemStatus(void* output_message, uint32_t message_len, HmiSystemStatus  status);

/**
 * Get/set charging cash for kBrokerTopic_Hmi_App_ErrorCodeData topic
 */
int32_t Libbroker_GetErrorCodeData(void* input_message,  uint32_t message_len, uint64_t* error_code);
int32_t Libbroker_SetErrorCodeData(void* output_message, uint32_t message_len, uint64_t  error_code);

/**
 * Get/set MAC address of EV for kBrokerTopic_Ocpp_Control_EvMac topic
 */
int32_t Libbroker_GetEvMac(void* input_message,  uint32_t message_len, uint16_t* gun_id, uint8_t* ev_mac);
int32_t Libbroker_SetEvMac(void* output_message, uint32_t message_len, uint16_t  gun_id, uint8_t* ev_mac);

/**
 * Authen info messages for kBrokerTopic_Ocpp_Authen_AuthenDone topic
 */
int32_t Libbroker_GetAuthenResult(void* input_message,  uint32_t message_len, uint16_t* gun_id, AuthenTypes* authen_type, EvTypes* ev_type, bool* authen_ok);
int32_t Libbroker_SetAuthenResult(void* output_message, uint32_t message_len, uint16_t  gun_id, AuthenTypes  authen_type, EvTypes  ev_type, bool  authen_ok);

int32_t Libbroker_GetEnergyTransferState(void* input_message,  uint32_t message_len, uint16_t* gun_id, EnergyTransferStates* state);
int32_t Libbroker_SetEnergyTransferState(void* output_message, uint32_t message_len, uint16_t  gun_id, EnergyTransferStates  state);

/**
 * Authen info messages for kBrokerTopic_Ocpp_Authen_AuthenDone topic
 */
int32_t Libbroker_SetPostDetailResult(void* output_message, uint32_t message_len, PostDetailResult_t *info);

int32_t Libbroker_GetSystemOpMode(void* input_message,  uint32_t message_len, SystemOpModes* op_mode);
int32_t Libbroker_SetSystemOpMode(void* output_message, uint32_t message_len, SystemOpModes  op_mode);

/**
 * Get/set fast charge info for kBrokerTopic_Charge_Control_FastCharge topic
 */
int32_t Libbroker_GetFastChargeInfo(void* input_message,  uint32_t message_len, uint16_t* gun_id, bool* is_enabled);
int32_t Libbroker_SetFastChargeInfo(void* output_message, uint32_t message_len, uint16_t  gun_id, bool  is_enabled);

/**
 * Set charging report info for kBrokerTopic_Charge_Control_Report topic
 */
int32_t Libbroker_SetChargingReportInfo(void* input_message, uint32_t message_len, uint8_t gun_id, bool is_ok, const char* ev_mac, uint64_t time, uint64_t power_val, uint64_t power_mul);

/**
 * Get/set gun error info for kBrokerTopic_Hmi_App_GunError topic
 */
int32_t Libbroker_GetGunErrorInfo(void*  input_message, uint32_t message_len, uint16_t* gun_id, bool* gun_error, bool* station_error);
int32_t Libbroker_SetGunErrorInfo(void* output_message, uint32_t message_len, uint16_t  gun_id, bool  gun_error, bool  station_error);

#ifdef __cplusplus
}
#endif

#endif // _LIBBROKER_MESSAGES_H_
