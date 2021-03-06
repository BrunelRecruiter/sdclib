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
 *  MdState.cpp
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

#include "SDCLib/Data/SDC/MDIB/MdState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"


namespace SDCLib {
namespace Data {
namespace SDC {


MdState::MdState(
) : data(Defaults::MdStateInit(
))
{}

MdState::operator CDM::MdState() const {
	return *data;
}

MdState::MdState(const CDM::MdState & object)
: data(new CDM::MdState(object))
{ }

MdState::MdState(const MdState & object)
: data(std::make_shared<CDM::MdState>(*object.data))
{ }

void MdState::copyFrom(const MdState & object) {
	data = std::make_shared<CDM::MdState>(*object.data);
}

MdState & MdState:: operator=(const MdState& object) {
	copyFrom(object);
	return *this;
}


MdState & MdState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool MdState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter MdState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool MdState::hasStateVersion() const {
	return data->getStateVersion().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

