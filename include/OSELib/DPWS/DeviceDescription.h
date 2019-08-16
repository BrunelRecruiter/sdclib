/*
 * DeviceDescription.h
 *
 *  Created on: 11.12.2015
 *      Author: sebastian, matthias, baumeister
 *
 *      Contains information about the provider, to which the consumer connects to. All devices xAddresses are saved here (no validity check).
 *      The validity of the connection is checked in each get-method.
 *
 */

#ifndef OSELIB_DPWS_DEVICEDESCRIPTION_H_
#define OSELIB_DPWS_DEVICEDESCRIPTION_H_

#include <mutex>
#include <string>

#include <Poco/URI.h>
#include <Poco/Net/IPAddress.h>

#include "OSELib/Helper/WithLogger.h"


namespace OSELib
{
	namespace DPWS
	{
		using URIVector = std::vector<Poco::URI>;

		class DeviceDescription : public WithLogger
		{
		private:

			mutable std::mutex m_mutex_epr;
			mutable std::mutex m_mutex_IP;
			mutable std::mutex m_mutex_URIs;

			std::string m_epr;
			Poco::Net::IPAddress m_localIP;

			// there may be more than one streaming addresses for compatibility with other frameworks
			URIVector ml_streamMulticastURIs;
			URIVector ml_contextServiceURIs;
			URIVector ml_eventServiceURIs;
			URIVector ml_getServiceURIs;
			URIVector ml_setServiceURIs;
			URIVector ml_waveformEventReportURIs;
			URIVector ml_deviceURIs;

		public:

			DeviceDescription();
			// Special Member Functions
			DeviceDescription(const DeviceDescription& p_obj) = delete;
			DeviceDescription(DeviceDescription&& p_obj) = delete;
			DeviceDescription& operator=(const DeviceDescription& p_obj) = delete;
			DeviceDescription& operator=(DeviceDescription&& p_obj) = delete;
			~DeviceDescription() = default;

			bool checkURIsValidity(const Poco::URI & uri) const;

			std::string getEPR() const;
			void setEPR(const std::string & epr);

			Poco::Net::IPAddress getLocalIP() const;
			void setLocalIP(const Poco::Net::IPAddress & localIP);

			Poco::URI getDeviceURI() const;
			void addDeviceURI(const Poco::URI & uri);

			Poco::URI getContextServiceURI() const;
			void addContextServiceURI(const Poco::URI & uri);

			Poco::URI getEventServiceURI() const;
			void addStateEventReportServiceURI(const Poco::URI & uri);

			Poco::URI getGetServiceURI() const;
			void addGetServiceURI(const Poco::URI & uri);

			Poco::URI getSetServiceURI() const;
			void addSetServiceURI(const Poco::URI & uri);

			void addWaveformServiceURI(const Poco::URI & uri);
			Poco::URI getWaveformEventReportURI() const;

			void addStreamMulticastAddressURI(const Poco::URI & uri);
			URIVector getStreamMulticastAddressURIs() const;

		};

	} /* namespace DPWS */
} /* namespace OSELib */

#endif /* OSELIB_DPWS_DEVICEDESCRIPTION_H_ */
