/*
 * PM_TokenElement.h
 *
 *  Created on: Mar 24, 2012
 *      Author: massi
 */

#ifndef PM_TOKENELEMENT_H_
#define PM_TOKENELEMENT_H_

#include "PM_Element.h"
#include <string>

namespace PhantomMenace
{

class TokenElement : public Element
{
	friend class ParsingEnvironment;

public:
	TokenElement(const std::string& iElementName,
			const std::string& iElementFormat);
	virtual ~TokenElement();

	const char getPreSeparator() const;
	const bool isPreSeparatorMandatory() const;
	const bool isPreSeparatorMultiple() const;

	const std::string& getElementFormat() const;

private:
	char aPreSeparator;
	bool aPreSeparatorMandatory;
	bool aPreSeparatorMultiple;

	std::string anElementFormat;

};

} /* namespace PhantomMenace */
#endif /* PM_TOKENELEMENT_H_ */
