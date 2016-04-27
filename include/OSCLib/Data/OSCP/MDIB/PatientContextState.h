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
 *  PatientContextState.h
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

#ifndef PATIENTCONTEXTSTATE_H_
#define PATIENTCONTEXTSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class PatientContextState {
private:
	PatientContextState(const CDM::PatientContextState & object);
	operator CDM::PatientContextState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	PatientContextState();
	PatientContextState(const PatientContextState & object);
	virtual ~PatientContextState();
    
    void copyFrom(const PatientContextState & object);
    PatientContextState & operator=(const PatientContextState & object);
    
    typedef CDM::PatientContextState WrappedType;
    typedef PatientContextDescriptor DescriptorType;

	PatientContextState & setHandle(const std::string & value);
	std::string getHandle() const;
	bool getHandle(std::string & out) const;
	bool hasHandle() const;

	PatientContextState & setDescriptorHandle(const std::string & value);
	std::string getDescriptorHandle() const;

	PatientContextState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	PatientContextState & setContextAssociation(const ContextAssociation & value);
	ContextAssociation getContextAssociation() const;
	bool getContextAssociation(ContextAssociation & out) const;
	bool hasContextAssociation() const;

	PatientContextState & setBindingMDIBVersion(const ReferencedVersion & value);
	ReferencedVersion getBindingMDIBVersion() const;

	PatientContextState & setUnbindingMDIBVersion(const ReferencedVersion & value);
	ReferencedVersion getUnbindingMDIBVersion() const;
	bool getUnbindingMDIBVersion(ReferencedVersion & out) const;
	bool hasUnbindingMDIBVersion() const;

	PatientContextState & setBindingStartTime(const Timestamp & value);
	Timestamp getBindingStartTime() const;
	bool getBindingStartTime(Timestamp & out) const;
	bool hasBindingStartTime() const;

	PatientContextState & setBindingEndTime(const Timestamp & value);
	Timestamp getBindingEndTime() const;
	bool getBindingEndTime(Timestamp & out) const;
	bool hasBindingEndTime() const;

	PatientContextState & addValidator(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getValidators() const;
	void clearValidators();
	
	PatientContextState & addIdentification(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getIdentifications() const;
	void clearIdentifications();
	
	PatientContextState & setCoreData(const PatientDemographicsCoreData & value);
	PatientDemographicsCoreData getCoreData() const;
	bool getCoreData(PatientDemographicsCoreData & out) const;
	bool hasCoreData() const;

private:
	std::shared_ptr<CDM::PatientContextState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* PATIENTCONTEXTSTATE_H_ */