/*
 * DPWSDiscoveryClientSocketImpl.cpp
 *
 *  Created on: 11.12.2015, matthias
 *  Modified on: 26.11.2019, baumeister
 *
 */

#include "OSELib/DPWS/DPWSDiscoveryClientSocketImpl.h"
#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/DPWS/DPWSCommon.h"
#include "OSELib/Helper/BufferAdapter.h"

#include "SDCLib/SDCInstance.h"
#include "SDCLib/Config/NetworkConfig.h"

#include "DataModel/NormalizedMessageModel.hxx"

#include <Poco/Buffer.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/SocketNotification.h>

using namespace OSELib;
using namespace OSELib::DPWS;
using namespace OSELib::DPWS::Impl;

struct SendMulticastMessage : public Poco::Notification {
	SendMulticastMessage(const std::string & p_message)
	: m_content(p_message) {}
	const std::string m_content;
};

const MESSAGEMODEL::Envelope buildProbeMessage(const OSELib::DPWS::ProbeType & p_filter)
{
	MESSAGEMODEL::Envelope::HeaderType t_header;
	{
		t_header.setAction(probeUri);
		t_header.setTo(discoveryUri);
		t_header.setMessageID(xml_schema::Uri(SDCLib::SDCInstance::calcMSGID()));
	}
	MESSAGEMODEL::Envelope::BodyType t_body;
	{
		t_body.setProbe(p_filter);
	}

	return MESSAGEMODEL::Envelope(t_header, t_body);
}

const MESSAGEMODEL::Envelope buildResolveMessage(const OSELib::DPWS::ResolveType & p_filter)
{
	MESSAGEMODEL::Envelope::HeaderType t_header;
	{
		t_header.setAction(resolveUri);
		t_header.setTo(discoveryUri);
		t_header.setMessageID(xml_schema::Uri(SDCLib::SDCInstance::calcMSGID()));
	}
	MESSAGEMODEL::Envelope::BodyType t_body;
	{
		t_body.setResolve(p_filter);
	}

	return MESSAGEMODEL::Envelope(t_header, t_body);
}

DPWSDiscoveryClientSocketImpl::DPWSDiscoveryClientSocketImpl(
        SDCLib::Config::NetworkConfig_shared_ptr p_config,
		ByeNotificationDispatcher & p_byeDispatcher,
		HelloNotificationDispatcher & p_helloDispatcher,
		ProbeMatchNotificationDispatcher & p_probeMatchDispatcher,
		ResolveMatchNotificationDispatcher & p_resolveDispatcher)
