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

#include <cereal/types/vector.hpp>
#include "../cereal/cereal_ext.hpp"
#include "../cereal/schema_enum.hpp"
#include "../cereal/schema_string.hpp"
#include "../cereal/schema_array.hpp"
#include "../cereal/schema_date_time.hpp"
#include <vector>

namespace lgpl3 { namespace ocpp201 { 

template<typename Type>
using optional=cereal::optional<Type>;

template<std::size_t MaxSize, std::size_t MinSize=1>
using schema_string=cereal::schema_string<MaxSize, MinSize>;

template<typename Type, std::size_t MaxSize, std::size_t MinSize=1>
using schema_array=cereal::schema_array<Type,MaxSize, MinSize>;

template<typename SchemaSet>
using schema_enum_value=cereal::schema_enum_value<SchemaSet>;

using schema_date_time=cereal::schema_data_time;

using schema_boolean=cereal::schema_boolean;

SCHEMA_ENUM(AttributeEnum,\
    Actual,\
    Target,\
    MinSet,\
    MaxSet);
using AttributeEnumType=schema_enum_value<AttributeEnum>;

SCHEMA_ENUM(AuthorizationStatusEnum,\
    Accepted,\
    Blocked,\
    ConcurrentTx,\
    Expired,\
    Invalid,\
    NoCredit,\
    NotAllowedTypeEVSE,\
    NotAtThisLocation,\
    NotAtThisTime,\
    Unknown);
using AuthorizationStatusEnumType=schema_enum_value<AuthorizationStatusEnum>;

SCHEMA_ENUM(CertificateSigningUseEnum,\
    ChargingStationCertificate,\
    V2GCertificate);
using CertificateSigningUseEnumType=schema_enum_value<CertificateSigningUseEnum>;

SCHEMA_ENUM(ChargingLimitSourceEnum,\
    EMS,\
    Other,\
    SO,\
    CSO);
using ChargingLimitSourceEnumType=schema_enum_value<ChargingLimitSourceEnum>;

SCHEMA_ENUM(ChargingProfileKindEnum,\
    Absolute,\
    Recurring,\
    Relative);
using ChargingProfileKindEnumType=schema_enum_value<ChargingProfileKindEnum>;

SCHEMA_ENUM(ChargingProfilePurposeEnum,\
    ChargingStationExternalConstraints,\
    ChargingStationMaxProfile,\
    TxDefaultProfile,\
    TxProfile);
using ChargingProfilePurposeEnumType=schema_enum_value<ChargingProfilePurposeEnum>;

SCHEMA_ENUM(ChargingRateUnitEnum,\
    W,\
    A);
using ChargingRateUnitEnumType=schema_enum_value<ChargingRateUnitEnum>;

SCHEMA_ENUM(CostKindEnum,\
    CarbonDioxideEmission,\
    RelativePricePercentage,\
    RenewableGenerationPercentage);
using CostKindEnumType=schema_enum_value<CostKindEnum>;

SCHEMA_ENUM(GenericDeviceModelStatusEnum,\
    Accepted,\
    Rejected,\
    NotSupported,\
    EmptyResultSet);
using GenericDeviceModelStatusEnumType=schema_enum_value<GenericDeviceModelStatusEnum>;

SCHEMA_ENUM(GenericStatusEnum,\
    Accepted,\
    Rejected);
using GenericStatusEnumType=schema_enum_value<GenericStatusEnum>;

SCHEMA_ENUM(GetCertificateIdUseEnum,\
    V2GRootCertificate,\
    MORootCertificate,\
    CSMSRootCertificate,\
    V2GCertificateChain,\
    ManufacturerRootCertificate);
using GetCertificateIdUseEnumType=schema_enum_value<GetCertificateIdUseEnum>;

SCHEMA_ENUM(HashAlgorithmEnum,\
    SHA256,\
    SHA384,\
    SHA512);
using HashAlgorithmEnumType=schema_enum_value<HashAlgorithmEnum>;

SCHEMA_ENUM(IdTokenEnum,\
    Central,\
    eMAID,\
    ISO14443,\
    KeyCode,\
    Local,\
    NoAuthorization,\
    ISO15693);
using IdTokenEnumType=schema_enum_value<IdTokenEnum>;

SCHEMA_ENUM(LocationEnum,\
    Body,\
    Cable,\
    EV,\
    Inlet,\
    Outlet);
using LocationEnumType=schema_enum_value<LocationEnum>;

SCHEMA_ENUM(MeasurandEnum,\
    Current.Export,\
    Current.Import,\
    Current.Offered,\
    Energy.Active.Export.Register,\
    Energy.Active.Import.Register,\
    Energy.Reactive.Export.Register,\
    Energy.Reactive.Import.Register,\
    Energy.Active.Export.Interval,\
    Energy.Active.Import.Interval,\
    Energy.Active.Net,\
    Energy.Reactive.Export.Interval,\
    Energy.Reactive.Import.Interval,\
    Energy.Reactive.Net,\
    Energy.Apparent.Net,\
    Energy.Apparent.Import,\
    Energy.Apparent.Export,\
    Frequency,\
    Power.Active.Export,\
    Power.Active.Import,\
    Power.Factor,\
    Power.Offered,\
    Power.Reactive.Export,\
    Power.Reactive.Import,\
    SoC,\
    Voltage);
using MeasurandEnumType=schema_enum_value<MeasurandEnum>;

SCHEMA_ENUM(MessageFormatEnum,\
    ASCII,\
    HTML,\
    URI,\
    UTF8);
using MessageFormatEnumType=schema_enum_value<MessageFormatEnum>;

SCHEMA_ENUM(MessagePriorityEnum,\
    AlwaysFront,\
    InFront,\
    NormalCycle);
using MessagePriorityEnumType=schema_enum_value<MessagePriorityEnum>;

SCHEMA_ENUM(MessageStateEnum,\
    Charging,\
    Faulted,\
    Idle,\
    Unavailable);
using MessageStateEnumType=schema_enum_value<MessageStateEnum>;

SCHEMA_ENUM(MonitorEnum,\
    UpperThreshold,\
    LowerThreshold,\
    Delta,\
    Periodic,\
    PeriodicClockAligned);
using MonitorEnumType=schema_enum_value<MonitorEnum>;

SCHEMA_ENUM(PhaseEnum,\
    L1,\
    L2,\
    L3,\
    N,\
    L1-N,\
    L2-N,\
    L3-N,\
    L1-L2,\
    L2-L3,\
    L3-L1);
using PhaseEnumType=schema_enum_value<PhaseEnum>;

SCHEMA_ENUM(ReadingContextEnum,\
    Interruption.Begin,\
    Interruption.End,\
    Other,\
    Sample.Clock,\
    Sample.Periodic,\
    Transaction.Begin,\
    Transaction.End,\
    Trigger);
using ReadingContextEnumType=schema_enum_value<ReadingContextEnum>;

SCHEMA_ENUM(RecurrencyKindEnum,\
    Daily,\
    Weekly);
using RecurrencyKindEnumType=schema_enum_value<RecurrencyKindEnum>;

SCHEMA_ENUM(RequestStartStopStatusEnum,\
    Accepted,\
    Rejected);
using RequestStartStopStatusEnumType=schema_enum_value<RequestStartStopStatusEnum>;

struct CustomDataType
{
    schema_string<255> vendorId;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "vendorId", vendorId);
    }
};

