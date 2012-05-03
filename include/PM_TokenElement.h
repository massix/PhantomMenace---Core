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
	bool shouldPreSeparatorBeEscaped() const;

	const std::string& getElementFormat() const;

	const std::string& getElementValue() const;

private:
	char aPreSeparator;
	bool aPreSeparatorMandatory;
	bool aPreSeparatorMultiple;

	std::string anElementFormat;
	std::string anElementValue;

protected:
	void setElementValue(const std::string& iValue);
};

} /* namespace PhantomMenace */
#endif /* PM_TOKENELEMENT_H_ */
