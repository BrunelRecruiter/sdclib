
#include "OSCLib/Data/OSCP/MDIB/AlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ClockDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/DicomDeviceDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnsembleContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MdDescription.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/VmdDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextDescriptor.h"

#include "osdm.hxx"

// debug
//#include "OSCLib/Util/DebugOut.h"
#include <iostream>

namespace OSCLib {
namespace Data {
namespace OSCP {

template<class AlertSystemOwner>
bool findAlertConditionDescriptorImpl(const AlertSystemOwner & owner, const std::string & handle, AlertConditionDescriptor & outDescriptor) {
		if (owner.AlertSystem().present()) {
		const CDM::AlertSystemDescriptor & alertSystem(owner.AlertSystem().get());
		for (const auto & descriptor : alertSystem.AlertCondition()) {
			if (dynamic_cast<const LimitAlertConditionDescriptor::WrappedType *>(&descriptor)) {
				continue;
			}
			if (descriptor.Handle() == handle) {
				outDescriptor = ConvertFromCDM::convert(descriptor);
				return true;
			}
		}
	}
	return false;
}

bool MdDescription::findDescriptor(const std::string & handle, AlertConditionDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		if (findAlertConditionDescriptorImpl(mds, handle, outDescriptor)) {
			return true;
		}
		for (const auto & vmdDescriptor : mds.Vmd()) {
			if (findAlertConditionDescriptorImpl(vmdDescriptor, handle, outDescriptor)) {
				return true;
			}
		}
	}

	return false;
}

template<class AlertSystemOwner>
bool findAlertSignalDescriptorImpl(const AlertSystemOwner & owner, const std::string & handle, AlertSignalDescriptor & outDescriptor) {
	if (owner.AlertSystem().present()) {
		const CDM::AlertSystemDescriptor & alertSystem(owner.AlertSystem().get());
		for (const auto & descriptor : alertSystem.AlertSignal()) {
			if (descriptor.Handle() == handle) {
				outDescriptor = ConvertFromCDM::convert(descriptor);
				return true;
			}
		}
	}
	return false;
}

bool MdDescription::findDescriptor(const std::string & handle, AlertSignalDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		if (findAlertSignalDescriptorImpl(mds, handle, outDescriptor)) {
			return true;
		}
		for (const auto & vmdDescriptor : mds.Vmd()) {
			if (findAlertSignalDescriptorImpl(vmdDescriptor, handle, outDescriptor)) {
				return true;
			}
		}
	}

	return false;
}

template<class AlertSystemOwner>
bool findAlertSystemDescriptorImpl(const AlertSystemOwner & owner, const std::string & handle, AlertSystemDescriptor & outDescriptor) {
	if (owner.AlertSystem().present()) {
		const CDM::AlertSystemDescriptor & alertSystem(owner.AlertSystem().get());
		if (alertSystem.Handle() == handle) {
			outDescriptor = ConvertFromCDM::convert(alertSystem);
			return true;
		}
	}
	return false;
}

bool MdDescription::findDescriptor(const std::string & handle, AlertSystemDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		if (findAlertSystemDescriptorImpl(mds, handle, outDescriptor)) {
			return true;
		}
		for (const auto & vmdDescriptor : mds.Vmd()) {
			if (findAlertSystemDescriptorImpl(vmdDescriptor, handle, outDescriptor)) {
				return true;
			}
		}
	}

	return false;
}

template<class AlertSystemOwner>
bool findLimitAlertConditionDescriptorImpl(const AlertSystemOwner & owner, const std::string & handle, LimitAlertConditionDescriptor & outDescriptor) {
	if (owner.AlertSystem().present()) {
		const CDM::AlertSystemDescriptor & alertSystem(owner.AlertSystem().get());
		for (const auto & descriptor : alertSystem.AlertCondition()) {
			if (descriptor.Handle() == handle) {
				if (const CDM::LimitAlertConditionDescriptor * match = dynamic_cast<const CDM::LimitAlertConditionDescriptor *>(&descriptor)) {
					outDescriptor = ConvertFromCDM::convert(*match);
					return true;
				}
			}
		}
	}
	return false;
}

bool MdDescription::findDescriptor(const std::string & handle, LimitAlertConditionDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		if (findLimitAlertConditionDescriptorImpl(mds, handle, outDescriptor)) {
			return true;
		}
		for (const auto & vmdDescriptor : mds.Vmd()) {
			if (findLimitAlertConditionDescriptorImpl(vmdDescriptor, handle, outDescriptor)) {
				return true;
			}
		}
	}

	return false;
}