: OSELib::Helper::WithLogger(Log::DISCOVERY)
, m_networkConfig(p_config)
, m_byeDispatcher(p_byeDispatcher)
, m_helloDispatcher(p_helloDispatcher)
, m_probeMatchDispatcher(p_probeMatchDispatcher)
, m_resolveDispatcher(p_resolveDispatcher)
, m_ipv4MulticastAddress(Poco::Net::SocketAddress(p_config->_getMulticastIPv4(), p_config->_getMulticastPortv4()))
, m_ipv6MulticastAddress(Poco::Net::SocketAddress(p_config->_getMulticastIPv6(), p_config->_getMulticastPortv6()))
{

    if (m_networkConfig->getIP4enabled())
    {
        // Create DiscoverySocket
        m_ipv4DiscoverySocket = Poco::Net::MulticastSocket(Poco::Net::IPAddress::Family::IPv4);

        // Add only interfaces bound to the SDCInstance
        if (m_networkConfig->isBound()) {
            // Bind DiscoverySocket

			// TODO: Poco::Net::IPAddress() returns 0.0.0.0 which doesnt allow fitlering by adapter refactor!
            auto t_ipv4BindingAddress = Poco::Net::SocketAddress(Poco::Net::IPAddress(), m_ipv4MulticastAddress.port());
            m_ipv4DiscoverySocket.bind(t_ipv4BindingAddress, m_SO_REUSEADDR_FLAG, m_SO_REUSEPORT_FLAG);
            // Add all interfaces
            for (auto t_interface : m_networkConfig->getNetworkInterfaces()) {
                try
                {
                    // Interface - Join group: Note: Fails if we enumerate a bridge that is already connected
                    m_ipv4DiscoverySocket.joinGroup(m_ipv4MulticastAddress.host(), t_interface->m_if);
                    // DatagramSocket
                    Poco::Net::DatagramSocket t_datagramSocket(Poco::Net::SocketAddress(t_interface->m_IPv4, m_ipv4DatagrammSocketPort), t_interface->SO_REUSEADDR_FLAG);
                    t_datagramSocket.setReusePort(t_interface->SO_REUSEPORT_FLAG);
                    t_datagramSocket.setBlocking(false);
                    m_reactor.addEventHandler(t_datagramSocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketReadable));
                    ml_socketSendMessageQueue[t_datagramSocket].clear();
                }
                catch (...) {
                    // todo fixme. This loop fails, when a network interface has serveral network addresses, i.e. 2 IPv6 global scoped addresses
                    log_error([&] { return "Something went wrong in binding to : " + t_interface->m_name; });
                    continue;
                }
            }
        }
        else {
            // Bind DiscoverySocket
            auto t_ipv4BindingAddress = Poco::Net::SocketAddress(Poco::Net::IPAddress(), m_ipv4MulticastAddress.port());
            m_ipv4DiscoverySocket.bind(t_ipv4BindingAddress, m_SO_REUSEADDR_FLAG, m_SO_REUSEPORT_FLAG);
            // Add all interfaces
            for (const auto & nextIf : Poco::Net::NetworkInterface::list()) {
                if (nextIf.supportsIPv4() && nextIf.address().isUnicast() && !nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv4).isLoopback()) {
                    try
                    {
                        // Interface - Join group: Note: Fails if we enumerate a bridge that is already connected
                        m_ipv4DiscoverySocket.joinGroup(m_ipv4MulticastAddress.host(), nextIf);
                        // DatagramSocket
                        Poco::Net::DatagramSocket t_datagramSocket(Poco::Net::SocketAddress(nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv4), m_ipv4DatagrammSocketPort), m_SO_REUSEADDR_FLAG);
                        t_datagramSocket.setReusePort(m_SO_REUSEPORT_FLAG);
                        t_datagramSocket.setBlocking(false);
                        m_reactor.addEventHandler(t_datagramSocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketReadable));
                        ml_socketSendMessageQueue[t_datagramSocket].clear();
                    }
                    catch (...) {
                        log_error([&] { return "Something went wrong in binding to : " + nextIf.adapterName(); });
                        continue;
                    }
                }
            }
        }
        // Nonblocking
        m_ipv4DiscoverySocket.setBlocking(false);
        // TTL
        m_ipv4DiscoverySocket.setTimeToLive(UPD_MULTICAST_TIMETOLIVE);
        // Add Ipv4 Socket EventHandler
        m_reactor.addEventHandler(m_ipv4DiscoverySocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable));
	}
    if (m_networkConfig->getIP6enabled())
    {
        // Create DiscoverySocket
        m_ipv6DiscoverySocket = Poco::Net::MulticastSocket(Poco::Net::IPAddress::Family::IPv6);

        // Add only interfaces bound to the SDCInstance
        if (m_networkConfig->isBound()) {
            // Bind DiscoverySocket
            auto t_ipv6BindingAddress = Poco::Net::SocketAddress(Poco::Net::IPAddress{ Poco::Net::IPAddress::Family::IPv6 }, m_ipv6MulticastAddress.port());
            m_ipv6DiscoverySocket.bind(t_ipv6BindingAddress, m_SO_REUSEADDR_FLAG, m_SO_REUSEPORT_FLAG);
            for (auto t_interface : m_networkConfig->getNetworkInterfaces()) {
                try {
                    // Interface - Join group: Note: Fails if we enumerate a bridge that is already connected
                    m_ipv6DiscoverySocket.joinGroup(m_ipv6MulticastAddress.host(), t_interface->m_if);
                    // DatagramSocket
                    Poco::Net::DatagramSocket t_datagramSocket(Poco::Net::SocketAddress(t_interface->m_IPv6, m_ipv6DatagrammSocketPort), t_interface->SO_REUSEADDR_FLAG);
                    t_datagramSocket.setReusePort(t_interface->SO_REUSEPORT_FLAG);
                    t_datagramSocket.setBlocking(false);
                    m_reactor.addEventHandler(t_datagramSocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketReadable));
                    ml_socketSendMessageQueue[t_datagramSocket].clear();
                }
                catch (...) {
                    // todo fixme. This loop fails, when a network interface has serveral network addresses, i.e. 2 IPv6 global scoped addresses
                    log_error([&] { return "Something went wrong in binding to : " + t_interface->m_name; });
                    continue;
                }
            }
        }
        else {
            // Bind DiscoverySocket
			auto t_ipv6BindingAddress = Poco::Net::SocketAddress(Poco::Net::IPAddress{ Poco::Net::IPAddress::Family::IPv6 }, m_ipv6MulticastAddress.port());
            m_ipv6DiscoverySocket.bind(t_ipv6BindingAddress, m_SO_REUSEADDR_FLAG, m_SO_REUSEPORT_FLAG);
            // Add all interfaces
            for (const auto & nextIf : Poco::Net::NetworkInterface::list()) {
                if (nextIf.supportsIPv6() && nextIf.address().isUnicast() && !nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv6).isLoopback()) {
                    try {
                        // Interface - Join group: Note: Fails if we enumerate a bridge that is already connected
                        m_ipv6DiscoverySocket.joinGroup(m_ipv6MulticastAddress.host(), nextIf);
                        // DatagramSocket
                        Poco::Net::DatagramSocket t_datagramSocket(Poco::Net::SocketAddress(nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv6), m_ipv6DatagrammSocketPort), m_SO_REUSEADDR_FLAG);
                        t_datagramSocket.setReusePort(m_SO_REUSEPORT_FLAG);
                        t_datagramSocket.setBlocking(false);
                        m_reactor.addEventHandler(t_datagramSocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketReadable));
                        ml_socketSendMessageQueue[t_datagramSocket].clear();
                    } catch (...) {
                        // todo fixme. This loop fails, when a network interface has serveral network addresses, i.e. 2 IPv6 global scoped addresses
                        log_error([&] { return "Something went wrong"; });
                    }
                }
            }
        }
        // Nonblocking
        m_ipv6DiscoverySocket.setBlocking(false);
        // TTL
        m_ipv6DiscoverySocket.setTimeToLive(UPD_MULTICAST_TIMETOLIVE);
        // Add Ipv6 Socket EventHandler
        m_reactor.addEventHandler(m_ipv6DiscoverySocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable));
    }

    // Start the Thread with the SocketReactor
	m_reactorThread.start(m_reactor);
}

