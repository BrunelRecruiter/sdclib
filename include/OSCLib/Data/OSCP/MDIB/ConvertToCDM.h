/*
 * ConvertToCDM.h
 *
 *  Created on: 26.01.2015
 *      Author: roehser
 */

#ifndef DATA_OSCP_MDIB_CONVERTTOCDM_H_
#define DATA_OSCP_MDIB_CONVERTTOCDM_H_

#include "EnumMappings.h"
#include "MDIB-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class ConvertToCDM {
public:
	ConvertToCDM();
	virtual ~ConvertToCDM();

	static bool convert(const bool & source);
	static double convert(const double & source);
	static unsigned int convert(const unsigned int & source);
	static int convert(const int & source);
	static long convert(const long & source);
	static long long convert(const long long & source);
	static std::string convert(const std::string & source);
	static unsigned short int convert(const unsigned short int & source);

	static CDM::Activation convert(const Activation & source);
	static CDM::AlertConditionKind convert(const AlertConditionKind & source);
	static CDM::AlertConditionPriority convert(const AlertConditionPriority & source);
	static CDM::AlertSignalManifestation convert(const AlertSignalManifestation & source);
	static CDM::CalibrationState convert(const CalibrationState & source);
	static CDM::ComponentActivation convert(const ComponentActivation & source);
	static CDM::ContextAssociation convert(const ContextAssociation & source);
	static CDM::DICOMTransferRole convert(const DICOMTransferRole & source);
	static CDM::GenerationMode convert(const GenerationMode & source);
	static CDM::IntendedUse convert(const IntendedUse & source);
	static CDM::InvocationState convert(const InvocationState & source);
	static CDM::MetricAvailability convert(const MetricAvailability & source);
	static CDM::MetricCategory convert(const MetricCategory & source);
	static CDM::MetricMeasurementValidity convert(const MetricMeasurementValidity & source);
	static CDM::MetricRetrievability convert(const MetricRetrievability & source);
	static CDM::MonitoredAlertLimits convert(const MonitoredAlertLimits & source);
	static CDM::OperatingMode convert(const OperatingMode & source);
	static CDM::PatientType convert(const PatientType & source);
	static CDM::PausableActivation convert(const PausableActivation & source);
	static CDM::PrimaryAlertSignalLocation convert(const PrimaryAlertSignalLocation & source);
	static CDM::Sex convert(const Sex & source);
	static CDM::SignalPresence convert(const SignalPresence & source);

	template <class WrapperType>
	static std::unique_ptr<typename WrapperType::WrappedType> convert(const WrapperType & source);
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

#endif /* DATA_OSCP_MDIB_CONVERTTOCDM_H_ */
