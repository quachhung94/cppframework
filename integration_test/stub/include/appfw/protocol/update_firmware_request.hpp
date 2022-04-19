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

struct FirmwareType
{
    optional<CustomDataType> customData;
    optional<schema_date_time> installDateTime;
    schema_string<512> location;
    schema_date_time retrieveDateTime;
    optional<schema_string<800>> signature;
    optional<schema_string<5500>> signingCertificate;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "installDateTime", installDateTime);
        cereal::nvp(archive, "location", location);
        cereal::nvp(archive, "retrieveDateTime", retrieveDateTime);
        cereal::nvp(archive, "signature", signature);
        cereal::nvp(archive, "signingCertificate", signingCertificate);
    }
};

struct UpdateFirmwareRequest
{
    static const char* action() { return "UpdateFirmware"; }

    optional<CustomDataType> customData;
    FirmwareType firmware;
    int requestId;
    optional<int> retries;
    optional<int> retryInterval;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "firmware", firmware);
        cereal::nvp(archive, "requestId", requestId);
        cereal::nvp(archive, "retries", retries);
        cereal::nvp(archive, "retryInterval", retryInterval);
    }
};



} } 