DPWSDiscoveryClientSocketImpl::~DPWSDiscoveryClientSocketImpl()
{
	m_reactor.removeEventHandler(m_ipv4DiscoverySocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable));
	m_reactor.removeEventHandler(m_ipv6DiscoverySocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable));

    for (auto t_interface : m_networkConfig->getNetworkInterfaces()) {
        try
        {
            if (m_networkConfig->getIP4enabled()) { m_ipv4DiscoverySocket.leaveGroup(m_ipv4MulticastAddress.host(), t_interface->m_if); }
            if (m_networkConfig->getIP6enabled()) { m_ipv6DiscoverySocket.leaveGroup(m_ipv6MulticastAddress.host(), t_interface->m_if); }
        }
        catch (...) {
            // todo fixme. This loop fails, when a network interface has serveral network addresses, i.e. 2 IPv6 global scoped addresses
            log_error([&] { return "Some thing went wrong leaving : " + t_interface->m_name; });
            continue;
        }
    }

	for (auto & t_messagingSocketMapping : ml_socketSendMessageQueue)
	{
		m_reactor.removeEventHandler(t_messagingSocketMapping.first, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketReadable));
		m_reactor.removeEventHandler(t_messagingSocketMapping.first, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketWritable));
	}

	m_reactor.stop();
	m_reactorThread.join();
}

void DPWSDiscoveryClientSocketImpl::sendProbe(const ProbeType& p_filter)
{
	const MESSAGEMODEL::Envelope t_message(buildProbeMessage(p_filter));
	if (t_message.getHeader().getMessageID().present()) {
		m_messagingContext.registerMessageId(t_message.getHeader().getMessageID().get());
	}
	for (auto & t_socketQueue : ml_socketSendMessageQueue) {
		t_socketQueue.second.enqueueNotification(new SendMulticastMessage(serializeMessage(t_message)));
		m_reactor.addEventHandler(t_socketQueue.first, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketWritable));
	}
}

