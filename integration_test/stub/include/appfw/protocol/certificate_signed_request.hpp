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

struct CertificateSignedRequest
{
    static const char* action() { return "CertificateSigned"; }

    schema_string<10000> certificate;
    optional<CertificateSigningUseEnumType> certificateType;
    optional<CustomDataType> customData;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "certificateChain", certificate);
        cereal::nvp(archive, "certificateType", certificateType);
        cereal::nvp(archive, "customData", customData);
    }
};



} } 

