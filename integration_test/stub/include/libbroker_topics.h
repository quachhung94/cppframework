
#ifndef _LIBBROKER_TOPICS_H_
#define _LIBBROKER_TOPICS_H_

/**
 * Broker topic enumeration
 */
typedef enum {
    kBrokerTopicMin = 0,
    kBrokerTopic_Hmi_Rfid_ConnectionStatus = kBrokerTopicMin,
    kBrokerTopic_Hmi_Rfid_ErrorCode,
    kBrokerTopic_Hmi_Rfid_Uid,
    kBrokerTopic_Hmi_Display_ConnectionStatus,
    kBrokerTopic_Hmi_Display_ErrorCode,
    kBrokerTopic_Hmi_Display_ScreenIdCurrent,
    kBrokerTopic_Hmi_Display_ScreenIdActive,
    kBrokerTopic_Hmi_Ext_ConnectionStatus,
    kBrokerTopic_Hmi_Ext_ErrorCode,
    kBrokerTopic_Hmi_App_ErrorCode,
    kBrokerTopic_Hmi_App_GunStatus,
    kBrokerTopic_Hmi_App_GunError,
    kBrokerTopic_Hmi_App_GunCableCheck,
    kBrokerTopic_Hmi_App_HlcStatus,
    kBrokerTopic_Hmi_App_Icon4g,
    kBrokerTopic_Hmi_App_IconWifi,
    kBrokerTopic_Hmi_App_IconLan,
    kBrokerTopic_Hmi_App_Cloud,
    kBrokerTopic_Hmi_App_Account,
    kBrokerTopic_Hmi_App_BattPercent,
    kBrokerTopic_Hmi_App_ChargingTime,
    kBrokerTopic_Hmi_App_ChargingPower,
    kBrokerTopic_Hmi_App_ChargingEnergy,
    kBrokerTopic_Hmi_App_ChargingCash,
    kBrokerTopic_Hmi_App_WaitEvConnectTimeout,
    kBrokerTopic_Hmi_App_ActiveSocket,
    kBrokerTopic_Hmi_App_SystemStatus,
    kBrokerTopic_Hmi_App_ErrorCodeData,
    kBrokerTopic_Ocpp_Control_EvMac,
    kBrokerTopic_Ocpp_Control_AuthenDone,
    kBrokerTopic_Ocpp_Control_RemoteStop,
    kBrokerTopic_Charge_Control_EnergyTransfer,
    kBrokerTopic_Charge_Control_FastCharge,
    kBrokerTopic_Charge_Control_Report,
    kBrokerTopic_Diag_Post_Start,
    kBrokerTopic_Diag_Post_DetailResult,
    kBrokerTopic_System_OpMode,
    kBrokerTopic_Charge_Wrong_Sequence,
    kBrokerTopicMax
} BrokerTopics;

#endif // _LIBBROKER_TOPICS_H_
