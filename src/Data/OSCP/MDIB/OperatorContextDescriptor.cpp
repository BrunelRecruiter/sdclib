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
 *  OperatorContextDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/OperatorContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OperatorContextDescriptor::OperatorContextDescriptor() : data(Defaults::OperatorContextDescriptor()) {
}

OperatorContextDescriptor::operator CDM::OperatorContextDescriptor() const {
	return *data;
}

OperatorContextDescriptor::OperatorContextDescriptor(const CDM::OperatorContextDescriptor & object) : data(new CDM::OperatorContextDescriptor(object)) {

}

OperatorContextDescriptor::OperatorContextDescriptor(const OperatorContextDescriptor & object) : data(new CDM::OperatorContextDescriptor(*object.data)) {

}

OperatorContextDescriptor::~OperatorContextDescriptor() {

}

void OperatorContextDescriptor::copyFrom(const OperatorContextDescriptor & object) {
	*data = *object.data;
}

OperatorContextDescriptor & OperatorContextDescriptor:: operator=(const OperatorContextDescriptor & object) {
	copyFrom(object);
	return *this;
}


OperatorContextDescriptor & OperatorContextDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue OperatorContextDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool OperatorContextDescriptor::hasType() const {
	return data->Type().present();
}
	
OperatorContextDescriptor & OperatorContextDescriptor::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


std::string OperatorContextDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
OperatorContextDescriptor & OperatorContextDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter OperatorContextDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool OperatorContextDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
OperatorContextDescriptor & OperatorContextDescriptor::setIntendedUse(const IntendedUse & value) {
	data->IntendedUse(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextDescriptor::getIntendedUse(IntendedUse & out) const {
	if (data->IntendedUse().present()) {
		out = ConvertFromCDM::convert(data->IntendedUse().get());
		return true;
	}
	return false;
}

IntendedUse OperatorContextDescriptor::getIntendedUse() const {
	return ConvertFromCDM::convert(data->IntendedUse().get());
}
	
bool OperatorContextDescriptor::hasIntendedUse() const {
	return data->IntendedUse().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
