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

SCHEMA_ENUM(ResetEnum,\
    Immediate,\
    OnIdle);
using ResetEnumType=schema_enum_value<ResetEnum>;

struct ResetRequest
{
    static const char* action() { return "Reset"; }

    optional<CustomDataType> customData;
    optional<int> evseId;
    ResetEnumType type;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "evseId", evseId);
        cereal::nvp(archive, "type", type);
    }
};



} } 

