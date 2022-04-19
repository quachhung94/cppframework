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

SCHEMA_ENUM(ReservationUpdateStatusEnum,\
    Expired,\
    Removed);
using ReservationUpdateStatusEnumType=schema_enum_value<ReservationUpdateStatusEnum>;

struct ReservationStatusUpdateRequest
{
    static const char* action() { return "ReservationStatusUpdate"; }

    optional<CustomDataType> customData;
    int reservationId;
    ReservationUpdateStatusEnumType reservationUpdateStatus;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "reservationId", reservationId);
        cereal::nvp(archive, "reservationUpdateStatus", reservationUpdateStatus);
    }
};



} } 

