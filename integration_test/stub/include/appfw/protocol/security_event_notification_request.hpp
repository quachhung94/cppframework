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

struct SecurityEventNotificationRequest
{
    static const char* action() { return "SecurityEventNotification"; }

    optional<CustomDataType> customData;
    optional<schema_string<255>> techInfo;
    schema_date_time timestamp;
    schema_string<50> type;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "techInfo", techInfo);
        cereal::nvp(archive, "timestamp", timestamp);
        cereal::nvp(archive, "type", type);
    }
};



} } 

