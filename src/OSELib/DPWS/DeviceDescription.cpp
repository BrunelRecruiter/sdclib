/*
 * DeviceDescription.cpp
 *
 *  Created on: 11.12.2015
 *      Author: matthias, sebastian
 *
 *      contains information about the provider
 */

#include "OSELib/DPWS/DeviceDescription.h"


namespace OSELib {
namespace DPWS {

DeviceDescription::DeviceDescription() : WithLogger(Log::DISCOVERY) {

}

bool DeviceDescription::checkURIsValidity(const Poco::URI & uri) const {
	// Checks if a given URI is valid by trying to establish a connection
	try {
		Poco::Net::StreamSocket connection;
		connection.connect(Poco::Net::SocketAddress(uri.getHost(), uri.getPort()), Poco::Timespan(50000));
		return true;
	} catch (...) {
		log_debug([&] { return "Contacting xAddress failed: " + uri.toString(); });
		return false;
	}
}


std::string DeviceDescription::getEPR() const {
	return _epr;
}
void DeviceDescription::setEPR(const std::string & epr) {
	_epr = epr;
}

Poco::Net::IPAddress DeviceDescription::getLocalIP() const {
	return _localIP;
}
void DeviceDescription::setLocalIP(const Poco::Net::IPAddress & localIP) {
	_localIP = localIP;
}

Poco::URI DeviceDescription::getDeviceURI() const {
	return _deviceURI;
}
void DeviceDescription::setDeviceURI(const Poco::URI & uri) {
	_deviceURI = uri;
}

Poco::URI DeviceDescription::getContextServiceURI() const {
	for (const auto iter : _contextServiceURIs) {
		if (checkURIsValidity(iter)) {
			return iter;
		}
	}
	throw std::runtime_error("All ContextServiceURIs are not valid.");
}
void DeviceDescription::addContextServiceURI(const Poco::URI & uri) {
	_contextServiceURIs.push_back(uri);
}

Poco::URI DeviceDescription::getEventServiceURI() const {
	for (const auto iter : _eventServiceURIs) {
			if (checkURIsValidity(iter)) {
				return iter;
			}
		}
		throw std::runtime_error("All EventServiceURIs are not valid.");
}
void DeviceDescription::addEventServiceURI(const Poco::URI & uri) {
	_eventServiceURIs.push_back(uri);
}

Poco::URI DeviceDescription::getGetServiceURI() const {
	for (const auto iter : _getServiceURIs) {
		if (checkURIsValidity(iter)) {
			return iter;
		}
	}
	throw std::runtime_error("All GetServiceURIs are not valid.");
}
void DeviceDescription::addGetServiceURI(const Poco::URI & uri) {
	_getServiceURIs.push_back(uri);
}

Poco::URI DeviceDescription::getSetServiceURI() const {
	for (const auto iter : _setServiceURIs) {
		if (checkURIsValidity(iter)) {
			return iter;
		}
	}
	throw std::runtime_error("All SetServiceURIs are not valid.");
}
void DeviceDescription::addSetServiceURI(const Poco::URI & uri) {
	_setServiceURIs.push_back(uri);
}

void DeviceDescription::addWaveformEventReportURI(const Poco::URI & uri) {
	_waveformEventReportURIs.push_back(uri);
}

Poco::URI DeviceDescription::getWaveformEventReportURI() const {
	for (const auto iter : _waveformEventReportURIs) {
		if (checkURIsValidity(iter)) {
			return iter;
		}
	}
	throw std::runtime_error("All WaveformEventReportURIs are not valid.");
}

void DeviceDescription::addStreamMulticastAddressURI(const Poco::URI & uri) {
	_streamMulticastURIs.push_back(uri);
}

const std::list<Poco::URI>& DeviceDescription::getStreamMulticastAddressURIs() const {
	return _streamMulticastURIs;
}

DeviceDescription::~DeviceDescription() {

}

} /* namespace DPWS */
} /* namespace OSELib */
