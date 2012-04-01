/*
 * PM_TokenElement.cpp
 *
 *  Created on: Mar 24, 2012
 *      Author: massi
 */

#include "PM_TokenElement.h"
#include "PM_Element.h"

namespace PhantomMenace {

TokenElement::TokenElement(const std::string& iElementName,
		const std::string& iElementFormat) :
		Element(iElementName),
		aPreSeparator(' '),
		aPreSeparatorMandatory(false),
		aPreSeparatorMultiple(false),
		anElementFormat(iElementFormat)
{

}

TokenElement::~TokenElement()
{

}

const char TokenElement::getPreSeparator() const
{
	return aPreSeparator;
}

const bool TokenElement::isPreSeparatorMandatory() const
{
	return aPreSeparatorMandatory;
}

const bool TokenElement::isPreSeparatorMultiple() const
{
	return aPreSeparatorMultiple;
}

const std::string& TokenElement::getElementFormat() const
{
	return anElementFormat;
}
} /* namespace PhantomMenace */