struct AdditionalInfoType
{
    schema_string<36> additionalIdToken;
    optional<CustomDataType> customData;
    schema_string<50> type;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "additionalIdToken", additionalIdToken);
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "type", type);
    }
};

struct CertificateHashDataType
{
    optional<CustomDataType> customData;
    HashAlgorithmEnumType hashAlgorithm;
    schema_string<128> issuerKeyHash;
    schema_string<128> issuerNameHash;
    schema_string<40> serialNumber;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "hashAlgorithm", hashAlgorithm);
        cereal::nvp(archive, "issuerKeyHash", issuerKeyHash);
        cereal::nvp(archive, "issuerNameHash", issuerNameHash);
        cereal::nvp(archive, "serialNumber", serialNumber);
    }
};

struct ChargingSchedulePeriodType
{
    optional<CustomDataType> customData;
    double limit;
    optional<int> numberPhases;
    optional<int> phaseToUse;
    int startPeriod;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "limit", limit);
        cereal::nvp(archive, "numberPhases", numberPhases);
        cereal::nvp(archive, "phaseToUse", phaseToUse);
        cereal::nvp(archive, "startPeriod", startPeriod);
    }
};

struct CostType
{
    int amount;
    optional<int> amountMultiplier;
    CostKindEnumType costKind;
    optional<CustomDataType> customData;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "amount", amount);
        cereal::nvp(archive, "amountMultiplier", amountMultiplier);
        cereal::nvp(archive, "costKind", costKind);
        cereal::nvp(archive, "customData", customData);
    }
};

