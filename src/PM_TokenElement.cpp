/* Copyright (c) 2012, Massimo Gengarelli <massimo.gengarelli@gmail.com>
 *
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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

bool TokenElement::shouldPreSeparatorBeEscaped() const
{
	return (
		aPreSeparator == '|' ||
		aPreSeparator == '[' ||
		aPreSeparator == ']' ||
		aPreSeparator == '+' ||
		aPreSeparator == '*' ||
		aPreSeparator == '\\' ||
		aPreSeparator == '(' ||
		aPreSeparator == ')');
}

void TokenElement::setElementValue(const std::string& iValue)
{
	anElementValue = iValue;
}

const std::string& TokenElement::getElementValue() const
{
	return anElementValue;
}
} /* namespace PhantomMenace */
