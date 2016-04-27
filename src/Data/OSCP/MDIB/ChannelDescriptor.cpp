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
 *  ChannelDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ProductionSpecification.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

ChannelDescriptor::ChannelDescriptor() : data(Defaults::ChannelDescriptor()) {
}

ChannelDescriptor::operator CDM::ChannelDescriptor() const {
	return *data;
}

ChannelDescriptor::ChannelDescriptor(const CDM::ChannelDescriptor & object) : data(new CDM::ChannelDescriptor(object)) {

}

ChannelDescriptor::ChannelDescriptor(const ChannelDescriptor & object) : data(new CDM::ChannelDescriptor(*object.data)) {

}

ChannelDescriptor::~ChannelDescriptor() {

}

void ChannelDescriptor::copyFrom(const ChannelDescriptor & object) {
	*data = *object.data;
}

ChannelDescriptor & ChannelDescriptor:: operator=(const ChannelDescriptor & object) {
	copyFrom(object);
	return *this;
}


ChannelDescriptor & ChannelDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue ChannelDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool ChannelDescriptor::hasType() const {
	return data->Type().present();
}
	
ChannelDescriptor & ChannelDescriptor::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


std::string ChannelDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
ChannelDescriptor & ChannelDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter ChannelDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool ChannelDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
ChannelDescriptor & ChannelDescriptor::setIntendedUse(const IntendedUse & value) {
	data->IntendedUse(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelDescriptor::getIntendedUse(IntendedUse & out) const {
	if (data->IntendedUse().present()) {
		out = ConvertFromCDM::convert(data->IntendedUse().get());
		return true;
	}
	return false;
}

IntendedUse ChannelDescriptor::getIntendedUse() const {
	return ConvertFromCDM::convert(data->IntendedUse().get());
}
	
bool ChannelDescriptor::hasIntendedUse() const {
	return data->IntendedUse().present();
}
	
ChannelDescriptor & ChannelDescriptor::addProductionSpecification(const ProductionSpecification & value) {
	data->ProductionSpecification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ProductionSpecification> ChannelDescriptor::getProductionSpecifications() const {
	std::vector<ProductionSpecification> result;
	result.reserve(data->ProductionSpecification().size());
	for (const auto & value: data->ProductionSpecification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void ChannelDescriptor::clearProductionSpecifications() {
	data->ProductionSpecification().clear();
}

ChannelDescriptor & ChannelDescriptor::setAlertSystem(const AlertSystemDescriptor & value) {
	data->AlertSystem(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelDescriptor::getAlertSystem(AlertSystemDescriptor & out) const {
	if (data->AlertSystem().present()) {
		out = ConvertFromCDM::convert(data->AlertSystem().get());
		return true;
	}
	return false;
}

AlertSystemDescriptor ChannelDescriptor::getAlertSystem() const {
	return ConvertFromCDM::convert(data->AlertSystem().get());
}
	
bool ChannelDescriptor::hasAlertSystem() const {
	return data->AlertSystem().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
