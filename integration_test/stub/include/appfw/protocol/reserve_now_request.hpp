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

SCHEMA_ENUM(ConnectorEnum,\
    cCCS1,\
    cCCS2,\
    cG105,\
    cTesla,\
    cType1,\
    cType2,\
    s309-1P-16A,\
    s309-1P-32A,\
    s309-3P-16A,\
    s309-3P-32A,\
    sBS1361,\
    sCEE-7-7,\
    sType2,\
    sType3,\
    Other1PhMax16A,\
    Other1PhOver16A,\
    Other3Ph,\
    Pan,\
    wInductive,\
    wResonant,\
    Undetermined,\
    Unknown);
using ConnectorEnumType=schema_enum_value<ConnectorEnum>;

struct ReserveNowRequest
{
    static const char* action() { return "ReserveNow"; }

    optional<ConnectorEnumType> connectorType;
    optional<CustomDataType> customData;
    optional<int> evseId;
    schema_date_time expiryDateTime;
    optional<IdTokenType> groupIdToken;
    int id;
    IdTokenType idToken;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "connectorType", connectorType);
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "evseId", evseId);
        cereal::nvp(archive, "expiryDateTime", expiryDateTime);
        cereal::nvp(archive, "groupIdToken", groupIdToken);
        cereal::nvp(archive, "id", id);
        cereal::nvp(archive, "idToken", idToken);
    }
};



} } 