struct ConsumptionCostType
{
    schema_array<CostType,3,1> cost;
    optional<CustomDataType> customData;
    double startValue;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "cost", cost);
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "startValue", startValue);
    }
};

struct EVSEType
{
    optional<int> connectorId;
    optional<CustomDataType> customData;
    int id;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "connectorId", connectorId);
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "id", id);
    }
};

struct ComponentType
{
    optional<CustomDataType> customData;
    optional<EVSEType> evse;
    optional<schema_string<50>> instance;
    schema_string<50> name;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "evse", evse);
        cereal::nvp(archive, "instance", instance);
        cereal::nvp(archive, "name", name);
    }
};

struct GroupIdTokenType
{
    optional<CustomDataType> customData;
    schema_string<36> idToken;
    IdTokenEnumType type;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "idToken", idToken);
        cereal::nvp(archive, "type", type);
    }
};

struct IdTokenType
{
    optional<schema_array<AdditionalInfoType,65536,1>> additionalInfo;
    optional<CustomDataType> customData;
    schema_string<36> idToken;
    IdTokenEnumType type;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "additionalInfo", additionalInfo);
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "idToken", idToken);
        cereal::nvp(archive, "type", type);
    }
};

struct MessageContentType
{
    schema_string<512> content;
    optional<CustomDataType> customData;
    MessageFormatEnumType format;
    optional<schema_string<8>> language;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "content", content);
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "format", format);
        cereal::nvp(archive, "language", language);
    }
};

struct IdTokenInfoType
{
    optional<schema_date_time> cacheExpiryDateTime;
    optional<int> chargingPriority;
    optional<CustomDataType> customData;
    optional<schema_array<int,65536,1>> evseId;
    optional<GroupIdTokenType> groupIdToken;
    optional<schema_string<8>> language1;
    optional<schema_string<8>> language2;
    optional<MessageContentType> personalMessage;
    AuthorizationStatusEnumType status;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "cacheExpiryDateTime", cacheExpiryDateTime);
        cereal::nvp(archive, "chargingPriority", chargingPriority);
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "evseId", evseId);
        cereal::nvp(archive, "groupIdToken", groupIdToken);
        cereal::nvp(archive, "language1", language1);
        cereal::nvp(archive, "language2", language2);
        cereal::nvp(archive, "personalMessage", personalMessage);
        cereal::nvp(archive, "status", status);
    }
};

struct MessageInfoType
{
    optional<CustomDataType> customData;
    optional<ComponentType> display;
    optional<schema_date_time> endDateTime;
    int id;
    MessageContentType message;
    MessagePriorityEnumType priority;
    optional<schema_date_time> startDateTime;
    optional<MessageStateEnumType> state;
    optional<schema_string<36>> transactionId;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "display", display);
        cereal::nvp(archive, "endDateTime", endDateTime);
        cereal::nvp(archive, "id", id);
        cereal::nvp(archive, "message", message);
        cereal::nvp(archive, "priority", priority);
        cereal::nvp(archive, "startDateTime", startDateTime);
        cereal::nvp(archive, "state", state);
        cereal::nvp(archive, "transactionId", transactionId);
    }
};

struct OCSPRequestDataType
{
    optional<CustomDataType> customData;
    HashAlgorithmEnumType hashAlgorithm;
    schema_string<128> issuerKeyHash;
    schema_string<128> issuerNameHash;
    schema_string<512> responderURL;
    schema_string<40> serialNumber;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "hashAlgorithm", hashAlgorithm);
        cereal::nvp(archive, "issuerKeyHash", issuerKeyHash);
        cereal::nvp(archive, "issuerNameHash", issuerNameHash);
        cereal::nvp(archive, "responderURL", responderURL);
        cereal::nvp(archive, "serialNumber", serialNumber);
    }
};

struct RelativeTimeIntervalType
{
    optional<CustomDataType> customData;
    optional<int> duration;
    int start;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "duration", duration);
        cereal::nvp(archive, "start", start);
    }
};

struct SalesTariffEntryType
{
    optional<schema_array<ConsumptionCostType,3,1>> consumptionCost;
    optional<CustomDataType> customData;
    optional<int> ePriceLevel;
    RelativeTimeIntervalType relativeTimeInterval;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "consumptionCost", consumptionCost);
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "ePriceLevel", ePriceLevel);
        cereal::nvp(archive, "relativeTimeInterval", relativeTimeInterval);
    }
};

