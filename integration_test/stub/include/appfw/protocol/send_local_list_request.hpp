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

SCHEMA_ENUM(UpdateEnum,\
    Differential,\
    Full);
using UpdateEnumType=schema_enum_value<UpdateEnum>;

struct AuthorizationData
{
    optional<CustomDataType> customData;
    IdTokenType idToken;
    optional<IdTokenInfoType> idTokenInfo;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "idToken", idToken);
        cereal::nvp(archive, "idTokenInfo", idTokenInfo);
    }
};

struct SendLocalListRequest
{
    static const char* action() { return "SendLocalList"; }

    optional<CustomDataType> customData;
    optional<schema_array<AuthorizationData,65536,1>> localAuthorizationList;
    UpdateEnumType updateType;
    int versionNumber;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "localAuthorizationList", localAuthorizationList);
        cereal::nvp(archive, "updateType", updateType);
        cereal::nvp(archive, "versionNumber", versionNumber);
    }
};



} } 

