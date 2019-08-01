#ifndef SCHEMA_PARTICIPANTMODEL_H
#define SCHEMA_PARTICIPANTMODEL_H

#include "SchemaExtensionPoint.h"

namespace SCHEMA
{
const static std::string SCHEMA_BICEPS_PARTICIPANTMODEL_NAME("BICEPS_ParticipantModel.xsd");

const static std::string SCHEMA_BICEPS_PARTICIPANTMODEL_CONTENT = std::string(R"(<?xml version="1.0" encoding="UTF-8"?>
<xsd:schema xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:ext="http://standards.ieee.org/downloads/11073/11073-10207-2017/extension" xmlns:pm="http://standards.ieee.org/downloads/11073/11073-10207-2017/participant" targetNamespace="http://standards.ieee.org/downloads/11073/11073-10207-2017/participant" elementFormDefault="qualified" attributeFormDefault="unqualified" xml:lang="en">
	<xsd:import namespace="http://standards.ieee.org/downloads/11073/11073-10207-2017/extension" schemaLocation=")" + SCHEMA_EXTENSIONPOINT_NAME + R"("/>
	<xsd:annotation>
		<xsd:documentation>This XML schema defines the 'Basic Integrated Clinical Environment Protocol Specification' (BICEPS) that is a Domain Information Model (DIM) for point of care medical device communication. It encompasses the device model and the corresponding messages. This XML Schema is based on the ISO/IEEE 11073-10201 Domain Information Model standard, which belongs to the "Point-of-care medical device communication" standard family in ISO/IEEE 11073. This standard family should not to be confused with the ISO/IEEE 11073 "Personal Health Device" standard family.
While former is based on the standards ISO/IEEE 11073-10101, 11073-10201, 11073-20101, and 11073-30200, the latter is based on ISO/IEEE 11073-20601 and ISO/IEEE 11073-104xx.
The Domain Information model is subdivided into two parts, a static part (referred to as Descriptor) that provides general information about the the hardware specification of the elements and a dynamic part (referred to as State) that may change during time.</xsd:documentation>
	</xsd:annotation>
	<!--Section: MDIB (Medical Device Information Base)-->
	<xsd:complexType name="Mdib">
		<xsd:annotation>
			<xsd:documentation>Root object that comprises the capability description of the represented MDSs in pm:MdDescription (descriptive part) as well as the current state in pm:MdState (state part).</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="MdDescription" type="pm:MdDescription" minOccurs="0"/>
			<xsd:element name="MdState" type="pm:MdState" minOccurs="0"/>
		</xsd:sequence>
		<xsd:attributeGroup ref="pm:MdibVersionGroup"/>
	</xsd:complexType>
	<xsd:complexType name="MdDescription">
		<xsd:annotation>
			<xsd:documentation>MdDescription is the root container to represent the descriptive part of the MDIB. The descriptive part describes the capabilities provided by a POC MEDICAL DEVICE, e.g., which measurements, alerts and settings it provides. As the descriptive part does not change as frequently as the state part, it is well-known as the (almost) static part of the MDIB. The MdDescription's counterpart is pm:MdState.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Mds" type="pm:MdsDescriptor" minOccurs="0" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>List of MDSs that are contained in the MDIB.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
		</xsd:sequence>
		<xsd:attribute name="DescriptionVersion" type="pm:VersionCounter" use="optional">
			<xsd:annotation>
				<xsd:documentation>Version number of the description. The version number is incremented by one every time the descriptive part changes. The implied value SHALL be "0".</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
	</xsd:complexType>
	<xsd:complexType name="MdState">
		<xsd:annotation>
			<xsd:documentation>MdState is the root container to represent the state part of the MDIB. The state part describes the values provided by a POC MEDICAL DEVICE, e.g., which measurement or alert values as well as patient demographics it provides. As the state part most often changes very frequently, it is well-known as the dynamic part of the MDIB. The MdState's counterpart is pm:MdDescription.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="State" type="pm:AbstractState" minOccurs="0" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>List of states that describe the volatile status of the objects in the MDIB.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
		</xsd:sequence>
		<xsd:attribute name="StateVersion" type="pm:VersionCounter" use="optional">
			<xsd:annotation>
				<xsd:documentation>Version number of the states. The version number is incremented by one every time the state part changes. The implied value SHALL be "0".</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
	</xsd:complexType>
	<!--Common Data Types-->
	<xsd:simpleType name="MeasurementValidity">
		<xsd:annotation>
			<xsd:documentation>Level of validity of a measured value.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Vld">
				<xsd:annotation>
					<xsd:documentation>Vld = Valid. A measured value that is correct from the perspective of the measuring device.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Vldated">
				<xsd:annotation>
					<xsd:documentation>Vldated = Validated Data. A measured value where the validity has been confirmed by an external actor, e.g., an operator, other than the POC MEDICAL DEVICE.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Ong">
				<xsd:annotation>
					<xsd:documentation>Ong = Measurement Ongoing. Indicates that a new measurement is just being taken and therefore measured value is not available.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Qst">
				<xsd:annotation>
					<xsd:documentation>Qst = Questionable. A measured value where correctness can not be guaranteed.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Calib">
				<xsd:annotation>
					<xsd:documentation>Calib = Calibration Ongoing. A measured value where correctness can not be guaranteed, because a calibration is currently going on.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Inv">
				<xsd:annotation>
					<xsd:documentation>Inv = Invalid. A measured value that is incorrect from the perspective of the measuring device.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Oflw">
				<xsd:annotation>
					<xsd:documentation>Oflw = Overflow. A measured value where correctness cannot be guaranteed as it is above all defined technical ranges.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Uflw">
				<xsd:annotation>
					<xsd:documentation>Uflw = Underflow. A measured value where correctness cannot be guaranteed as it is below all defined technical ranges.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="NA">
				<xsd:annotation>
					<xsd:documentation>NA = Not Available. No value can be derived, e.g., if a sensor is not placed correctly.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="Timestamp">
		<xsd:annotation>
			<xsd:documentation>An unsigned 64-bit integer value that represents a timestamp.
			
__R5001: A timestamp SHALL count the milliseconds between the current time and midnight, January 1, 1970 UTC without leap seconds.__

__R5002: Timestamps are an optional feature of the MDIB. If anywhere in the MDIB a timestamp is used, the SERVICE PROVIDER SHALL provide a pm:ClockDescriptor ELEMENT.__

NOTE 1—Typically all systems assume that a day has 86400 seconds.
NOTE 2—While the unit of time of pm:Timestamp is a millisecond, the granularity of the value depends on the hardware/software system and might be larger (e.g., tens of milliseconds).</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:unsignedLong"/>
	</xsd:simpleType>
	<xsd:simpleType name="VersionCounter">
		<xsd:annotation>
			<xsd:documentation>A version counter to provide versionized MDIB objects. The initial value of a version counter SHALL be "0".

__R5003: VersionCounter values SHALL never be decremented.__</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:unsignedLong"/>
	</xsd:simpleType>
	<xsd:simpleType name="ReferencedVersion">
		<xsd:annotation>
			<xsd:documentation>In contrast to pm:VersionCounter, ReferencedVersion does not represent a version of an MDIB object, but a reference to a particular version of an MDIB object.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="pm:VersionCounter"/>
	</xsd:simpleType>
	<xsd:attributeGroup name="MdibVersionGroup">
		<xsd:annotation>
			<xsd:documentation>MdibVersionGroup is a triple populated with a pm:VersionCounter, an instance id (xsd:unsignedLong) and a sequence id (xsd:anyURI).

Semantics of instance and sequence identifiers relate to WS-Discovery [WS-Discovery]. In contrast to WS-Discovery, in which the instance id is mandatory and the sequence id is optional, this standard defines the sequence id to be REQUIRED and the instance id to be OPTIONAL.</xsd:documentation>
		</xsd:annotation>
		<xsd:attribute name="MdibVersion" type="pm:VersionCounter" use="optional">
			<xsd:annotation>
				<xsd:documentation>The unique change version number of the MDIB. The implied value of the initial version SHALL be "0".</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="SequenceId" type="xsd:anyURI" use="required">
			<xsd:annotation>
				<xsd:documentation>SequenceId identifies a sequence within the context of ./@InstanceId.

__R5029: SequenceId SHALL be compared per RFC 3986 Section 6.2.1 Simple String Comparison [RFC3986].__</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="InstanceId" type="xsd:unsignedLong">
			<xsd:annotation>
				<xsd:documentation>Value that indicates an instantiation counter.

__R5004: If InstanceId is used, it SHALL be incremented by a positive value (>= 1) when the SequenceId has changed.__

NOTE—This occurs each time the POC MEDICAL DEVICE has gone down, lost state, and came back up again.

__R5005: InstanceId SHOULD NOT be incremented otherwise than defined in R5004.__

NOTE 1—Means to set this value include, but are not limited to:

- A counter that is incremented on each cold boot
- The boot time of the POC MEDICAL DEVICE, expressed as seconds elapsed since midnight January 1, 1970

NOTE 2—The MDIB version's instance id is different to the pm:InstanceIdentifier data type.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
	</xsd:attributeGroup>
	<xsd:simpleType name="CodeIdentifier">
		<xsd:annotation>
			<xsd:documentation>CodeIdentifier defines an arbitrary CODE identifier with a minimum length of 1 character.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:minLength value="1"/>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="SymbolicCodeName">
		<xsd:annotation>
			<xsd:documentation>SymbolicCodeName is a symbolic, programmatic form of a pm:CodeIdentifier term.

NOTE—SymbolicCodeName is the equivalent of the Reference ID attribute that is defined in IEEE 11073-10101.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:minLength value="1"/>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="LocalizedTextRef">
		<xsd:annotation>
			<xsd:documentation>LocalizedTextRef defines a reference to a localized text.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:minLength value="1"/>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="LocalizedTextContent">
		<xsd:annotation>
			<xsd:documentation>Content restriction for pm:LocalizedText ELEMENTs.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:minLength value="0"/>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="LocalizedTextWidth">
		<xsd:annotation>
			<xsd:documentation>LocalizedTextWidth indicates the width of a localized text based on the number of fullwidth characters in order to allow a SERVICE CONSUMER an effective filtering and querying for translations.

In the following, a line is defined as the content of the text from either the beginning of the text or the beginning of a previous line until the next occurance of period mark, question mark, exclamation mark, or paragraph.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="xs">
				<xsd:annotation>
					<xsd:documentation>A line has 4 or less fullwidth characters.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="s">
				<xsd:annotation>
					<xsd:documentation>A line has 8 or less fullwidth characters.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="m">
				<xsd:annotation>
					<xsd:documentation>A line has 12 or less fullwidth characters.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="l">
				<xsd:annotation>
					<xsd:documentation>A line has 16 or less fullwidth characters.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="xl">
				<xsd:annotation>
					<xsd:documentation>A line has 20 or less fullwidth characters.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="xxl">
				<xsd:annotation>
					<xsd:documentation>A line has 21 or more fullwidth characters.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="LocalizedText">
		<xsd:annotation>
			<xsd:documentation>LocalizedText is a bundled ELEMENT to reference texts in different languages or to provide a text in a specific language.

The goal of text references is to shrink the overall size of the MDIB by only providing a single reference to a text file that translates a text into multiple languages instead of flooding the MDIB with all translated texts. Referenced texts can be requested by the LOCALIZATION SERVICE. If no LOCALIZATION SERVICE exist, the application can make use of LocalizedText to represent a text in a single language.

__R5047: If ./@Lang and ./@Ref are present, then the text SHALL be only available in the language specified by ./@Lang.__

__R5048: If ./@Lang is present and ./@Ref is not present, then ./@Lang SHALL specify the language of the LocalizedText's content. The Text is not available through the LOCALIZATION SERVICE.__

__R5049: If ./@Lang is not present and ./@Ref is present, then the text SHALL be available through the LOCALIZATION SERVICE.__

__R5050: If ./@Lang and ./@Ref are not present, then the language of the LocalizedText's content is unknown. The text SHALL NOT be available through the LOCALIZATION SERVICE.__</xsd:documentation>
		</xsd:annotation>
		<xsd:simpleContent>
			<xsd:extension base="pm:LocalizedTextContent">
				<xsd:attribute name="Ref" type="pm:LocalizedTextRef">
					<xsd:annotation>
						<xsd:documentation>References a text in a localized text file.

Text references SHALL be unique regardless of any HANDLE name.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="Lang" type="xsd:language">
					<xsd:annotation>
						<xsd:documentation>Lang specifies the language of the localized text.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="Version" type="pm:ReferencedVersion">
					<xsd:annotation>
						<xsd:documentation>Version defines the current revision of the referenced text in the localized text file.

__R5006: Texts might change over time, but references are per definition unique and typically do not change. To check if a text that is referenced by ./@Ref has changed, pm:LocalizedText SHALL include Version if ./@Ref is set.

NOTE—This saves to query a localized text file if the referencing ELEMENT has changed, but the referenced text has not. If Version is not given, a client has to assume that the text changes every time the referencing ELEMENT changes. In this case, the client is encouraged to query the localized text file on each modification.__

__R5007: To keep things simple, every translated text in a localized text file that belongs to a particular reference SHALL share the same version number.__

NOTE—From this it follows that if Version has changed, every translation of a referenced text is obsolete even if only a single translation has changed.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="TextWidth" type="pm:LocalizedTextWidth">
					<xsd:annotation>
						<xsd:documentation>Text width as defined in pm:LocalizedTextWidth.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:simpleContent>
	</xsd:complexType>
	<xsd:complexType name="CodedValue">
		<xsd:annotation>
			<xsd:documentation>In general, in an interoperability format, objects, attributes, and methods are identified by nomenclature codes. CodedValue offers the ability to represent such nomenclature codes.

Two CodedValue objects C1 and C2 are equivalent, if

- C1/@Code equals C2/@Code
- C1/@CodingSystem equals C2/@CodingSystem, both with expanded default values
- C1/@CodingSystemVersion equals C2/@CodingSystemVersion
- If there exists a CodedValue object T1 in C1/pm:Translation and a CodedValue object T2 in C2/pm:Translation such that T1 and T2 are equivalent, C1 and T2 are equivalent, or C2 and T1 are equivalent.

NOTE 1—In case that ./@CodingSystem is not explicitly defined in CodedValue, it is replaced implicitly by a default identifier. The ./@CodingSystem ATTRIBUTE is then called "expanded". 
NOTE 2—As prescribed in ./@CodingSystemVersion, a version is set only if a unique version identification by ./@CodingSystem is not possible. Hence, there can be no implicit version mismatch.
NOTE 3—Equivalence between CodedValue objects is not necessarily transitive.
			</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="CodingSystemName" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>Human-readable name of the CODING SYSTEM that is described by pm:CodedValue/@CodingSystem.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
			<xsd:element name="ConceptDescription" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>Multiple OPTIONAL human-readable texts that describe the CODE in more detail.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
			<xsd:element name="Translation" minOccurs="0" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>Set of alternative or equivalent representations.</xsd:documentation>
				</xsd:annotation>
				<xsd:complexType>
					<xsd:sequence>
						<xsd:element ref="ext:Extension" minOccurs="0"/>
					</xsd:sequence>
					<xsd:attribute name="Code" type="pm:CodeIdentifier" use="required">
						<xsd:annotation>
							<xsd:documentation>A code as defined by pm:CodedValue/@Code.</xsd:documentation>
						</xsd:annotation>
					</xsd:attribute>
					<xsd:attribute name="CodingSystem" type="xsd:anyURI">
						<xsd:annotation>
							<xsd:documentation>A coding system as defined by pm:CodedValue/@CodingSystem.</xsd:documentation>
						</xsd:annotation>
					</xsd:attribute>
					<xsd:attribute name="CodingSystemVersion" type="xsd:string">
						<xsd:annotation>
							<xsd:documentation>A coding system version as defined by pm:CodedValue/@CodingSystemVersion.</xsd:documentation>
						</xsd:annotation>
					</xsd:attribute>
				</xsd:complexType>
			</xsd:element>
		</xsd:sequence>
		<xsd:attribute name="Code" type="pm:CodeIdentifier" use="required">
			<xsd:annotation>
				<xsd:documentation>REQUIRED unique identifier of the CODE in the CODING SYSTEM.

Example: as "20720" from Block 2, of IEEE 11073-10101:2004, is the id for "MDC_PRESS_AWAY", the context-free CODE (CF_Code10) is "151792" which represents the unique identifier used within IEEE 11073-10101:2004.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="CodingSystem" type="xsd:anyURI">
			<xsd:annotation>
				<xsd:documentation>Unique identifier of a CODING SYSTEM that pm:CodedValue/@Code originating from.

If no CODING SYSTEM is defined, the implied value SHALL be "urn:oid:1.2.840.10004.1.1.1.0.0.1", which refers to ISO/IEC 11073-10101.

Example: "urn:oid:1.2.840.10004.1.1.1.0.0.1" for the ISO/IEC 11073-10101.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="CodingSystemVersion" type="xsd:string">
			<xsd:annotation>
				<xsd:documentation>CodingSystemVersion is a particular version of the CODING SYSTEM defined by pm:CodedValue/@CodingSystem. CodingSystemVersion SHALL be set if multiple versions of the underlying CODING SYSTEM exist and a unique identification of the CODED VALUE is not possible by other means.

Example: "20041215" for the ISO/IEC 11073-10101:2004, as it is the release date of the standard's first edition.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="SymbolicCodeName" type="pm:SymbolicCodeName">
			<xsd:annotation>
				<xsd:documentation>See pm:SymbolicCodeName.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
	</xsd:complexType>
	<!-- Instance Identifier & CodedValue 
	see 			http://www.hl7.org/documentcenter/public_temp_50880C1B-1C23-BA17-0C922B819FE091A2/standards/V3/core_principles/infrastructure/coreprinciples/v3modelcoreprinciples.html#coreP_Identifying-ii-cd 
-->
	<xsd:complexType name="InstanceIdentifier">
		<xsd:annotation>
			<xsd:documentation>An identifier that uniquely identifies a thing or object.

Examples: object identifiers for medical record numbers, order ids, location ids, etc. InstanceIdentifier is defined in accordance to [InstanceIdentifier].

./@Root and ./@Extension of an instance identifier do not identify the type of the object being identified, or the type of the association between the object and the identifier - they only form the identifier itself. The identifier type SHALL be expressed by ./Type.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Type" type="pm:CodedValue" minOccurs="0">
				<xsd:annotation>
					<xsd:documentation>Type designates the type of the instance identifier, e.g., whether it is an MRN, license number, visit number etc.

Since it is possible that semantic meaning of an instance identifier is comprehensively conveyed using the encompassing XML ELEMENTs, Type is OPTIONAL.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
			<xsd:element name="IdentifierName" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>IdentifierName is a localized human-readable name for the namespace represented in ./@Root.

NOTE—IdentifierName has no computational value and hence can never modify the meaning of ./@Root. The purpose of IdentifierName is to assist an unaided human interpreter of an instance identifier value to interpret the identifier. Applications ought not to perform any decision-making, matching, filtering or other processing based on this presence or value of this property. It is for display and development assistance only.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
		</xsd:sequence>
		<xsd:attribute name="Root">
			<xsd:annotation>
				<xsd:documentation>A unique identifier that guarantees the global uniqueness of the instance identifier. Root alone is allowed to build the entire instance identifier.

If ./@Extension is present, Root is the unique identifier for the "namespace" of the identifier in ./@Extension.

In situations where ./@Extension is known, but Root is not known, the implied value of a non-existent Root SHALL match the value defined in R0135. 

NOTE—Example: a POC MEDICAL DEVICE with an attached simple bar code scanner could create a new instance identifier with an unknown root and an extension that is set to the bar code number. Root is then applied later in time.</xsd:documentation>
			</xsd:annotation>
			<xsd:simpleType>
				<xsd:restriction base="xsd:anyURI">
					<xsd:minLength value="1"/>
				</xsd:restriction>
			</xsd:simpleType>
		</xsd:attribute>
		<xsd:attribute name="Extension" use="optional">
			<xsd:annotation>
				<xsd:documentation>A character string as a unique identifier within the scope of pm:InstanceIdentifier/pm:Root.
If a non-null Extension exists, pm:InstanceIdentifier/pm:Root specifies a namespace ("assigning authority" or "identifier type").

__R5008: Extension MAY be empty if pm:InstanceIdentifier/pm:Root is the complete unique identifier.__

__R5009: If pm:InstanceIdentifier/pm:Root is not a complete unique identifier and Extension is not known, then Extension SHALL be populated with a null-flavor "Unknown".__

NOTE—How the null-flavor "Unknown" is encoded, depends on the use-case and type of pm:InstanceIdentifier/pm:Root URI.</xsd:documentation>
			</xsd:annotation>
			<xsd:simpleType>
				<xsd:restriction base="xsd:string">
					<xsd:minLength value="1"/>
				</xsd:restriction>
			</xsd:simpleType>
		</xsd:attribute>
	</xsd:complexType>
	<xsd:complexType name="Range">
		<xsd:annotation>
			<xsd:documentation>A range of decimal values which provides a lower and an upper bound as well as a step width.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
		</xsd:sequence>
		<xsd:attribute name="Lower" type="xsd:decimal" use="optional">
			<xsd:annotation>
				<xsd:documentation>The including lower bound of the range.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="Upper" type="xsd:decimal" use="optional">
			<xsd:annotation>
				<xsd:documentation>The including upper bound of the range.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="StepWidth" type="xsd:decimal" use="optional">
			<xsd:annotation>
				<xsd:documentation>The numerical distance between two values in the range of the given upper and lower bound.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="RelativeAccuracy" type="xsd:decimal" use="optional">
			<xsd:annotation>
				<xsd:documentation>Maximum relative error in relation to the correct value within the given range.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="AbsoluteAccuracy" type="xsd:decimal" use="optional">
			<xsd:annotation>
				<xsd:documentation>Maximum absolute error in relation to the correct value within the given range.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
	</xsd:complexType>
	<xsd:complexType name="Measurement">
		<xsd:annotation>
			<xsd:documentation>Measurement describes a measurement and is used only for stateful object attributes that do not have a reference to a descriptor object.

Example: Weight of a patient.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="MeasurementUnit" type="pm:CodedValue">
				<xsd:annotation>
					<xsd:documentation>The unit (dimension) of pm:Measurement.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
		</xsd:sequence>
		<xsd:attribute name="MeasuredValue" type="xsd:decimal" use="required">
			<xsd:annotation>
				<xsd:documentation>The value of pm:Measurement.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
	</xsd:complexType>
	<xsd:simpleType name="SafetyClassification">
		<xsd:annotation>
			<xsd:documentation>SafetyClassification allows POC MEDICAL DEVICE manufacturers to limit their responsibility for the provided objects that allow informational use or use in clinical functions. It reflects the quality of the respective data from the risk management perspective of the data provider.

Enumeration values prefixed with "Med" indicate that the manufacturer has considered a clinical function related to the object in its development process, particularly the risk management, software development, usability, and verification process.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Inf">
				<xsd:annotation>
					<xsd:documentation>Inf = Informational. The descriptor and the related state information are intended to be used for information purposes only. They are not intended to be used in clinical functions.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="MedA">
				<xsd:annotation>
					<xsd:documentation>MedA = Medical Class A. The descriptor and related state information are intended to be used in clinical functions, specifically for general display in order to support patient and device monitoring. The displayed data is not intended to be used as sole source for diagnostic or therapeutic decisions. Deviations from this intended use are in the sole responsibility of the SERVICE CONSUMER.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="MedB">
				<xsd:annotation>
					<xsd:documentation>MedB = Medical Class B. The descriptor and related state information are intended to be used in clinical functions. The manufacturer has specified and considered a specific intended use for the data, which could result in non-serious injury. Deviations from this intended use are in the sole responsibility of the SERVICE CONSUMER.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="MedC">
				<xsd:annotation>
					<xsd:documentation>MedC = Medical Class C. The descriptor and related state information are intended to be used in clinical functions. The manufacturer has specified and considered a specific intended use for the data, which could result in serious injury. Deviations from this intended use are in the sole responsibility of the SERVICE CONSUMER.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="ComponentActivation">
		<xsd:annotation>
			<xsd:documentation>Activation state of a component, i.e., any type that is derived from pm:AbstractComponentState and pm:AbstractMetricState.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="On">
				<xsd:annotation>
					<xsd:documentation>The component is operating.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="NotRdy">
				<xsd:annotation>
					<xsd:documentation>NotRdy = Not Ready. The component is not ready to be operated and not operating, but initialization is ongoing.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="StndBy">
				<xsd:annotation>
					<xsd:documentation>StndBy = Stand By. The component is ready to be operated, but not currently operating.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Off">
				<xsd:annotation>
					<xsd:documentation>The component is inactive.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Shtdn">
				<xsd:annotation>
					<xsd:documentation>Shtdn = Shutdown. The component is ceasing from being ready to be operated or operating, but not yet inactive.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Fail">
				<xsd:annotation>
					<xsd:documentation>Fail = Failure. The component has detected a failure and is not ready to be operated.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="ApprovedJurisdictions">
		<xsd:annotation>
			<xsd:documentation>List of regions in which a DEVICE COMPONENT is approved to be operated. If the list does not contain any entries, then the DEVICE COMPONENT is not approved for any region.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element name="ApprovedJurisdiction" type="pm:InstanceIdentifier" minOccurs="0" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>Region in which the DEVICE COMPONENT is approved to be operated.

NOTE—See also: https://unstats.un.org/unsd/methodology/m49/</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
		</xsd:sequence>
	</xsd:complexType>
	<xsd:complexType name="OperatingJurisdiction">
		<xsd:annotation>
			<xsd:documentation>The current region information that is configured for a component. The preferred root SHOULD be https://unstats.un.org/unsd/methodology/m49, which addresses the "Standard country or area codes for statistical use (M49)\". Example: a root of "https://unstats.un.org/unsd/methodology/m49" with an extension value of "276" addresses Germany.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:InstanceIdentifier"/>
		</xsd:complexContent>
	</xsd:complexType>
	<!--Section: Base Descriptor and State Objects-->
	<xsd:simpleType name="Handle">
		<xsd:annotation>
			<xsd:documentation>A HANDLE is used to efficiently identify an object in the MDIB.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:minLength value="1"/>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="HandleRef">
		<xsd:annotation>
			<xsd:documentation>HandleRef describes a HANDLE reference. It is used to form logical connections to ELEMENTs that possess a pm:Handle ATTRIBUTE.

Example: a METRIC state is associated with a METRIC descriptor (pm:AbstractDescriptor/@Handle) by means of an ATTRIBUTE of type pm:HandleRef (see pm:AbstractState/@DescriptorHandle).</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:minLength value="1"/>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="PhysicalConnectorInfo">
		<xsd:annotation>
			<xsd:documentation>PhysicalConnectorInfo defines a number in order to allow to guide the clinical user for a failure, e.g., in case of a disconnection of a sensor or an ultrasonic handpiece.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Label" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>A human-readable label that describes the physical connector.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
		</xsd:sequence>
		<xsd:attribute name="Number" type="xsd:int">
			<xsd:annotation>
				<xsd:documentation>Number designates the connector number of the physical connector.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
	</xsd:complexType>
	<xsd:complexType name="AbstractDescriptor">
		<xsd:annotation>
			<xsd:documentation>AbstractDescriptor defines foundational meta information of any object that is included in the descriptive part of the MDIB. Any descriptor object is derived from pm:AbstractDescriptor. The AbstractDescriptor's counterpart is pm:AbstractState.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Type" type="pm:CodedValue" minOccurs="0">
				<xsd:annotation>
					<xsd:documentation>The descriptor type that provides specific information about the descriptor instance, e.g., an pm:MdsDescriptor that designates an anesthesia workstation.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
		</xsd:sequence>
		<xsd:attribute name="Handle" type="pm:Handle" use="required">
			<xsd:annotation>
				<xsd:documentation>The unique HANDLE of the descriptor. The HANDLE can be used by pm:AbstractState to reference the descriptor.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="DescriptorVersion" type="pm:VersionCounter" use="optional">
			<xsd:annotation>
				<xsd:documentation>DescriptorVersion is incremented by one with every descriptor modification. The implied value for the initial descriptor instance SHALL be "0".</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="SafetyClassification" type="pm:SafetyClassification" use="optional">
			<xsd:annotation>
				<xsd:documentation>The safety classification of the data that is described with this descriptor. The implied value SHALL be "Inf".</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
	</xsd:complexType>
	<xsd:complexType name="AbstractState">
		<xsd:annotation>
			<xsd:documentation>AbstractState defines foundational meta information of any object that is included in the state part of the MDIB. Any state object is derived from pm:AbstractState. The pm:AbstractState's counterpart is pm:AbstractDescriptor.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
		</xsd:sequence>
		<xsd:attribute name="StateVersion" type="pm:VersionCounter">
			<xsd:annotation>
				<xsd:documentation>StateVersion is incremented by one with every state modification. The implied value for the initial state instance SHALL be "0".</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="DescriptorHandle" type="pm:HandleRef" use="required">
			<xsd:annotation>
				<xsd:documentation>The HANDLE reference of a descriptor to which the state belongs.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="DescriptorVersion" type="pm:ReferencedVersion">
			<xsd:annotation>
				<xsd:documentation>The current version of the descriptor to that the state belongs to. The implied value for the initial state instance SHALL be "0".</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
	</xsd:complexType>
	<xsd:complexType name="AbstractMultiState">
		<xsd:annotation>
			<xsd:documentation>AbstractMultiState is derived from pm:AbstractState. In contrast to pm:AbstractState, AbstractMultiState possesses a HANDLE name. The HANDLE name uniquely identifies the state, which is required if the relation to a descriptor is ambiguous.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractState">
				<xsd:sequence>
					<xsd:element name="Category" type="pm:CodedValue" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>A CODED VALUE that allows to categorize a multi state inside the set of multi states that belong to a descriptor of a certain type.
NOTE—By using the pm:AbstractMultiState/pm:Category it is possible to represent, e.g., different steps in a workflow (multiple states) with different association states. This is in contrast to the pm:WorkflowContextDescriptor/pm:Type where different workflow types are described that the POC MEDICAL DEVICE supports. See Clause 5.2.6 for more details.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="Handle" type="pm:Handle" use="required">
					<xsd:annotation>
						<xsd:documentation>A name to uniquely identify the state.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<!--Section: Device Components-->
	<xsd:complexType name="AbstractDeviceComponentDescriptor">
		<xsd:annotation>
			<xsd:documentation>AbstractDeviceComponentDescriptor describes a basic DEVICE COMPONENT.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractDescriptor">
				<xsd:sequence>
					<xsd:element name="ProductionSpecification" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>List of production specifications of the component. The production specification describes ELEMENTs such as part numbers, serial numbers, revisions, etc.</xsd:documentation>
						</xsd:annotation>
						<xsd:complexType>
							<xsd:sequence>
								<xsd:element name="SpecType" type="pm:CodedValue">
									<xsd:annotation>
										<xsd:documentation>SpecType is the specification type, such as serial number, part number, hardware revision, software revision, etc.</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
								<xsd:element name="ProductionSpec" type="xsd:string">
									<xsd:annotation>
										<xsd:documentation>ProductionSpec describes the printable string of the production specification ELEMENT.</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
								<xsd:element name="ComponentId" type="pm:InstanceIdentifier" minOccurs="0">
									<xsd:annotation>
										<xsd:documentation>Describes the internal component unique identification. This is a provision for manufacturer specific standard components using a private object identifier (OID).</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
							</xsd:sequence>
						</xsd:complexType>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="AbstractComplexDeviceComponentDescriptor">
		<xsd:annotation>
			<xsd:documentation>AbstractComplexDeviceComponentDescriptor adds an OPTIONAL pm:AlertSystemDescriptor and pm:ScoDescriptor to pm:AbstractDeviceComponentDescriptor.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractDeviceComponentDescriptor">
				<xsd:sequence>
					<xsd:element name="AlertSystem" type="pm:AlertSystemDescriptor" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>An OPTIONAL ALERT SYSTEM that supervises conditions for all sublevels in the hierarchy including the ALERT SYSTEM hosting node itself.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="Sco" type="pm:ScoDescriptor" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>A service control object to define remote control operations. Any pm:AbstractOperationDescriptor/@OperationTarget within this SCO SHALL only reference this or child descriptors within the CONTAINMENT TREE.

NOTE—In modular systems, dynamically plugged-in modules would typically be modeled as VMDs. Such VMDs potentially have their own SCO. In every other case, SCO operations are modeled in pm:MdsDescriptor/pm:Sco.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:simpleType name="CalibrationState">
		<xsd:annotation>
			<xsd:documentation>Calibration state of a component.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="No">
				<xsd:annotation>
					<xsd:documentation>No = Not Calibrated. Defines that a component is not calibrated.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Req">
				<xsd:annotation>
					<xsd:documentation>Req = Calibration Required. Defines that a component requires a calibration.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Run">
				<xsd:annotation>
					<xsd:documentation>Run = Running. Defines that a calibration for a component is running.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Cal">
				<xsd:annotation>
					<xsd:documentation>Cal = Calibrated. Defines that a component is calibrated.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Oth">
				<xsd:annotation>
					<xsd:documentation>Oth = Other. The calibration state is defined by other means.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="CalibrationType">
		<xsd:annotation>
			<xsd:documentation>Type of a calibration method.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Offset">
				<xsd:annotation>
					<xsd:documentation>Offset calibration.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Gain">
				<xsd:annotation>
					<xsd:documentation>Gain calibration</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="TP">
				<xsd:annotation>
					<xsd:documentation>Two point calibration.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Unspec">
				<xsd:annotation>
					<xsd:documentation>Unspecified calibration type.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="CalibrationInfo">
		<xsd:annotation>
			<xsd:documentation>Provides information in terms of component calibration. By default, it only maintains a calibration flag.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="CalibrationDocumentation" minOccurs="0" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>CalibrationDocumentation provides information regarding necessary or performed calibration steps including potential calibration results like accuracy.</xsd:documentation>
				</xsd:annotation>
				<xsd:complexType>
					<xsd:sequence>
						<xsd:element name="Documentation" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded">
							<xsd:annotation>
								<xsd:documentation>Human-readable documentation of a CalibrationDocumentation entry.</xsd:documentation>
							</xsd:annotation>
						</xsd:element>
						<xsd:element name="CalibrationResult" minOccurs="0" maxOccurs="unbounded">
							<xsd:annotation>
								<xsd:documentation/>
							</xsd:annotation>
							<xsd:complexType>
								<xsd:sequence>
									<xsd:element name="Code" type="pm:CodedValue">
										<xsd:annotation>
											<xsd:documentation>Code that semantically describes the calibration result.</xsd:documentation>
										</xsd:annotation>
									</xsd:element>
									<xsd:element name="Value" type="pm:Measurement">
										<xsd:annotation>
											<xsd:documentation>Measurement that represents the value related to that specific calibration result.</xsd:documentation>
										</xsd:annotation>
									</xsd:element>
								</xsd:sequence>
							</xsd:complexType>
						</xsd:element>
					</xsd:sequence>
				</xsd:complexType>
			</xsd:element>
		</xsd:sequence>
		<xsd:attribute name="ComponentCalibrationState" type="pm:CalibrationState">
			<xsd:annotation>
				<xsd:documentation>ATTRIBUTE definition of ComponentCalibration.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="Type" type="pm:CalibrationType" use="optional">
			<xsd:annotation>
				<xsd:documentation>Type of the calibration. The implied value SHALL be "Unspec".</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="Time" type="pm:Timestamp" use="optional">
			<xsd:annotation>
				<xsd:documentation>Time of the calibration.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
	</xsd:complexType>
	<xsd:complexType name="AbstractDeviceComponentState">
		<xsd:annotation>
			<xsd:documentation>State of a component that is part of an MDS.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractState">
				<xsd:sequence>
					<xsd:element name="CalibrationInfo" type="pm:CalibrationInfo" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Provides information about the last calibration that was performed.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="NextCalibration" type="pm:CalibrationInfo" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Provides information about the next calibration that will be performed.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="PhysicalConnector" type="pm:PhysicalConnectorInfo" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>The physical connector number for this component, see pm:PhysicalConnectorInfo.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="ActivationState" type="pm:ComponentActivation">
					<xsd:annotation>
						<xsd:documentation>See pm:ComponentActivation. The implied value SHALL be "On".</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="OperatingHours" type="xsd:unsignedInt">
					<xsd:annotation>
						<xsd:documentation>OPTIONAL amount of operating hours (e.g., an OR light). There are no further semantics defined.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="OperatingCycles" type="xsd:int">
					<xsd:annotation>
						<xsd:documentation>OPTIONAL amount of operarting cycles, e.g., the number of measurements taken within the component. There are no further semantics defined.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="AbstractComplexDeviceComponentState">
		<xsd:annotation>
			<xsd:documentation>AbstractComplexDeviceComponentState acts as a base class for DEVICE COMPONENT states that have alerting and SCO capabilities.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractDeviceComponentState"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="MdsDescriptor">
		<xsd:annotation>
			<xsd:documentation>MdsDescriptor represents an MDS that in turn represents a POC MEDICAL DEVICE such as an anesthesia workstation. It contains an abstraction of the hardware specification of a POC MEDICAL DEVICE plus a list of VMDs, contextual information and clock object.

NOTE—The IEEE 11073-10201 has different specializations that are all representable by MdsDescriptor.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractComplexDeviceComponentDescriptor">
				<xsd:sequence>
					<xsd:element name="MetaData" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Describes POC MEDICAL DEVICE meta data.</xsd:documentation>
						</xsd:annotation>
						<xsd:complexType>
							<xsd:sequence>
								<xsd:element ref="ext:Extension" minOccurs="0"/>
								<xsd:element name="Udi" minOccurs="0" maxOccurs="unbounded">
									<xsd:annotation>
										<xsd:documentation>UDI fragments as defined by the FDA.

NOTE 1—The amount of ELEMENTs is unbounded in order to support the provision of UDIs from different jurisdictions.
NOTE 2—If needed, the UDI's distinct identification code can be inserted as an extension to the MetaData object.</xsd:documentation>
									</xsd:annotation>
									<xsd:complexType>
										<xsd:sequence>
											<xsd:element ref="ext:Extension" minOccurs="0"/>
											<xsd:element name="DeviceIdentifier" type="xsd:string">
												<xsd:annotation>
													<xsd:documentation>A mandatory, fixed portion of a UDI that identifies the labeler and the specific version or model of a device.</xsd:documentation>
												</xsd:annotation>
											</xsd:element>
											<xsd:element name="HumanReadableForm" type="xsd:string">
												<xsd:annotation>
													<xsd:documentation>UDI human readable form as printed on the barcode.</xsd:documentation>
												</xsd:annotation>
											</xsd:element>
											<xsd:element name="Issuer" type="pm:InstanceIdentifier">
												<xsd:annotation>
													<xsd:documentation>Organization that has issued the UDI.</xsd:documentation>
												</xsd:annotation>
											</xsd:element>
											<xsd:element name="Jurisdiction" type="pm:InstanceIdentifier" minOccurs="0">
												<xsd:annotation>
													<xsd:documentation>Jurisdiction that the UDI is valid for. If no value is defined, then the UDI is not bound to a specific jurisdiction.</xsd:documentation>
												</xsd:annotation>
											</xsd:element>
										</xsd:sequence>
									</xsd:complexType>
								</xsd:element>
								<xsd:element name="LotNumber" type="xsd:string" minOccurs="0">
									<xsd:annotation>
										<xsd:documentation>OPTIONAL lot number of manufacturer.</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
								<xsd:element name="Manufacturer" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded">
									<xsd:annotation>
										<xsd:documentation>OPTIONAL texts that describe the manufacturer name.</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
								<xsd:element name="ManufactureDate" type="xsd:dateTime" minOccurs="0">
									<xsd:annotation>
										<xsd:documentation>OPTIONAL date when the device was made.</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
								<xsd:element name="ExpirationDate" type="xsd:dateTime" minOccurs="0">
									<xsd:annotation>
										<xsd:documentation>OPTIONAL date and time of expiry of the device (if applicable).</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
								<xsd:element name="ModelName" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded">
									<xsd:annotation>
										<xsd:documentation>OPTIONAL texts that describe the model name.</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
								<xsd:element name="ModelNumber" type="xsd:string" minOccurs="0">
									<xsd:annotation>
										<xsd:documentation>OPTIONAL model number of the MDS.</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
								<xsd:element name="SerialNumber" type="xsd:string" minOccurs="0" maxOccurs="unbounded">
									<xsd:annotation>
										<xsd:documentation>OPTIONAL serial numbers of the system.</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
							</xsd:sequence>
						</xsd:complexType>
					</xsd:element>
					<xsd:element name="SystemContext" type="pm:SystemContextDescriptor" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>See pm:SystemContextDescriptor.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="Clock" type="pm:ClockDescriptor" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>If supported, an MDS inserts date/time capabilities here.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="Battery" type="pm:BatteryDescriptor" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>If supported, an MDS inserts battery capabilities here.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="ApprovedJurisdictions" type="pm:ApprovedJurisdictions" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>List of regions in which the the MDS is approved to be operated. If the list does not contain any entries, then the MDS is not approved for any region. If the list is not specified, then the MDS is approved to be operated in any region.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="Vmd" type="pm:VmdDescriptor" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>Ordered list of VMDs that belongs to the MDS. The list is ordered by the position of the VMD in the list where the ELEMENT with a lower list index has a higher clinical relevance than any entry with a higher list index. The SERVICE PROVIDER defines the clinical relevance and MAY reorder the list at any time.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:simpleType name="MdsOperatingMode">
		<xsd:annotation>
			<xsd:documentation>MdsOperatingMode defines the interpretation constraints of the data that is provided by an MDS.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Nml">
				<xsd:annotation>
					<xsd:documentation>Nml = Normal. The POC MEDICAL DEVICE operates in a mode that supports the fulfillment of its clinical functions.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Dmo">
				<xsd:annotation>
					<xsd:documentation>Dmo = Demo. The POC MEDICAL DEVICE operates in a mode that is intended for demonstration purposes only. Arbitrary values are generated.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Srv">
				<xsd:annotation>
					<xsd:documentation>Srv = Service. The POC MEDICAL DEVICE operates in a mode that is intended for services purposes only.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Mtn">
				<xsd:annotation>
					<xsd:documentation>MTN = Maintenance. The POC MEDICAL DEVICE operates in a mode that is intended for maintenance purposes only.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="MdsState">
		<xsd:annotation>
			<xsd:documentation>Definition of the state of an pm:MdsDescriptor.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractComplexDeviceComponentState">
				<xsd:sequence>
					<xsd:element name="OperatingJurisdiction" type="pm:OperatingJurisdiction" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>The current region information that is configured for the MDS. See also pm:OperatingJurisdiction. OperatingJurisdiction SHALL NOT be inserted if there is no pm:MdsDescriptor/pm:ApprovedJurisdictions list present.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="Lang" type="xsd:language">
					<xsd:annotation>
						<xsd:documentation>The current locale information that is configured for an MDS in accordance with RFC 5646 (see http://tools.ietf.org/html/rfc5646). For example, this is the language that is used for display purposes on the UI. The implied value SHALL be "en".</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="OperatingMode" type="pm:MdsOperatingMode" use="optional">
					<xsd:annotation>
						<xsd:documentation>The operating mode of an MDS. Typically, an MDS operates in normal mode, so the implied value SHALL be "Nml".</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="VmdDescriptor">
		<xsd:annotation>
			<xsd:documentation>VmdDescriptor describes a VMD. A VMD is an abstraction for a module (medical-related subsystem) of an MDS. According to IEEE 11073-10201, an MDS with one VMD is a single purpose POC MEDICAL DEVICE in contrast to an MDS with multiple VMDs that has multiple purposes.

Example of a multiple purpose POC MEDICAL DEVICE: an anesthesia workstation (one MDS) with a ventilation unit (one VMD), a patient monitoring unit (another VMD), and gas delivery/monitor system (another VMD). In the IEEE 11073-10201 a VMD might not be a hardware module, it also can be pure software.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractComplexDeviceComponentDescriptor">
				<xsd:sequence>
					<xsd:element name="ApprovedJurisdictions" type="pm:ApprovedJurisdictions" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>List of regions in which the the VMD is approved to be operated. If the list does not contain any entries, then the VMD is not approved for any region. If the list is not specified, then the VMD is approved to be operated in any region.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="Channel" type="pm:ChannelDescriptor" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>Ordered list of CHANNELs that allow hierarchical information organization of METRICs or ALERT SYSTEMs. The list is ordered by the position of the CHANNEL in the list where the ELEMENT with a lower list index has a higher clinical relevance than any entry with a higher list index. The SERVICE PROVIDER defines the clinical relevance and MAY reorder the list at any time.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="VmdState">
		<xsd:annotation>
			<xsd:documentation>The state of a VMD.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractComplexDeviceComponentState">
				<xsd:sequence>
					<xsd:element name="OperatingJurisdiction" type="pm:OperatingJurisdiction" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>The current region information that is configured for the VMD. See also pm:OperatingJurisdiction. OperatingJurisdiction SHALL NOT be inserted if there is no pm:VmdDescriptor/pm:ApprovedJurisdictions list present.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="ChannelDescriptor">
		<xsd:annotation>
			<xsd:documentation>ChannelDescriptor describes a CHANNEL to group METRICs and alerts. It is used for organizational purposes only.

Example: an example would be a blood pressure VMD with one CHANNEL to group together all METRICs that deal with the blood pressure (e.g., pressure value, pressure waveform). A second CHANNEL object could be used to group together METRICs that deal with heart rate.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractDeviceComponentDescriptor">
				<xsd:sequence>
					<xsd:element name="Metric" type="pm:AbstractMetricDescriptor" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>List of METRICs that are grouped into the CHANNEL. The list is ordered by the position of the METRIC in the list where the ELEMENT with a lower list index has a higher clinical relevance than any entry with a higher list index. The SERVICE PROVIDER defines the clinical relevance and MAY reorder the list at any time.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="ChannelState">
		<xsd:annotation>
			<xsd:documentation>The state of a CHANNEL.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractDeviceComponentState"/>
		</xsd:complexContent>
	</xsd:complexType>
	<!--Section: Alerts-->
	<!--Sub-section: Abstract Definitions-->
	<xsd:complexType name="AbstractAlertDescriptor">
		<xsd:annotation>
			<xsd:documentation>AbstractAlertDescriptor acts as a base class for all alert descriptors that contain static alert meta information.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="AbstractAlertState">
		<xsd:annotation>
			<xsd:documentation>AbstractAlertState acts as a base class for all alert states that contain dynamic/volatile alert meta information.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractState">
				<xsd:attribute name="ActivationState" type="pm:AlertActivation" use="required">
					<xsd:annotation>
						<xsd:documentation>See pm:AlertActivation.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<!--Sub-section: Alert System-->
	<xsd:simpleType name="AlertActivation">
		<xsd:annotation>
			<xsd:documentation>The activation state of any ALERT SYSTEM ELEMENT, i.e., pm:AlertSystemState, pm:AlertConditionState, pm:LimitAlertConditionState, and pm:AlertSignalState.

Special meanings MAY apply depending on the ALERT SYSTEM ELEMENT.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="On">
				<xsd:annotation>
					<xsd:documentation>The ALERT SYSTEM ELEMENT is operating.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Off">
				<xsd:annotation>
					<xsd:documentation>The ALERT SYSTEM ELEMENT is not operating.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Psd">
				<xsd:annotation>
					<xsd:documentation>Psd = Paused. The ALERT SYSTEM ELEMENT is temporarily not operating.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="SystemSignalActivation">
		<xsd:annotation>
			<xsd:documentation>Defines a tuple consisting of an pm:AlertSignalManifestation and an pm:AlertActivation to describe the alert activation state of a certain ALERT SIGNAL manifestation.

Example: ./@Manifestation is "Aud" and ./@State is "Psd" means that any audible alert activation is paused.
</xsd:documentation>
		</xsd:annotation>
		<xsd:attribute name="Manifestation" type="pm:AlertSignalManifestation" use="required">
			<xsd:annotation>
				<xsd:documentation>See pm:AlertSignalManifestation.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="State" type="pm:AlertActivation" use="required">
			<xsd:annotation>
				<xsd:documentation>See pm:AlertActivation.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
	</xsd:complexType>
	<xsd:complexType name="AlertSystemDescriptor">
		<xsd:annotation>
			<xsd:documentation>AlertSystemDescriptor describes an ALERT SYSTEM to detect ALERT CONDITIONs and generate ALERT SIGNALs, which belong to specific ALERT CONDITIONs.

ALERT CONDITIONs are represented by a list of pm:AlertConditionDescriptor ELEMENTs and ALERT SIGNALs are represented by a list of pm:AlertSignalDescriptor ELEMENTs.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractAlertDescriptor">
				<xsd:sequence>
					<xsd:element name="AlertCondition" type="pm:AlertConditionDescriptor" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>Description of all ALERT CONDITIONs that can be detected by the surrounding ALERT SYSTEM.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="AlertSignal" type="pm:AlertSignalDescriptor" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>Description of all ALERT SIGNALs that MAY be generated by the surrounding ALERT SYSTEM as a consequence of a detected ALERT CONDITIONs.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="MaxPhysiologicalParallelAlarms" type="xsd:unsignedInt">
					<xsd:annotation>
						<xsd:documentation>The maximum number of physiological alarm conditions that can be present at a point of time. If no value is given, an unlimited number SHALL be assumed.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="MaxTechnicalParallelAlarms" type="xsd:unsignedInt">
					<xsd:annotation>
						<xsd:documentation>The maximum number of technical alarm conditions that can be present at a point of time. If no value is given, an unlimited number SHALL be assumed.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="SelfCheckPeriod" type="xsd:duration">
					<xsd:annotation>
						<xsd:documentation>The self check time period defines the value after which a self test of the ALERT SYSTEM is performed. This self check period MAY be used to detect if an ALERT SYSTEM is still operating.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="AlertSystemState">
		<xsd:annotation>
			<xsd:documentation>AlertSystemState contains the dynamic/volatile information of an ALERT SYSTEM. See pm:AlertSystemDescriptor for static information.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractAlertState">
				<xsd:sequence>
					<xsd:element name="SystemSignalActivation" type="pm:SystemSignalActivation" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>Describes a compound ALERT SIGNAL activation for local audible, visible, and tangible ALERT SIGNALs within the ALERT SYSTEM.

If a SystemSignalActivation SSA is set for any ALERT SIGNAL manifestation within an ALERT SYSTEM, then the following rules SHALL apply for any local ALERT SIGNAL ASi within the ALERT SYSTEM where SSA/@Manifestation is equal to ASi/@Manifestation:

- If SSA/@State is "On", any ASi/@ActivationState is "On", "Off", or "Psd"
- If SSA/@State is "Psd", any ASi/@ActivationState is "Psd" or "Off"
- If SSA/@State is "Off", all ASi/@ActivationState are "Off"
- If any ASi/@ActivationState is "On" then SSA/@State is "On"
- If all ASi/@ActivationState are "Psd" then SSA/@State is "Psd"
- If all ASi/@ActivationState are "Off" then SSA/@State is "Off"

NOTE 1—A local ALERT SIGNAL is an ALERT SIGNAL where pm:AlertSignalState/@Location is set to "Loc", whereas a remote ALERT SIGNAL is an ALERT SIGNAL where pm:AlertSignalState/@Location is set to "Rem".
NOTE 2—Remote signals are not considered by SystemSignalActivation.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="LastSelfCheck" type="pm:Timestamp">
					<xsd:annotation>
						<xsd:documentation>Timepoint when the ALERT SYSTEM has performed a self check the last time. LastSelfCheck SHALL be updated on every pm:AlertSystemDescriptor/pm:SelfCheckPeriod.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="SelfCheckCount" type="xsd:long">
					<xsd:annotation>
						<xsd:documentation>Number of self checks performed.

This specification does not prescribe the origin of the value, i.e., whether the counter is incremented since the last boot or whether the counter represents the self checks ever performed.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="PresentPhysiologicalAlarmConditions" type="pm:AlertConditionReference">
					<xsd:annotation>
						<xsd:documentation>List of HANDLE references to the present physiological alarm conditions that have been determined by the ALERT SYSTEM.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="PresentTechnicalAlarmConditions" type="pm:AlertConditionReference">
					<xsd:annotation>
						<xsd:documentation>List of HANDLE references to the present technical alarm conditions that have been determined by the ALERT SYSTEM.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<!--Sub-section: Alert Conditions-->
	<xsd:complexType name="CauseInfo">
		<xsd:annotation>
			<xsd:documentation>Cause information for an ALERT CONDITION.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="RemedyInfo" type="pm:RemedyInfo" minOccurs="0">
				<xsd:annotation>
					<xsd:documentation>OPTIONAL information on how to remedy the ALERT CONDITION.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
			<xsd:element name="Description" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>OPTIONAL human-readable texts that describe the cause.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
		</xsd:sequence>
	</xsd:complexType>
	<xsd:complexType name="RemedyInfo">
		<xsd:annotation>
			<xsd:documentation>Remedy information for a cause of an ALERT CONDITION.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Description" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>OPTIONAL human-readable texts that describe the remedy information.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
		</xsd:sequence>
	</xsd:complexType>
	<xsd:simpleType name="AlertConditionKind">
		<xsd:annotation>
			<xsd:documentation>AlertConditionKind categorizes ALERT CONDITIONs by their origin.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Phy">
				<xsd:annotation>
					<xsd:documentation>Phy = Physiological. The condition arises from a patient-related variable. Examples: "blood pressure high" or "minute volume low".</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Tec">
				<xsd:annotation>
					<xsd:documentation>Tec = Technical. The condition arises from a monitored equipment-related or ALERT SYSTEM-related variable. Examples: "battery low" or "sensor unplugged".</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Oth">
				<xsd:annotation>
					<xsd:documentation>Oth = Other. The condition arises from another origin, e.g., equipment-user advisory conditions like "room temperature high".</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="AlertConditionPriority">
		<xsd:annotation>
			<xsd:documentation>AlertConditionPriority categorizes ALERT CONDITIONs into priorities.

AlertConditionPriority can be used to distinguish the severity of the potential or actual hazard that exists if an ALERT CONDITION is present.

NOTE—The priority is assigned through risk analysis.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Lo">
				<xsd:annotation>
					<xsd:documentation>Lo = Low. Awareness of the ALERT CONDITION is required.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Me">
				<xsd:annotation>
					<xsd:documentation>Me = Medium. Prompt response to remove the ALERT CONDITION is required.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Hi">
				<xsd:annotation>
					<xsd:documentation>Hi = High. Immediate response to remove the ALERT CONDITION is required.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="None">
				<xsd:annotation>
					<xsd:documentation>No awareness of the ALERT CONDITION is required.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="AlertConditionDescriptor">
		<xsd:annotation>
			<xsd:documentation>An ALERT CONDITION contains the information about a potentially or actually HAZARDOUS SITUATION. 

Examples: a physiological alarm limit has been exceeded or a sensor has been unplugged.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractAlertDescriptor">
				<xsd:sequence>
					<xsd:element name="Source" type="pm:HandleRef" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>A list of HANDLE references to sources (e.g., METRICs) that cause the ALERT CONDITION.

Example if a source is present: the heart rate METRIC is the source for a "heart rate high" ALERT CONDITION.
Example if no source is present: a "cable disconnection" ALERT CONDITION has no source.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="CauseInfo" type="pm:CauseInfo" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>Information about possible causes if the ALERT CONDITION is present.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="Kind" type="pm:AlertConditionKind" use="required">
					<xsd:annotation>
						<xsd:documentation>See pm:AlertConditionKind.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="Priority" type="pm:AlertConditionPriority" use="required">
					<xsd:annotation>
						<xsd:documentation>See pm:AlertConditionPriority.

NOTE—If the ATTRIBUTE pm:AlertConditionState/@ActualPriority is present, the priority defined for pm:AlertConditionDescriptor MAY not reflect the current severity of the potential or actual hazard that exists if the ALERT CONDITION is present.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="DefaultConditionGenerationDelay" type="xsd:duration">
					<xsd:annotation>
						<xsd:documentation>DefaultConditionGenerationDelay is the period that describes delay from the physical fullfilment of an ALERT CONDITION to the generation of the ALERT CONDITION on the POC MEDICAL DEVICE. The implied value SHALL be "PT0S".</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="CanEscalate">
					<xsd:annotation>
						<xsd:documentation>Indicates if an alert condition can escalate from one priority to another.</xsd:documentation>
					</xsd:annotation>
					<xsd:simpleType>
						<xsd:restriction base="pm:AlertConditionPriority">
							<xsd:enumeration value="Lo">
								<xsd:annotation>
									<xsd:documentation>Lo = Low. Alert condition can escalate to low priority.</xsd:documentation>
								</xsd:annotation>
							</xsd:enumeration>
							<xsd:enumeration value="Me">
								<xsd:annotation>
									<xsd:documentation>Me = Medium. Alert condition can escalate to medium priority.</xsd:documentation>
								</xsd:annotation>
							</xsd:enumeration>
							<xsd:enumeration value="Hi">
								<xsd:annotation>
									<xsd:documentation>Hi = High. Alert condition can escalate to high priority.</xsd:documentation>
								</xsd:annotation>
							</xsd:enumeration>
						</xsd:restriction>
					</xsd:simpleType>
				</xsd:attribute>
				<xsd:attribute name="CanDeescalate">
					<xsd:annotation>
						<xsd:documentation>Indicates if an alert condition can deescalate from one priority to another.</xsd:documentation>
					</xsd:annotation>
					<xsd:simpleType>
						<xsd:restriction base="pm:AlertConditionPriority">
							<xsd:enumeration value="Me">
								<xsd:annotation>
									<xsd:documentation>Me = Medium. Alert condition can deescalate to medium priority.</xsd:documentation>
								</xsd:annotation>
							</xsd:enumeration>
							<xsd:enumeration value="Lo">
								<xsd:annotation>
									<xsd:documentation>Lo = Low. Alert condition can deescalate to low priority.</xsd:documentation>
								</xsd:annotation>
							</xsd:enumeration>
							<xsd:enumeration value="None">
								<xsd:annotation>
									<xsd:documentation>No = None. Alert condition can deescalate to condition with no priority.</xsd:documentation>
								</xsd:annotation>
							</xsd:enumeration>
						</xsd:restriction>
					</xsd:simpleType>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:simpleType name="AlertConditionReference">
		<xsd:annotation>
			<xsd:documentation>A list of HANDLE references that point to ALERT CONDITIONs.</xsd:documentation>
		</xsd:annotation>
		<xsd:list itemType="pm:HandleRef"/>
	</xsd:simpleType>
	<xsd:complexType name="AlertConditionState">
		<xsd:annotation>
			<xsd:documentation>AlertConditionState contains the dynamic/volatile information of an ALERT CONDITION. See pm:AlertConditionDescriptor for static information.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractAlertState">
				<xsd:attribute name="ActualConditionGenerationDelay" type="xsd:duration">
					<xsd:annotation>
						<xsd:documentation>ActualConditionGenerationDelay overrides pm:AlertConditionDescriptor/@DefaultConditionGenerationDelay.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="ActualPriority" type="pm:AlertConditionPriority">
					<xsd:annotation>
						<xsd:documentation>The current priority of the ALERT CONDITION that has been modified by an escalation or de-escalation process. 

NOTE—If this ATTRIBUTE is present in an pm:AlertConditonState ELEMENT, the related pm:AlertConditionDescritptor/pm:Priority ELEMENT MAY NOT reflect the current severity of the potential or actual hazard that exists if this ALERT CONDITION is present.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="Rank" type="xsd:int">
					<xsd:annotation>
						<xsd:documentation>The rank is an optional ATTRIBUTE allowing finer distinction of ALERT CONDITION priorities. A ranking is a relationship between a set of items such that, for any two items, the first is either "ranked higher than", "ranked lower than" or "ranked equal to" the second.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="Presence" type="xsd:boolean">
					<xsd:annotation>
						<xsd:documentation>The Presence ATTRIBUTE is set to "true" if the ALERT CONDITION has been detected and is still present. Otherwise it is set to "false". The implied value SHALL be "false".</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="DeterminationTime" type="pm:Timestamp">
					<xsd:annotation>
						<xsd:documentation>Timepoint when the ALERT CONDITION has changed its presence the last time.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="LimitAlertConditionDescriptor">
		<xsd:annotation>
			<xsd:documentation>LimitAlertConditionDescriptor is a specialization of an ALERT CONDITION that is active if at least one limit for a referenced METRIC has been violated.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AlertConditionDescriptor">
				<xsd:sequence>
					<xsd:element name="MaxLimits" type="pm:Range">
						<xsd:annotation>
							<xsd:documentation>The maximum possible range for the limit bounds.

Example: the ECG values can be measured in a specific range. At some point the measured values are afflicted with noise, which makes them not valid for limits. Therefore, the maximum allowed range can be restricted.

The unit of the limits in pm:Range SHALL be the unit of the referenced pm:AlertConditionDescriptor/pm:Source.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="AutoLimitSupported" type="xsd:boolean">
					<xsd:annotation>
						<xsd:documentation>AutoLimitSupported indicates whether (true) or not (false) a limit ALERT CONDITION provides support for automatic limit adaption. The implied value SHALL be "false".</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:simpleType name="AlertConditionMonitoredLimits">
		<xsd:annotation>
			<xsd:documentation>Indicates which limits of a pm:LimitAlertCondition ELEMENT are monitored to trigger ALERT SIGNALs.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="All">
				<xsd:annotation>
					<xsd:documentation>Both alert limits are monitored.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="LoOff">
				<xsd:annotation>
					<xsd:documentation>LoOff = Low-Off. Low-limit violation detection is either currently turned off if the state possesses a low-limit value or is not supported at all.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="HiOff">
				<xsd:annotation>
					<xsd:documentation>HiOff = Hi-Off. High-limit violation detection is either currently turned off if the state possesses a high-limit value or is not supported at all.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="None">
				<xsd:annotation>
					<xsd:documentation>No alert limits are monitored. 

NOTE—This flag is not equal to the activation state "Off" that pm:AlertConditionState/@ActivationState provides, although the result w.r.t. to alert signalization is the same.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="LimitAlertConditionState">
		<xsd:annotation>
			<xsd:documentation>A state of a limit ALERT CONDITION.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AlertConditionState">
				<xsd:sequence>
					<xsd:element name="Limits" type="pm:Range">
						<xsd:annotation>
							<xsd:documentation>Limit values for the pm:LimitAlertConditionState type.

The unit of the limits in pm:Range SHALL be the unit of the referenced pm:AlertConditionDescriptor/pm:Source.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="MonitoredAlertLimits" type="pm:AlertConditionMonitoredLimits" use="required">
					<xsd:annotation>
						<xsd:documentation>Monitored alert limits of the limit ALERT CONDITION. See pm:AlertConditionMonitoredLimits

NOTE—If the pm:AlertConditionState/@ActivationState ATTRIBUTE is not set to "On", the presence of the limit ALERT CONDITION is not detected. From a consumer perspective this is equivalent to the case when the pm:AlertConditionState/@ActivationState ATTRIBUTE is "On" and pm:AlertConditionState/@MonitoredAlertLimits is "None". The difference is that in the latter case the source for the ALERT CONDITION is still supervised, but the presence flag is not generated even if the limits are violated.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="AutoLimitActivationState" type="pm:AlertActivation" use="optional">
					<xsd:annotation>
						<xsd:documentation>Indicates if the limits for the limit ALERT CONDITION are adjusted automatically.

"On": limit is adjusted automatically
"Off": limit is not adjusted automatically
"Psd": limit is temporarily not adjusted automatically</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<!--Sub-section: Alert Signals-->
	<xsd:simpleType name="AlertSignalManifestation">
		<xsd:annotation>
			<xsd:documentation>AlertSignalManifestation categorizes ALERT SIGNALs by the way they can be recognized by the alerted human, e.g., the nurse.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Aud">
				<xsd:annotation>
					<xsd:documentation>Aud = Audible. The ALERT SIGNAL manifests in an audible manner, i.e., the alert can be heard. Example: an alarm sound.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Vis">
				<xsd:annotation>
					<xsd:documentation>Vis = Visible. The ALERT SIGNAL manifests in a visible manner, i.e., the alert can be seen. Example: a red flashing light.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Tan">
				<xsd:annotation>
					<xsd:documentation>Tan = Tangible. The ALERT SIGNAL manifests in a tangible manner, i.e., the alert can be felt. Example: vibration.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Oth">
				<xsd:annotation>
					<xsd:documentation>Oth = Other. The ALERT SIGNAL manifests in a manner not further specified.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="AlertSignalDescriptor">
		<xsd:annotation>
			<xsd:documentation>AlertSignalDescriptor represents an ALERT SIGNAL. An ALERT SIGNAL contains information about the way an ALERT CONDITION is communicated to a human. It is generated by an ALERT SYSTEM to indicate the presence or occurrence of an ALERT CONDITION.

Example: a signal could be a lamp (see pm:AlertSignalDescriptor/pm:Manifestation) on a remote POC MEDICAL DEVICE, such as the nurses handheld device (see pm:AlertSignalDescriptor/pm:SignalDelegationSupported), which starts flashing when the heart rate is exceeding 150bmp (see pm:AlertSignalDescriptor/pm:ConditionSignaled) for more than 2 seconds (see pm:AlertSignalDescriptor/pm:DefaultSignalGenerationDelay), and keeps flashing until the nurse confirms the alarm, even if the alarm condition is not present anymore (see pm:AlertSignalDescriptor/pm:Latching).</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractAlertDescriptor">
				<xsd:attribute name="ConditionSignaled" type="pm:HandleRef">
					<xsd:annotation>
						<xsd:documentation>Reference to an ALERT CONDITION communicated by the ALERT SIGNAL. The ALERT CONDITION signaled has to be in the same ALERT SYSTEM or in an ALERT SYSTEM that is underneath the ALERT SYSTEM of this ALERT SIGNAL in the CONTAINMENT TREE.

Example: assume an MDS possesses two VMDs and an ALERT SYSTEM A, and each of these VMDs possess itself an ALERT SYSTEM (B and C). An ALERT SIGNAL from the ALERT SYSTEM A of the MDS is allowed to reference an ALERT CONDITION from the ALERT SYSTEMs A, B and C. In contrast to this an ALERT SIGNAL from the ALERT SYSTEM B is allowed to reference only ALERT CONDITIONs from the ALERT SYSTEM B and not from the ALERT SYSTEM A or C.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="Manifestation" type="pm:AlertSignalManifestation" use="required">
					<xsd:annotation>
						<xsd:documentation>See pm:AlertSignalManifestation.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="Latching" type="xsd:boolean" use="required">
					<xsd:annotation>
						<xsd:documentation>An ALERT SIGNAL is latching if it outlives its triggering ALERT CONDITION until it is stopped by deliberate action.

Example: if the patient's heart rate exceeds a given limit for a certain time, but then normalizes such that the ALERT CONDITION no longer exists, it might be desirable to keep the ALERT SIGNAL alive until, e.g., the nurse confirms it. Otherwise the ALERT CONDITION could pass unnoticed.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="DefaultSignalGenerationDelay" type="xsd:duration">
					<xsd:annotation>
						<xsd:documentation>DefaultSignalGenerationDelay is the default period from the onset of an ALERT CONDITION to the generation of the ALERT SIGNAL. The implied value SHALL be "PT0S".

Example: if the heart rate exceeds a limit periodically as the actual rate oscillates around the limit value, it might be desirable to not directly generate the ALERT SIGNAL whenever the limit is exceeded, but to wait for the given delay first.

In the case of a FALLBACK ALERT SIGNAL, DefaultSignalGenerationDelay is the default period of time from when a PARTICIPANT last retriggered the SetAlertStateOperation to the generation of the FALLBACK ALERT SIGNAL.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="MinSignalGenerationDelay" type="xsd:duration">
					<xsd:annotation>
						<xsd:documentation>OPTIONAL minimum delay of pm:AlertSignalState/@ActualSignalGenerationDelay.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="MaxSignalGenerationDelay" type="xsd:duration">
					<xsd:annotation>
						<xsd:documentation>OPTIONAL maximum delay of pm:AlertSignalState/@ActualSignalGenerationDelay.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="SignalDelegationSupported" type="xsd:boolean">
					<xsd:annotation>
						<xsd:documentation>SignalDelegationSupported is set to "true" to indicate if the signal can be generated at another PARTICIPANT as primary ALERT SIGNAL, otherwise "false". The implied value SHALL be "false".</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="AcknowledgementSupported" type="xsd:boolean" use="optional">
					<xsd:annotation>
						<xsd:documentation>AcknowledgementSupported is set to "true" to indicate if the ALERT SIGNAL supports acknowledgment. The implied value SHALL be "false".</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="AcknowledgeTimeout" type="xsd:duration" use="optional">
					<xsd:annotation>
						<xsd:documentation>Indicates the acknowledgment timeout if the signal supports acknowledgment. If no duration is defined, an indefinite acknowledgment timeout SHALL be supported.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:simpleType name="AlertSignalPresence">
		<xsd:annotation>
			<xsd:documentation>Generation state of an ALERT SIGNAL.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="On">
				<xsd:annotation>
					<xsd:documentation>Indicates that an ALERT SIGNAL is currently generated.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Off">
				<xsd:annotation>
					<xsd:documentation>Indicates that an ALERT SIGNAL is currently not generated.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Latch">
				<xsd:annotation>
					<xsd:documentation>Latch = Latched. "Latched" indicates that an ALERT SIGNAL is currently generated even if the ALERT CONDITION is no longer present.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Ack">
				<xsd:annotation>
					<xsd:documentation>Ack = Acknowledged. "Acknowledged" indicates that an ALERT SIGNAL is currently not generated due to an acknowledgment even if the ALERT CONDITION is still present. Acknowledged signals are those, where an auditory ALERT SIGNAL that is related to a currently active ALERT CONDITION, is inactive until the ALERT CONDITION is no longer present.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="AlertSignalPrimaryLocation">
		<xsd:annotation>
			<xsd:documentation>AlertSignalPrimaryLocation defines where the primary ALERT SIGNAL is generated.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Loc">
				<xsd:annotation>
					<xsd:documentation>Loc = Local. The ALERT SIGNAL is perceivable on the machine where the ALERT CONDITION has been detected.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Rem">
				<xsd:annotation>
					<xsd:documentation>Rem = Remote. The ALERT SIGNAL is perceivable on a remote machine.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="AlertSignalState">
		<xsd:annotation>
			<xsd:documentation>AlertSignalState contains the dynamic/volatile information of an ALERT SIGNAL. See pm:AlertSignalDescriptor for static information.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractAlertState">
				<xsd:attribute name="ActualSignalGenerationDelay" type="xsd:duration">
					<xsd:annotation>
						<xsd:documentation>ActualSignalGenerationDelay overrides pm:AlertSignalDescriptor/@DefaultSignalGenerationDelay.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="Presence" type="pm:AlertSignalPresence" use="optional">
					<xsd:annotation>
						<xsd:documentation>See pm:AlertSignalPresence. The implied value SHALL be "Off".</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="Location" type="pm:AlertSignalPrimaryLocation" use="optional">
					<xsd:annotation>
						<xsd:documentation>See pm:AlertSignalPrimaryLocation. The implied value SHALL be "Loc".</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="Slot" type="xsd:unsignedInt" use="optional">
					<xsd:annotation>
						<xsd:documentation>The slot is a 0-based index that allows a prioritization of the ALERT SIGNAL w.r.t. signal tangibility. The Slot SHOULD be used if the medium for signal generation has only a limited capability of parallel signal generation. The smaller the slot index, the higher is the priority in generation of the signal.

Example: if a signal is audible and there are different audio signals for different ALERT SIGNALs, and more than one ALERT SIGNAL has to be generated, the generating system has to decide which of the ALERT SIGNALs it generates as overlaying audio signals might not be desirable. For example, if the first ALERT SIGNAL has a slot number of 0 and the second ALERT SIGNAL has a slot number 1 and both signals are active, than the ALERT SYSTEM generates only the ALERT SIGNAL with the slot number 0.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<!--Section: Medical-->
	<!--Sub-section: Metric Values-->
	<xsd:simpleType name="QualityIndicator">
		<xsd:annotation>
			<xsd:documentation>Indicates the quality of a determined value, where 0 means lowest quality and 1 means high quality w.r.t. to the validity level.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:decimal">
			<xsd:minInclusive value="0">
				<xsd:annotation>
					<xsd:documentation>The minimal value that indicates that the signal has the worst quality.</xsd:documentation>
				</xsd:annotation>
			</xsd:minInclusive>
			<xsd:maxInclusive value="1">
				<xsd:annotation>
					<xsd:documentation>The maximal value that indicates that the signal has the best quality.</xsd:documentation>
				</xsd:annotation>
			</xsd:maxInclusive>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="GenerationMode">
		<xsd:annotation>
			<xsd:documentation>Describes whether METRIC data is generated by real measurements or under unreal settings (demo or test data).</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Real">
				<xsd:annotation>
					<xsd:documentation>Real = Real Data. A value that is generated under real conditions.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Test">
				<xsd:annotation>
					<xsd:documentation>Test = Test Data. A value that is arbitrary and is for testing purposes only.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Demo">
				<xsd:annotation>
					<xsd:documentation>Demo = Demo Data. A value that is arbitrary and is for demonstration purposes only.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="AbstractMetricValue">
		<xsd:annotation>
			<xsd:documentation>Abstract value of a METRIC.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="MetricQuality">
				<xsd:annotation>
					<xsd:documentation>The quality state of the determined value of a METRIC.</xsd:documentation>
				</xsd:annotation>
				<xsd:complexType>
					<xsd:sequence>
						<xsd:element ref="ext:Extension" minOccurs="0"/>
					</xsd:sequence>
					<xsd:attribute name="Validity" type="pm:MeasurementValidity" use="required">
						<xsd:annotation>
							<xsd:documentation>While Validity is "Ong" or "NA", the enclosing METRIC value SHALL not possess a determined value. See also pm:MeasurementValidity.

NOTE—In case of other values the enclosing METRIC is allowed to possess a determined value.</xsd:documentation>
						</xsd:annotation>
					</xsd:attribute>
					<xsd:attribute name="Mode" type="pm:GenerationMode">
						<xsd:annotation>
							<xsd:documentation>Describes whether data is generated by a real METRIC source or is part of any test or demo data. The implied value SHALL be "Real".</xsd:documentation>
						</xsd:annotation>
					</xsd:attribute>
					<xsd:attribute name="Qi" type="pm:QualityIndicator">
						<xsd:annotation>
							<xsd:documentation>See pm:QualityIndicator. The implied value SHALL be "1".</xsd:documentation>
						</xsd:annotation>
					</xsd:attribute>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="Annotation" minOccurs="0" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>Annotation of a METRIC state value.</xsd:documentation>
				</xsd:annotation>
				<xsd:complexType>
					<xsd:sequence>
						<xsd:element ref="ext:Extension" minOccurs="0"/>
						<xsd:element name="Type" type="pm:CodedValue">
							<xsd:annotation>
								<xsd:documentation>The CODED VALUE that describes the annotation of the ELEMENT.

Example: attach triggers in waveform curves.</xsd:documentation>
							</xsd:annotation>
						</xsd:element>
					</xsd:sequence>
				</xsd:complexType>
			</xsd:element>
		</xsd:sequence>
		<xsd:attribute name="StartTime" type="pm:Timestamp" use="optional">
			<xsd:annotation>
				<xsd:documentation>Time when measurement activity was started.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="StopTime" type="pm:Timestamp" use="optional">
			<xsd:annotation>
				<xsd:documentation>Time when measurement activity was stopped.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="DeterminationTime" type="pm:Timestamp" use="optional">
			<xsd:annotation>
				<xsd:documentation>Time when determined value has been derived from measurement.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
	</xsd:complexType>
	<xsd:complexType name="NumericMetricValue">
		<xsd:annotation>
			<xsd:documentation>Numeric value of a METRIC state.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractMetricValue">
				<xsd:attribute name="Value" type="xsd:decimal" use="optional">
					<xsd:annotation/>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="StringMetricValue">
		<xsd:annotation>
			<xsd:documentation>String value of a METRIC state.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractMetricValue">
				<xsd:attribute name="Value" type="xsd:string" use="optional">
					<xsd:annotation/>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:simpleType name="RealTimeValueType">
		<xsd:annotation>
			<xsd:documentation>Defines the real-time sample array value type comprising a whitespace separated list of decimal numbers.</xsd:documentation>
		</xsd:annotation>
		<xsd:list itemType="xsd:decimal"/>
	</xsd:simpleType>
	<xsd:complexType name="SampleArrayValue">
		<xsd:annotation>
			<xsd:documentation>Type that contains sequences of values, i.e., sample arrays.

The ./pmMetricQuality ELEMENT relates to all samples.

NOTE 1—pm:Timestamp (see base: pm:AbstractMetricValue) refers to the first value of the array. The individual timestamps of the values can thus be computed from the sample rate (see pm:RealTimeSampleArrayMetricDescriptor).
NOTE 2—If ./pmMetricQuality cannot be applied to all samples due to, e.g., some invalid values, a SERVICE PROVIDER can decide to set ./pmMetricQuality/@Validity to "Qst" or "Inv".</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractMetricValue">
				<xsd:sequence>
					<xsd:element name="ApplyAnnotation" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>Annotations MAY only apply to specific values in the real-time sample array. The ApplyAnnotation set relates annotations to sample indices. If no ApplyAnnotation ELEMENT is provided all annotations are valid for all values in the context.</xsd:documentation>
						</xsd:annotation>
						<xsd:complexType>
							<xsd:attribute name="AnnotationIndex" type="xsd:unsignedInt" use="required">
								<xsd:annotation>
									<xsd:documentation>Index number of the annotation that is addressed by the ApplyAnnotation ELEMENT. The index number refers to the (n+1)-nth pm:AbstractMetricValue/pm:Annotation ELEMENT. Hence, numbering is zero-based.</xsd:documentation>
								</xsd:annotation>
							</xsd:attribute>
							<xsd:attribute name="SampleIndex" type="xsd:unsignedInt" use="required">
								<xsd:annotation>
									<xsd:documentation>Index number of the sample the defined annotation refers to. The index number addresses the (n+1)-nth number in the pm:RealTimeSampleArrayValue/pm:Samples ATTRIBUTE. Hence, numbering is zero-based.</xsd:documentation>
								</xsd:annotation>
							</xsd:attribute>
						</xsd:complexType>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="Samples" type="pm:RealTimeValueType">
					<xsd:annotation/>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<!--Sub-section: Base Metric Descriptor and State-->
	<xsd:simpleType name="MetricCategory">
		<xsd:annotation>
			<xsd:documentation>The METRIC category makes it possible to distinguish between different manifestations of a METRIC like measurements, settings or recommendations. 

Example: if the respiratory rate can be adjusted and the ventilator is smart and provides a recommendation, there are likely be at least three METRICs with a type of "Respiratory Rate": 

- 1 METRIC with MetricCategory set to Measurement. This METRIC is the actual measured value.
- 1 METRIC with MetricCategory set to Setting. This METRIC is the adjustable value.
- 1 METRIC with MetricCategory set to Recommendation. This METRIC is the recommended value derived from some smart algorithm.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Unspec">
				<xsd:annotation>
					<xsd:documentation>Unspec = Unspecified. None of the categories in MetricCategory is valid for the METRIC.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Msrmt">
				<xsd:annotation>
					<xsd:documentation>Msrmt = Measurement. The METRIC has been derived by measurement.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Clc">
				<xsd:annotation>
					<xsd:documentation>Clc = Calculation. The METRIC has been derived by calculation only.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Set">
				<xsd:annotation>
					<xsd:documentation>Set = Setting. The METRIC has a value that is adjustable by some (local or remote) control means.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Preset">
				<xsd:annotation>
					<xsd:documentation>Preset = Presetting. The METRIC has a value that is adjustable by some (local or remote) control means. Once the value is adjusted, it remains a Preset until committed, at which point it becomes a setting.

Related settings MAY be defined by using pm:AbstractMetricDescriptor/pm:Relation.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Rcmm">
				<xsd:annotation>
					<xsd:documentation>Rcmm = Recommendation. The METRIC is a proposal for a setting or presetting. The related setting or presetting MAY be defined by using pm:AbstractMetricDescriptor/pm:Relation.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="DerivationMethod">
		<xsd:annotation>
			<xsd:documentation>In some circumstances, e.g., in spot-check situations or when dealing with settings, METRIC values might be entered manually. DerivationMethod provides an enumeration to designate if a METRIC is set automatically or manually.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Auto">
				<xsd:annotation>
					<xsd:documentation>Auto = Automatic derivation. The METRIC value is derived by an automatic mechanism (e.g., electronically measured).</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Man">
				<xsd:annotation>
					<xsd:documentation>Man = Manual derivation. The METRIC is derived manually by a clinican/human.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="MetricAvailability">
		<xsd:annotation>
			<xsd:documentation>Availability of the means that derives the METRIC state.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Intr">
				<xsd:annotation>
					<xsd:documentation>Intr = Intermittent. Stopping or ceasing for a time; alternately ceasing and beginning again. 

Example: non-invasive blood pressure measurement.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Cont">
				<xsd:annotation>
					<xsd:documentation>Cont = Continuous. Without break, cessation, or interruption; without intervening time.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="EntryRef">
		<xsd:annotation>
			<xsd:documentation>A list of CONTAINMENT TREE ENTRY handle references.</xsd:documentation>
		</xsd:annotation>
		<xsd:list itemType="pm:HandleRef"/>
	</xsd:simpleType>
	<xsd:complexType name="AbstractMetricDescriptor">
		<xsd:annotation>
			<xsd:documentation>An abstract descriptor for a METRIC.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractDescriptor">
				<xsd:sequence>
					<xsd:element name="Unit" type="pm:CodedValue">
						<xsd:annotation>
							<xsd:documentation>CODED VALUE for the unit of a METRIC.

NOTE—If the METRIC is dimensionless and has no unit, use the corresponding CODE from the CODING SYSTEM (e.g., 262656 (4::512) for IEEE 11073-10101 MDC_DIM_DIMLESS).</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="BodySite" type="pm:CodedValue" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>OPTIONAL list of CODED VALUEs that describe the body sites where the METRIC is derived from or where it is applied to.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="Relation" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>Relation allows the modelling of relationships between a metric and other containtment tree entries. Related containment tree entries are defined in ./@Entries, whereby the flavor of a relationship can be set up in ./@Kind.

The cardinality of Relation is zero or more in order to express relations of different flavors for the same METRIC.

NOTE—Example: some settings of high frequency cutting devices cause changes in measurements (e.g., current form can influences the maximum emitted power). If such a setting is controllable by external means, presumably the SERVICE CONSUMER wants to be able to gain knowledge of affected measurements, which might be then accessed through the Relation element.</xsd:documentation>
						</xsd:annotation>
						<xsd:complexType>
							<xsd:sequence>
								<xsd:element ref="ext:Extension" minOccurs="0"/>
								<xsd:element name="Code" type="pm:CodedValue" minOccurs="0">
									<xsd:annotation>
										<xsd:documentation>Code allows to semantically describe the relationship between the METRIC and the list of related containment tree entries defined in ./pm:Relation/@Entries.</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
								<xsd:element name="Identification" type="pm:InstanceIdentifier" minOccurs="0">
									<xsd:annotation>
										<xsd:documentation>Identification allow relations to be grouped by instance identifiers.

NOTE—By that a SERVICE PROVIDER can, e.g., group sets of recommendations or presettings in order to allow easy identification.</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
							</xsd:sequence>
							<xsd:attribute name="Kind" use="required">
								<xsd:annotation>
									<xsd:documentation>Kind specifies the relationship between the METRIC and referenced containment tree entries. Referenced containment tree entries are defined in ./pm:Relation/@Entries.</xsd:documentation>
								</xsd:annotation>
								<xsd:simpleType>
									<xsd:restriction base="xsd:string">
										<xsd:enumeration value="Rcm">
											<xsd:annotation>
												<xsd:documentation>Rcm = Recommendation. The METRIC is a recommendation for the containment tree entries defined in ./pm:Relation/@Entries.</xsd:documentation>
											</xsd:annotation>
										</xsd:enumeration>
										<xsd:enumeration value="PS">
											<xsd:annotation>
												<xsd:documentation>PS = Pre-setting. This METRIC is a pre-setting for the containment tree entries defined in ./pm:Relation/@Entries.</xsd:documentation>
											</xsd:annotation>
										</xsd:enumeration>
										<xsd:enumeration value="SST">
											<xsd:annotation>
												<xsd:documentation>SST = Set of summary statistics. The METRIC is part of a set of summary statistics for a sample where other METRICs that belong to the summary statistics are defined in ./pm:Relation/@Entries.</xsd:documentation>
											</xsd:annotation>
										</xsd:enumeration>
										<xsd:enumeration value="ECE">
											<xsd:annotation>
												<xsd:documentation>ECE = Effect on containment tree entries. When changed, the METRIC has an effect on the containment tree entries defined in ./pm:Relation/@Entries. If Kind is "ECE", ./pm:Relation/pm:Code SHOULD be set to classify the effect.</xsd:documentation>
											</xsd:annotation>
										</xsd:enumeration>
										<xsd:enumeration value="DCE">
											<xsd:annotation>
												<xsd:documentation>DCE = Derived from containment tree entries. The METRIC is derived from the containment tree entries defined in ./pm:Relation/@Entries. If Kind is "DCE", ./pm:Relation/pm:Code MAY be set to classify the form of derivation.</xsd:documentation>
											</xsd:annotation>
										</xsd:enumeration>
										<xsd:enumeration value="Oth">
											<xsd:annotation>
												<xsd:documentation>Oth = Other. Relation is specified by other means, e.g., ./pm:Relation/pm:Code or extension element.</xsd:documentation>
											</xsd:annotation>
										</xsd:enumeration>
									</xsd:restriction>
								</xsd:simpleType>
							</xsd:attribute>
							<xsd:attribute name="Entries" type="pm:EntryRef" use="required">
								<xsd:annotation>
									<xsd:documentation>List of HANDLE references that relate to the METRIC. The relationship flavor is defined in ./pm:Relation/@Kind.</xsd:documentation>
								</xsd:annotation>
							</xsd:attribute>
						</xsd:complexType>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="MetricCategory" type="pm:MetricCategory" use="required">
					<xsd:annotation>
						<xsd:documentation>See pm:MetricCategory.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="DerivationMethod" type="pm:DerivationMethod">
					<xsd:annotation>
						<xsd:documentation>See pm:DerivationMethod. The default value SHALL be applied, depending on pm:AbstractDescriptor/@MetricCategory.

- If pm:AbstractDescriptor/@MetricCategory is "Set" or "Preset", then the default value of DerivationMethod is "Man"
- If pm:AbstractDescriptor/@MetricCategory is "Clc", "Msrmt", "Rcmm", then the default value of DerivationMethod is "Auto"
- If pm:AbstractDescriptor/@MetricCategory is "Unspec", then no default value is being implied</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="MetricAvailability" type="pm:MetricAvailability" use="required">
					<xsd:annotation>
						<xsd:documentation>See pm:MetricAvailability.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="MaxMeasurementTime" type="xsd:duration" use="optional">
					<xsd:annotation>
						<xsd:documentation>Maximum duration between start and stop time of measurment.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="MaxDelayTime" type="xsd:duration" use="optional">
					<xsd:annotation>
						<xsd:documentation>Maximum delay to real time. 
For a measurement or calculation, the maximum delay to real time is the estimated or known maximum difference between the point in time when a physical variable value has been present and when the value has been computed and is ready for communication. This MAY include an averaging period, but it does not include the communication delay. 
For a setting, the maximum delay to real time is the estimated or known maximum difference between the point in time when a setting has been confirmed to be applicable and the time when the setting becomes effective on the actuator. This does not include any communication delay.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="DeterminationPeriod" type="xsd:duration" use="optional">
					<xsd:annotation>
						<xsd:documentation>The maximum time interval between two determination steps of determined values under normal conditions.

- For METRICs with sample arrays as determined values where the availability is not continuous, this is the period of time between two determination steps, e.g., waveform snippets that are periodically determined.
- For METRICs with sample arrays as determined values where the availability is continuous, this is the period of time until the next waveform frame is generated.

NOTE—The determination period that is defined in the descriptor, might not be the currently active determination period. The active determination period is part of the METRIC state.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="LifeTimePeriod" type="xsd:duration" use="optional">
					<xsd:annotation>
						<xsd:documentation>Given the timestamp of a measured METRIC value. The OPTIONAL ATTRIBUTE LifeTimePeriod defines the duration after the measured METRIC value is not useful anymore.

Example: a non-invasive blood pressure measured intermittently might only be considered useful for 24 hours. Hence, LifeTimePeriod would be "PT24H".</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="ActivationDuration" type="xsd:duration" use="optional">
					<xsd:annotation>
						<xsd:documentation>ActivationDuration defines the maximum time period pm:AbstractMetricState/@Activation is "On" before it changes to any other state.

NOTE—ActivationDuration is used to indicate the time that a measurement is performed after it has been activated. Example: if automatically measured NIBP is limited to a certain time period only in order to ensure that blood flow in the arm is ensured, then ActivationDuration could have a value of, e.g., five minutes.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="AbstractMetricState">
		<xsd:annotation>
			<xsd:documentation>Abstract state of a METRIC.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractState">
				<xsd:sequence>
					<xsd:element name="BodySite" type="pm:CodedValue" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>OPTIONAL list of CODED VALUEs that describe the body sites where the measurement is performed or where the setting is applied to.
This list of body sites MAY provide more details to location of the measurement or setting that are be available at runtime only or that changes at runtime of the POC MEDICAL DEVICE. It SHOULD NOT contradict the location that has been listed in the descriptor.

Example: if in the descriptor the location "Upper Abdomen" is defined, than the state's body site give more details to where the measurement is performed like "Upper Right Quadrant" and "Liver".</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="PhysicalConnector" type="pm:PhysicalConnectorInfo" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>The physical connector number for this METRIC, see pm:PhysicalConnectorInfo.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="ActivationState" type="pm:ComponentActivation">
					<xsd:annotation>
						<xsd:documentation>The activation state of a METRIC. The implied value SHALL be "On".</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="ActiveDeterminationPeriod" type="xsd:duration">
					<xsd:annotation>
						<xsd:documentation>OPTIONAL information of the currently active determination repetition time if it is different from the default determination time that is defined in the descriptive part. ActiveDeterminationPeriod is not necessarily the same as the update period of the periodic event service.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="LifeTimePeriod" type="xsd:duration" use="optional">
					<xsd:annotation>
						<xsd:documentation>OPTIONAL currently active life-time period that supersedes pm:AbstractMetricDescriptor/@LifeTimePeriod.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<!--Sub-section: Derived Metric Descriptors and States-->
	<xsd:complexType name="NumericMetricDescriptor">
		<xsd:annotation>
			<xsd:documentation>Specification of a METRIC descriptor type that represents a single numerical measurement and status information. Example: a heart rate measurement.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractMetricDescriptor">
				<xsd:sequence>
					<xsd:element name="TechnicalRange" type="pm:Range" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>The technical possible range of determined values.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="Resolution" type="xsd:decimal" use="required">
					<xsd:annotation>
						<xsd:documentation>The resolution of the means to determine the METRIC's value. The resolution is the minimum determinable difference between two determined values.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="AveragingPeriod" type="xsd:duration">
					<xsd:annotation>
						<xsd:documentation>Timespan from where the measured values are used to determine the METRIC's value by averaging with some algorithm.

NOTE—The averaging period defined in the descriptor might be not the currently active averaging period. The active averaging period is part of pm:NumericMetricState.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="NumericMetricState">
		<xsd:annotation>
			<xsd:documentation>State of a numeric METRIC.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractMetricState">
				<xsd:sequence>
					<xsd:element name="MetricValue" type="pm:NumericMetricValue" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>OPTIONAL current value of the METRIC.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="PhysiologicalRange" type="pm:Range" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>The physiological reasonable range of determined values.

NOTE—This is not an alarming range.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="ActiveAveragingPeriod" type="xsd:duration" use="optional">
					<xsd:annotation>
						<xsd:documentation>OPTIONAL information of the currently active time period used to average values if it is different from the default value that is defined in the descriptor.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="StringMetricDescriptor">
		<xsd:annotation>
			<xsd:documentation>A string METRIC represents a textual status or annotation information.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractMetricDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="StringMetricState">
		<xsd:annotation>
			<xsd:documentation>State of a string METRIC.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractMetricState">
				<xsd:sequence>
					<xsd:element name="MetricValue" type="pm:StringMetricValue" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>OPTIONAL current value of the METRIC.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="EnumStringMetricDescriptor">
		<xsd:annotation>
			<xsd:documentation>An enumerated string METRIC represents a textual status or annotation information with a constrained set of possible values.

Example: a ventilation mode.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:StringMetricDescriptor">
				<xsd:sequence>
					<xsd:element name="AllowedValue" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>List of values that the enumerated string METRIC accepts as a valid value.</xsd:documentation>
						</xsd:annotation>
						<xsd:complexType>
							<xsd:sequence>
								<xsd:element name="Value" type="xsd:string">
									<xsd:annotation>
										<xsd:documentation>Accepted string value.</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
								<xsd:element name="Type" type="pm:CodedValue" minOccurs="0">
									<xsd:annotation>
										<xsd:documentation>OPTIONAL pm:CodedValue to semantically describe the allowed value.</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
								<xsd:element name="Identification" type="pm:InstanceIdentifier" minOccurs="0">
									<xsd:annotation>
										<xsd:documentation>OPTIONAL identification to apply instance identifiers to each allowed value.</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
								<xsd:element name="Characteristic" type="pm:Measurement" minOccurs="0">
									<xsd:annotation>
										<xsd:documentation>OPTIONAL field to attach a dimensional measurement to each allowed value.</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
							</xsd:sequence>
						</xsd:complexType>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="EnumStringMetricState">
		<xsd:annotation>
			<xsd:documentation>State of an enumerated string METRIC.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:StringMetricState"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="RealTimeSampleArrayMetricDescriptor">
		<xsd:annotation>
			<xsd:documentation>Declares a sample array that represents a real-time continuous waveform. An example would be an electrocardiogram (ECG) real-time wave.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractMetricDescriptor">
				<xsd:sequence>
					<xsd:element name="TechnicalRange" type="pm:Range" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>The maximum range of the values of the real-time sample array.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="Resolution" type="xsd:decimal" use="required">
					<xsd:annotation>
						<xsd:documentation>The resolution of the means to determine the METRIC's value. The Resolution is the minimum determinable difference between two determined values.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="SamplePeriod" type="xsd:duration" use="required">
					<xsd:annotation>
						<xsd:documentation>The sample period of the real-time sample array, i.e., how often waveform samples are generated. SamplePeriod is always given as a period between samples, e.g., 5 milliseconds.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="RealTimeSampleArrayMetricState">
		<xsd:annotation>
			<xsd:documentation>State of a stream METRIC descriptor. It contains a list of sample values. This sample array is used to transport waveform stream information.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractMetricState">
				<xsd:sequence>
					<xsd:element name="MetricValue" type="pm:SampleArrayValue" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>OPTIONAL current value of the METRIC.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="PhysiologicalRange" type="pm:Range" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>The physiological reasonable range of determined values.

NOTE—This is not an alarming range.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="DistributionSampleArrayMetricDescriptor">
		<xsd:annotation>
			<xsd:documentation>Declares a sample array that represents linear value distributions in the form of arrays containing scaled sample values. In contrast to real-time sample arrays, distribution sample arrays provide observed spatial values, not time points.

NOTE—An example for a distribution sample array metric might be a fourier-transformed electroencephalogram to derive frequency distribution.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractMetricDescriptor">
				<xsd:sequence>
					<xsd:element name="TechnicalRange" type="pm:Range" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>The maximum range of the values of the distribution sample array.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="DomainUnit" type="pm:CodedValue">
						<xsd:annotation>
							<xsd:documentation>The CODED VALUE that is used for domain values (x axis).</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="DistributionRange" type="pm:Range">
						<xsd:annotation>
							<xsd:documentation>Minimum and maximum domain values. A linear scale is assumed unless a step width is given.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="Resolution" type="xsd:decimal" use="required">
					<xsd:annotation>
						<xsd:documentation>The resolution of the means to determine the METRIC's value. Resolution is the minimum determinable difference between two determined values.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="DistributionSampleArrayMetricState">
		<xsd:annotation>
			<xsd:documentation>State of a distribution sample array METRIC descriptor. It contains a list of sample values. This sample array is used to transport spatial range information.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractMetricState">
				<xsd:sequence>
					<xsd:element name="MetricValue" type="pm:SampleArrayValue" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>OPTIONAL current value of the METRIC.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="PhysiologicalRange" type="pm:Range" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>The physiological reasonable range of determined values.

NOTE—This is not an alarming range.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<!--Section: Remote Control-->
	<!--Sub-section: Base Types-->
	<xsd:simpleType name="OperationRef">
		<xsd:annotation>
			<xsd:documentation>A list of operation handle references.</xsd:documentation>
		</xsd:annotation>
		<xsd:list itemType="pm:HandleRef"/>
	</xsd:simpleType>
	<xsd:complexType name="ScoDescriptor">
		<xsd:annotation>
			<xsd:documentation>ScoDescriptor describes the capabilities of the SCO.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractDeviceComponentDescriptor">
				<xsd:sequence>
					<xsd:element name="Operation" type="pm:AbstractOperationDescriptor" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>A list of operations that are provided by the SCO. The list is ordered by the position of the operation in the list where the ELEMENT with a lower list index has a higher clinical relevance than any entry with a higher list index. The SERVICE PROVIDER defines the clinical relevance and MAY reorder the list at any time.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="ScoState">
		<xsd:annotation>
			<xsd:documentation>Corresponding state of pm:ScoDescriptor.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractDeviceComponentState">
				<xsd:sequence>
					<xsd:element name="OperationGroup" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>OperationGroup defines groups of operations in order to allow clinical grouping and prioritization of operations.</xsd:documentation>
						</xsd:annotation>
						<xsd:complexType>
							<xsd:sequence>
								<xsd:element ref="ext:Extension" minOccurs="0"/>
								<xsd:element name="Type" type="pm:CodedValue">
									<xsd:annotation>
										<xsd:documentation>Type sematically describes the operation group.</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
							</xsd:sequence>
							<xsd:attribute name="OperatingMode" type="pm:OperatingMode">
								<xsd:annotation>
									<xsd:documentation>OperatingMode defines the operating mode of the whole operation group, see also pm:OperatingMode.</xsd:documentation>
								</xsd:annotation>
							</xsd:attribute>
							<xsd:attribute name="Operations" type="pm:OperationRef">
								<xsd:annotation>
									<xsd:documentation>Handle references to all operations enclosed by the operation group. The list is ordered such that the entry with a lower list index has a higher clinical relevance than any entry with a higher list index. The SERVICE PROVIDER defines the clinical relevance and MAY reorder the list at any time.</xsd:documentation>
								</xsd:annotation>
							</xsd:attribute>
						</xsd:complexType>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="InvocationRequested" type="pm:OperationRef">
					<xsd:annotation>
						<xsd:documentation>Prioritized list of operations that are requested to be invoked by a SERVICE CONSUMER.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="InvocationRequired" type="pm:OperationRef">
					<xsd:annotation>
						<xsd:documentation>Prioritized list of operations that are required to be invoked by a SERVICE CONSUMER.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="AbstractOperationDescriptor">
		<xsd:annotation>
			<xsd:documentation>Abstract description of an operation that is exposed on the SCO.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractDescriptor">
				<xsd:attribute name="OperationTarget" type="pm:HandleRef" use="required">
					<xsd:annotation>
						<xsd:documentation>A HANDLE reference this operation is targeted to. In case of a single state this is the HANDLE of the descriptor. In case that multiple states may belong to one descriptor (pm:AbstractMultiState), OperationTarget is the HANDLE of one of the state instances (if the state is modified by the operation).</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="MaxTimeToFinish" type="xsd:duration">
					<xsd:annotation>
						<xsd:documentation>MaxTimeToFinish defines the maximum time an operation takes to get from the initial receiving of the command to a successful end.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="InvocationEffectiveTimeout" type="xsd:duration">
					<xsd:annotation>
						<xsd:documentation>InvocationEffectiveTimeout defines a time period in which the result of an invocation is effective after it has been successfully finished. When the time is up and the operation has not been retriggered, then the SERVICE PROVIDER MAY revert the operation target to another state.

NOTE—Example: if an arbitrary client remotely controls the cutter of a high frequency cutting device, due to safety reasons the cutter trigger might have a timeout until it stops automatically. To enable continuous activation, the client has to send repeated triggers within the given InvocationEffectiveTimeout duration.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="Retriggerable" type="xsd:boolean">
					<xsd:annotation>
						<xsd:documentation>Retriggerable is only applicable if ./@InvocationEffectiveTimeout is set. If set to "true", then Retriggerable indicates that a call to the activate operation resets the current ./@InvocationEffectiveTimeout, otherwise it will be left as it is until ./@InvocationEffectiveTimeout times out.

The implied value SHALL be "true".</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="AccessLevel">
					<xsd:annotation>
						<xsd:documentation>AccessLevel defines a user group to whom access to the operation is granted. The implied value SHALL be "Usr".
						
__R5054: Access to the invocation of the operation SHALL be restricted to the defined user group by a SERVICE CONSUMER.__</xsd:documentation>
					</xsd:annotation>
					<xsd:simpleType>
						<xsd:restriction base="xsd:string">
							<xsd:enumeration value="Usr">
								<xsd:annotation>
									<xsd:documentation>Usr = User. Any person interacting with (i.e., operating or handling) the POC MEDICAL DEVICE.</xsd:documentation>
								</xsd:annotation>
							</xsd:enumeration>
							<xsd:enumeration value="CSUsr">
								<xsd:annotation>
									<xsd:documentation>CSUsr = Clinical Super User. Individuals or entity accountable to the RESPONSIBLE ORGANIZATION that configure clinical relevant settings of a POC MEDICAL DEVICE.</xsd:documentation>
								</xsd:annotation>
							</xsd:enumeration>
							<xsd:enumeration value="RO">
								<xsd:annotation>
									<xsd:documentation>RO = Responsible Organization. Access is restricted to a RESPONSIBLE ORGANIZATION.</xsd:documentation>
								</xsd:annotation>
							</xsd:enumeration>
							<xsd:enumeration value="SP">
								<xsd:annotation>
									<xsd:documentation>SP = Service Personnel. Access is restricted to SERVICE PERSONNEL.</xsd:documentation>
								</xsd:annotation>
							</xsd:enumeration>
							<xsd:enumeration value="Oth">
								<xsd:annotation>
									<xsd:documentation>Oth = Other. Access is restricted by other means (e.g., an extension).</xsd:documentation>
								</xsd:annotation>
							</xsd:enumeration>
						</xsd:restriction>
					</xsd:simpleType>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="AbstractSetStateOperationDescriptor">
		<xsd:annotation>
			<xsd:documentation>Abstract description of an operation that is exposed on the SCO and is intended to be used to set a complete state.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractOperationDescriptor">
				<xsd:sequence>
					<xsd:element name="ModifiableData" type="xsd:string" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>ModifiableData describes a list of ATTRIBUTEs and ELEMENTs the underlying operation modifies on invocation by means of XPath expressions.

__R5010: If the ModifiableData list is empty, then all ELEMENTs/ATTRIBUTEs SHALL be modifiable except for pm:AbstractMultiState/@Handle, pm:AbstractState/@DescriptorHandle, pm:AbstractState/@StateVersion, and pm:AbstractState/@DescriptorVersion.__

__R5011: The root ELEMENT of the XPath expressions SHALL be the state of the CONTAINMENT TREE ENTRY referenced by pm:AbstractOperationDescriptor/@OperationTarget.__</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:simpleType name="OperatingMode">
		<xsd:annotation>
			<xsd:documentation>Mode of an operation state.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Dis">
				<xsd:annotation>
					<xsd:documentation>Dis = Disabled. Object is disabled.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="En">
				<xsd:annotation>
					<xsd:documentation>En = Enabled. Object is enabled</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="NA">
				<xsd:annotation>
					<xsd:documentation>NA = Not Available. Object is not available for interaction. This means that it is defined but currently not in a mode so that it can be interacted with.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="AbstractOperationState">
		<xsd:annotation>
			<xsd:documentation>State of an operation that is exposed on the SCO.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractState">
				<xsd:attribute name="OperatingMode" type="pm:OperatingMode" use="required">
					<xsd:annotation>
						<xsd:documentation>Operating mode that defines if the operation is accessible.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<!--Sub-section: Derived Operation Descriptors and States-->
	<xsd:complexType name="SetValueOperationDescriptor">
		<xsd:annotation>
			<xsd:documentation>Describes a numeric set operation for a specific object state in the MDIB that is exposed on the SCO.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractOperationDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SetValueOperationState">
		<xsd:annotation>
			<xsd:documentation>State of a numeric set operation that is exposed on the SCO.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractOperationState">
				<xsd:sequence>
					<xsd:element name="AllowedRange" type="pm:Range" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>The currently allowed ranges that can be requested.

NOTE—The given ranges need to be a (strict or non-strict) subset of the technical range of the referenced descriptor.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SetStringOperationDescriptor">
		<xsd:annotation>
			<xsd:documentation>Describes a string set operation for a specific object state in the MDIB that is exposed on the SCO.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractOperationDescriptor">
				<xsd:attribute name="MaxLength" type="xsd:unsignedLong" use="optional">
					<xsd:annotation>
						<xsd:documentation>An optional parameter that gives the maximum length of the input string that is supported by the operation.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SetStringOperationState">
		<xsd:annotation>
			<xsd:documentation>State of a string set operation that is exposed on the SCO.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractOperationState">
				<xsd:sequence>
					<xsd:element name="AllowedValues" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>An OPTIONAL list of currently allowed string values that can be requested. If the list is empty, then there is not limitation.</xsd:documentation>
						</xsd:annotation>
						<xsd:complexType>
							<xsd:sequence>
								<xsd:element name="Value" type="xsd:string" minOccurs="1" maxOccurs="unbounded">
									<xsd:annotation>
										<xsd:documentation>A single allowed value that can be requested.</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
							</xsd:sequence>
						</xsd:complexType>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="ActivateOperationDescriptor">
		<xsd:annotation>
			<xsd:documentation>Describes an activate operation that is exposed on the SCO. Activate operations are any parameterized operations that trigger an arbitrary action. The action that is triggered SHALL be defined by the pm:AbstractDescriptor/pm:Type ELEMENT.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractSetStateOperationDescriptor">
				<xsd:sequence>
					<xsd:element name="Argument" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>Argument description for an activate operation.</xsd:documentation>
						</xsd:annotation>
						<xsd:complexType>
							<xsd:sequence>
								<xsd:element name="ArgName" type="pm:CodedValue">
									<xsd:annotation>
										<xsd:documentation>CODED VALUE that describes this argument.</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
								<xsd:element name="Arg" type="xsd:QName">
									<xsd:annotation>
										<xsd:documentation>Data type of the argument, defined by a qualified name.</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
							</xsd:sequence>
						</xsd:complexType>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="ActivateOperationState">
		<xsd:annotation>
			<xsd:documentation>State of an activate operation that is exposed on the SCO.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractOperationState"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SetContextStateOperationDescriptor">
		<xsd:annotation>
			<xsd:documentation>Describes a context state set operation for a specific context state in the MDIB that is exposed on SCO.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractSetStateOperationDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SetContextStateOperationState">
		<xsd:annotation>
			<xsd:documentation>State of a context state set operation that is exposed on the SCO.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractOperationState"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SetMetricStateOperationDescriptor">
		<xsd:annotation>
			<xsd:documentation>Describes a METRIC state set operation for a specific METRIC state in the MDIB that is exposed on the SCO.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractSetStateOperationDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SetMetricStateOperationState">
		<xsd:annotation>
			<xsd:documentation>State of a METRIC state set operation that is exposed on the SCO.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractOperationState"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SetComponentStateOperationDescriptor">
		<xsd:annotation>
			<xsd:documentation>Describes a component state set operation for a specific component state in the MDIB that is exposed on the SCO.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractSetStateOperationDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SetComponentStateOperationState">
		<xsd:annotation>
			<xsd:documentation>State of a component state set operation that is exposed on the SCO.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractOperationState"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SetAlertStateOperationDescriptor">
		<xsd:annotation>
			<xsd:documentation>Describes an alert state set operation for a specific alert state in the MDIB that is exposed on the SCO.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractSetStateOperationDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SetAlertStateOperationState">
		<xsd:annotation>
			<xsd:documentation>State of an alert state set operation that is exposed on the SCO.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractOperationState"/>
		</xsd:complexContent>
	</xsd:complexType>
	<!--Section: Clock-->
	<xsd:simpleType name="TimeZone">
		<xsd:annotation>
			<xsd:documentation>TimeZone describes the time zone and DST setting of a clock in POSIX format (ISO/IEC/IEEE 9945).

Example: CST6CDT,M3.2.0/2:00:00,M11.1.0/2:00:00, which would effect a change to daylight saving time at 2:00 AM on the second Sunday in March and change back at 2:00 AM on the first Sunday in November, and keep 6 hours time offset from GMT every year.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string"/>
	</xsd:simpleType>
	<xsd:complexType name="ClockDescriptor">
		<xsd:annotation>
			<xsd:documentation>ClockDescriptor describes the capabilities of an MDS regarding date/time handling and synchronization. The presense of a ClockDescriptor does not imply any specific hardware or software support.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractDeviceComponentDescriptor">
				<xsd:sequence>
					<xsd:element name="TimeProtocol" type="pm:CodedValue" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>OPTIONAL list of protocols that can be used to set the POC MEDICAL DEVICE's clock. An empty list implies that the clock cannot be set and is therefore uncalibrated and unsynchronized (e.g., equal to MDC:MDC_TIME_SYNC_NONE).   
Example: {MDC:MDC_TIME_SYNC_EBWW, MDC:MDC_TIME_SYNC_SNTPV4, MDC:MDC_TIME_SYNC_NTPV3} if the clock supports synchronization using manually setting on the POC MEDICAL DEVICE, SNTP v4.0 (RFC 2030) and NTP v3.0 (RFC 1305).</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="Resolution" type="xsd:duration">
					<xsd:annotation>
						<xsd:documentation>Time between actual ticks of the clock in microseconds. If none is given, the resolution is unknown.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="ClockState">
		<xsd:annotation>
			<xsd:documentation>State of a clock of an MDS.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractDeviceComponentState">
				<xsd:sequence>
					<xsd:element name="ActiveSyncProtocol" type="pm:CodedValue" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Protocol that is actively being used for time sync.

Examples: MDC:MDC_TIME_SYNC_NTPV3 if the clock is synchronized using NTP v3.0 (RFC 1305) or MDC:MDC_TIME_SYNC_NONE if the clock is not synchronized.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="ReferenceSource" type="xsd:string" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>Identifies the clock's external reference source(s), e.g., NTP server addresses.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="DateAndTime" type="pm:Timestamp">
					<xsd:annotation>
						<xsd:documentation>Current date/time setting. As the current date/time changes at a high frequency, a change of this value SHALL NOT cause an update of the state version unless it has been synchronized either remotely or manually.

NOTE—DateAndTime could be filled when the clock is explicitly requested.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="RemoteSync" type="xsd:boolean" use="required">
					<xsd:annotation>
						<xsd:documentation>Indicates if the time is synchronized to an external source or set by an operator.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="Accuracy" type="xsd:decimal" use="optional">
					<xsd:annotation>
						<xsd:documentation>Accuracy is a decimal number indicating the maximum error in seconds of the absolute time relative to a primary reference clock source.

In systems where time synchronization is not used and the clock is set manually by "eyeball and wristwatch" (EBWW), this SHALL be initialized to three minutes when the clock time is set. If NTP is used, this is equivalent to Root Dispersion + 1⁄2 Root Delay.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="LastSet" type="pm:Timestamp">
					<xsd:annotation>
						<xsd:documentation>Time point when the absolute time was set or synchronized.

NOTE 1—If a time synchronization protocol is used that "changes" the time and date at a high frequency, it is proposed to update this value at a lower periodicity (e.g., once every 10 minutes or once an hour), so as not to consume communications bandwidth unnecessarily.
NOTE 2—Synchronization might be achieved by slewing the time. This means that the virtual frequency of the software clock is adjusted to make the clock go faster or slower until it is corrected.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="TimeZone" type="pm:TimeZone" use="optional">
					<xsd:annotation>
						<xsd:documentation>Identifies the time zone and DST of the clock.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="CriticalUse" type="xsd:boolean" use="optional">
					<xsd:annotation>
						<xsd:documentation>Identifies that the clock information is actively being used in care delivery algorithms/protocols. The implied value SHALL be "false".</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<!--Section: Battery-->
	<xsd:complexType name="BatteryDescriptor">
		<xsd:annotation>
			<xsd:documentation>For battery-powered devices, battery information can be contained in this object.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractDeviceComponentDescriptor">
				<xsd:sequence>
					<xsd:element name="CapacityFullCharge" type="pm:Measurement" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Current battery capacity after a full charge.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="CapacitySpecified" type="pm:Measurement" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Rated capacity the manufacturer claims for the battery.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="VoltageSpecified" type="pm:Measurement" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Specified battery voltage.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="BatteryState">
		<xsd:annotation>
			<xsd:documentation>State of a battery of an MDS.

The current power source is designated by ./@ActivationState:

- If ./@ActivationState equals "On", the device is running on battery
- If ./@ActivationState equals "Off", the device is in mains operation and currently not able to be run on battery
- If ./@ActivationState equals "StndBy", the device is in mains operation and can be switched to run on battery
- If ./@ActivationState equals "Fail", the battery has a malfunction. Detailed error information SHOULD be communicated by using an ALERT SYSTEM.

Enumerations "Shtdn" and "NotRdy" are undefined for BatteryState.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractDeviceComponentState">
				<xsd:sequence>
					<xsd:element name="CapacityRemaining" type="pm:Measurement" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Remaining capacity at current load.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="Voltage" type="pm:Measurement" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Voltage between the terminals of a cell or battery when being discharged. See also IEC 60050-482 International Electrotechnical Vocabulary, 482-03-28.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="Current" type="pm:Measurement" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Electric current delivered by a battery during its discharge; negative if battery is charge. See also IEC 60050-482 International Electrotechnical Vocabulary, 482-03-24.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="Temperature" type="pm:Measurement" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Current battery temperature.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="RemainingBatteryTime" type="pm:Measurement" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Current remaining time until battery is discharged.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="ChargeStatus">
					<xsd:annotation>
						<xsd:documentation>Current charge status of the battery.</xsd:documentation>
					</xsd:annotation>
					<xsd:simpleType>
						<xsd:restriction base="xsd:string">
							<xsd:enumeration value="Ful">
								<xsd:annotation>
									<xsd:documentation>Ful = Full. All available active material is in a state such that the charging under the selected conditions produces no significant increase of capacity. See also IEC 60050-482 International Electrotechnical Vocabulary, 482-05-42.</xsd:documentation>
								</xsd:annotation>
							</xsd:enumeration>
							<xsd:enumeration value="ChB">
								<xsd:annotation>
									<xsd:documentation>ChB = Charging Battery. Battery is currently supplied with electric energy from an external circuit. See also IEC 60050-482 International Electrotechnical Vocabulary, 482-05-27.</xsd:documentation>
								</xsd:annotation>
							</xsd:enumeration>
							<xsd:enumeration value="DisChB">
								<xsd:annotation>
									<xsd:documentation>DisChB = Discharging Battery. Battery delivers, to an external electric circuit and under specified conditions, electric energy produced in the cells. See also IEC 60050-482 International Electrotechnical Vocabulary, 482-03-23</xsd:documentation>
								</xsd:annotation>
							</xsd:enumeration>
							<xsd:enumeration value="DEB">
								<xsd:annotation>
									<xsd:documentation>DEB = Discharged Empty Battery. Discharged secondary battery. See also IEC 60050-482 International Electrotechnical Vocabulary, 482-05-31.</xsd:documentation>
								</xsd:annotation>
							</xsd:enumeration>
						</xsd:restriction>
					</xsd:simpleType>
				</xsd:attribute>
				<xsd:attribute name="ChargeCycles" type="xsd:unsignedInt">
					<xsd:annotation>
						<xsd:documentation>Number of charge/discharge cycles.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<!--Section: Context-->
	<!--Sub-section: Context Device Component-->
	<xsd:complexType name="SystemContextDescriptor">
		<xsd:annotation>
			<xsd:documentation>The context of an MDS that lists the possible relationship of a POC MEDICAL DEVICE into its usage environment by means of context descriptors. Context descriptors do not contain any stateful information. They only assert that the underlying MDS can provide corresponding context state information.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractDeviceComponentDescriptor">
				<xsd:sequence>
					<xsd:element name="PatientContext" type="pm:PatientContextDescriptor" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>The patient context indicates that the POC MEDICAL DEVICE is able to process information about the patient that it is associated with.

A SERVICE PROVIDER SHALL NOT insert or delete the context descriptor ELEMENT during runtime, except when the whole MDS appears/disappears.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="LocationContext" type="pm:LocationContextDescriptor" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>The location context indicates that the POC MEDICAL DEVICE can provide information about the location(s) that it is associated with.

A SERVICE PROVIDER SHALL NOT insert or delete the context descriptor ELEMENT during runtime, except when the whole MDS appears/disappears.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="EnsembleContext" type="pm:EnsembleContextDescriptor" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>The ensemble context indicates that the POC MEDICAL DEVICE can provide information about the ensemble(s) that it is associated with. An ensemble represents an arbitrary grouping of POC MEDICAL DEVICE. The semantics depend on the ensemble itself.

A SERVICE PROVIDER SHALL NOT insert or delete the context descriptor ELEMENT during runtime, except when the whole MDS appears/disappears.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="OperatorContext" type="pm:OperatorContextDescriptor" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>The operator context indicates that the POC MEDICAL DEVICE can provide information about the operator(s) that it is associated with.

A SERVICE PROVIDER SHALL NOT insert or delete the context descriptor ELEMENT during runtime, except when the whole MDS appears/disappears.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="WorkflowContext" type="pm:WorkflowContextDescriptor" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>The workflow context indicates that the POC MEDICAL DEVICE can provide information about the workflow step(s) that it is associated with.

A SERVICE PROVIDER SHALL NOT insert or delete the context descriptor ELEMENT during runtime, except when the whole MDS appears/disappears.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="MeansContext" type="pm:MeansContextDescriptor" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>The means context indicates that the POC MEDICAL DEVICE can provide information about utilized means.

A SERVICE PROVIDER SHALL NOT insert or delete the context descriptor ELEMENT during runtime, except when the whole MDS appears/disappears.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SystemContextState">
		<xsd:annotation>
			<xsd:documentation>Corresponding state of pm:SystemContextDescriptor. This state comes with no additional attributes.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractDeviceComponentState"/>
		</xsd:complexContent>
	</xsd:complexType>
	<!--Sub-section: Base Types-->
	<xsd:complexType name="AbstractContextDescriptor">
		<xsd:annotation>
			<xsd:documentation>Abstract base class for objects that specify that the MDS is able to provide context information that MAY be of relevance for the state data that is present at the communication interface at a certain point of time or time period.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:simpleType name="ContextAssociation">
		<xsd:annotation>
			<xsd:documentation>Defines an association between an arbitrary context and an MDS.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="No">
				<xsd:annotation>
					<xsd:documentation>No = Not Associated. There is currently no context information associated, such that there cannot be made any assumptions on the encompassing context.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Pre">
				<xsd:annotation>
					<xsd:documentation>Pre = Pre-Associated. Context information is in a pre-association state.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Assoc">
				<xsd:annotation>
					<xsd:documentation>Assoc = Associated. Context information is associated.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Dis">
				<xsd:annotation>
					<xsd:documentation>Dis = Disassociated. Context information is no longer associated.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="AbstractContextState">
		<xsd:annotation>
			<xsd:documentation>Base type of a context state. Every context state can be identified as valid by a validator instance. Moreover, a context state's lifecycle is determined by a start and end. AbstractContextState bundles these information.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractMultiState">
				<xsd:sequence>
					<xsd:element name="Validator" type="pm:InstanceIdentifier" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>OPTIONAL list of actors (e.g., persons, devices or any identifiable systems) which have confirmed that a binding of a context state to an MDS is correct.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="Identification" type="pm:InstanceIdentifier" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>OPTIONAL ordered list of identifiers for the context. The list is ordered by the position of the identifiers in the list where the ELEMENT with the lower list index has a higher relevance than any entry with a higher list index. The SERVICE PROVIDER defines the relevance and MAY reorder the list at any time.

NOTE 1—Identification can be used to span a communication context between SERVICE PROVIDERs and SERVICE CONSUMERs.
NOTE 2—Identification can be empty, e.g., if pm:AbstractContextState/@ContextAssociation is "No".</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="ContextAssociation" type="pm:ContextAssociation">
					<xsd:annotation>
						<xsd:documentation>Association of a context. The implied value SHALL be "No".

__R5027: Before a SERVICE PROVIDER decides to remove a specific context state from its MDIB, it SHALL change the context association of that context state to "No".__

NOTE—BICEPS supports no special state removal flag. Therefore, a SERVICE CONSUMER has to rely on the context association in order to decide if a context state can be kept in memory or removed from memory.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="BindingMdibVersion" type="pm:ReferencedVersion" use="optional">
					<xsd:annotation>
						<xsd:documentation>BindingMdibVersion points to the version of an MDIB when a binding of the context state to an MDS starts.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="UnbindingMdibVersion" type="pm:ReferencedVersion">
					<xsd:annotation>
						<xsd:documentation>UnbindingMdibVersion points to the version of an MDIB when a binding of a context state to an MDS ends (i.e., the version where the context association was disassociated the first time).</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="BindingStartTime" type="pm:Timestamp">
					<xsd:annotation>
						<xsd:documentation>Point in time when a binding of a context state to an MDS starts.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
				<xsd:attribute name="BindingEndTime" type="pm:Timestamp">
					<xsd:annotation>
						<xsd:documentation>Point in time when a binding of a context state to an MDS ends.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="BaseDemographics">
		<xsd:annotation>
			<xsd:documentation>Definition of basic demographic information.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Givenname" type="xsd:string" minOccurs="0">
				<xsd:annotation>
					<xsd:documentation>Given name of a person.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
			<xsd:element name="Middlename" type="xsd:string" minOccurs="0" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>Middle name of a person.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
			<xsd:element name="Familyname" type="xsd:string" minOccurs="0">
				<xsd:annotation>
					<xsd:documentation>Family name of a person.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
			<xsd:element name="Birthname" type="xsd:string" minOccurs="0">
				<xsd:annotation>
					<xsd:documentation>Birth name of a person.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
			<xsd:element name="Title" type="xsd:string" minOccurs="0">
				<xsd:annotation>
					<xsd:documentation>Title of a person.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
		</xsd:sequence>
	</xsd:complexType>
	<xsd:complexType name="PersonReference">
		<xsd:annotation>
			<xsd:documentation>A reference to an identifiable person with a name.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Identification" type="pm:InstanceIdentifier" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>The list of identifiers for the person.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
			<xsd:element name="Name" type="pm:BaseDemographics" minOccurs="0">
				<xsd:annotation>
					<xsd:documentation>The name of the person.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
		</xsd:sequence>
	</xsd:complexType>
	<xsd:complexType name="LocationDetail">
		<xsd:annotation>
			<xsd:documentation>Details about a location. This information is derived from the HL7 PV1-3 PL.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
		</xsd:sequence>
		<xsd:attribute name="PoC" type="xsd:string" use="optional">
			<xsd:annotation>
				<xsd:documentation>Name of a point of care unit, e.g., nursing unit, department, or clinic.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="Room" type="xsd:string" use="optional">
			<xsd:annotation>
				<xsd:documentation>Name of the room of a location.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="Bed" type="xsd:string" use="optional">
			<xsd:annotation>
				<xsd:documentation>Name of the bed of a location.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="Facility" type="xsd:string" use="optional">
			<xsd:annotation>
				<xsd:documentation>Name of the facility of a location.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="Building" type="xsd:string" use="optional">
			<xsd:annotation>
				<xsd:documentation>Name of the building of a location.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="Floor" type="xsd:string" use="optional">
			<xsd:annotation>
				<xsd:documentation>Name of the floor of a building.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
	</xsd:complexType>
	<!--Sub-section: Patient Context-->
	<xsd:complexType name="PatientContextDescriptor">
		<xsd:annotation>
			<xsd:documentation>Context descriptor to specify that the MDS possesses a patient-device association.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:simpleType name="Sex">
		<xsd:annotation>
			<xsd:documentation>Sex of a human. 

"Sex" refers to the biological and physiological characteristics that define men and women, while "Gender" refers to the socially constructed roles, behaviors, activities, and attributes that a given society considers appropriate for men and women. See http://www.who.int/gender/whatisgender/en/index.html.

NOTE—ISO/IEC 5218:2004 defines four CODEs that represent human sexes.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Unspec">
				<xsd:annotation>
					<xsd:documentation>Unspec = Unspecified. Sex is not designated.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="M">
				<xsd:annotation>
					<xsd:documentation>M = Male. Indicates a male patient.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="F">
				<xsd:annotation>
					<xsd:documentation>F = Female. Indicates a female patient.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Unkn">
				<xsd:annotation>
					<xsd:documentation>Unkn = Unknown. Indicates that the sex is unknown for different reasons.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="PatientType">
		<xsd:annotation>
			<xsd:documentation>Type of a patient.</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Unspec">
				<xsd:annotation>
					<xsd:documentation>Unspec = Unspecified. Unspecified type.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Ad">
				<xsd:annotation>
					<xsd:documentation>Ad = Adult. Indicates an adult patient.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Ado">
				<xsd:annotation>
					<xsd:documentation>Ado = Adolescent. Indicates an adolescent patient with approximate age range of 12 years to 21 years.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Ped">
				<xsd:annotation>
					<xsd:documentation>Ped = Pediatric. Indicates a pediatric patient with approximate age range of 2 years to 12 years.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Inf">
				<xsd:annotation>
					<xsd:documentation>Inf = Infant. Indicates an infant patient with approximate age range of 1 month to 2 years.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Neo">
				<xsd:annotation>
					<xsd:documentation>Neo = Neonatal. Indicates a neonatal patient with approximate age range of birth to 1 month.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Oth">
				<xsd:annotation>
					<xsd:documentation>Oth = Other. The patient type is designated by some other means.</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="PatientDemographicsCoreData">
		<xsd:annotation>
			<xsd:documentation>The patient demographics data as defined in ISO/IEEE 11073-10201:2004 (6.10.1 Patient Demographics object).
			
__R5012: If the POC MEDICAL DEVICE itself has patient-related observations (e.g., weight, height, etc.) as in- or output, these SHOULD be modelled as METRICs.__

NOTE—In contrast to PatientDemographicsCoreData, METRICs provide a sophisticated observation description, e.g., regarding quality and time-related attributes.

__R5013: The pm:PatientDemographicsCoreData type is intended to be used for information purposes only. Whenever a value is available, it is considered as valid. Invalid values SHALL not be transmitted.__</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:BaseDemographics">
				<xsd:sequence>
					<xsd:element name="Sex" type="pm:Sex" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Sex of the patient.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="PatientType" type="pm:PatientType" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Category of the patient. It refers to the ISO/IEEE 11073-10201:2004 PatientType.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="DateOfBirth" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Date of birth of the patient.

If the timepoint of birth matters, the value SHALL be populated with a time zone.</xsd:documentation>
						</xsd:annotation>
						<xsd:simpleType>
							<xsd:union memberTypes="xsd:dateTime xsd:date xsd:gYearMonth xsd:gYear"/>
						</xsd:simpleType>
					</xsd:element>
					<xsd:element name="Height" type="pm:Measurement" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Height of the patient.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="Weight" type="pm:Measurement" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Weight of the patient.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="Race" type="pm:CodedValue" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Race of the patient.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="NeonatalPatientDemographicsCoreData">
		<xsd:annotation>
			<xsd:documentation>NeonatalPatientDemographicsCoreData constitutes patient demographics for neonates.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:PatientDemographicsCoreData">
				<xsd:sequence>
					<xsd:element name="GestationalAge" type="pm:Measurement" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Gestational age.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="BirthLength" type="pm:Measurement" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Patient length at birth time.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="BirthWeight" type="pm:Measurement" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Patient weight at birth time.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="HeadCircumference" type="pm:Measurement" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Head circumference at birth time.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="Mother" type="pm:PersonReference" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Information about the mother of the neonate.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="PatientContextState">
		<xsd:annotation>
			<xsd:documentation>Observed information about a patient, e.g., demographics.

NOTE—PatientContextState contains information that is typical for a header in an anamnesis questionnaire.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextState">
				<xsd:sequence>
					<xsd:element name="CoreData" type="pm:PatientDemographicsCoreData" minOccurs="0"/>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<!--Sub-section: Location Context-->
	<xsd:complexType name="LocationContextDescriptor">
		<xsd:annotation>
			<xsd:documentation>Context descriptor to specify that the MDS is able to provide information regarding the current spatial position.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="LocationContextState">
		<xsd:annotation>
			<xsd:documentation>A context state that identifies a location in a hospital.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextState">
				<xsd:sequence>
					<xsd:element name="LocationDetail" type="pm:LocationDetail" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>LocationDetail provides human-readable detailed location information. LocationDetail SHOULD NOT be used to form location-based logical systems of devices.

NOTE—Instead, pm:AbstractContextState/pm:Identification can be used to build logical groupings.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<!--Sub-section: Workflow Context-->
	<xsd:complexType name="WorkflowContextDescriptor">
		<xsd:annotation>
			<xsd:documentation>Context descriptor to specify that the MDS is able to provide workflow information.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="ClinicalInfo">
		<xsd:annotation>
			<xsd:documentation>This type describes a minimal clinical observation.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Type" type="pm:CodedValue" minOccurs="0">
				<xsd:annotation>
					<xsd:documentation>Type of clinical information, e.g., allergy, intolerance, clinical condition, diagnosis, problem, etc.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
			<xsd:element name="Code" type="pm:CodedValue" minOccurs="0">
				<xsd:annotation>
					<xsd:documentation>Code that specifies the kind of the type of observation, e.g., a specific allergy or a specific diagnosis.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
			<xsd:element name="Criticality" minOccurs="0">
				<xsd:annotation>
					<xsd:documentation>Potential clinical harm if this clinical information is not considered while treating the patient. The implied value SHALL be "Lo".</xsd:documentation>
				</xsd:annotation>
				<xsd:simpleType>
					<xsd:restriction base="xsd:string">
						<xsd:enumeration value="Lo">
							<xsd:annotation>
								<xsd:documentation>Lo = Low. Non-compliance does not result in a severe, life-threatening, or fatal situation.</xsd:documentation>
							</xsd:annotation>
						</xsd:enumeration>
						<xsd:enumeration value="Hi">
							<xsd:annotation>
								<xsd:documentation>Hi = High. Non-compliance might result in a severe, life-threatening, or fatal situation.</xsd:documentation>
							</xsd:annotation>
						</xsd:enumeration>
					</xsd:restriction>
				</xsd:simpleType>
			</xsd:element>
			<xsd:element name="Description" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>List of possible (localized) free text descriptions of the clinical information.

If a pm:CodedValue for this clinical information is available, it is encouraged to be set as pm:ClinicalInfo/pm:Code.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
			<xsd:element name="RelatedMeasurement" minOccurs="0" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>Related measurements for this clinical observation if applicable.</xsd:documentation>
				</xsd:annotation>
				<xsd:complexType>
					<xsd:sequence>
						<xsd:element name="Value" type="pm:Measurement">
							<xsd:annotation>
								<xsd:documentation>The related measurement's value.</xsd:documentation>
							</xsd:annotation>
						</xsd:element>
						<xsd:element name="ReferenceRange" minOccurs="0" maxOccurs="unbounded">
							<xsd:annotation>
								<xsd:documentation>Representation of the normal or abnormal reference range for the measurement.</xsd:documentation>
							</xsd:annotation>
							<xsd:complexType>
								<xsd:sequence>
									<xsd:element name="Range" type="pm:Range">
										<xsd:annotation>
											<xsd:documentation>Range that SHALL be populated at least with ./@Lower or ./@Upper.</xsd:documentation>
										</xsd:annotation>
									</xsd:element>
									<xsd:element name="Meaning" type="pm:CodedValue" minOccurs="0">
										<xsd:annotation>
											<xsd:documentation>Indicates the meaning of the reference range.</xsd:documentation>
										</xsd:annotation>
									</xsd:element>
								</xsd:sequence>
							</xsd:complexType>
						</xsd:element>
					</xsd:sequence>
					<xsd:attribute name="Validity" type="pm:MeasurementValidity">
						<xsd:annotation>
							<xsd:documentation>Validity of the related measurement. See also pm:MeasurementValidity.</xsd:documentation>
						</xsd:annotation>
					</xsd:attribute>
				</xsd:complexType>
			</xsd:element>
		</xsd:sequence>
	</xsd:complexType>
	<xsd:complexType name="ImagingProcedure">
		<xsd:annotation>
			<xsd:documentation>ImagingProcedure provides identifiers used by the DICOM and HL7 standard to identify the requested imaging procedures resulting from an order in a the hospital. Often these identifiers are created/assigned by the main hospital information system or departmental information systems and are taken over into any medical images by DICOM equipment in the context of this procedure.
The listed ELEMENTs have been taken over from the IHE Radiology Technical Framework's RAD-4 transaction ("Procedure Scheduled") and re-uses the identifiers listed for the HL7 Version 2.5.1 IPC segment group of the OBR segment. Therefore, it is recommended to comply to the underlying HL7 and DICOM data types in order to have seamless integration with other clinical IT such as DICOM modalities or image archives (PACS).

In order to comply to the hierarchy behind the given identifiers, the following rules (taken from IHE) SHALL apply: if a Requested Procedure is comprised of multiple Scheduled Procedure Steps and/or if a Scheduled Procedure Step is comprised of multiple Protocol Codes, each applicable Scheduled Procedure Step / Protocol Code combination is included as a separate ProcedureDetails structure, i.e., the complex type "ProcedureDetails" occurs the same amount of times as there are different Scheduled Procedure Step IDs plus the amount of different Scheduled Procedure Step / Protocol Code combinations.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="AccessionIdentifier" type="pm:InstanceIdentifier">
				<xsd:annotation>
					<xsd:documentation>The Accession Identifier (in DICOM "Accession ID") is an identifier of an "Imaging Service Request", and is (in this ProcedureDetails context) at the top of the hierarchy. A limit of sixteen (16) characters is required to allow compatibility with DICOM.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
			<xsd:element name="RequestedProcedureId" type="pm:InstanceIdentifier">
				<xsd:annotation>
					<xsd:documentation>An pm:ImagingProcedure/pm:AccessionIdentifier can result in various Requested Procedures, each identified uniquely (within the context of the pm:ImagingProcedure/pm:AccessionIdentifier) through a RequestedProcedureID. A limit of sixteen (16) characters is required to allow compatibility with DICOM.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
			<xsd:element name="StudyInstanceUid" type="pm:InstanceIdentifier">
				<xsd:annotation>
					<xsd:documentation>The Study Instance UID is a world-wide unique identifier used by DICOM modalities to group together images in a so-called Study. This grouping is REQUIRED. Under the Study, the modality creates one or more so-called Series which again contain the images. The Series identification ("Series Instance UID") is part of the Procedure Details which refer to a planning process, since a modality is responsible to decide how many Series are created and how their identifiers should look like.
A limit of sixty-four (64) characters is required to allow compatibility with DICOM, with only numbers and dot characters permitted (e.g. 1.2.134124.4.12.34).</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
			<xsd:element name="ScheduledProcedureStepId" type="pm:InstanceIdentifier">
				<xsd:annotation>
					<xsd:documentation>Under a Study (i.e. a Study Instance UID), a Procedure reflected by these ProcedureDetails can be planned in a finer granularity by scheduling different steps that should be performed (usually at a DICOM modality), the so-called "Scheduled Procedure Step"s. Each of these steps is identified by a Scheduled Procedure Step ID. A limit of sixteen (16) characters is required to allow compatibility with DICOM.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
			<xsd:element name="Modality" type="pm:CodedValue" minOccurs="0">
				<xsd:annotation>
					<xsd:documentation>The field modality describes the type of equipment (usually DICOM equipment) used. DICOM offers a list of short identifiers for different device categories, e.g. CT for "Computer Tomography" or US for "Ultrasound". It is advised to follow the list of terms defined in the DICOM standard part 3. A limit of sixteen (16) characters for the first component is required to allow compatibility with DICOM.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
			<xsd:element name="ProtocolCode" type="pm:CodedValue" minOccurs="0">
				<xsd:annotation>
					<xsd:documentation>Below each Scheduled Procedure Step the work can be defined in more detail by defining one or more Protocol Codes under it. A limit of sixteen (16) characters for the first component and sixty-four (64) characters for the second component is required to allow compatibility with DICOM.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
		</xsd:sequence>
	</xsd:complexType>
	<xsd:complexType name="LocationReference">
		<xsd:annotation>
			<xsd:documentation>A reference to an identifiable location with human readable location details.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Identification" type="pm:InstanceIdentifier" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>The list of identifiers for the location.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
			<xsd:element name="LocationDetail" type="pm:LocationDetail" minOccurs="0">
				<xsd:annotation>
					<xsd:documentation>Human readable location details which are intended for information purposes only.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
		</xsd:sequence>
	</xsd:complexType>
	<xsd:complexType name="OrderDetail">
		<xsd:annotation>
			<xsd:documentation>Details of an order that will be performed or that has been performed.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Start" type="xsd:dateTime" minOccurs="0">
				<xsd:annotation>
					<xsd:documentation>Data for start of requested/performed procedure.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
			<xsd:element name="End" type="xsd:dateTime" minOccurs="0">
				<xsd:annotation>
					<xsd:documentation>Data for end of requested/performed procedure.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
			<xsd:element name="Performer" type="pm:PersonParticipation" minOccurs="0" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>Names with roles of attending staff.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
			<xsd:element name="Service" type="pm:CodedValue" minOccurs="0" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>Identifier and textual descriptions of requested/performed procedures </xsd:documentation>
				</xsd:annotation>
			</xsd:element>
			<xsd:element name="ImagingProcedure" type="pm:ImagingProcedure" minOccurs="0" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>ImagingProcedure provide identifiers used by the DICOM and HL7 standard to identify the requested imaging procedures resulting from an order in a the hospital.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
		</xsd:sequence>
	</xsd:complexType>
	<xsd:complexType name="PersonParticipation">
		<xsd:annotation>
			<xsd:documentation>A reference to an identifiable person with a name that participates in a role.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:PersonReference">
				<xsd:sequence>
					<xsd:element name="Role" type="pm:CodedValue" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>Roles the referenced person acts in the relationship.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="WorkflowContextState">
		<xsd:annotation>
			<xsd:documentation>A context state to identify a step in a clinical workflow.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextState">
				<xsd:sequence>
					<xsd:element name="WorkflowDetail" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>A workflow step for a clinical treatment or diagnostic procedure or monitoring procedure.</xsd:documentation>
						</xsd:annotation>
						<xsd:complexType>
							<xsd:sequence>
								<xsd:element ref="ext:Extension" minOccurs="0"/>
								<xsd:element name="Patient" type="pm:PersonReference">
									<xsd:annotation>
										<xsd:documentation>Subject of the order.</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
								<xsd:element name="AssignedLocation" type="pm:LocationReference" minOccurs="0">
									<xsd:annotation>
										<xsd:documentation>Location the order assigned to.</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
								<xsd:element name="VisitNumber" type="pm:InstanceIdentifier" minOccurs="0">
									<xsd:annotation>
										<xsd:documentation>Reference key of inpatient stay or outpatient visit of the patient administration system.</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
								<xsd:element name="DangerCode" type="pm:CodedValue" minOccurs="0" maxOccurs="unbounded">
									<xsd:annotation>
										<xsd:documentation>Identifier and textual descriptions of patient immanent risks, e.g., infectious diseases.</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
								<xsd:element name="RelevantClinicalInfo" type="pm:ClinicalInfo" minOccurs="0" maxOccurs="unbounded">
									<xsd:annotation>
										<xsd:documentation>Clinical information that is relevant for the order.</xsd:documentation>
									</xsd:annotation>
								</xsd:element>
								<xsd:element name="RequestedOrderDetail" minOccurs="0">
									<xsd:annotation>
										<xsd:documentation>Initial order details at the time of order release.</xsd:documentation>
									</xsd:annotation>
									<xsd:complexType>
										<xsd:complexContent>
											<xsd:extension base="pm:OrderDetail">
												<xsd:sequence>
													<xsd:element name="ReferringPhysician" type="pm:PersonReference" minOccurs="0">
														<xsd:annotation>
															<xsd:documentation>Physician as the initiator of the clinical process, e.g. the general practitioner.</xsd:documentation>
														</xsd:annotation>
													</xsd:element>
													<xsd:element name="RequestingPhysician" type="pm:PersonReference" minOccurs="0">
														<xsd:annotation>
															<xsd:documentation>Source that initiated the order.</xsd:documentation>
														</xsd:annotation>
													</xsd:element>
													<xsd:element name="PlacerOrderNumber" type="pm:InstanceIdentifier">
														<xsd:annotation>
															<xsd:documentation>Reference key of the order generating system.</xsd:documentation>
														</xsd:annotation>
													</xsd:element>
												</xsd:sequence>
											</xsd:extension>
										</xsd:complexContent>
									</xsd:complexType>
								</xsd:element>
								<xsd:element name="PerformedOrderDetail" minOccurs="0">
									<xsd:annotation>
										<xsd:documentation>Recent state of order details after order has been performed.</xsd:documentation>
									</xsd:annotation>
									<xsd:complexType>
										<xsd:complexContent>
											<xsd:extension base="pm:OrderDetail">
												<xsd:sequence>
													<xsd:element name="FillerOrderNumber" type="pm:InstanceIdentifier" minOccurs="0">
														<xsd:annotation>
															<xsd:documentation>Reference key of the order filler system/ departmental system completing or changing order details.</xsd:documentation>
														</xsd:annotation>
													</xsd:element>
													<xsd:element name="ResultingClinicalInfo" type="pm:ClinicalInfo" minOccurs="0" maxOccurs="unbounded">
														<xsd:annotation>
															<xsd:documentation>Clinical information resulting from the service.</xsd:documentation>
														</xsd:annotation>
													</xsd:element>
												</xsd:sequence>
											</xsd:extension>
										</xsd:complexContent>
									</xsd:complexType>
								</xsd:element>
							</xsd:sequence>
						</xsd:complexType>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<!--Sub-section: Operator Context-->
	<xsd:complexType name="OperatorContextDescriptor">
		<xsd:annotation>
			<xsd:documentation>Context descriptor to specify that the MDS is able to provide operator information.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="OperatorContextState">
		<xsd:annotation>
			<xsd:documentation>A context state that identifies an operator of an MDS or a part of it.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextState">
				<xsd:sequence>
					<xsd:element name="OperatorDetails" type="pm:BaseDemographics" minOccurs="0">
						<xsd:annotation>
							<xsd:documentation>Human-readable details (i.e., name) about the operator.</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<!--Sub-section: Means Context-->
	<xsd:complexType name="MeansContextDescriptor">
		<xsd:annotation>
			<xsd:documentation>Context descriptor to specify that the MDS is able to provide information about utilized means.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="MeansContextState">
		<xsd:annotation>
			<xsd:documentation>A context state to identify a means that is utilized by an MDS or a part of it.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextState"/>
		</xsd:complexContent>
	</xsd:complexType>
	<!--Sub-section: Ensemble Context-->
	<xsd:complexType name="EnsembleContextDescriptor">
		<xsd:annotation>
			<xsd:documentation>Context descriptor to specify that the MDS is able to provide ensemble information.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="EnsembleContextState">
		<xsd:annotation>
			<xsd:documentation>A context state that identifies an ensemble of POC MEDICAL DEVICEs. How the ensemble is grouped and what meaning is conveyed by the ensemble, is determined by other means.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextState"/>
		</xsd:complexContent>
	</xsd:complexType>
	<!--Section: Containment Tree-->
	<xsd:attributeGroup name="ContainmentTreeInfo">
		<xsd:annotation>
			<xsd:documentation>ContainmentTreeInfo summarizes ATTRIBUTEs related to a CONTAINMENT TREE entry.</xsd:documentation>
		</xsd:annotation>
		<xsd:attribute name="HandleRef" type="pm:HandleRef" use="optional">
			<xsd:annotation>
				<xsd:documentation>Handle reference to the descriptor that the CONTAINMENT TREE entry represents.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="ParentHandleRef" type="pm:HandleRef" use="optional">
			<xsd:annotation>
				<xsd:documentation>Handle reference to the parent descriptor of the descriptor that this CONTAINMENT TREE entry represents.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="EntryType" type="xsd:QName" use="optional">
			<xsd:annotation>
				<xsd:documentation>Qualified name of the descriptor that the CONTAINMENT TREE entry represents.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="ChildrenCount" type="xsd:int" use="optional">
			<xsd:annotation>
				<xsd:documentation>Number of child ELEMENTs that the CONTAINMENT TREE entry possesses.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
	</xsd:attributeGroup>
	<xsd:complexType name="ContainmentTree">
		<xsd:annotation>
			<xsd:documentation>CONTAINMENT TREE part of an ELEMENT of an MDS CONTAINMENT TREE.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Entry" type="pm:ContainmentTreeEntry" minOccurs="0" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>An entry of a CONTAINMENT TREE ENTRY.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
		</xsd:sequence>
		<xsd:attributeGroup ref="pm:ContainmentTreeInfo"/>
	</xsd:complexType>
	<xsd:complexType name="ContainmentTreeEntry">
		<xsd:annotation>
			<xsd:documentation>An entry in a CONTAINMENT TREE.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Type" type="pm:CodedValue" minOccurs="0">
				<xsd:annotation>
					<xsd:documentation>If given, pm:AbstractDescriptor/pm:Type of the descriptor that is conveyed with the CONTAINMENT TREE entry.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
		</xsd:sequence>
		<xsd:attributeGroup ref="pm:ContainmentTreeInfo"/>
	</xsd:complexType>
	<xsd:element name="MdibContainer" type="pm:Mdib"></xsd:element>
</xsd:schema>)");

}
#endif