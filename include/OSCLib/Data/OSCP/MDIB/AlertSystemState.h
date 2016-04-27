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
 *  AlertSystemState.h
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#ifndef ALERTSYSTEMSTATE_H_
#define ALERTSYSTEMSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class AlertSystemState {
private:
	AlertSystemState(const CDM::AlertSystemState & object);
	operator CDM::AlertSystemState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	AlertSystemState();
	AlertSystemState(const AlertSystemState & object);
	virtual ~AlertSystemState();
    
    void copyFrom(const AlertSystemState & object);
    AlertSystemState & operator=(const AlertSystemState & object);
    
    typedef CDM::AlertSystemState WrappedType;
    typedef AlertSystemDescriptor DescriptorType;
    typedef OSCPProviderAlertSystemStateHandler ProviderHandlerType;
    typedef OSCPConsumerAlertSystemStateHandler ConsumerHandlerType;

	AlertSystemState & setHandle(const std::string & value);
	std::string getHandle() const;
	bool getHandle(std::string & out) const;
	bool hasHandle() const;

	AlertSystemState & setDescriptorHandle(const std::string & value);
	std::string getDescriptorHandle() const;

	AlertSystemState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	AlertSystemState & setActivationState(const PausableActivation & value);
	PausableActivation getActivationState() const;

	AlertSystemState & setPresentPhysiologicalAlarmConditions(const AlertConditionReference & value);
	AlertConditionReference getPresentPhysiologicalAlarmConditions() const;
	bool getPresentPhysiologicalAlarmConditions(AlertConditionReference & out) const;
	bool hasPresentPhysiologicalAlarmConditions() const;

	AlertSystemState & setPresentTechnicalAlarmConditions(const AlertConditionReference & value);
	AlertConditionReference getPresentTechnicalAlarmConditions() const;
	bool getPresentTechnicalAlarmConditions(AlertConditionReference & out) const;
	bool hasPresentTechnicalAlarmConditions() const;

private:
	std::shared_ptr<CDM::AlertSystemState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ALERTSYSTEMSTATE_H_ */