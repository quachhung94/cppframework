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

struct ClearChargingProfileType
{
    optional<ChargingProfilePurposeEnumType> chargingProfilePurpose;
    optional<CustomDataType> customData;
    optional<int> evseId;
    optional<int> stackLevel;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "chargingProfilePurpose", chargingProfilePurpose);
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "evseId", evseId);
        cereal::nvp(archive, "stackLevel", stackLevel);
    }
};

struct ClearChargingProfileRequest
{
    static const char* action() { return "ClearChargingProfile"; }

    optional<ClearChargingProfileType> chargingProfileCriteria;
    optional<int> chargingProfileId;
    optional<CustomDataType> customData;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "chargingProfileCriteria", chargingProfileCriteria);
        cereal::nvp(archive, "chargingProfileId", chargingProfileId);
        cereal::nvp(archive, "customData", customData);
    }
};



} } 

