/*
 * PM_ParsingEnvironment.h
 *
 *  Created on: Mar 24, 2012
 *      Author: massi
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
