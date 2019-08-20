
#ifndef OSELIB_SDC_REPORTRAITS_H_
#define OSELIB_SDC_REPORTRAITS_H_

#include "osdm-fwd.hxx"

namespace OSELib {
namespace SDC {

struct DescriptionModificationReportTraits {
	typedef MDM::DescriptionModificationReport ReportType;
	static xml_schema::Qname MessageType();
	static std::string NotificationName();
	static xml_schema::Qname PortType();
	static std::string Action();
};

struct EpisodicAlertReportTraits {
	typedef MDM::EpisodicAlertReport ReportType;
	typedef IStateEventServiceEventSink Dispatcher;
	static xml_schema::Qname MessageType();
	static std::string NotificationName();
	static xml_schema::Qname PortType();
	static std::string Action();
	static void dispatch(Dispatcher & dispatcher, const ReportType & request);
};

struct EpisodicContextReportTraits {
	typedef MDM::EpisodicContextReport ReportType;
	typedef IContextServiceEventSink Dispatcher;
	static xml_schema::Qname MessageType();
	static std::string NotificationName();	
	static xml_schema::Qname PortType();
	static std::string Action();
	static void dispatch(Dispatcher & dispatcher, const ReportType & request);
};

struct EpisodicMetricReportTraits {
	typedef MDM::EpisodicMetricReport ReportType;
	typedef IStateEventServiceEventSink Dispatcher;
	static xml_schema::Qname MessageType();
	static std::string NotificationName();
	static xml_schema::Qname PortType();
	static std::string Action();
	static void dispatch(Dispatcher & dispatcher, const ReportType & request);
};

struct OperationInvokedReportTraits {
	typedef MDM::OperationInvokedReport ReportType;
	typedef ISetServiceEventSink Dispatcher;
	static xml_schema::Qname MessageType();
	static std::string NotificationName();
	static xml_schema::Qname PortType();
	static std::string Action();
	static void dispatch(Dispatcher & dispatcher, const ReportType & request);
};

struct PeriodicAlertReportTraits {
	typedef MDM::PeriodicAlertReport ReportType;
	typedef IStateEventServiceEventSink Dispatcher;
	static xml_schema::Qname MessageType();
	static std::string NotificationName();
	static xml_schema::Qname PortType();
	static std::string Action();
	static void dispatch(Dispatcher & dispatcher, const ReportType & request);
};

struct PeriodicContextReportTraits {
	typedef MDM::PeriodicContextReport ReportType;
	typedef IContextServiceEventSink Dispatcher;
	static xml_schema::Qname MessageType();
	static std::string NotificationName();	
	static xml_schema::Qname PortType();
	static std::string Action();
	static void dispatch(Dispatcher & dispatcher, const ReportType & request);
};

struct PeriodicMetricReportTraits {
	typedef MDM::PeriodicMetricReport ReportType;
	typedef IStateEventServiceEventSink Dispatcher;
	static xml_schema::Qname MessageType();
	static std::string NotificationName();
	static xml_schema::Qname PortType();
	static std::string Action();
	static void dispatch(Dispatcher & dispatcher, const ReportType & request);
};

struct WaveformStreamTraits {
	typedef MDM::WaveformStream ReportType;
	typedef IStateEventServiceEventSink Dispatcher;
	static xml_schema::Qname MessageType();
	static std::string NotificationName();
	static xml_schema::Qname PortType();
	static std::string Action();
	static void dispatch(Dispatcher & dispatcher, const ReportType & request);
};

}
}
#endif /* OSELIB_SDC_REPORTRAITS_H_ */
