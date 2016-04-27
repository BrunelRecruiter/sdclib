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
 *  LocalizedText.h
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

#ifndef LOCALIZEDTEXT_H_
#define LOCALIZEDTEXT_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class LocalizedText {
private:
	LocalizedText(const CDM::LocalizedText & object);
	operator CDM::LocalizedText() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	LocalizedText();
	LocalizedText(const LocalizedText & object);
	virtual ~LocalizedText();
    
    void copyFrom(const LocalizedText & object);
    LocalizedText & operator=(const LocalizedText & object);
    
    typedef CDM::LocalizedText WrappedType;

	LocalizedText & setLang(const Language & value);
	Language getLang() const;
	bool getLang(Language & out) const;
	bool hasLang() const;

	std::string get() const;
	LocalizedText & set(const std::string & value); 
private:
	std::shared_ptr<CDM::LocalizedText> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* LOCALIZEDTEXT_H_ */