struct SalesTariffType
{
    optional<CustomDataType> customData;
    int id;
    optional<int> numEPriceLevels;
    optional<schema_string<32>> salesTariffDescription;
    schema_array<SalesTariffEntryType,1024,1> salesTariffEntry;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "id", id);
        cereal::nvp(archive, "numEPriceLevels", numEPriceLevels);
        cereal::nvp(archive, "salesTariffDescription", salesTariffDescription);
        cereal::nvp(archive, "salesTariffEntry", salesTariffEntry);
    }
};

struct ChargingScheduleType
{
    ChargingRateUnitEnumType chargingRateUnit;
    schema_array<ChargingSchedulePeriodType,1024,1> chargingSchedulePeriod;
    optional<CustomDataType> customData;
    optional<int> duration;
    int id;
    optional<double> minChargingRate;
    optional<SalesTariffType> salesTariff;
    optional<schema_date_time> startSchedule;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "chargingRateUnit", chargingRateUnit);
        cereal::nvp(archive, "chargingSchedulePeriod", chargingSchedulePeriod);
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "duration", duration);
        cereal::nvp(archive, "id", id);
        cereal::nvp(archive, "minChargingRate", minChargingRate);
        cereal::nvp(archive, "salesTariff", salesTariff);
        cereal::nvp(archive, "startSchedule", startSchedule);
    }
};

struct ChargingProfileType
{
    ChargingProfileKindEnumType chargingProfileKind;
    ChargingProfilePurposeEnumType chargingProfilePurpose;
    schema_array<ChargingScheduleType,3,1> chargingSchedule;
    optional<CustomDataType> customData;
    int id;
    optional<RecurrencyKindEnumType> recurrencyKind;
    int stackLevel;
    optional<schema_string<36>> transactionId;
    optional<schema_date_time> validFrom;
    optional<schema_date_time> validTo;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "chargingProfileKind", chargingProfileKind);
        cereal::nvp(archive, "chargingProfilePurpose", chargingProfilePurpose);
        cereal::nvp(archive, "chargingSchedule", chargingSchedule);
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "id", id);
        cereal::nvp(archive, "recurrencyKind", recurrencyKind);
        cereal::nvp(archive, "stackLevel", stackLevel);
        cereal::nvp(archive, "transactionId", transactionId);
        cereal::nvp(archive, "validFrom", validFrom);
        cereal::nvp(archive, "validTo", validTo);
    }
};

struct SignedMeterValueType
{
    optional<CustomDataType> customData;
    schema_string<50> encodingMethod;
    schema_string<2500> publicKey;
    schema_string<2500> signedMeterData;
    schema_string<50> signingMethod;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "encodingMethod", encodingMethod);
        cereal::nvp(archive, "publicKey", publicKey);
        cereal::nvp(archive, "signedMeterData", signedMeterData);
        cereal::nvp(archive, "signingMethod", signingMethod);
    }
};

struct UnitOfMeasureType
{
    optional<CustomDataType> customData;
    optional<int> multiplier;
    optional<schema_string<20>> unit;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "multiplier", multiplier);
        cereal::nvp(archive, "unit", unit);
    }
};

struct SampledValueType
{
    optional<ReadingContextEnumType> context;
    optional<CustomDataType> customData;
    optional<LocationEnumType> location;
    optional<MeasurandEnumType> measurand;
    optional<PhaseEnumType> phase;
    optional<SignedMeterValueType> signedMeterValue;
    optional<UnitOfMeasureType> unitOfMeasure;
    double value;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "context", context);
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "location", location);
        cereal::nvp(archive, "measurand", measurand);
        cereal::nvp(archive, "phase", phase);
        cereal::nvp(archive, "signedMeterValue", signedMeterValue);
        cereal::nvp(archive, "unitOfMeasure", unitOfMeasure);
        cereal::nvp(archive, "value", value);
    }
};

struct MeterValueType
{
    optional<CustomDataType> customData;
    schema_array<SampledValueType,65536,1> sampledValue;
    schema_date_time timestamp;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "sampledValue", sampledValue);
        cereal::nvp(archive, "timestamp", timestamp);
    }
};

struct VariableType
{
    optional<CustomDataType> customData;
    optional<schema_string<50>> instance;
    schema_string<50> name;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "instance", instance);
        cereal::nvp(archive, "name", name);
    }
};

struct ComponentVariableType
{
    ComponentType component;
    optional<CustomDataType> customData;
    optional<VariableType> variable;

    template<typename Archive>
    void serialize(Archive& archive)
    {
        cereal::nvp(archive, "component", component);
        cereal::nvp(archive, "customData", customData);
        cereal::nvp(archive, "variable", variable);
    }
};



} } 

