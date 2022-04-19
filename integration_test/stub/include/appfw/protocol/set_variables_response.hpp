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

SCHEMA_ENUM(SetVariableStatusEnum,\
    Accepted,\
    Rejected,\
    InvalidValue,\
    UnknownComponent,\
    UnknownVariable,\
    NotSupportedAttributeType,\
    OutOfRange,\
    RebootRequired);
using SetVariableStatusEnumType=schema_enum_value<SetVariableStatusEnum>;

struct SetVariableResultType
{
    SetVariableStatusEnumType attributeStatus;
    optional<AttributeEnumType> attributeType;
    ComponentType component;
    optional<CustomDataType> customData;
    VariableType variable;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "attributeStatus", attributeStatus);
        cereal::nvp(archive, "attributeType", attributeType);
        cereal::nvp(archive, "component", component);
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "variable", variable);
    }
};

struct SetVariablesResponse
{
    optional<CustomDataType> customData;
    schema_array<SetVariableResultType,65536,1> setVariableResult;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "setVariableResult", setVariableResult);
    }
};



} } 

