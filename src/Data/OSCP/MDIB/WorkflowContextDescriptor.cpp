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
 *  WorkflowContextDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/WorkflowContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

WorkflowContextDescriptor::WorkflowContextDescriptor() : data(Defaults::WorkflowContextDescriptor()) {
}

WorkflowContextDescriptor::operator CDM::WorkflowContextDescriptor() const {
	return *data;
}

WorkflowContextDescriptor::WorkflowContextDescriptor(const CDM::WorkflowContextDescriptor & object) : data(new CDM::WorkflowContextDescriptor(object)) {

}

WorkflowContextDescriptor::WorkflowContextDescriptor(const WorkflowContextDescriptor & object) : data(new CDM::WorkflowContextDescriptor(*object.data)) {

}

WorkflowContextDescriptor::~WorkflowContextDescriptor() {

}

void WorkflowContextDescriptor::copyFrom(const WorkflowContextDescriptor & object) {
	*data = *object.data;
}

WorkflowContextDescriptor & WorkflowContextDescriptor:: operator=(const WorkflowContextDescriptor & object) {
	copyFrom(object);
	return *this;
}


WorkflowContextDescriptor & WorkflowContextDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue WorkflowContextDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool WorkflowContextDescriptor::hasType() const {
	return data->Type().present();
}
	
WorkflowContextDescriptor & WorkflowContextDescriptor::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


std::string WorkflowContextDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
WorkflowContextDescriptor & WorkflowContextDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter WorkflowContextDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool WorkflowContextDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
WorkflowContextDescriptor & WorkflowContextDescriptor::setIntendedUse(const IntendedUse & value) {
	data->IntendedUse(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextDescriptor::getIntendedUse(IntendedUse & out) const {
	if (data->IntendedUse().present()) {
		out = ConvertFromCDM::convert(data->IntendedUse().get());
		return true;
	}
	return false;
}

IntendedUse WorkflowContextDescriptor::getIntendedUse() const {
	return ConvertFromCDM::convert(data->IntendedUse().get());
}
	
bool WorkflowContextDescriptor::hasIntendedUse() const {
	return data->IntendedUse().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
