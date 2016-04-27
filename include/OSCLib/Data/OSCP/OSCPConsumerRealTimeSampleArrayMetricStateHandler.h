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
 * OSCPConsumerRealTimeSampleArrayMetricStateHandler.h
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, roehser
 */

#ifndef INCLUDE_OSCLIB_DATA_OSCP_OSCPCONSUMERREALTIMESAMPLEARRAYMETRICSTATEHANDLER_H_
#define INCLUDE_OSCLIB_DATA_OSCP_OSCPCONSUMERREALTIMESAMPLEARRAYMETRICSTATEHANDLER_H_

#include "OSCLib/Data/OSCP/OSCPConsumerEventHandler.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPConsumerRealTimeSampleArrayMetricStateHandler: public OSCPConsumerEventHandler {
public:
	OSCPConsumerRealTimeSampleArrayMetricStateHandler() {}
	virtual ~OSCPConsumerRealTimeSampleArrayMetricStateHandler() {}

	typedef RealTimeSampleArrayMetricState StateType;

    /**
    * @brief Receive notifications about the state.
    *
    * @param state The state on which a notification event occurred.
    */
    virtual void onStateChanged(const RealTimeSampleArrayMetricState & state) = 0;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

#endif /* INCLUDE_OSCLIB_DATA_OSCP_OSCPCONSUMERREALTIMESAMPLEARRAYMETRICSTATEHANDLER_H_ */