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

struct AuthorizeRequest
{
    static const char* action() { return "Authorize"; }

    optional<CustomDataType> customData;
    IdTokenType idToken;
    optional<schema_array<OCSPRequestDataType,4,1>> iso15118CertificateHashData;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "idToken", idToken);
        cereal::nvp(archive, "iso15118CertificateHashData", iso15118CertificateHashData);
    }
};



} } 

