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

struct RequestStartTransactionRequest
{
    static const char* action() { return "RequestStartTransaction"; }

    optional<ChargingProfileType> chargingProfile;
    optional<CustomDataType> customData;
    optional<int> evseId;
    optional<IdTokenType> groupIdToken;
    IdTokenType idToken;
    int remoteStartId;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "chargingProfile", chargingProfile);
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "evseId", evseId);
        cereal::nvp(archive, "groupIdToken", groupIdToken);
        cereal::nvp(archive, "idToken", idToken);
        cereal::nvp(archive, "remoteStartId", remoteStartId);
    }
};



} } 

