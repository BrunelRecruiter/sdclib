
#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/FutureInvocationState.h"
#include "OSCLib/Data/OSCP/OSCPConsumerEventHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerEnumStringMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerNumericMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerStringMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerAlertSignalStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerContextStateChangedHandler.h"
#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Data/OSCP/OSCPProviderActivateOperationHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderLimitAlertConditionStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderAlertSignalStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderAlertSystemStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderContextStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderComponentStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderEnumStringMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderHydraMDSStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderNumericMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderStringMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPServiceManager.h"
#include "OSCLib/Data/OSCP/MDIB/ActivateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemState.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/ComponentState.h"
#include "OSCLib/Data/OSCP/MDIB/DateTime.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/HydraMDSDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/HydraMDSState.h"
#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextState.h"
#include "OSCLib/Data/OSCP/MDIB/MDDescription.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/OperationInvocationContext.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextState.h"
#include "OSCLib/Data/OSCP/MDIB/PatientDemographicsCoreData.h"
#include "OSCLib/Data/OSCP/MDIB/Range.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContext.h"
#include "OSCLib/Data/OSCP/MDIB/SystemMetaData.h"
#include "OSCLib/Data/OSCP/MDIB/VMDDescriptor.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/Task.h"
#include "../AbstractOSCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"

#include "Poco/Event.h"
#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"

using namespace OSCLib;
using namespace OSCLib::Util;
using namespace OSCLib::Data::OSCP;

namespace OSCLib {
namespace Tests {
namespace SimpleOSCP {

const std::string DEVICE_ENDPOINT_REFERENCE("EPR_1234");
const std::string DEVICE_UDI("UDI_1234");
const int DEFAULT_TIMEOUT(5000);

const std::string MDS_HANDLE("sampleMDS");
const std::string VMD_DESCRIPTOR_HANDLE("vmd_descriptor");
const std::string CHANNEL_DESCRIPTOR_HANDLE("first_channel");

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Consumer event handlers
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ExampleConsumerNumericHandler : public OSCPConsumerNumericMetricStateHandler {
public:
	ExampleConsumerNumericHandler(const std::string & handle) :
    	weight(0),
		handle(handle)
	{
	}

    virtual ~ExampleConsumerNumericHandler() {

    }

    void onStateChanged(const NumericMetricState & state) override {
        double val = state.getObservedValue().getValue();
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Consumer: Received value changed of " << handle << ": " << val << std::endl;
    	Poco::Mutex::ScopedLock lock(mutex);
        weight = (float)val;
        eventEMR.set();
    }

    void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) override {
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Consumer: Received operation invoked (ID, STATE) of " << handle << ": " << oic.transactionId << ", " << EnumToString::convert(is) << std::endl;
    }

    std::string getHandle() override {
        return handle;
    }

    float getWeight() {
    	Poco::Mutex::ScopedLock lock(mutex);
    	float result(weight);
        return result;
    }

	Poco::Event & getEventEMR() {
		return eventEMR;
	}

private:
    Poco::Mutex mutex;
    float weight;
    const std::string handle;
    Poco::Event eventEMR;
};

class ExampleConsumerEnumStringMetricHandler : public OSCPConsumerEnumStringMetricStateHandler {
public:
	ExampleConsumerEnumStringMetricHandler(const std::string & handle) :
		handle(handle)
	{
	}

    virtual ~ExampleConsumerEnumStringMetricHandler() {

    }

    void onStateChanged(const EnumStringMetricState & state) override {
    	const std::string val(state.getObservedValue().getValue());
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Consumer: Received value changed of " << handle << ": " << val << std::endl;
        eventEMR.set();
    }

    void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) override {
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Consumer: Received operation invoked (ID, STATE) of " << handle << ": " << oic.transactionId << ", " << EnumToString::convert(is) << std::endl;
    }

    std::string getHandle() override {
        return handle;
    }

	Poco::Event & getEventEMR() {
		return eventEMR;
	}

private:
    const std::string handle;
    Poco::Event eventEMR;
};

class ExampleConsumerStringMetricHandler : public OSCPConsumerStringMetricStateHandler {
public:
	ExampleConsumerStringMetricHandler(const std::string & handle) :
		handle(handle)
	{
	}

    virtual ~ExampleConsumerStringMetricHandler() {

    }

    void onStateChanged(const StringMetricState & state) override {
    	const std::string val(state.getObservedValue().getValue());
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Consumer: Received value changed of " << handle << ": " << val << std::endl;
        eventEMR.set();
    }

    void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) override {
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Consumer: Received operation invoked (ID, STATE) of " << handle << ": " << oic.transactionId << ", " << EnumToString::convert(is) << std::endl;
    }

    std::string getHandle() override {
        return handle;
    }

	Poco::Event & getEventEMR() {
		return eventEMR;
	}

private:
    const std::string handle;
    Poco::Event eventEMR;
};

class ExampleConsumerAlertSignalHandler : public OSCPConsumerAlertSignalStateHandler {
public:
	ExampleConsumerAlertSignalHandler(const std::string & handle) :
		handle(handle)
	{
	}

    virtual ~ExampleConsumerAlertSignalHandler() {

    }

