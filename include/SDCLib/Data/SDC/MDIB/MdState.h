/**
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

/*
 *  MdState.h
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, buerger, roehser
 */

/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 *
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#ifndef MDSTATE_H_
#define MDSTATE_H_

#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/SDC-fwd.h"
#include "DataModel/osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class MdState
{
private:
	MdState(const CDM::MdState & object);
	operator CDM::MdState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdDescription;
public:
	MdState(
	);
	MdState(const MdState& object);
	virtual ~MdState() = default;

    void copyFrom(const MdState& object);
    MdState & operator=(const MdState& object);

    typedef CDM::MdState WrappedType;

	MdState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;


	// use this API function to get a copy of the MDIB's internal state
	template<class TState>
	std::unique_ptr<TState> findState(const std::string & handle) const;

	std::vector<ActivateOperationState> findActivateOperationStates() const;
	std::vector<AlertConditionState> findAlertConditionStates() const;
	std::vector<AlertSignalState> findAlertSignalStates() const;
	std::vector<AlertSystemState> findAlertSystemStates() const;
	std::vector<ClockState> findClockStates() const;
	std::vector<EnsembleContextState> findEnsembleContextStates() const;
	std::vector<EnumStringMetricState> findEnumStringMetricStates() const;
	std::vector<MdsState> findMdsStates() const;
	std::vector<LimitAlertConditionState> findLimitAlertConditionStates() const;
	std::vector<LocationContextState> findLocationContextStates() const;
	std::vector<NumericMetricState> findNumericMetricStates() const;
	std::vector<OperatorContextState> findOperatorContextStates() const;
	std::vector<PatientContextState> findPatientContextStates() const;
	std::vector<RealTimeSampleArrayMetricState> findRealTimeSampleArrayMetricStates() const;
	std::vector<StringMetricState> findStringMetricStates() const;
	std::vector<WorkflowContextState> findWorkflowContextStates() const;

    MdState & addState(const AlertConditionState & source);
    MdState & addState(const AlertSignalState & source);
    MdState & addState(const AlertSystemState & source);
    MdState & addState(const ClockState & source);
    MdState & addState(const EnsembleContextState & source);
    MdState & addState(const EnumStringMetricState & source);
    MdState & addState(const LocationContextState & source);
    MdState & addState(const LimitAlertConditionState & source);
    MdState & addState(const MdsState & source);
    MdState & addState(const MeansContextState & source);
    MdState & addState(const NumericMetricState & source);
    MdState & addState(const OperatorContextState & source);
    MdState & addState(const PatientContextState & source);
    MdState & addState(const RealTimeSampleArrayMetricState & source);
    MdState & addState(const DistributionSampleArrayMetricState & source);
    MdState & addState(const StringMetricState & source);
    MdState & addState(const WorkflowContextState & source);
    MdState & addState(const VmdState & source);
    MdState & addState(const ChannelState & source);
    MdState & addState(const ScoState & source);
	MdState & addState(const SystemContextState & source);
	MdState & addState(const ActivateOperationState & source);
	MdState & addState(const SetAlertStateOperationState & source);
	MdState & addState(const SetContextStateOperationState & source);
	MdState & addState(const SetStringOperationState & source);
	MdState & addState(const SetValueOperationState & source);


private:
    // these classes are for internal finding states in the MDIB
    // the initialize objects which reference is processed
	bool findState(const std::string & handle, ActivateOperationState & outState) const;
	bool findState(const std::string & handle, AlertConditionState & outState) const;
	bool findState(const std::string & handle, AlertSignalState & outState) const;
	bool findState(const std::string & handle, AlertSystemState & outState) const;
	bool findState(const std::string & handle, ClockState & outState) const;
	bool findState(const std::string & handle, EnsembleContextState & outState) const;
	bool findState(const std::string & handle, EnumStringMetricState & outState) const;
    bool findState(const std::string & handle, MdsState & outState) const;
	bool findState(const std::string & handle, LimitAlertConditionState & outState) const;
	bool findState(const std::string & handle, LocationContextState & outState) const;
	bool findState(const std::string & handle, NumericMetricState & outState) const;
	bool findState(const std::string & handle, OperatorContextState & outState) const;
	bool findState(const std::string & handle, PatientContextState & outState) const;
	bool findState(const std::string & handle, RealTimeSampleArrayMetricState & outState) const;
	bool findState(const std::string & handle, StringMetricState & outState) const;
	bool findState(const std::string & handle, WorkflowContextState & outState) const;
	bool findState(const std::string & handle, VmdState & outState) const;
	bool findState(const std::string & handle, ChannelState & outState) const;
	bool findState(const std::string & handle, ScoState & outState) const;
	bool findState(const std::string & handle, SystemContextState & outState) const;
	bool findState(const std::string & handle, SetAlertStateOperationState & outState) const;
	bool findState(const std::string & handle, SetContextStateOperationState & outState) const;
	bool findState(const std::string & handle, SetStringOperationState & outState) const;
	bool findState(const std::string & handle, SetValueOperationState & outState) const;

	template <class WrapperStateDescriptorType>
    bool findStateImpl(const std::string & handle, WrapperStateDescriptorType & out) const;

    template <class WrapperStateDescriptorType>
    MdState & addStateImpl(const WrapperStateDescriptorType & source);

    template <class WrapperStateDescriptorType, class ForbiddenType>
    std::vector<WrapperStateDescriptorType> findStatesImpl() const;
    template <class WrapperStateDescriptorType>
    std::vector<WrapperStateDescriptorType> findStatesImpl() const;
private:
	std::shared_ptr<CDM::MdState> data = nullptr;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* MDSTATE_H_ */
