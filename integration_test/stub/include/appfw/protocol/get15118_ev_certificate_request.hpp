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

SCHEMA_ENUM(CertificateActionEnum,\
    Install,\
    Update);
using CertificateActionEnumType=schema_enum_value<CertificateActionEnum>;

struct Get15118EVCertificateRequest
{
    static const char* action() { return "Get15118EVCertificate"; }

    CertificateActionEnumType certificateAction;
    optional<CustomDataType> customData;
    schema_string<5600> exiRequest;
    schema_string<50> iso15118SchemaVersion;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "action", certificateAction);
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "exiRequest", exiRequest);
        cereal::nvp(archive, "iso15118SchemaVersion", iso15118SchemaVersion);
    }
};



} } 