    void onStateChanged(const AlertSignalState & state) override {
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Consumer: Received alert signal changed of " << handle << ", presence = " << EnumToString::convert(state.getPresence()) << std::endl;
        if (state.getPresence() == SignalPresence::Off) {
        	eventEAROff.set();
        }
        if (state.getPresence() == SignalPresence::On) {
        	eventEAROn.set();
        }
        if (state.getPresence() == SignalPresence::Latch) {
        	eventEARLatch.set();
        }
    }

    void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) override {
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Consumer: Received operation invoked (ID, STATE) of " << handle << ": " << oic.transactionId << ", " << EnumToString::convert(is) << std::endl;
    }

    std::string getHandle() override {
        return handle;
    }

	Poco::Event & getEventEAROff() {
		return eventEAROff;
	}

	Poco::Event & getEventEAROn() {
		return eventEAROn;
	}

	Poco::Event & getEventEARLatch() {
		return eventEARLatch;
	}

private:
    const std::string handle;
    Poco::Event eventEAROff;
    Poco::Event eventEAROn;
    Poco::Event eventEARLatch;
};

class ContextEventHandler : public OSCPConsumerContextStateChangedHandler {
public:

	ContextEventHandler(const std::vector<std::string> & handles) : _handles(handles) {
	}

	virtual void onContextStateChanged(const std::vector<std::string> & handles) override {
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Consumer: Received context values changed!" << std::endl;
        if (handles.size() > 0) {
        	if (std::find(_handles.begin(), _handles.end(), handles.front()) != _handles.end()) {
        		eventEMR.set();
        	}
        }
	}

	Poco::Event & getEventEMR() {
		return eventEMR;
	}

private:
	Poco::Event eventEMR;
	const std::vector<std::string> _handles;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Provider handlers
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


class ContextHandler : public OSCPProviderContextStateHandler {
public:
	ContextHandler() {
	}

	virtual InvocationState onStateChangeRequest(
		const std::vector<EnsembleContextState> & ,
		const std::vector<LocationContextState> & lcStates,
		const std::vector<OperatorContextState> & ,
		const std::vector<PatientContextState> & pcStates,
		const std::vector<WorkflowContextState> & ,
		const OperationInvocationContext & ) override {

		if (lcStates.empty() && pcStates.empty()) {
			return InvocationState::FAILED;
		}

		if ((lcStates.size() > 0 && lcStates[0].getDescriptorHandle() != "location_context")
			|| (pcStates.size() > 0 && pcStates[0].getDescriptorHandle() != "patient_context")) {
			return InvocationState::FAILED;
		}

		DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: ContextHandler received state change request" << std::endl;
		if (lcStates.size() > 0) {
            updateState(lcStates[0]);
		}
		if (pcStates.size() > 0) {
            updateState(pcStates[0]);
        }
	    return InvocationState::FINISHED;
	}

    // Get inital states
	virtual std::vector<LocationContextState> getLocationContextStates() override {
        LocationContextState locationState;
        // This device magically knows its location
        locationState
            .setHandle("location_context_state")
            .setDescriptorHandle("location_context")
            .addIdentification(
            InstanceIdentifier()
            .setroot("MyHospital")
            .setextension("Room 23")
            );
		std::vector<LocationContextState> result;
		result.push_back(locationState);
		return result;
	}

    // Get inital states
    virtual std::vector<PatientContextState> getPatientContextStates() override {
        PatientContextState patientState;
        patientState
            .setHandle("patient_context_state")
            .setDescriptorHandle("patient_context")
            .addIdentification(
            InstanceIdentifier()
            .setroot("max")
            .setextension("mustermann")
            );
        std::vector<PatientContextState> result;
		result.push_back(patientState);
		return result;
	}

};

class MaxValueStateHandler : public OSCPProviderNumericMetricStateHandler {
public:

    MaxValueStateHandler() {
    }

    InvocationState onStateChangeRequest(const NumericMetricState & state, const OperationInvocationContext & oic) override {
        // Invocation has been fired as WAITING when entering this method
    	DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: MaxValueStateHandler received state change request" << std::endl;

    	notifyOperationInvoked(oic, InvocationState::STARTED);

        // we can update here, but if we return FINISHED, the framework will also update
        //updateState(state);

        // Usually, update the real device's state here.

        return InvocationState::FINISHED;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // Helper method
    NumericMetricState createState() {
        NumericMetricState result;
        result
            .setObservedValue(NumericMetricValue().setValue(2.0))
            .setComponentActivationState(ComponentActivation::ON)
            .setDescriptorHandle("handle_max")
            .setHandle("handle_max_state");
        return result;
    }

    NumericMetricState getInitialState() override {
        NumericMetricState result = createState();
        return result;
    }

    // Convenience value getter
    float getMaxWeight() {
        NumericMetricState result;
        // TODO: in real applications, check if findState returns true!
        getParentProvider().getMDState().findState("handle_max", result);
        // TODO: in real applications, check if state has an observed value and if the observed value has a value!
        return (float)result.getObservedValue().getValue();
    }

};

class CurValueStateHandler : public OSCPProviderNumericMetricStateHandler {
public:

    CurValueStateHandler() {
    }

    // onStateChangeRequest not implemented (state is read-only - MEASUREMENT)

    // Helper method
    NumericMetricState createState(float value) {
        NumericMetricState result;
        result
            .setObservedValue(NumericMetricValue().setValue(value))
            .setComponentActivationState(ComponentActivation::ON)
            .setDescriptorHandle("handle_cur");
        return result;
    }

    NumericMetricState getInitialState() override {
        return createState(0);
    }

