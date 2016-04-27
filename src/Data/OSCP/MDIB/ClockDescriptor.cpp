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
 *  ClockDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/ClockDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/Duration.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

ClockDescriptor::ClockDescriptor() : data(Defaults::ClockDescriptor()) {
}

ClockDescriptor::operator CDM::ClockDescriptor() const {
	return *data;
}

ClockDescriptor::ClockDescriptor(const CDM::ClockDescriptor & object) : data(new CDM::ClockDescriptor(object)) {

}

ClockDescriptor::ClockDescriptor(const ClockDescriptor & object) : data(new CDM::ClockDescriptor(*object.data)) {

}

ClockDescriptor::~ClockDescriptor() {

}

void ClockDescriptor::copyFrom(const ClockDescriptor & object) {
	*data = *object.data;
}

ClockDescriptor & ClockDescriptor:: operator=(const ClockDescriptor & object) {
	copyFrom(object);
	return *this;
}


ClockDescriptor & ClockDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool ClockDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue ClockDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool ClockDescriptor::hasType() const {
	return data->Type().present();
}
	
ClockDescriptor & ClockDescriptor::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


std::string ClockDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
ClockDescriptor & ClockDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool ClockDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter ClockDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool ClockDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
ClockDescriptor & ClockDescriptor::setIntendedUse(const IntendedUse & value) {
	data->IntendedUse(ConvertToCDM::convert(value));
	return *this;
}

bool ClockDescriptor::getIntendedUse(IntendedUse & out) const {
	if (data->IntendedUse().present()) {
		out = ConvertFromCDM::convert(data->IntendedUse().get());
		return true;
	}
	return false;
}

IntendedUse ClockDescriptor::getIntendedUse() const {
	return ConvertFromCDM::convert(data->IntendedUse().get());
}
	
bool ClockDescriptor::hasIntendedUse() const {
	return data->IntendedUse().present();
}
	
ClockDescriptor & ClockDescriptor::setResolution(const Duration & value) {
	data->Resolution(ConvertToCDM::convert(value));
	return *this;
}

bool ClockDescriptor::getResolution(Duration & out) const {
	if (data->Resolution().present()) {
		out = ConvertFromCDM::convert(data->Resolution().get());
		return true;
	}
	return false;
}

Duration ClockDescriptor::getResolution() const {
	return ConvertFromCDM::convert(data->Resolution().get());
}
	
bool ClockDescriptor::hasResolution() const {
	return data->Resolution().present();
}
	
ClockDescriptor & ClockDescriptor::addTimeProtocol(const CodedValue & value) {
	data->TimeProtocol().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> ClockDescriptor::getTimeProtocols() const {
	std::vector<CodedValue> result;
	result.reserve(data->TimeProtocol().size());
	for (const auto & value: data->TimeProtocol()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void ClockDescriptor::clearTimeProtocols() {
	data->TimeProtocol().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
