#pragma once

/**
*
* This file is auto generated using this exact command:
*     ../../generator/20/schema-to-cpp-header2.py
*     --input-dir=../../schemas/201
*     --namespace=lgpl3
*     --namespace=ocpp201
*     --include=<cereal/types/vector.hpp>
*     --include="../cereal/cereal_ext.hpp"
*     --include="../cereal/schema_enum.hpp"
*     --include="../cereal/schema_string.hpp"
*     --include="../cereal/schema_array.hpp"
*     --include="../cereal/schema_date_time.hpp"
*
*/

#include "./common.hpp"

namespace lgpl3 { namespace ocpp201 { 

SCHEMA_ENUM(ChargingStateEnum,\
    Charging,\
    EVConnected,\
    SuspendedEV,\
    SuspendedEVSE,\
    Idle);
using ChargingStateEnumType=schema_enum_value<ChargingStateEnum>;

SCHEMA_ENUM(ReasonEnum,\
    DeAuthorized,\
    EmergencyStop,\
    EnergyLimitReached,\
    EVDisconnected,\
    GroundFault,\
    ImmediateReset,\
    Local,\
    LocalOutOfCredit,\
    MasterPass,\
    Other,\
    OvercurrentFault,\
    PowerLoss,\
    PowerQuality,\
    Reboot,\
    Remote,\
    SOCLimitReached,\
    StoppedByEV,\
    TimeLimitReached,\
    Timeout);
using ReasonEnumType=schema_enum_value<ReasonEnum>;

SCHEMA_ENUM(TransactionEventEnum,\
    Ended,\
    Started,\
    Updated);
using TransactionEventEnumType=schema_enum_value<TransactionEventEnum>;

SCHEMA_ENUM(TriggerReasonEnum,\
    Authorized,\
    CablePluggedIn,\
    ChargingRateChanged,\
    ChargingStateChanged,\
    Deauthorized,\
    EnergyLimitReached,\
    EVCommunicationLost,\
    EVConnectTimeout,\
    MeterValueClock,\
    MeterValuePeriodic,\
    TimeLimitReached,\
    Trigger,\
    UnlockCommand,\
    StopAuthorized,\
    EVDeparted,\
    EVDetected,\
    RemoteStop,\
    RemoteStart,\
    AbnormalCondition,\
    SignedDataReceived,\
    ResetCommand);
using TriggerReasonEnumType=schema_enum_value<TriggerReasonEnum>;

struct TransactionType
{
    optional<ChargingStateEnumType> chargingState;
    optional<CustomDataType> customData;
    optional<int> remoteStartId;
    optional<ReasonEnumType> stoppedReason;
    optional<int> timeSpentCharging;
    schema_string<36> transactionId;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "chargingState", chargingState);
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "remoteStartId", remoteStartId);
        cereal::nvp(archive, "stoppedReason", stoppedReason);
        cereal::nvp(archive, "timeSpentCharging", timeSpentCharging);
        cereal::nvp(archive, "transactionId", transactionId);
    }
};

struct TransactionEventRequest
{
    static const char* action() { return "TransactionEvent"; }

    optional<double> cableMaxCurrent;
    optional<CustomDataType> customData;
    TransactionEventEnumType eventType;
    optional<EVSEType> evse;
    optional<IdTokenType> idToken;
    optional<schema_array<MeterValueType,65536,1>> meterValue;
    optional<int> numberOfPhasesUsed;
    optional<schema_boolean> offline;
    optional<int> reservationId;
    int seqNo;
    schema_date_time timestamp;
    TransactionType transactionInfo;
    TriggerReasonEnumType triggerReason;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "cableMaxCurrent", cableMaxCurrent);
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "eventType", eventType);
        cereal::nvp(archive, "evse", evse);
        cereal::nvp(archive, "idToken", idToken);
        cereal::nvp(archive, "meterValue", meterValue);
        cereal::nvp(archive, "numberOfPhasesUsed", numberOfPhasesUsed);
        cereal::nvp(archive, "offline", offline);
        cereal::nvp(archive, "reservationId", reservationId);
        cereal::nvp(archive, "seqNo", seqNo);
        cereal::nvp(archive, "timestamp", timestamp);
        cereal::nvp(archive, "transactionInfo", transactionInfo);
        cereal::nvp(archive, "triggerReason", triggerReason);
    }
};



} } 

