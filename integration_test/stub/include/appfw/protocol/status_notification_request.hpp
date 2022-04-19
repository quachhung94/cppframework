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

SCHEMA_ENUM(ConnectorStatusEnum,\
    Available,\
    Occupied,\
    Reserved,\
    Unavailable,\
    Faulted);
using ConnectorStatusEnumType=schema_enum_value<ConnectorStatusEnum>;

struct StatusNotificationRequest
{
    static const char* action() { return "StatusNotification"; }

    int connectorId;
    ConnectorStatusEnumType connectorStatus;
    optional<CustomDataType> customData;
    int evseId;
    schema_date_time timestamp;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "connectorId", connectorId);
        cereal::nvp(archive, "connectorStatus", connectorStatus);
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "evseId", evseId);
        cereal::nvp(archive, "timestamp", timestamp);
    }
};



} } 

