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

SCHEMA_ENUM(PublishFirmwareStatusEnum,\
    Downloaded,\
    DownloadFailed,\
    Downloading,\
    DownloadScheduled,\
    DownloadPaused,\
    PublishFailed,\
    Published,\
    InvalidChecksum,\
    ChecksumVerified);
using PublishFirmwareStatusEnumType=schema_enum_value<PublishFirmwareStatusEnum>;

struct PublishFirmwareStatusNotificationRequest
{
    static const char* action() { return "PublishFirmwareStatusNotification"; }

    optional<CustomDataType> customData;
    optional<schema_array<schema_string<512>, 65536, 1>> location;
    optional<int> requestId;
    PublishFirmwareStatusEnumType status;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "location", location);
        cereal::nvp(archive, "requestId", requestId);
        cereal::nvp(archive, "status", status);
    }
};



} } 

