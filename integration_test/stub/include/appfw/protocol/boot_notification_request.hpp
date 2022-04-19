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

SCHEMA_ENUM(BootReasonEnum,\
    ApplicationReset,\
    FirmwareUpdate,\
    LocalReset,\
    PowerUp,\
    RemoteReset,\
    ScheduledReset,\
    Triggered,\
    Unknown,\
    Watchdog);
using BootReasonEnumType=schema_enum_value<BootReasonEnum>;

struct ModemType
{
    optional<CustomDataType> customData;
    optional<schema_string<20>> iccid;
    optional<schema_string<20>> imsi;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "iccid", iccid);
        cereal::nvp(archive, "imsi", imsi);
    }
};

struct ChargingStationType
{
    optional<CustomDataType> customData;
    optional<schema_string<50>> firmwareVersion;
    schema_string<20> model;
    optional<ModemType> modem;
    optional<schema_string<25>> serialNumber;
    schema_string<50> vendorName;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "firmwareVersion", firmwareVersion);
        cereal::nvp(archive, "model", model);
        cereal::nvp(archive, "modem", modem);
        cereal::nvp(archive, "serialNumber", serialNumber);
        cereal::nvp(archive, "vendorName", vendorName);
    }
};

struct BootNotificationRequest
{
    static const char* action() { return "BootNotification"; }

    ChargingStationType chargingStation;
    optional<CustomDataType> customData;
    BootReasonEnumType reason;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "chargingStation", chargingStation);
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "reason", reason);
    }
};



} } 

