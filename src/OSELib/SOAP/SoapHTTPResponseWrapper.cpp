/*
 * SoapHTTPResponseWrapper.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */
#include "OSELib/SOAP/SoapHTTPResponseWrapper.h"
#include "TCP/TCPBroadcastServerHandler.h"


namespace OSELib {
namespace SOAP {

SoapHTTPResponseWrapper::SoapHTTPResponseWrapper(
		Poco::Net::HTTPServerResponse & httpResponse,
		HTTPStatus httpStatus
		) :
	WithLogger(Log::HTTP),
	_httpResponse(httpResponse),
	_httpStatus(httpStatus)
{
}

void SoapHTTPResponseWrapper::send(const std::string & content) {

	if(Network::TCPBroadcastServerHandler::getInstance("127.0.0.1", 8000)->isStarted() && content != "")
	{
		Network::TCPBroadcastServerHandler::getInstance("127.0.0.1", 8000)->broadcastMessage(content);
	}

	log_debug([&] { return "Delivering http response: " + content; });
	_httpResponse.setStatus(_httpStatus);
	_httpResponse.setContentType("application/soap+xml");
	_httpResponse.setContentLength(content.size());
	_httpResponse.send() << content << std::flush;
}

} /* namespace SOAP */
} /* namespace OSELib */
