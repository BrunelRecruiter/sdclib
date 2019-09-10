/*
 * NamigConvention.h
 *
 *  Created on: Jul 22, 2019
 *      Author: rosenau
 */
#ifndef EXAMPLES_ABSTRACTCONSUMERSIMULATOR_NAMIGCONVENTION_H_
#define EXAMPLES_ABSTRACTCONSUMERSIMULATOR_NAMIGCONVENTION_H_

#include <string>

namespace SDCLib {
namespace Data {
namespace SDC {
namespace ACS {

const std::string ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX = "_REQUEST_ACTION_BB";
const std::string ACTIVATE_FOR_SUBSCRIBE_OPERATION_ON_DUT_POSTFIX = "_SUBSCRIBE_ACTION_BB";
const std::string ACTIVATE_FOR_UNSUBSCRIBE_OPERATION_ON_DUT_POSTFIX = "_UNSUBSCRIBE_ACTION_BB";
const std::string DEFAULT_ENDPOINTREFERENCE_DISCOVERY_PROVIDER = "DEVICE_UNDER_TEST_DISCOVERY_PROVIDER_BB";
const std::string DISCOVERY_PROVIDER_CHANNEL = "DISCOVERY_PROVIDER_CHANNEL_BB";
const std::string DISCOVERY_PROVIDER_VMD = "DISCOVERY_PROVIDER_VMD_BB";
const std::string DISCOVERY_PROVIDER_MDS = "DISCOVERY_PROVIDER_MDS_BB";
const std::string SET_DEVICE_UNDER_TEST_ENDPOINT_REF = "SET_DUT_ENDPOINT_REFERENCE_STRING_BB";
const std::string DISCOVER_AVAILABLE_ENDPOINT_REFERENCES = "DISCOVER_AVAILABLE_ENPOINT_REFERENCES_ACTION_BB";
const std::string DISCOVER_DEVICE_UNDER_TEST = "DISCOVER_DEVICE_UNDER_TEST_ACTION_BB";
const std::string SET_MIRROR_PROVIDER_ENDPOINT_REF = "SET_MIRROR_PROVIDER_ENDPOINT_REFERENCE_STRING_BB";
const std::string GET_AVAILABLE_ENDPOINT_REFERENCES = "GET_AVAILABLE_ENDPOINT_REFERENCES_STRING_BB";
const std::string SETUP_MIRROR_PROVIDER = "SETUP_MIRROR_PROVIDER_ACTION_BB";
const std::string STRING_UNIT = "MDC_DIM_DIMLESS";
const std::string GET_DUT_MDIB = "GET_DUT_MDIB";
const std::string CONTROL_DUT_CHANNEL = "CONTROL_DUT_CHANNEL";
const std::string CONTROL_DUT_VMD = "CONTROL_DUT_VMD";
const std::string CONTROL_DUT_MDS = "CONTROL_DUT_MDS";
const std::string CONTROL_MM_CHANNEL = "CONTROL_MM_CHANNEL";
const std::string CONTROL_MM_VMD = "CONTROL_MM_VMD";
const std::string CONTROL_MM_MDS = "CONTROL_MM_MDS";
const std::string MM_BB_CONTROL_ENUM_POSTFIX = "_MM_CONTROL_ENUN_BB";
const std::string MM_BB_CONTROL_DO_NOTHING = "MM_BB_CONTROL_DO_NOTHING";
const std::string MM_BB_CONTROL_EMPTY_MESSAGE = "MM_CONTROL_EMPTY_MESSAGE_BB";
const std::string MM_BB_CONTROL_EMPTY_HEADER = "MM_CONTROL_EMPTY_HEADER_BB";
const std::string MM_BB_CONTROL_EMPTY_BODY = "MM_CONTROL_EMPTY_BODY_BB";
const std::string MM_BB_CONTROL_RANDOM_MSG_DEFECT = "MM_CONTROL_RANDOM_MSG_DEFECT_BB";
const std::string MM_BB_CONTROL_CODED_ENUM_POSTFIX = "_MM_CONTROL_ENUM_CODED_VALUE"


} //ACS
} //SDC
} //Data
} //SDCLib
#endif /* EXAMPLES_ABSTRACTCONSUMERSIMULATOR_NAMIGCONVENTION_H_ */
