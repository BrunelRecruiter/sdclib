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
 *  CauseInfo.h
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#ifndef CAUSEINFO_H_
#define CAUSEINFO_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class CauseInfo {
private:
	CauseInfo(const CDM::CauseInfo & object);
	operator CDM::CauseInfo() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	CauseInfo();
	CauseInfo(const CauseInfo & object);
	virtual ~CauseInfo();
    
    void copyFrom(const CauseInfo & object);
    CauseInfo & operator=(const CauseInfo & object);
    
    typedef CDM::CauseInfo WrappedType;

	CauseInfo & setRemedy(const RemedyInfo & value);
	RemedyInfo getRemedy() const;
	bool getRemedy(RemedyInfo & out) const;
	bool hasRemedy() const;

	CauseInfo & addDescription(const LocalizedText & value);
	std::vector<LocalizedText> getDescriptions() const;
	void clearDescriptions();
	
private:
	std::shared_ptr<CDM::CauseInfo> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* CAUSEINFO_H_ */