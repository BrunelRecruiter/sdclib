/*
 * ConvertFromCDM.h
 *
 *  Created on: 26.01.2015
 *      Author: roehser
 */

#ifndef DATA_OSCP_MDIB_CONVERTFROMCDM_H_
#define DATA_OSCP_MDIB_CONVERTFROMCDM_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/MDIB/MDIB-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class ConvertFromCDM {
public:
	ConvertFromCDM();
	virtual ~ConvertFromCDM();

	static bool convert(const bool & source);
	static double convert(const double & source);
	static unsigned int convert(const unsigned int & source);
	static unsigned short int convert(const unsigned short int & source);
	static int convert(const int & source);
	static long convert(const long & source);
	static long long convert(const long long & source);
	static std::string convert(const std::string & source);

	static Activation convert(const CDM::Activation & source);
	static ActivateOperationDescriptor convert(const CDM::ActivateOperationDescriptor & source);
	static AlertConditionDescriptor convert(const CDM::AlertConditionDescriptor & source);
	static AlertConditionKind convert(const CDM::AlertConditionKind & source);
	static AlertConditionPriority convert(const CDM::AlertConditionPriority & source);
	static AlertConditionReference convert(const CDM::AlertConditionReference & source);
	static AlertConditionState convert(const CDM::AlertConditionState & source);
	static AlertSignalDescriptor convert(const CDM::AlertSignalDescriptor & source);
	static AlertSignalManifestation convert(const CDM::AlertSignalManifestation & source);
	static AlertSignalState convert(const CDM::AlertSignalState & source);
	static AlertSystemDescriptor convert(const CDM::AlertSystemDescriptor & source);
	static AlertSystemState convert(const CDM::AlertSystemState & source);
	static Annotation convert(const CDM::Annotation & source);
	static Base64Binary convert(const CDM::Base64Binary & source);
	static BaseDemographics convert(const CDM::BaseDemographics & source);
	static CalibrationInfo convert(const CDM::CalibrationInfo & source);
	static CalibrationState convert(const CDM::CalibrationState & source);
	static CauseInfo convert(const CDM::CauseInfo & source);
	static ChannelDescriptor convert(const CDM::ChannelDescriptor & source);
	static ClinicalInfo convert(const CDM::ClinicalInfo & source);
	static ClockDescriptor convert(const CDM::ClockDescriptor & source);
	static ClockState convert(const CDM::ClockState & source);
	static CodedValue convert(const CDM::CodedValue & source);
	static ComponentActivation convert(const CDM::ComponentActivation & source);
	static ComponentState convert(const CDM::ComponentState & source);
	static ContextAssociation convert(const CDM::ContextAssociation & source);
	static DateTime convert(const CDM::DateTime & source);
	static DICOMDeviceDescriptor convert(const CDM::DICOMDeviceDescriptor & source);
	static DICOMNetworkAE convert(const CDM::DICOMNetworkAE & source);
	static DICOMNetworkConnection convert(const CDM::DICOMNetworkConnection & source);
	static DICOMTransferCapability convert(const CDM::DICOMTransferCapability & source);
	static DICOMTransferRole convert(const CDM::DICOMTransferRole & source);
	static Duration convert(const CDM::Duration & source);
	static EnsembleContextDescriptor convert(const CDM::EnsembleContextDescriptor & source);
	static EnsembleContextState convert(const CDM::EnsembleContextState & source);
	static EnumNomenRef convert(const CDM::EnumNomenRef & source);
	static EnumStringMetricDescriptor convert(const CDM::EnumStringMetricDescriptor & source);
	static EnumStringMetricState convert(const CDM::EnumStringMetricState & source);
	static GenerationMode convert(const CDM::GenerationMode & source);
	static HydraMDSDescriptor convert(const CDM::HydraMDSDescriptor & source);
	static HydraMDSState convert(const CDM::HydraMDSState & source);
	static ImagingProcedure convert(const CDM::ImagingProcedure & source);
	static InstanceIdentifier convert(const CDM::InstanceIdentifier & source);
	static IntendedUse convert(const CDM::IntendedUse & source);
	static InvocationState convert(const CDM::InvocationState & source);
	static Language convert(const CDM::Language & source);
	static LimitAlertConditionDescriptor convert(const CDM::LimitAlertConditionDescriptor & source);
	static LimitAlertConditionState convert(const CDM::LimitAlertConditionState & source);
	static LocalizedText convert(const CDM::LocalizedText & source);
	static LocationContextDescriptor convert(const CDM::LocationContextDescriptor & source);
	static LocationContextState convert(const CDM::LocationContextState & source);
	static MDDescription convert(const CDM::MDDescription & source);
	static MDState convert(const CDM::MDState & source);
	static Measure convert(const CDM::Measure & source);
	static MeasurementState convert(const CDM::MeasurementState & source);
	static MetricAvailability convert(const CDM::MetricAvailability & source);
	static MetricCategory convert(const CDM::MetricCategory & source);
	static MetricMeasurementValidity convert(const CDM::MetricMeasurementValidity & source);
	static MetricRetrievability convert(const CDM::MetricRetrievability & source);
	static MonitoredAlertLimits convert(const CDM::MonitoredAlertLimits & source);
	static NumericMetricDescriptor convert(const CDM::NumericMetricDescriptor & source);
	static NumericMetricState convert(const CDM::NumericMetricState & source);
	static NumericMetricValue convert(const CDM::NumericMetricValue & source);
	static OperatingMode convert(const CDM::OperatingMode & source);
	static OperationState convert(const CDM::OperationState & source);
	static OperatorContextDescriptor convert(const CDM::OperatorContextDescriptor & source);
	static OperatorContextState convert(const CDM::OperatorContextState & source);
	static Order convert(const CDM::Order & source);
	static OrderDetail convert(const CDM::OrderDetail & source);
	static PatientContextDescriptor convert(const CDM::PatientContextDescriptor & source);
	static PatientContextState convert(const CDM::PatientContextState & source);
	static PatientDemographicsCoreData convert(const CDM::PatientDemographicsCoreData & source);
	static PatientType convert(const CDM::PatientType & source);
	static PausableActivation convert(const CDM::PausableActivation & source);
	static PersonParticipation convert(const CDM::PersonParticipation & source);
	static PersonReference convert(const CDM::PersonReference & source);
	static PrimaryAlertSignalLocation convert(const CDM::PrimaryAlertSignalLocation & source);
	static ProductionSpecification convert(const CDM::ProductionSpecification & source);
	static Range convert(const CDM::Range & source);
	static RealTimeSampleArrayMetricDescriptor convert(const CDM::RealTimeSampleArrayMetricDescriptor & source);
	static RealTimeSampleArrayMetricState convert(const CDM::RealTimeSampleArrayMetricState & source);
	static RealTimeSampleArrayValue convert(const CDM::RealTimeSampleArrayValue & source);
	static ReferencedVersion convert(const CDM::ReferencedVersion & source);
	static RemedyInfo convert(const CDM::RemedyInfo & source);
	static RTValueType convert(const CDM::RTValueType & source);
	static SampleIndex convert(const CDM::SampleIndex & source);
	static SCODescriptor convert(const CDM::SCODescriptor & source);
	static SetAlertStateOperationDescriptor convert(const CDM::SetAlertStateOperationDescriptor & source);
	static SetContextOperationDescriptor convert(const CDM::SetContextOperationDescriptor & source);
	static SetRangeOperationDescriptor convert(const CDM::SetRangeOperationDescriptor & source);
	static SetStringOperationDescriptor convert(const CDM::SetStringOperationDescriptor & source);
	static SetValueOperationDescriptor convert(const CDM::SetValueOperationDescriptor & source);
	static Sex convert(const CDM::Sex & source);
	static SignalPresence convert(const CDM::SignalPresence & source);
	static StringMetricDescriptor convert(const CDM::StringMetricDescriptor & source);
	static StringMetricState convert(const CDM::StringMetricState & source);
	static StringMetricValue convert(const CDM::StringMetricValue & source);
	static SystemContext convert(const CDM::SystemContext & source);
	static SystemMetaData convert(const CDM::SystemMetaData & source);
	static Timestamp convert(const CDM::Timestamp & source);
	static TimeZone convert(const CDM::TimeZone & source);
	static VersionCounter convert(const CDM::VersionCounter & source);
	static VMDDescriptor convert(const CDM::VMDDescriptor & source);
	static WorkflowContextDescriptor convert(const CDM::WorkflowContextDescriptor & source);
	static WorkflowContextState convert(const CDM::WorkflowContextState & source);
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

#endif /* DATA_OSCP_MDIB_CONVERTFROMCDM_H_ */