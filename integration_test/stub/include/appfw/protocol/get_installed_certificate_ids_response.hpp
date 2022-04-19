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

SCHEMA_ENUM(GetInstalledCertificateStatusEnum,\
    Accepted,\
    NotFound);
using GetInstalledCertificateStatusEnumType=schema_enum_value<GetInstalledCertificateStatusEnum>;

struct CertificateHashDataChainType
{
    CertificateHashDataType certificateHashData;
    GetCertificateIdUseEnumType certificateType;
    optional<schema_array<CertificateHashDataType,4,1>> childCertificateHashData;
    optional<CustomDataType> customData;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "certificateHashData", certificateHashData);
        cereal::nvp(archive, "certificateType", certificateType);
        cereal::nvp(archive, "childCertificateHashData", childCertificateHashData);
        cereal::nvp(archive, "customData", customData);
    }
};

struct GetInstalledCertificateIdsResponse
{
    optional<schema_array<CertificateHashDataChainType,65536,1>> certificateHashDataChain;
    optional<CustomDataType> customData;
    GetInstalledCertificateStatusEnumType status;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "certificateHashDataChain", certificateHashDataChain);
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "status", status);
    }
};



} } 

