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
 * MDIBContainer.cpp
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#include "OSCLib/Data/OSCP/MDIB/AlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MdDescription.h"
#include "OSCLib/Data/OSCP/MDIB/custom/MdibContainer.h"
#include "OSCLib/Data/OSCP/MDIB/MdState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"

#include "osdm.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

MdibContainer::MdibContainer() :
		mddescription(new MdDescription()),
		mdstate(new MdState()),
		mdibVersion(0) {

}

MdibContainer::~MdibContainer() {

}

void MdibContainer::setMdDescription(const MdDescription & source) {
    *mddescription = source;
}

MdDescription MdibContainer::getMdDescription() const {
    return *mddescription;
}

void MdibContainer::setMdState(const MdState & source) {
    *mdstate = source;
}

MdState MdibContainer::getMdState() const {
    return *mdstate;
}

void MdibContainer::setMdibVersion(const unsigned long long int version) {
	mdibVersion = version;
}
unsigned long long int MdibContainer::getMdibVersion() const {
	return mdibVersion;
}

bool MdibContainer::findDescriptor(const std::string & handle, AlertConditionDescriptor & outDescriptor) const {
	return mddescription->findDescriptor(handle, outDescriptor);
}

bool MdibContainer::findDescriptor(const std::string & handle, AlertSignalDescriptor & outDescriptor) const {
	return mddescription->findDescriptor(handle, outDescriptor);
}

bool MdibContainer::findDescriptor(const std::string & handle, AlertSystemDescriptor & outDescriptor) const {
	return mddescription->findDescriptor(handle, outDescriptor);
}

bool MdibContainer::findDescriptor(const std::string & handle, LimitAlertConditionDescriptor & outDescriptor) const {
	return mddescription->findDescriptor(handle, outDescriptor);
}

bool MdibContainer::findDescriptor(const std::string & handle, EnumStringMetricDescriptor & outDescriptor) const {
	return mddescription->findDescriptor(handle, outDescriptor);
}

bool MdibContainer::findDescriptor(const std::string & handle, NumericMetricDescriptor & outDescriptor) const {
	return mddescription->findDescriptor(handle, outDescriptor);
}

bool MdibContainer::findDescriptor(const std::string & handle, StringMetricDescriptor & outDescriptor) const {
	return mddescription->findDescriptor(handle, outDescriptor);
}

bool MdibContainer::findDescriptor(const std::string & handle, RealTimeSampleArrayMetricDescriptor & outDescriptor) const {
	return mddescription->findDescriptor(handle, outDescriptor);
}

bool MdibContainer::findState(const std::string & handle, EnumStringMetricState & outState) const {
	return mdstate->findState(handle, outState);
}

bool MdibContainer::findState(const std::string & handle, NumericMetricState & outState) const {
	return mdstate->findState(handle, outState);
}

bool MdibContainer::findState(const std::string & handle, RealTimeSampleArrayMetricState & outState) const {
	return mdstate->findState(handle, outState);
}

bool MdibContainer::findState(const std::string & handle, StringMetricState & outState) const {
	return mdstate->findState(handle, outState);
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */