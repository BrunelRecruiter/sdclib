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
 *  AlertSignalDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/AlertSignalDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Duration.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

AlertSignalDescriptor::AlertSignalDescriptor() : data(Defaults::AlertSignalDescriptor()) {
}

AlertSignalDescriptor::operator CDM::AlertSignalDescriptor() const {
	return *data;
}

AlertSignalDescriptor::AlertSignalDescriptor(const CDM::AlertSignalDescriptor & object) : data(new CDM::AlertSignalDescriptor(object)) {

}

AlertSignalDescriptor::AlertSignalDescriptor(const AlertSignalDescriptor & object) : data(new CDM::AlertSignalDescriptor(*object.data)) {

}

AlertSignalDescriptor::~AlertSignalDescriptor() {

}

void AlertSignalDescriptor::copyFrom(const AlertSignalDescriptor & object) {
	*data = *object.data;
}

AlertSignalDescriptor & AlertSignalDescriptor:: operator=(const AlertSignalDescriptor & object) {
	copyFrom(object);
	return *this;
}


AlertSignalDescriptor & AlertSignalDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue AlertSignalDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool AlertSignalDescriptor::hasType() const {
	return data->Type().present();
}
	
AlertSignalDescriptor & AlertSignalDescriptor::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


std::string AlertSignalDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
AlertSignalDescriptor & AlertSignalDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter AlertSignalDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool AlertSignalDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
AlertSignalDescriptor & AlertSignalDescriptor::setIntendedUse(const IntendedUse & value) {
	data->IntendedUse(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getIntendedUse(IntendedUse & out) const {
	if (data->IntendedUse().present()) {
		out = ConvertFromCDM::convert(data->IntendedUse().get());
		return true;
	}
	return false;
}

IntendedUse AlertSignalDescriptor::getIntendedUse() const {
	return ConvertFromCDM::convert(data->IntendedUse().get());
}
	
bool AlertSignalDescriptor::hasIntendedUse() const {
	return data->IntendedUse().present();
}
	
AlertSignalDescriptor & AlertSignalDescriptor::setConditionSignaled(const std::string & value) {
	data->ConditionSignaled(ConvertToCDM::convert(value));
	return *this;
}


std::string AlertSignalDescriptor::getConditionSignaled() const {
	return ConvertFromCDM::convert(data->ConditionSignaled());
}
	
AlertSignalDescriptor & AlertSignalDescriptor::setManifestation(const AlertSignalManifestation & value) {
	data->Manifestation(ConvertToCDM::convert(value));
	return *this;
}


AlertSignalManifestation AlertSignalDescriptor::getManifestation() const {
	return ConvertFromCDM::convert(data->Manifestation());
}
	
AlertSignalDescriptor & AlertSignalDescriptor::setLatching(const bool & value) {
	data->Latching(ConvertToCDM::convert(value));
	return *this;
}


bool AlertSignalDescriptor::getLatching() const {
	return ConvertFromCDM::convert(data->Latching());
}
	
AlertSignalDescriptor & AlertSignalDescriptor::setDefaultSignalGenerationDelay(const Duration & value) {
	data->DefaultSignalGenerationDelay(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getDefaultSignalGenerationDelay(Duration & out) const {
	if (data->DefaultSignalGenerationDelay().present()) {
		out = ConvertFromCDM::convert(data->DefaultSignalGenerationDelay().get());
		return true;
	}
	return false;
}

Duration AlertSignalDescriptor::getDefaultSignalGenerationDelay() const {
	return ConvertFromCDM::convert(data->DefaultSignalGenerationDelay().get());
}
	
bool AlertSignalDescriptor::hasDefaultSignalGenerationDelay() const {
	return data->DefaultSignalGenerationDelay().present();
}
	
AlertSignalDescriptor & AlertSignalDescriptor::setSignalDelegationSupported(const bool & value) {
	data->SignalDelegationSupported(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getSignalDelegationSupported(bool & out) const {
	if (data->SignalDelegationSupported().present()) {
		out = ConvertFromCDM::convert(data->SignalDelegationSupported().get());
		return true;
	}
	return false;
}

bool AlertSignalDescriptor::getSignalDelegationSupported() const {
	return ConvertFromCDM::convert(data->SignalDelegationSupported().get());
}
	
bool AlertSignalDescriptor::hasSignalDelegationSupported() const {
	return data->SignalDelegationSupported().present();
}
	
AlertSignalDescriptor & AlertSignalDescriptor::setAcknowledgementSupported(const bool & value) {
	data->AcknowledgementSupported(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getAcknowledgementSupported(bool & out) const {
	if (data->AcknowledgementSupported().present()) {
		out = ConvertFromCDM::convert(data->AcknowledgementSupported().get());
		return true;
	}
	return false;
}

bool AlertSignalDescriptor::getAcknowledgementSupported() const {
	return ConvertFromCDM::convert(data->AcknowledgementSupported().get());
}
	
bool AlertSignalDescriptor::hasAcknowledgementSupported() const {
	return data->AcknowledgementSupported().present();
}
	
AlertSignalDescriptor & AlertSignalDescriptor::setAcknowledgeTimeout(const Duration & value) {
	data->AcknowledgeTimeout(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getAcknowledgeTimeout(Duration & out) const {
	if (data->AcknowledgeTimeout().present()) {
		out = ConvertFromCDM::convert(data->AcknowledgeTimeout().get());
		return true;
	}
	return false;
}

Duration AlertSignalDescriptor::getAcknowledgeTimeout() const {
	return ConvertFromCDM::convert(data->AcknowledgeTimeout().get());
}
	
bool AlertSignalDescriptor::hasAcknowledgeTimeout() const {
	return data->AcknowledgeTimeout().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