    void setNumericValue(float value) {
        NumericMetricState currentWeightState = createState(value);
        // Call update function (this will update internal MDIB and increase MDIB version number)
        updateState(currentWeightState);
    }

};

class EnumStringMetricStateHandler : public OSCPProviderEnumStringMetricStateHandler {
public:

	EnumStringMetricStateHandler() {
    }

    InvocationState onStateChangeRequest(const EnumStringMetricState & state, const OperationInvocationContext & oic) override {
        // Invocation has been fired as WAITING when entering this method
    	DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: EnumStringMetricStateHandler received state change request" << std::endl;
    	notifyOperationInvoked(oic, InvocationState::STARTED);

        // we can update here, but if we return FINISHED, the framework will also notify
        //updateState(currentStringState);

        // Usually, update the real device's state here.

        return InvocationState::FINISHED;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // Helper method
    EnumStringMetricState createState(const std::string & value) {
        EnumStringMetricState result;
        result
            .setObservedValue(StringMetricValue().setValue(value))
            .setComponentActivationState(ComponentActivation::ON)
            .setDescriptorHandle("handle_enum")
            .setHandle("handle_enum_state");
        return result;
    }

    EnumStringMetricState getInitialState() override {
        return createState("hello");
    }

};

class StrValueStateHandler : public OSCPProviderStringMetricStateHandler {
public:

    StrValueStateHandler() {
    }

    InvocationState onStateChangeRequest(const StringMetricState & state, const OperationInvocationContext & oic) override {
        // Invocation has been fired as WAITING when entering this method
    	DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: StrValueStateHandler received state change request" << std::endl;
    	notifyOperationInvoked(oic, InvocationState::STARTED);

        // we can update here, but if we return FINISHED, the framework will also notify
        //updateState(currentStringState);

        // Usually, update the real device's state here.

        return InvocationState::FINISHED;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // Helper method
    StringMetricState createState(const std::string & value) {
        StringMetricState result;
        result
            .setObservedValue(StringMetricValue().setValue(value))
            .setComponentActivationState(ComponentActivation::ON)
            .setDescriptorHandle("handle_str");
        return result;
    }

    StringMetricState getInitialState() override {
        return createState("Test");
    }

    // Convenience setter
    void setStringValue(const std::string & value) {
        StringMetricState currentState = createState(value);
        updateState(currentState);
    }

};

class AlertSignalStateHandler : public OSCPProviderAlertSignalStateHandler {
public:

	AlertSignalStateHandler() {
    }

    InvocationState onStateChangeRequest(const AlertSignalState & state, const OperationInvocationContext & oic) override {
        // Invocation has been fired as WAITING when entering this method
    	DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: AlertSignalStateHandler received state change: " << EnumToString::convert(state.getPresence()) << std::endl;

    	notifyOperationInvoked(oic, InvocationState::STARTED);

    	// Update the real device's state here (update device alarms)! Check state's presence and alertSignalState's presence values!

    	// we can update here, but if we return FINISHED, the framework will also notify
    	//updateState(alertSignalState);

        return InvocationState::FINISHED;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // Helper method
    AlertSignalState createState() {
        AlertSignalState result;
        result
            .setDescriptorHandle("handle_alert_signal")  // Reference alert signal descriptor's handle
            .setActivationState(PausableActivation::ON)  // Component is working
            .setPresence(SignalPresence::Off);  // No alarm signal
        return result;
    }

    AlertSignalState getInitialState() override {
        return createState();
    }

};

class LatchingAlertSignalStateHandler : public OSCPProviderAlertSignalStateHandler {
public:

	LatchingAlertSignalStateHandler() {
    }

    InvocationState onStateChangeRequest(const AlertSignalState & state, const OperationInvocationContext & oic) override {
        // Invocation has been fired as WAITING when entering this method
    	DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: LatchingAlertSignalStateHandler received state change: " << EnumToString::convert(state.getPresence()) << std::endl;

    	notifyOperationInvoked(oic, InvocationState::STARTED);

    	// Update the real device's state here (update device alarms)! Check state's presence and alertSignalState's presence values!

    	// we can update here, but if we return FINISHED, the framework will also notify
    	//updateState(alertSignalState);

        return InvocationState::FINISHED;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // Helper method
    AlertSignalState createState() {
        AlertSignalState result;
        result
            .setDescriptorHandle("handle_alert_signal_latching")  // Reference alert signal descriptor's handle
            .setActivationState(PausableActivation::ON)  // Component is working
            .setPresence(SignalPresence::Off);  // No alarm signal
        return result;
    }

    AlertSignalState getInitialState() override {
        return createState();
    }



};

class LimitAlertConditionStateHandler : public OSCPProviderLimitAlertConditionStateHandler {
public:

	LimitAlertConditionStateHandler() 
	{
	}