void DPWSDiscoveryClientSocketImpl::sendResolve(const ResolveType& p_filter)
{
	const MESSAGEMODEL::Envelope t_message(buildResolveMessage(p_filter));
	if (t_message.getHeader().getMessageID().present()) {
		m_messagingContext.registerMessageId(t_message.getHeader().getMessageID().get());
	}
	for (auto & t_socketQueue : ml_socketSendMessageQueue) {
		t_socketQueue.second.enqueueNotification(new SendMulticastMessage(serializeMessage(t_message)));
		m_reactor.addEventHandler(t_socketQueue.first, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketWritable));
	}
}

void DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable(Poco::Net::ReadableNotification * p_notification)
{
	const Poco::AutoPtr<Poco::Net::ReadableNotification> t_pNf(p_notification);
	Poco::Net::MulticastSocket t_socket(t_pNf->socket());
	const int t_available(t_socket.available());
	if (t_available == 0) {
		return;
	}

	Poco::Buffer<char> t_buf(t_available);
	Poco::Net::SocketAddress t_remoteAddr;
	const int t_received(t_socket.receiveFrom(t_buf.begin(), t_available, t_remoteAddr, 0));
	Helper::BufferAdapter t_adapter(t_buf, t_received);

	auto t_message(parseMessage(t_adapter));
	if (nullptr == t_message) {
		return;
	}

	if (! t_message->getHeader().getMessageID().present()) {
		return;
	}
	if (! m_messagingContext.registerMessageId(t_message->getHeader().getMessageID().get())) {
        log_debug([&] { return "DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable. registerMessageId failed!"; });
		return;
	}
	if (! t_message->getHeader().getAppSequence().present()) {
		return;
	}
	if (! m_messagingContext.registerAppSequence(t_message->getHeader().getAppSequence().get())) {
		return;
	}
	if (t_message->getBody().getHello().present()) {
		if (! verifyHello(*t_message)) {
			return;
		}
		m_helloDispatcher.dispatch(t_message->getBody().getHello().get());
	} else if (t_message->getBody().getBye().present()) {
		if (! verifyBye(*t_message)) {
			return;
		}
		m_byeDispatcher.dispatch(t_message->getBody().getBye().get());
	}
}

// for receiving the probe / resolve match messages that are send unicast
void DPWSDiscoveryClientSocketImpl::onDatagrammSocketReadable(Poco::Net::ReadableNotification * p_notification)
{
	const Poco::AutoPtr<Poco::Net::ReadableNotification> t_pNf(p_notification);
	Poco::Net::DatagramSocket t_socket(t_pNf->socket());
	const int t_available(t_socket.available());
	if (t_available == 0) {
		return;
	}

	Poco::Buffer<char> t_buf(t_available);
	Poco::Net::SocketAddress t_remoteAddr;
	const int t_received(t_socket.receiveFrom(t_buf.begin(), t_available, t_remoteAddr, 0));
	Helper::BufferAdapter t_adapter(t_buf, t_received);
	auto t_message(parseMessage(t_adapter));

	if (nullptr == t_message) {
		return;
	}
	if (t_message->getHeader().getMessageID().present()) {
		if (!m_messagingContext.registerMessageId(t_message->getHeader().getMessageID().get())) {
            log_debug([&] { return "DPWSDiscoveryClientSocketImpl::onDatagrammSocketReadable. registerMessageId failed!"; });
			return;
		}
	}
	if (t_message->getBody().getProbeMatches().present()) {
		const WS::DISCOVERY::ProbeMatchesType & probeMatches(t_message->getBody().getProbeMatches().get());
		for (const auto & probeMatch : probeMatches.getProbeMatch()) {
			m_probeMatchDispatcher.dispatch(probeMatch);
		}
	} else if (t_message->getBody().getResolveMatches().present()) {
		const WS::DISCOVERY::ResolveMatchesType & resolveMatches(t_message->getBody().getResolveMatches().get());
		if (resolveMatches.getResolveMatch().present()) {
			m_resolveDispatcher.dispatch(resolveMatches.getResolveMatch().get());
		}
	}
}

