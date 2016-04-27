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
 *  PatientDemographicsCoreData.cpp
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

#include "OSCLib/Data/OSCP/MDIB/PatientDemographicsCoreData.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/DateTime.h"
#include "OSCLib/Data/OSCP/MDIB/Measure.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

PatientDemographicsCoreData::PatientDemographicsCoreData() : data(Defaults::PatientDemographicsCoreData()) {
}

PatientDemographicsCoreData::operator CDM::PatientDemographicsCoreData() const {
	return *data;
}

PatientDemographicsCoreData::PatientDemographicsCoreData(const CDM::PatientDemographicsCoreData & object) : data(new CDM::PatientDemographicsCoreData(object)) {

}

PatientDemographicsCoreData::PatientDemographicsCoreData(const PatientDemographicsCoreData & object) : data(new CDM::PatientDemographicsCoreData(*object.data)) {

}

PatientDemographicsCoreData::~PatientDemographicsCoreData() {

}

void PatientDemographicsCoreData::copyFrom(const PatientDemographicsCoreData & object) {
	*data = *object.data;
}

PatientDemographicsCoreData & PatientDemographicsCoreData:: operator=(const PatientDemographicsCoreData & object) {
	copyFrom(object);
	return *this;
}


PatientDemographicsCoreData & PatientDemographicsCoreData::setGivenname(const std::string & value) {
	data->Givenname(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getGivenname(std::string & out) const {
	if (data->Givenname().present()) {
		out = ConvertFromCDM::convert(data->Givenname().get());
		return true;
	}
	return false;
}

std::string PatientDemographicsCoreData::getGivenname() const {
	return ConvertFromCDM::convert(data->Givenname().get());
}
	
bool PatientDemographicsCoreData::hasGivenname() const {
	return data->Givenname().present();
}
	
PatientDemographicsCoreData & PatientDemographicsCoreData::setFamilyname(const std::string & value) {
	data->Familyname(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getFamilyname(std::string & out) const {
	if (data->Familyname().present()) {
		out = ConvertFromCDM::convert(data->Familyname().get());
		return true;
	}
	return false;
}

std::string PatientDemographicsCoreData::getFamilyname() const {
	return ConvertFromCDM::convert(data->Familyname().get());
}
	
bool PatientDemographicsCoreData::hasFamilyname() const {
	return data->Familyname().present();
}
	
PatientDemographicsCoreData & PatientDemographicsCoreData::setBirthname(const std::string & value) {
	data->Birthname(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getBirthname(std::string & out) const {
	if (data->Birthname().present()) {
		out = ConvertFromCDM::convert(data->Birthname().get());
		return true;
	}
	return false;
}

std::string PatientDemographicsCoreData::getBirthname() const {
	return ConvertFromCDM::convert(data->Birthname().get());
}
	
bool PatientDemographicsCoreData::hasBirthname() const {
	return data->Birthname().present();
}
	
PatientDemographicsCoreData & PatientDemographicsCoreData::setTitle(const std::string & value) {
	data->Title(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getTitle(std::string & out) const {
	if (data->Title().present()) {
		out = ConvertFromCDM::convert(data->Title().get());
		return true;
	}
	return false;
}

std::string PatientDemographicsCoreData::getTitle() const {
	return ConvertFromCDM::convert(data->Title().get());
}
	
bool PatientDemographicsCoreData::hasTitle() const {
	return data->Title().present();
}
	
PatientDemographicsCoreData & PatientDemographicsCoreData::addMiddlename(const std::string & value) {
	data->Middlename().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> PatientDemographicsCoreData::getMiddlenames() const {
	std::vector<std::string> result;
	result.reserve(data->Middlename().size());
	for (const auto & value: data->Middlename()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void PatientDemographicsCoreData::clearMiddlenames() {
	data->Middlename().clear();
}

PatientDemographicsCoreData & PatientDemographicsCoreData::setSex(const Sex & value) {
	data->Sex(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getSex(Sex & out) const {
	if (data->Sex().present()) {
		out = ConvertFromCDM::convert(data->Sex().get());
		return true;
	}
	return false;
}

Sex PatientDemographicsCoreData::getSex() const {
	return ConvertFromCDM::convert(data->Sex().get());
}
	
bool PatientDemographicsCoreData::hasSex() const {
	return data->Sex().present();
}
	
PatientDemographicsCoreData & PatientDemographicsCoreData::setPatientType(const PatientType & value) {
	data->PatientType(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getPatientType(PatientType & out) const {
	if (data->PatientType().present()) {
		out = ConvertFromCDM::convert(data->PatientType().get());
		return true;
	}
	return false;
}

PatientType PatientDemographicsCoreData::getPatientType() const {
	return ConvertFromCDM::convert(data->PatientType().get());
}
	
bool PatientDemographicsCoreData::hasPatientType() const {
	return data->PatientType().present();
}
	
PatientDemographicsCoreData & PatientDemographicsCoreData::setDateOfBirth(const DateTime & value) {
	data->DateOfBirth(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getDateOfBirth(DateTime & out) const {
	if (data->DateOfBirth().present()) {
		out = ConvertFromCDM::convert(data->DateOfBirth().get());
		return true;
	}
	return false;
}

DateTime PatientDemographicsCoreData::getDateOfBirth() const {
	return ConvertFromCDM::convert(data->DateOfBirth().get());
}
	
bool PatientDemographicsCoreData::hasDateOfBirth() const {
	return data->DateOfBirth().present();
}
	
PatientDemographicsCoreData & PatientDemographicsCoreData::setHeight(const Measure & value) {
	data->Height(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getHeight(Measure & out) const {
	if (data->Height().present()) {
		out = ConvertFromCDM::convert(data->Height().get());
		return true;
	}
	return false;
}

Measure PatientDemographicsCoreData::getHeight() const {
	return ConvertFromCDM::convert(data->Height().get());
}
	
bool PatientDemographicsCoreData::hasHeight() const {
	return data->Height().present();
}
	
PatientDemographicsCoreData & PatientDemographicsCoreData::setWeight(const Measure & value) {
	data->Weight(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getWeight(Measure & out) const {
	if (data->Weight().present()) {
		out = ConvertFromCDM::convert(data->Weight().get());
		return true;
	}
	return false;
}

Measure PatientDemographicsCoreData::getWeight() const {
	return ConvertFromCDM::convert(data->Weight().get());
}
	
bool PatientDemographicsCoreData::hasWeight() const {
	return data->Weight().present();
}
	
PatientDemographicsCoreData & PatientDemographicsCoreData::setRace(const CodedValue & value) {
	data->Race(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getRace(CodedValue & out) const {
	if (data->Race().present()) {
		out = ConvertFromCDM::convert(data->Race().get());
		return true;
	}
	return false;
}

CodedValue PatientDemographicsCoreData::getRace() const {
	return ConvertFromCDM::convert(data->Race().get());
}
	
bool PatientDemographicsCoreData::hasRace() const {
	return data->Race().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