    InvocationState onStateChangeRequest(const LimitAlertConditionState & state, const OperationInvocationContext & ) override {
        // Invocation has been fired as WAITING when entering this method
        LimitAlertConditionState currentState;
        getParentProvider().getMDState().findState(state.getDescriptorHandle(), currentState);

    	DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: LimitAlertConditionStateHandler received state change, presence = " << state.getPresence() << std::endl;
        if (state.getPresence() != currentState.getPresence()) {
    		DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: LimitAlertConditionStateHandler detected presence change to: " << state.getPresence() << std::endl;
    		// do something...
    	}

    	// we can update here, but if we return FINISHED, the framework will also notify
    	//updateState(limitAlertConditionState);

    	return InvocationState::FINISHED;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    void sourceHasChanged(const std::string & sourceHandle) override {
    	DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: LimitAlertConditionStateHandler monitored source state changed." << std::endl;

    	// Check limit and trigger alarm condition, if needed (this method will then take care of handling all signal states)
        NumericMetricState sourceState;
        getParentProvider().getMDState().findState(sourceHandle, sourceState);
        LimitAlertConditionState limitAlertConditionState;
        getParentProvider().getMDState().findState("handle_alert_condition", limitAlertConditionState);
    	if (sourceState.getDescriptorHandle() != sourceHandle) {
    		return;
    	}
    	if (!sourceState.hasObservedValue()) {
    		return;
    	}
    	const auto sourceValue(sourceState.getObservedValue());
    	if (!sourceValue.hasValue()) {
    		return;
    	}
    	if (!limitAlertConditionState.hasLimits()) {
    		return;
    	}
    	const auto limits(limitAlertConditionState.getLimits());
    	if (!limits.hasUpper()) {
    		return;
    	}
    	if (!limits.hasLower()) {
    		return;
    	}

    	const bool triggerAlarm(sourceValue.getValue() > limits.getUpper() || sourceValue.getValue() < limits.getLower());
   		setAlertConditionPresence(limitAlertConditionState.getDescriptorHandle(), triggerAlarm, OperationInvocationContext::none());
    }

	// Can be used to switch condition on and off (e.g. propagate input from real device). Currently not used in this test.
	void setPresence(bool presence) {
		// We do not need to update our state here, this will be done in onStateChangeRequest (will be called by the method we invoke next)
		setAlertConditionPresence(getDescriptorHandle(), presence, OperationInvocationContext::none());
	}

    // Helper method
    LimitAlertConditionState createState() {
        LimitAlertConditionState result;
        result
            .setDescriptorHandle("handle_alert_condition")  // Reference alert signal descriptor's handle
            .setActivationState(PausableActivation::ON)  // Component is working
            .setPresence(false)
            .setMonitoredAlertLimits(MonitoredAlertLimits::ALL)
            .setLimits(Range().setLower(0.0).setUpper(2.0));
        return result;
    }

    LimitAlertConditionState getInitialState() override {
        return createState();
    }

};

class AlertSystemStateHandler : public OSCPProviderAlertSystemStateHandler {
public:

	AlertSystemStateHandler() {
    }

	AlertSystemState getInitialState() override {
        AlertSystemState alertSystemState;
        // reference alert system descriptor's handle
        alertSystemState
            .setActivationState(PausableActivation::ON)
            .setDescriptorHandle("handle_alert_system");
        return alertSystemState;
    }

};

class CommandHandler : public OSCPProviderActivateOperationHandler {
public:

	CommandHandler() {
    }

	InvocationState onActivateRequest(const MDIBContainer & , const OperationInvocationContext & ) override {
		DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: Received command!" << std::endl;
		return InvocationState::FINISHED;
	}

	std::string getDescriptorHandle() override {
		return "handle_cmd";
	}
};

class AlwaysOnComponentStateHandler : public OSCPProviderComponentStateHandler {
public:
    AlwaysOnComponentStateHandler(const std::string & descriptorHandle) {
        this->descriptorHandle = descriptorHandle;
    }

    // Helper method
    ComponentState createState() {
        ComponentState result;
        result
            .setDescriptorHandle(descriptorHandle)
            .setComponentActivationState(ComponentActivation::ON);
        return result;
    }

    virtual ComponentState getInitialState() override {
        ComponentState state = createState();
        return state;
    }

private:
    std::string descriptorHandle;
};

class AlwaysOnHydraMDSStateHandler : public OSCPProviderHydraMDSStateHandler {
public:
    AlwaysOnHydraMDSStateHandler(const std::string & descriptorHandle) {
        this->descriptorHandle = descriptorHandle;
    }

    // Helper method
    HydraMDSState createState() {
        HydraMDSState result;
        result
            .setDescriptorHandle(descriptorHandle)
            .setComponentActivationState(ComponentActivation::ON);
        return result;
    }

