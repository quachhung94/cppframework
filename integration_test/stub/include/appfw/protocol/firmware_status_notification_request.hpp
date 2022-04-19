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

SCHEMA_ENUM(FirmwareStatusEnum,\
    Downloaded,\
    DownloadFailed,\
    Downloading,\
    DownloadScheduled,\
    DownloadPaused,\
    Idle,\
    InstallationFailed,\
    Installing,\
    Installed,\
    InstallRebooting,\
    InstallScheduled,\
    InstallVerificationFailed,\
    InvalidSignature,\
    SignatureVerified);
using FirmwareStatusEnumType=schema_enum_value<FirmwareStatusEnum>;

struct FirmwareStatusNotificationRequest
{
    static const char* action() { return "FirmwareStatusNotification"; }

    optional<CustomDataType> customData;
    optional<int> requestId;
    FirmwareStatusEnumType status;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "requestId", requestId);
        cereal::nvp(archive, "status", status);
    }
};



} } 

