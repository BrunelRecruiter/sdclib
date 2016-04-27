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
 *  ImagingProcedure.h
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

#ifndef IMAGINGPROCEDURE_H_
#define IMAGINGPROCEDURE_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class ImagingProcedure {
private:
	ImagingProcedure(const CDM::ImagingProcedure & object);
	operator CDM::ImagingProcedure() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	ImagingProcedure();
	ImagingProcedure(const ImagingProcedure & object);
	virtual ~ImagingProcedure();
    
    void copyFrom(const ImagingProcedure & object);
    ImagingProcedure & operator=(const ImagingProcedure & object);
    
    typedef CDM::ImagingProcedure WrappedType;

	ImagingProcedure & setAccessionIdentifier(const InstanceIdentifier & value);
	InstanceIdentifier getAccessionIdentifier() const;

	ImagingProcedure & setRequestedProcedureID(const InstanceIdentifier & value);
	InstanceIdentifier getRequestedProcedureID() const;

	ImagingProcedure & setStudyInstanceUID(const InstanceIdentifier & value);
	InstanceIdentifier getStudyInstanceUID() const;

	ImagingProcedure & setScheduledProcedureStepID(const InstanceIdentifier & value);
	InstanceIdentifier getScheduledProcedureStepID() const;

	ImagingProcedure & setModality(const CodedValue & value);
	CodedValue getModality() const;
	bool getModality(CodedValue & out) const;
	bool hasModality() const;

	ImagingProcedure & setProtocolCode(const CodedValue & value);
	CodedValue getProtocolCode() const;
	bool getProtocolCode(CodedValue & out) const;
	bool hasProtocolCode() const;

private:
	std::shared_ptr<CDM::ImagingProcedure> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* IMAGINGPROCEDURE_H_ */