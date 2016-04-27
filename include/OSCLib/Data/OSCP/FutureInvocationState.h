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
 * FutureInvocationState.h
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, röhser
 */

#ifndef SRC_DATA_OSCP_FUTURETRANSACTIONSTATE_H_
#define SRC_DATA_OSCP_FUTURETRANSACTIONSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "Poco/Event.h"
#include "Poco/Mutex.h"

#include <map>
#include <memory>

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPConsumer;

class FutureInvocationState {
	friend class OSCPConsumer;
public:
	FutureInvocationState();
	virtual ~FutureInvocationState();

	bool waitReceived(InvocationState expected, int timeout);

	int getTransactionId() const;

private:
	void setEvent(InvocationState actual);

	int transactionId;
	OSCPConsumer * consumer;
	Poco::Mutex mutex;

	std::map<InvocationState, std::shared_ptr<Poco::Event>> invocationEvents;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

#endif /* SRC_DATA_OSCP_FUTURETRANSACTIONSTATE_H_ */