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


#ifndef PM_PARSINGENVIRONMENT_H_
#define PM_PARSINGENVIRONMENT_H_

#include "PM_Element.h"
#include "PM_GrammarElement.h"
#include "PM_TokenElement.h"

#include "PM_IP_Parser.h"

#include <vector>
#include <cstdlib>

typedef std::vector<PhantomMenace::TokenElement> ElementVector_t;

namespace PhantomMenace {

class ParsingEnvironment {
public:
	ParsingEnvironment();
	virtual ~ParsingEnvironment();

	bool parseFromFile(const std::string& iFileName);
	bool parse(const std::string& iRawInput);

	bool isEnvironmentValid() const;
	bool isGrammarLoaded() const;

	const GrammarElement& getGrammar() const;
	const ElementVector_t& getElements() const;

	void logElements() const;

	bool setLogFile(const std::string& iFilePath);
	void setLogFile(FILE *iFileFd);

	void setValueForElement(int index, const std::string& iElementValue);

	const TokenElement& operator[](const std::string& iElementName);

private:
	PhantomMenace::GrammarElement* grammar;
	ElementVector_t elements;
	PhantomMenace::IniParser::Parser *parser;

	bool validate();
	void buildElementsVector();

	bool valid;

	FILE *aLogFile;
};

} /* namespace PhantomMenace */
#endif /* PM_PARSINGENVIRONMENT_H_ */