bool MdDescription::findDescriptor(const std::string & handle, ChannelDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		for (const auto & vmdDescriptor : mds.Vmd()) {
			for (const auto & channelDescriptor : vmdDescriptor.Channel()) {
				if (channelDescriptor.Handle() == handle) {
					outDescriptor = ConvertFromCDM::convert(channelDescriptor);
					return true;
				}
			}
		}
	}
	return false;
}

template<class WrapperMetricDescriptorType>
bool MdDescription::findMetricDescriptorImpl(const std::string & handle, WrapperMetricDescriptorType & outMetric) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		for (const auto & vmdDescriptor : mds.Vmd()) {
			for (const auto & channelDescriptor : vmdDescriptor.Channel()) {
				for (const auto & metricDescriptor : channelDescriptor.Metric()) {
					if (metricDescriptor.Handle() != handle) {
						continue;
					}
					if (const typename WrapperMetricDescriptorType::WrappedType * foundMetric = dynamic_cast<const typename WrapperMetricDescriptorType::WrappedType *>(&metricDescriptor)) {
						outMetric = ConvertFromCDM::convert(*foundMetric);
						return true;
					}
				}
			}
		}
	}
	return false;
}

template<>
bool MdDescription::findMetricDescriptorImpl(const std::string & handle, StringMetricDescriptor & outMetric) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		for (const auto & vmdDescriptor : mds.Vmd()) {
			for (const auto & channelDescriptor : vmdDescriptor.Channel()) {
				for (const auto & metricDescriptor : channelDescriptor.Metric()) {
					if (metricDescriptor.Handle() != handle) {
						continue;
					}
					if (dynamic_cast<const EnumStringMetricDescriptor::WrappedType *>(&metricDescriptor)) {
						continue;
					}
					if (auto foundMetric = dynamic_cast<const StringMetricDescriptor::WrappedType *>(&metricDescriptor)) {
						outMetric = ConvertFromCDM::convert(*foundMetric);
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool MdDescription::findDescriptor(const std::string & handle, ClockDescriptor & outDescriptor) const {
	return findMetricDescriptorImpl(handle, outDescriptor);
}

bool MdDescription::findDescriptor(const std::string & handle, EnumStringMetricDescriptor & outDescriptor) const {
	return findMetricDescriptorImpl(handle, outDescriptor);
}

bool MdDescription::findDescriptor(const std::string & handle, NumericMetricDescriptor & outDescriptor) const {
	return findMetricDescriptorImpl(handle, outDescriptor);
}

bool MdDescription::findDescriptor(const std::string & handle, StringMetricDescriptor & outDescriptor) const {
	return findMetricDescriptorImpl(handle, outDescriptor);
}

bool MdDescription::findDescriptor(const std::string & handle, VmdDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		if (const CDM::MdsDescriptor * mds = dynamic_cast<const CDM::MdsDescriptor *>(&mds)) {
			for (const auto & vmdDescriptor : mds->Vmd()) {
				if (vmdDescriptor.Handle() == handle) {
					outDescriptor = ConvertFromCDM::convert(vmdDescriptor);
					return true;
				}
			}
		}
	}
	return false;
}

bool MdDescription::findDescriptor(const std::string & handle, RealTimeSampleArrayMetricDescriptor & outDescriptor) const {
	return findMetricDescriptorImpl(handle, outDescriptor);
}

bool MdDescription::findDescriptor(const std::string & handle, EnsembleContextDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		if (const CDM::MdsDescriptor * mds = dynamic_cast<const CDM::MdsDescriptor *>(&mds)) {
			if (mds->SystemContext().present()) {
				if (!mds->SystemContext().get().EnsembleContext().empty()) {
					for (const auto & descriptor : mds->SystemContext().get().EnsembleContext()) {
						if (descriptor.Handle() == handle) {
							outDescriptor = ConvertFromCDM::convert(descriptor);
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}


template <class MDSDescriptor>
void MdDescription::addMDSDescriptor(const MDSDescriptor & source) {
	CDM::MdDescription & mddescription(*this->data);
	mddescription.Mds().push_back(ConvertToCDM::convert(source));
}

template void MdDescription::addMDSDescriptor<MdsDescriptor>(const MdsDescriptor & source);
template void MdDescription::addMDSDescriptor<DicomDeviceDescriptor>(const DicomDeviceDescriptor & source);


template <class MDSDescriptor>
bool MdDescription::removeMDSDescriptor(const MDSDescriptor & object) {
	CDM::MdDescription & mddescription(*this->data);
	for (auto iter = mddescription.Mds().begin(); iter != mddescription.Mds().end(); iter++) {
		if (iter->Handle() == object.getHandle()) {
			mddescription.Mds().erase(iter);
			return true;
		}
	}
}

template bool MdDescription::removeMDSDescriptor<MdsDescriptor>(const MdsDescriptor & source);
template bool MdDescription::removeMDSDescriptor<DicomDeviceDescriptor>(const DicomDeviceDescriptor & source);


bool MdDescription::findDescriptor(const std::string & handle, LocationContextDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		if (const CDM::MdsDescriptor * mds = dynamic_cast<const CDM::MdsDescriptor *>(&mds)) {
			if (mds->SystemContext().present()) {
				if (mds->SystemContext().get().LocationContext().present()) {
					const auto & descriptor(mds->SystemContext().get().LocationContext().get());
					if (descriptor.Handle() == handle) {
						outDescriptor = ConvertFromCDM::convert(descriptor);
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool MdDescription::findDescriptor(const std::string & handle, OperatorContextDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		if (const CDM::MdsDescriptor * mds = dynamic_cast<const CDM::MdsDescriptor *>(&mds)) {
			if (mds->SystemContext().present()) {
				if (!mds->SystemContext().get().OperatorContext().empty()) {
					for (const auto & descriptor : mds->SystemContext().get().OperatorContext()) {
						if (descriptor.Handle() == handle) {
							outDescriptor = ConvertFromCDM::convert(descriptor);
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

bool MdDescription::findDescriptor(const std::string & handle, PatientContextDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		if (const CDM::MdsDescriptor * mds = dynamic_cast<const CDM::MdsDescriptor *>(&mds)) {
			if (mds->SystemContext().present()) {
				if (mds->SystemContext().get().PatientContext().present()) {
					const auto & descriptor(mds->SystemContext().get().LocationContext().get());
					if (descriptor.Handle() == handle) {
						outDescriptor = ConvertFromCDM::convert(descriptor);
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool MdDescription::findDescriptor(const std::string & handle, WorkflowContextDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		if (const CDM::MdsDescriptor * mds = dynamic_cast<const CDM::MdsDescriptor *>(&mds)) {
			if (mds->SystemContext().present()) {
				if (!mds->SystemContext().get().WorkflowContext().empty()) {
					for (const auto & descriptor : mds->SystemContext().get().WorkflowContext()) {
						if (descriptor.Handle() == handle) {
							outDescriptor = ConvertFromCDM::convert(descriptor);
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

bool MdDescription::getFirstHydraMDSDescriptor(MdsDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		if (const CDM::MdsDescriptor * mds = dynamic_cast<const CDM::MdsDescriptor *>(&mds)) {
			outDescriptor = ConvertFromCDM::convert(*mds);
			return true;
		}
	}
	return false;
}

bool MdDescription::findDescriptor(const std::string & handle, MdsDescriptor & outDescriptor) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		if (const CDM::MdsDescriptor * mds = dynamic_cast<const CDM::MdsDescriptor *>(&mds)) {
			if (mds->Handle() != handle) {
				continue;
			}
			outDescriptor = ConvertFromCDM::convert(*mds);
			return true;
		}
	}
	return false;
}

std::string MdDescription::getOperationTargetForOperationHandle(const std::string & operationHandle) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		if (const CDM::MdsDescriptor * mds = dynamic_cast<const CDM::MdsDescriptor *>(&mds)) {
			if (!mds->Sco().present()) {
				continue;
			}
			for (const auto & operation : mds->Sco().get().Operation()) {
				if (operation.Handle() == operationHandle) {
					return operation.OperationTarget();
				}
			}
		}
	}

	return "";
}

std::string MdDescription::getFirstOperationHandleForOperationTarget(const std::string & operationTarget) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		if (const CDM::MdsDescriptor * mds = dynamic_cast<const CDM::MdsDescriptor *>(&mds)) {
			if (!mds->Sco().present()) {
				continue;
			}
			for (const auto & operation : mds->Sco().get().Operation()) {
				if (operation.OperationTarget() == operationTarget) {
					return operation.Handle();
				}
			}
		}
	}

	return "";
}

std::vector<AlertConditionDescriptor> MdDescription::collectAllAlertConditionDescriptors() const {
	auto impl = [](const CDM::AlertSystemDescriptor & owner, std::vector<AlertConditionDescriptor> & out) {
		for (const auto & descriptor : owner.AlertCondition()) {
			if (dynamic_cast<const LimitAlertConditionDescriptor *>(&descriptor)) {
				continue;
			}
			out.push_back(ConvertFromCDM::convert(descriptor));
		}
	};

	std::vector<AlertConditionDescriptor> result;
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		if (const CDM::MdsDescriptor * mds = dynamic_cast<const CDM::MdsDescriptor *>(&mds)) {
			if (mds->AlertSystem().present()) {
				impl(mds->AlertSystem().get(), result);
			}
			for (const auto & vmdDescriptor : mds->Vmd()) {
				if (vmdDescriptor.AlertSystem().present()) {
					impl(vmdDescriptor.AlertSystem().get(), result);
				}
			}
		}
	}
	return result;
}

std::vector<AlertSignalDescriptor> MdDescription::collectAllAlertSignalDescriptors() const {
	auto impl = [](const CDM::AlertSystemDescriptor & owner, std::vector<AlertSignalDescriptor> & out) {
		for (const auto & descriptor : owner.AlertSignal()) {
			out.push_back(ConvertFromCDM::convert(descriptor));
		}
	};

	std::vector<AlertSignalDescriptor> result;
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		if (const CDM::MdsDescriptor * mds = dynamic_cast<const CDM::MdsDescriptor *>(&mds)) {
			if (mds->AlertSystem().present()) {
				impl(mds->AlertSystem().get(), result);
			}
			for (const auto & vmdDescriptor : mds->Vmd()) {
				if (vmdDescriptor.AlertSystem().present()) {
					impl(vmdDescriptor.AlertSystem().get(), result);
				}
			}
		}
	}
	return result;
}

std::vector<AlertSystemDescriptor> MdDescription::collectAllAlertSystemDescriptors() const {
	std::vector<AlertSystemDescriptor> result;
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		if (const CDM::MdsDescriptor * mds = dynamic_cast<const CDM::MdsDescriptor *>(&mds)) {
			if (mds->AlertSystem().present()) {
				result.push_back(ConvertFromCDM::convert(mds->AlertSystem().get()));
			}
			for (const auto & vmdDescriptor : mds->Vmd()) {
				if (vmdDescriptor.AlertSystem().present()) {
					result.push_back(ConvertFromCDM::convert(vmdDescriptor.AlertSystem().get()));
				}
			}
		}
	}
	return result;
}

std::vector<LimitAlertConditionDescriptor> MdDescription::collectAllLimitAlertConditionDescriptors() const {
	auto impl = [](const CDM::AlertSystemDescriptor & owner, std::vector<LimitAlertConditionDescriptor> & out) {
		for (const auto & descriptor : owner.AlertCondition()) {
			if (const CDM::LimitAlertConditionDescriptor * casted = dynamic_cast<const CDM::LimitAlertConditionDescriptor *>(&descriptor)) {
				out.push_back(ConvertFromCDM::convert(*casted));
			}
		}
	};

	std::vector<LimitAlertConditionDescriptor> result;
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		if (const CDM::MdsDescriptor * mds = dynamic_cast<const CDM::MdsDescriptor *>(&mds)) {
			if (mds->AlertSystem().present()) {
				impl(mds->AlertSystem().get(), result);
			}
			for (const auto & vmdDescriptor : mds->Vmd()) {
				if (vmdDescriptor.AlertSystem().present()) {
					impl(vmdDescriptor.AlertSystem().get(), result);
				}
			}
		}
	}
	return result;
}

std::vector<DicomDeviceDescriptor> MdDescription::collectAllDICOMDeviceDescriptors() const {
	std::vector<DicomDeviceDescriptor> result;
	const CDM::MdDescription & mddescription(*this->data);

	for (const auto & mds : mddescription.Mds()) {
		if (const CDM::DicomDeviceDescriptor * dicomDeviceDescriptor = dynamic_cast<const CDM::DicomDeviceDescriptor *>(&mds)) {
			result.push_back(ConvertFromCDM::convert(*dicomDeviceDescriptor));
		}
	}

	return result;
}

std::vector<MdsDescriptor> MdDescription::collectAllHydraMDSDescriptors() const {
	std::vector<MdsDescriptor> result;
	const CDM::MdDescription & mddescription(*this->data);

	for (const auto & mds : mddescription.Mds()) {
		if (const CDM::MdsDescriptor * mds = dynamic_cast<const CDM::MdsDescriptor *>(&mds)) {
			result.push_back(ConvertFromCDM::convert(*mds));
		}
	}

	return result;
}

std::vector<VmdDescriptor> MdDescription::collectAllVMDDescriptors() const {
	std::vector<VmdDescriptor> result;
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		if (const CDM::MdsDescriptor * mds = dynamic_cast<const CDM::MdsDescriptor *>(&mds)) {
			for (const auto & vmdDescriptor : mds->Vmd()) {
				result.push_back(ConvertFromCDM::convert(vmdDescriptor));
			}
		}
	}
	return result;
}

std::vector<ChannelDescriptor> MdDescription::collectAllChannelDescriptors() const {
	std::vector<ChannelDescriptor> result;
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		if (const CDM::MdsDescriptor * mds = dynamic_cast<const CDM::MdsDescriptor *>(&mds)) {
			for (const auto & vmdDescriptor : mds->Vmd()) {
				for (const auto & channelDescriptor : vmdDescriptor.Channel()) {
					result.push_back(ConvertFromCDM::convert(channelDescriptor));
				}
			}
		}
	}
	return result;
}

template <class WrapperMetricDescriptorType>
void MdDescription::collectMetricDescriptorImpl(std::vector<WrapperMetricDescriptorType> & out) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		if (const CDM::MdsDescriptor * mds = dynamic_cast<const CDM::MdsDescriptor *>(&mds)) {
			for (const auto & vmdDescriptor : mds->Vmd()) {
				for (const auto & channelDescriptor : vmdDescriptor.Channel()) {
					for (const auto & metricDescriptor : channelDescriptor.Metric()) {
						if (const typename WrapperMetricDescriptorType::WrappedType * foundMetric = dynamic_cast<const typename WrapperMetricDescriptorType::WrappedType *>(&metricDescriptor)) {
							out.push_back(ConvertFromCDM::convert(*foundMetric));
						}
					}
				}
			}
		}
	}
}

template <class WrapperMetricDescriptorType, class ForbiddenType>
void MdDescription::collectMetricDescriptorImpl(std::vector<WrapperMetricDescriptorType> & out) const {
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		if (const CDM::MdsDescriptor * mds = dynamic_cast<const CDM::MdsDescriptor *>(&mds)) {
			for (const auto & vmdDescriptor : mds->Vmd()) {
				for (const auto & channelDescriptor : vmdDescriptor.Channel()) {
					for (const auto & metricDescriptor : channelDescriptor.Metric()) {
						if (dynamic_cast<const typename ForbiddenType::WrappedType *>(&metricDescriptor)) {
							continue;
						}
						if (const typename WrapperMetricDescriptorType::WrappedType * foundMetric = dynamic_cast<const typename WrapperMetricDescriptorType::WrappedType *>(&metricDescriptor)) {
							out.push_back(ConvertFromCDM::convert(*foundMetric));
						}
					}
				}
			}
		}
	}
}

std::vector<ClockDescriptor> MdDescription::collectAllClockDescriptors() const {
	std::vector<ClockDescriptor> result;
	const CDM::MdDescription & mddescription(*this->data);
	for (const auto & mds : mddescription.Mds()) {
		if (const CDM::MdsDescriptor * mds = dynamic_cast<const CDM::MdsDescriptor *>(&mds)) {
			if (mds->Clock().present()) {
				result.push_back(ConvertFromCDM::convert(mds->Clock().get()));
			}
		}
	}
	return result;
}

std::vector<EnumStringMetricDescriptor> MdDescription::collectAllEnumStringMetricDescriptors() const {
	std::vector<EnumStringMetricDescriptor> result;
	collectMetricDescriptorImpl(result);
	return result;
}

std::vector<NumericMetricDescriptor> MdDescription::collectAllNumericMetricDescriptors() const {
	std::vector<NumericMetricDescriptor> result;
	collectMetricDescriptorImpl(result);
	return result;
}

std::vector<RealTimeSampleArrayMetricDescriptor> MdDescription::collectAllRealTimeSampleArrayMetricDescriptors() const {
	std::vector<RealTimeSampleArrayMetricDescriptor> result;
	collectMetricDescriptorImpl(result);
	return result;
}

std::vector<StringMetricDescriptor> MdDescription::collectAllStringMetricDescriptors() const {
	std::vector<StringMetricDescriptor> result;
	collectMetricDescriptorImpl<StringMetricDescriptor, EnumStringMetricDescriptor>(result);
	return result;
}

}
}
}