    virtual HydraMDSState getInitialState() override {
        HydraMDSState state = createState();
        return state;
    }

private:
    std::string descriptorHandle;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Provider
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class OSCPHoldingDeviceProvider : public OSCPProvider, public Util::Task {
public:
    OSCPHoldingDeviceProvider() :
    	currentWeight(0),
		channelState(CHANNEL_DESCRIPTOR_HANDLE),
		hydraMDSState(MDS_HANDLE),
		vmdState(VMD_DESCRIPTOR_HANDLE)
	{
    	setEndpointReference(DEVICE_ENDPOINT_REFERENCE);

        // Define semantic meaning of weight unit "kg", which will be used for defining the
        // current weight and the max weight below.
        CodedValue unit;
        unit	.setCodeId("MDCX_CODE_ID_KG")
				.setCodingSystemId("OR.NET.Codings")
        		.addConceptDescription(LocalizedText().set("Weight in kg"));

    	//
        // Setup metric descriptors
        //

        // define properties of current weight metric
        currentWeightMetric
			.setMetricCategory(MetricCategory::MEASUREMENT)
        	.setAvailability(MetricAvailability::CONTINUOUS)
			.setUnit(unit)
			.setType(
				CodedValue()
				.setCodeId("MDCX_CODE_ID_WEIGHT")
				.addConceptDescription(LocalizedText().set("Current weight")))
	        .setHandle("handle_cur");

        testEnumMetric
			.setMetricCategory(MetricCategory::SETTING)
			.setAvailability(MetricAvailability::CONTINUOUS)
			.setUnit(unit)
				.setType(
					CodedValue()
					.addConceptDescription(LocalizedText().set("Enum test")))
			.setHandle("handle_enum")
			.addAllowedValue("hello")
			.addAllowedValue("hallo")
			.addAllowedValue("bon jour");

        location.setHandle("location_context");
        patient.setHandle("patient_context");

        // define properties of max weight metric
        maxWeightMetric
			.setMetricCategory(MetricCategory::SETTING)
        	.setAvailability(MetricAvailability::CONTINUOUS)
        	.setUnit(unit)
			.setType(
        		CodedValue()
				.addConceptDescription(LocalizedText().set("Maximum weight")))
        	.setHandle("handle_max");

        // define properties of test string metric
        testStringMetric
			.setMetricCategory(MetricCategory::SETTING)
			.setAvailability(MetricAvailability::CONTINUOUS)
			.setType(
        		CodedValue()
				.addConceptDescription(LocalizedText().set("Test string")))
			.setHandle("handle_str");

        //
		// Setup alert system
		//

        // alert condition
        limitAlertCondition
			.addSource("handle_cur")
			.setType(
        		CodedValue()
				.setCodeId("MDCX_CODE_ID_ALERT_WEIGHT_CONDITION")
				.setCodingSystemId("OR.NET.Codings"))
			.setKind(AlertConditionKind::TECHNICAL)
			.setPriority(AlertConditionPriority::MEDIUM)
			.setHandle("handle_alert_condition");

        // create signal for condition
        alertSignal
			.setConditionSignaled("handle_alert_condition")
			.setManifestation(AlertSignalManifestation::VISIBLE)
			.setLatching(false)
			.setHandle("handle_alert_signal");

        latchingAlertSignal
			.setConditionSignaled("handle_alert_condition")
			.setManifestation(AlertSignalManifestation::VISIBLE)
			.setLatching(true)
			.setHandle("handle_alert_signal_latching");

        // State handlers

        addMDStateHandler(&contextStates);
        addMDStateHandler(&curValueState);
        addMDStateHandler(&enumState);
        addMDStateHandler(&maxValueState);
        addMDStateHandler(&strValueState);
        addMDStateHandler(&limitAlertConditionHandler);
        addMDStateHandler(&alertSigHandler);
        addMDStateHandler(&latchingAlertSigHandler);
        addMDStateHandler(&alertSysHandler);
        addMDStateHandler(&cmdHandler);
        addMDStateHandler(&channelState);
        addMDStateHandler(&hydraMDSState);
        addMDStateHandler(&vmdState);
    }

    MDDescription getMDDescription() override {

        // Alerts
        AlertSystemDescriptor alertSystem;
        alertSystem
			.addAlertSignal(alertSignal)
			.addAlertSignal(latchingAlertSignal)
			.addLimitAlertCondition(limitAlertCondition)
			.setHandle("handle_alert_system");

        // Channel
        ChannelDescriptor holdingDeviceChannel;
        holdingDeviceChannel
			.setHandle(CHANNEL_DESCRIPTOR_HANDLE)
			.setAlertSystem(alertSystem)
			.addMetric(currentWeightMetric)
			.addMetric(testEnumMetric)
        	.addMetric(maxWeightMetric)
        	.addMetric(testStringMetric)
			.setIntendedUse(IntendedUse::MEDICAL_A);

        // VMD
        VMDDescriptor holdingDeviceModule;
        holdingDeviceModule
			.setHandle(VMD_DESCRIPTOR_HANDLE)
			.addChannel(holdingDeviceChannel);

        // MDS
        HydraMDSDescriptor holdingDeviceSystem;
        holdingDeviceSystem
			.setHandle(MDS_HANDLE)
			.setMetaData(
				SystemMetaData()
				.setUDI(DEVICE_UDI)
				.addManufacturer(
					LocalizedText()
					.set("SurgiTAIX AG"))
				.addModelName(
					LocalizedText()
					.set("EndoTAIX"))
				.addModelNumber("1")
				.addSerialNumber("1234")
				)
			.setContext(
				SystemContext()
			    .setPatientContext(
			    		patient)
				.setLocationContext(
						location)
				)
			.addVMD(holdingDeviceModule)
			.setType(
                CodedValue()
                .setCodingSystemId("OR.NET.Codings")
        		.setCodeId("MDCX_CODE_ID_MDS"));

        createSetOperationForDescriptor(alertSignal, holdingDeviceSystem);
        createSetOperationForDescriptor(maxWeightMetric, holdingDeviceSystem);
        createSetOperationForDescriptor(testEnumMetric, holdingDeviceSystem);
        createSetOperationForDescriptor(testStringMetric, holdingDeviceSystem);
        createSetOperationForDescriptor(location, holdingDeviceSystem);
        createSetOperationForDescriptor(patient, holdingDeviceSystem);

        ActivateOperationDescriptor aod;
			aod.setHandle("handle_cmd")
			.setOperationTarget("handle_max");
        addActivateOperationForDescriptor(aod, holdingDeviceSystem);

        MDDescription mdd;
        mdd.addHydraMDSDescriptor(holdingDeviceSystem);

        return mdd;
    }

    // Update weight periodically
    virtual void runImpl() override {
    	float nextWeight = currentWeight + 0.2f;
    	if (nextWeight > 2.5f) {
    		nextWeight = 0.1;
    	}
		setCurrentWeight(nextWeight);
		Poco::Thread::sleep(1000);
    }

    void setCurrentWeight(float value) {
        Poco::Mutex::ScopedLock lock(getMutex());
        currentWeight = value;
        curValueState.setNumericValue(value);
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Changed value: " << currentWeight << std::endl;
        strValueState.setStringValue("Test " + std::to_string(value));
    }

private:
    float currentWeight;

    // The current weight
    NumericMetricDescriptor currentWeightMetric;

    // Maximum weight
    NumericMetricDescriptor maxWeightMetric;

    // Test enum
	EnumStringMetricDescriptor testEnumMetric;

    // Test string
    StringMetricDescriptor testStringMetric;

    // Location context
    LocationContextDescriptor location;
    PatientContextDescriptor patient;

    // Alert descriptors
    AlertSignalDescriptor alertSignal;
    AlertSignalDescriptor latchingAlertSignal;
    LimitAlertConditionDescriptor limitAlertCondition;

    // State (handlers)
    ContextHandler contextStates;
    MaxValueStateHandler maxValueState;
    CurValueStateHandler curValueState;
    EnumStringMetricStateHandler enumState;
    StrValueStateHandler strValueState;
    LimitAlertConditionStateHandler limitAlertConditionHandler;
    AlertSignalStateHandler alertSigHandler;
    LatchingAlertSignalStateHandler latchingAlertSigHandler;
    AlertSystemStateHandler alertSysHandler;
    CommandHandler cmdHandler;
    AlwaysOnComponentStateHandler channelState;
    AlwaysOnHydraMDSStateHandler hydraMDSState;
    AlwaysOnComponentStateHandler vmdState;
};

}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Test
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FixtureSimpleOSCP : Tests::AbstractOSCLibFixture {
	FixtureSimpleOSCP() : AbstractOSCLibFixture("FixtureSimpleOSCP", Util::DebugOut::Error, 9000) {}
};

SUITE(OSCP) {
TEST_FIXTURE(FixtureSimpleOSCP, simpleoscp)
{
	DebugOut::openLogFile("Test.log.txt", true);
	try
	{
        // Provider
        Tests::SimpleOSCP::OSCPHoldingDeviceProvider provider;
        provider.startup();    
        provider.start();

        //Poco::Thread::sleep(2000000);

        // Consumer
        OSCPServiceManager oscpsm;
        std::shared_ptr<OSCPConsumer> c(oscpsm.discoverEndpointReference(Tests::SimpleOSCP::DEVICE_ENDPOINT_REFERENCE));

        Tests::SimpleOSCP::ExampleConsumerNumericHandler eces1("handle_cur");
        Tests::SimpleOSCP::ExampleConsumerNumericHandler eces2("handle_max");
        Tests::SimpleOSCP::ExampleConsumerStringMetricHandler eces3("handle_str");
        Tests::SimpleOSCP::ExampleConsumerEnumStringMetricHandler eces4("handle_enum");
        Tests::SimpleOSCP::ExampleConsumerAlertSignalHandler alertSignalsink("handle_alert_signal");
        Tests::SimpleOSCP::ExampleConsumerAlertSignalHandler latchingAlertSignalsink("handle_alert_signal_latching");
        Tests::SimpleOSCP::ContextEventHandler ceh({"location_context", "patient_context"});

        // Discovery test
        CHECK_EQUAL(true, c != nullptr);

		if (c != nullptr) {
            const std::string xaddr(c->getProviderXAddr());

			OSCPConsumer & consumer = *c;
            // MDIB test
            MDIBContainer mdib(consumer.getMDIB());

            { // test access to system metadata of mds implemented by provider above
            	HydraMDSDescriptor mds;
            	if (mdib.getMDDescription().findDescriptor(Tests::SimpleOSCP::MDS_HANDLE, mds)) {
            		if (mds.hasMetaData()) {
            			const SystemMetaData metadata(mds.getMetaData());
            			if (metadata.hasUDI()) {
            	            const std::string remoteUDI(metadata.getUDI());
            	            CHECK_EQUAL(Tests::SimpleOSCP::DEVICE_UDI, remoteUDI);
            			}
            		}
            	}
            }
            { // test presence of system context descriptors
            	HydraMDSDescriptor mds;
            	if (mdib.getMDDescription().findDescriptor(Tests::SimpleOSCP::MDS_HANDLE, mds)) {
            		SystemContext sc(mds.getContext());
            		CHECK_EQUAL(true, sc.hasPatientContext());
            		CHECK_EQUAL(false, sc.hasOperatorContext());
            	}
            }
            {	// lookup descriptors that should exist for the provider implemented above
            	NumericMetricDescriptor curMetric;
				mdib.getMDDescription().findDescriptor("handle_cur", curMetric);
				CHECK_EQUAL("Current weight", curMetric.getType().getConceptDescriptions().at(0).get());
				CHECK_EQUAL("handle_cur", curMetric.getHandle());

				StringMetricDescriptor strMetric;
				CHECK_EQUAL(true, mdib.getMDDescription().findDescriptor("handle_str", strMetric));
				CHECK_EQUAL("handle_str", strMetric.getHandle());
            }

            // Register for consumer events
            CHECK_EQUAL(true, consumer.registerStateEventHandler(&eces1));
            CHECK_EQUAL(true, consumer.registerStateEventHandler(&eces2));
            CHECK_EQUAL(true, consumer.registerStateEventHandler(&eces3));
            CHECK_EQUAL(true, consumer.registerStateEventHandler(&eces4));
            // Register for alert signal events
            CHECK_EQUAL(true, consumer.registerStateEventHandler(&alertSignalsink));
            CHECK_EQUAL(true, consumer.registerStateEventHandler(&latchingAlertSignalsink));
            // Register for context changed events
            consumer.setContextStateChangedHandler(&ceh);

            Poco::Thread::sleep(2000);

            {	// Ensure that requests for wrong handles fail.
            	DebugOut(DebugOut::Default, "SimpleOSCP") << "Numeric test..." << std::endl;
				DebugOut(DebugOut::Default, "SimpleOSCP") << "SHOULD FAIL: " << std::endl;
				NumericMetricState tempState;
            	CHECK_EQUAL(false, consumer.requestState("unknown", tempState));
            }
            {	// Request state of current weight
            	NumericMetricState currentWeightState;
				CHECK_EQUAL(true, consumer.requestState("handle_cur", currentWeightState));
				CHECK_EQUAL(true, currentWeightState.hasObservedValue());
				if (currentWeightState.hasObservedValue()) {
					const double curWeight(currentWeightState.getObservedValue().getValue());
					CHECK_EQUAL(true, curWeight > 0.1);
				}
            }
            {	// Ensure that (read-only) metrics without matching SetOperation cannot be set.
            	DebugOut(DebugOut::Default, "SimpleOSCP") << "SHOULD FAIL: " << std::endl;
            	NumericMetricState currentWeightState;
				CHECK_EQUAL(true, consumer.requestState("handle_cur", currentWeightState));
            	CHECK_EQUAL(true, InvocationState::FAILED == consumer.commitState(currentWeightState));
            }
            {	// Get state of maximum weight
				NumericMetricState maxWeightState;
				CHECK_EQUAL(true, consumer.requestState("handle_max", maxWeightState));
				double maxWeight = maxWeightState.getObservedValue().getValue();
				CHECK_EQUAL(2.0, maxWeight);
            }
            {	// Get state of test enum
				EnumStringMetricState enumState;
				CHECK_EQUAL(true, consumer.requestState("handle_enum", enumState));
				const std::string enumValue(enumState.getObservedValue().getValue());
				CHECK_EQUAL("hello", enumValue);
            }
            {	// Set state of test enum with allowed enum value
				EnumStringMetricState enumState;
				CHECK_EQUAL(true, consumer.requestState("handle_enum", enumState));

				enumState.setObservedValue(StringMetricValue().setValue("bon jour"));
				FutureInvocationState fis;
				CHECK_EQUAL(true, InvocationState::WAITING == consumer.commitState(enumState, fis));
				CHECK_EQUAL(true, fis.waitReceived(InvocationState::FINISHED, Tests::SimpleOSCP::DEFAULT_TIMEOUT));
            }
            {	// Set state of test enum with illegal enum value
				EnumStringMetricState enumState;
				CHECK_EQUAL(true, consumer.requestState("handle_enum", enumState));
				const std::string enumValue(enumState.getObservedValue().getValue());
				CHECK_EQUAL("bon jour", enumValue);

				enumState.setObservedValue(StringMetricValue().setValue("bye"));
				FutureInvocationState fis;
				consumer.commitState(enumState, fis);
				CHECK_EQUAL(true, fis.waitReceived(InvocationState::FAILED, Tests::SimpleOSCP::DEFAULT_TIMEOUT));
            }

            // Wait here and let the current value exceed max value. This will trigger alert condition presence which in turn
            // will trigger an alert signal presence (Off -> On -> Latch)!
            Poco::Thread::sleep(8000);

			{	// Set state test for a numeric metric state (must succeed, use state handle instead of descriptor handle)
				NumericMetricState maxWeightState;
				CHECK_EQUAL(true, consumer.requestState("handle_max", maxWeightState));

				// Here, we increase max weight to switch condition presence => results in alert signal presence
				maxWeightState.setObservedValue(NumericMetricValue().setValue(10));
				FutureInvocationState fis;
				CHECK_EQUAL(true, InvocationState::WAITING == consumer.commitState(maxWeightState, fis));
				CHECK_EQUAL(true, fis.waitReceived(InvocationState::FINISHED, Tests::SimpleOSCP::DEFAULT_TIMEOUT));
			}

            {	// Set state test for a string metric state (must succeed)
                DebugOut(DebugOut::Default, "SimpleOSCP") << "String test...";
				StringMetricState stringState;
				stringState.setDescriptorHandle("handle_str");
				stringState.setObservedValue(StringMetricValue().setValue("Test2"));
				FutureInvocationState fis;
				CHECK_EQUAL(true, InvocationState::WAITING == consumer.commitState(stringState, fis));
				CHECK_EQUAL(true, fis.waitReceived(InvocationState::FINISHED, Tests::SimpleOSCP::DEFAULT_TIMEOUT));
            }

            {	// Activate test
                DebugOut(DebugOut::Default, "SimpleOSCP") << "Activate test...";
                FutureInvocationState fis;
				CHECK_EQUAL(true, InvocationState::WAITING == c->activate("handle_cmd", fis));
				CHECK_EQUAL(true, fis.waitReceived(InvocationState::FINISHED, Tests::SimpleOSCP::DEFAULT_TIMEOUT));
            }

            {	// Location context test
                DebugOut(DebugOut::Default, "SimpleOSCP") << "Location context test...";
                LocationContextState lcs;
                lcs.setDescriptorHandle("location_context");
                lcs.setHandle("location_context");
                lcs.setContextAssociation(ContextAssociation::ASSOCIATED);
                lcs.addIdentification(InstanceIdentifier().setroot("hello").setextension("world"));
                FutureInvocationState fis;
                ceh.getEventEMR().reset();
                CHECK_EQUAL(true, InvocationState::WAITING == consumer.commitState(lcs, fis));
				CHECK_EQUAL(true, ceh.getEventEMR().tryWait(3000));
				CHECK_EQUAL(true, fis.waitReceived(InvocationState::FINISHED, Tests::SimpleOSCP::DEFAULT_TIMEOUT));
				DebugOut(DebugOut::Default, "SimpleOSCP") << "Location context test done...";
            }
            {	// Patient context test
            	DebugOut(DebugOut::Default, "SimpleOSCP") << "Patient context test...";
				PatientContextState pcs;
				pcs.setDescriptorHandle("patient_context");
				pcs.setHandle("pat_context");
				pcs.setContextAssociation(ContextAssociation::ASSOCIATED);
				pcs.addIdentification(InstanceIdentifier().setroot("hello").setextension("world"));
				pcs.setCoreData(PatientDemographicsCoreData()
						.setGivenname("Max")
						.setBirthname("")
						.setFamilyname("Mustermann")
						.setDateOfBirth(DateTime().setyear(1982).setmonth(1).setday(1)));
				FutureInvocationState fis;
				ceh.getEventEMR().reset();
				CHECK_EQUAL(true, InvocationState::WAITING == consumer.commitState(pcs, fis));
				CHECK_EQUAL(true, ceh.getEventEMR().tryWait(3000));
				CHECK_EQUAL(true, fis.waitReceived(InvocationState::FINISHED, Tests::SimpleOSCP::DEFAULT_TIMEOUT));
				DebugOut(DebugOut::Default, "SimpleOSCP") << "Patient context test done...";
			}
            // Run for some time to receive and display incoming metric events.
			Poco::Thread::sleep(5000);

			// Stop dummy events created by provider
			provider.interrupt();

			{	// Switch alert signal state off
				AlertSignalState alertSignal;
				CHECK_EQUAL(true, consumer.requestState("handle_alert_signal", alertSignal));

				alertSignal.setPresence(SignalPresence::Off);
				FutureInvocationState fis;
				CHECK_EQUAL(true, InvocationState::WAITING == consumer.commitState(alertSignal, fis));
				CHECK_EQUAL(true, fis.waitReceived(InvocationState::FINISHED, Tests::SimpleOSCP::DEFAULT_TIMEOUT));
			}

            Poco::Thread::sleep(5000);

            CHECK_EQUAL(true, eces1.getWeight() > 0);

            CHECK_EQUAL(true, eces1.getEventEMR().tryWait(Tests::SimpleOSCP::DEFAULT_TIMEOUT));
            CHECK_EQUAL(true, eces2.getEventEMR().tryWait(Tests::SimpleOSCP::DEFAULT_TIMEOUT));
            CHECK_EQUAL(true, eces3.getEventEMR().tryWait(Tests::SimpleOSCP::DEFAULT_TIMEOUT));
            CHECK_EQUAL(true, eces4.getEventEMR().tryWait(Tests::SimpleOSCP::DEFAULT_TIMEOUT));
            CHECK_EQUAL(true, alertSignalsink.getEventEAROff().tryWait(Tests::SimpleOSCP::DEFAULT_TIMEOUT));
            CHECK_EQUAL(true, alertSignalsink.getEventEAROn().tryWait(Tests::SimpleOSCP::DEFAULT_TIMEOUT));
            CHECK_EQUAL(true, latchingAlertSignalsink.getEventEARLatch().tryWait(Tests::SimpleOSCP::DEFAULT_TIMEOUT));

            CHECK_EQUAL(true, consumer.unregisterStateEventHandler(&eces1));
            CHECK_EQUAL(true, consumer.unregisterStateEventHandler(&eces2));
            CHECK_EQUAL(true, consumer.unregisterStateEventHandler(&eces3));
            CHECK_EQUAL(true, consumer.unregisterStateEventHandler(&eces4));
            CHECK_EQUAL(true, consumer.unregisterStateEventHandler(&alertSignalsink));
            CHECK_EQUAL(true, consumer.unregisterStateEventHandler(&latchingAlertSignalsink));
            
            consumer.setContextStateChangedHandler(nullptr);

            DebugOut(DebugOut::Default, "SimpleOSCP") << "Finished...";
            
            consumer.disconnect();
		}

        Poco::Thread::sleep(2000);
        provider.shutdown();
    } catch (char const* exc) {
		DebugOut(DebugOut::Default, std::cerr, "simpleoscp") << exc;
	} catch (...) {
		DebugOut(DebugOut::Default, std::cerr, "simpleoscp") << "Unknown exception occurred!";
	}
	DebugOut::closeLogFile();
}
}