void DPWSDiscoveryClientSocketImpl::onDatagrammSocketWritable(Poco::Net::WritableNotification * p_notification)
{
	const Poco::AutoPtr<Poco::Net::WritableNotification> t_pNf(p_notification);
    // By Sebastian TTL
	// Poco::Net::DatagramSocket socket(pNf->socket());
    Poco::Net::MulticastSocket t_socket(t_pNf->socket());
    t_socket.setTimeToLive(OSELib::UPD_MULTICAST_TIMETOLIVE);

	const Poco::AutoPtr<Poco::Notification> t_rawMessage(ml_socketSendMessageQueue[t_socket].dequeueNotification());
	if (t_rawMessage.isNull()) {
		p_notification->source().removeEventHandler(t_socket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketWritable));
		return;
	}
	const Poco::AutoPtr<SendMulticastMessage> t_message(t_rawMessage.cast<SendMulticastMessage>());
	Poco::Net::SocketAddress t_multicastAddress(m_ipv4MulticastAddress);
	if (Poco::Net::IPAddress::Family::IPv6 == t_socket.address().family()) {
		t_multicastAddress = m_ipv6MulticastAddress;
	}

	t_socket.sendTo(t_message->m_content.c_str(), t_message->m_content.size(), t_multicastAddress, 0);
}

bool DPWSDiscoveryClientSocketImpl::verifyBye(const MESSAGEMODEL::Envelope & p_message)
{
	if (! p_message.getHeader().getMessageID().present()) {
		log_error([&] { return "Bye message: Missing MessageID."; });
		return false;
	}
	if (! p_message.getHeader().getAction().present()) {
		log_error([&] { return "Bye message: Missing Action."; });
		return false;
	}
	if (p_message.getHeader().getAction().get() != byeUri) {
		log_error([&] { return "Bye message: Invalid Action."; });
		return false;
	}
	if (! p_message.getHeader().getTo().present()) {
		log_error([&] { return "Bye message: Missing To."; });
		return false;
	}
	if (p_message.getHeader().getTo().get() != discoveryUri) {
		log_error([&] { return "Bye message: Invalid value of To."; });
		return false;
	}
	if (! p_message.getHeader().getAppSequence().present()) {
		log_error([&] { return "Bye message: Missing AppSequence."; });
		return false;
	}
	if (! p_message.getBody().getBye().present()) {
		log_error([&] { return "Bye message: Missing Body."; });
		return false;
	}
	if (p_message.getBody().getBye().get().getEndpointReference().getAddress() == "") {
		log_error([&] { return "Bye message: Empty EndpointReference."; });
		return false;
	}
	if (p_message.getHeader().getRelatesTo().present()) {
		log_error([&] { return "Bye message: RelatesTo field should not be present."; });
		return false;
	}
	return true;
}

bool DPWSDiscoveryClientSocketImpl::verifyHello(const MESSAGEMODEL::Envelope & p_message)
{
	if (! p_message.getHeader().getMessageID().present()) {
		log_error([&] { return "Hello message: Missing MessageID."; });
		return false;
	}
	if (! p_message.getHeader().getAction().present()) {
		log_error([&] { return "Hello message: Missing Action."; });
		return false;
	}
	if (p_message.getHeader().getAction().get() != helloUri) {
		log_error([&] { return "Hello message: Invalid Action."; });
		return false;
	}
	if (! p_message.getHeader().getTo().present()) {
		log_error([&] { return "Hello message: Missing To."; });
		return false;
	}
	if (p_message.getHeader().getTo().get() != discoveryUri) {
		log_error([&] { return "Hello message: Invalid value of To."; });
		return false;
	}
	if (! p_message.getHeader().getAppSequence().present()) {
		log_error([&] { return "Hello message: Missing AppSequence."; });
		return false;
	}
	if (! p_message.getBody().getHello().present()) {
		log_error([&] { return "Hello message: Missing body."; });
		return false;
	}
	if (p_message.getBody().getHello().get().getEndpointReference().getAddress() == "") {
		log_error([&] { return "Hello message: Empty EndpointReference."; });
		return false;
	}
	if (p_message.getHeader().getRelatesTo().present()) {
		log_error([&] { return "Hello message: RelatesTo field should not be present."; });
		return false;
	}

	return true;
}
