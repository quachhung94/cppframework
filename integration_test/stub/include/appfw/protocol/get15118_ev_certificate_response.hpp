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

SCHEMA_ENUM(Iso15118EVCertificateStatusEnum,\
    Accepted,\
    Failed);
using Iso15118EVCertificateStatusEnumType=schema_enum_value<Iso15118EVCertificateStatusEnum>;

struct Get15118EVCertificateResponse
{
    optional<CustomDataType> customData;
    schema_string<5600> exiResponse;
    Iso15118EVCertificateStatusEnumType status;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "exiResponse", exiResponse);
        cereal::nvp(archive, "status", status);
    }
};



} } 

