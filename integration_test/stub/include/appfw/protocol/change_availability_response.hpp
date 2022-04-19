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

SCHEMA_ENUM(ChangeAvailabilityStatusEnum,\
    Accepted,\
    Rejected,\
    Scheduled);
using ChangeAvailabilityStatusEnumType=schema_enum_value<ChangeAvailabilityStatusEnum>;

struct ChangeAvailabilityResponse
{
    optional<CustomDataType> customData;
    ChangeAvailabilityStatusEnumType status;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "status", status);
    }
};



} } 

