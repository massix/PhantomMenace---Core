/*
 * PM_ParsingEnvironment.cpp
 *
 *  Created on: Mar 24, 2012
 *      Author: massi
 */

#include "PM_ParsingEnvironment.h"
#include "PM_TokenElement.h"
#include "PM_IP_Parser.h"
#include "PM_IP_IniElement.h"

#include <iostream>
#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#define flog(x...) fprintf(aLogFile, x)

namespace PhantomMenace {

ParsingEnvironment::ParsingEnvironment() :
		grammar(0),
		parser(IniParser::Parser::getInstancePtr()),
		valid(false),
		aLogFile(stdout)
{
	IniParser::Parser::clearInstance();
}

ParsingEnvironment::~ParsingEnvironment()
{
	if (grammar)
		delete grammar;

	IniParser::Parser::resetInstance();
}

bool ParsingEnvironment::isEnvironmentValid() const
{
	return valid;
}

bool ParsingEnvironment::isGrammarLoaded() const
{
	return !(grammar == 0);
}

bool ParsingEnvironment::parse(const std::string& input)
{
	parser->parse(input.c_str());
	return validate();
}

bool ParsingEnvironment::parseFromFile(const std::string& iFileName)
{
	parser->parseFromFile(iFileName);
	return validate();
}

bool ParsingEnvironment::validate()
{
	if (parser->hasElement("grammar"))
	{
		const IniParser::IniElement& elem =
				parser->getElement("grammar");

		grammar = new GrammarElement(
				elem["grammar.name"],
				elem.hasAttribute("grammar.author")?
						elem["grammar.author"]: "",
				elem.hasAttribute("grammar.author.email")?
						elem["grammar.author.email"]: "",
				elem.hasAttribute("grammar.creationDate")?
						elem["grammar.creationDate"]: "");
		valid = true;

		buildElementsVector();

		return true;
	}

	return false;
}

const GrammarElement& ParsingEnvironment::getGrammar() const
{
	return (*grammar);
}

const ElementVector_t& ParsingEnvironment::getElements() const
{
	return elements;
}

void ParsingEnvironment::logElements() const
{
	flog("====[ PARSER LOG STARTING ]====\n");
	// Log the grammar
	flog("GRAMMAR ELEMENT:\n");
	flog("    NAME  : \"%s\"\n", grammar->getElementName().c_str());
	flog("    AUTHOR: \"%s\"\n", grammar->getAuthor().c_str());
	flog("    EMAIL : \"%s\"\n", grammar->getAuthorEmail().c_str());
	flog("    DATE  : \"%s\"\n", grammar->getCreationDate().c_str());

	// Log the tokens
	ElementVector_t::const_iterator ite;
	for (ite = this->elements.begin(); ite != this->elements.end(); ++ite)
	{
		flog("TOKEN ELEMENT:\n");
		flog("    NAME        : \"%s\"\n", ite->getElementName().c_str());
		flog("    PRESEPARATOR: \"%c\"\n", ite->getPreSeparator());
		flog("       MANDATORY: \"%s\"\n", ite->isPreSeparatorMandatory()?
				"Yes" : "No");
		flog("       MULTIPLE : \"%s\"\n", ite->isPreSeparatorMultiple()?
				"Yes" : "No");
		flog("    FORMAT      : \"%s\"\n", ite->getElementFormat().c_str());
	}

	flog("====[ PARSER LOG FINISHED ]====\n");
}

void ParsingEnvironment::buildElementsVector()
{
	const Elements_t& elements = parser->getElements();

	Elements_t::const_iterator ite;
	for (ite = elements.begin(); ite != elements.end(); ++ite)
	{
		if ((*ite).getElementName() == "token")
		{
			TokenElement token((*ite)["token.name"], (*ite)["token.string"]);

			if ((*ite).hasAttribute("token.preseparator"))
			{
				std::string aPreSep = (*ite)["token.preseparator"];
				boost::algorithm::erase_all(aPreSep, " ");
				token.aPreSeparator =
						boost::lexical_cast<int>(aPreSep);
			}

			if ((*ite).hasAttribute("token.preseparator.mandatory"))
				token.aPreSeparatorMandatory =
						(*ite)["token.preseparator.mandatory"] == "Yes"?
								true : false;

			if ((*ite).hasAttribute("token.preseparator.multiple"))
				token.aPreSeparatorMultiple =
						(*ite)["token.preseparator.multiple"] == "Yes"?
								true : false;

			this->elements.push_back(token);
		}
	}
}

bool ParsingEnvironment::setLogFile(const std::string& iFilePath)
{
	aLogFile = fopen(iFilePath.c_str(), "w+");
	if (!aLogFile)
	{
		aLogFile = stdout;
		return false;
	}

	return true;
}

void ParsingEnvironment::setLogFile(FILE *iFileFd)
{
	aLogFile = iFileFd;
}

void ParsingEnvironment::setValueForElement(int index,
		const std::string& iElementValue)
{
	try
	{
		elements[index].anElementValue = iElementValue;
	}
	catch(...)
	{
		/* Do nothing */
	}
}

const TokenElement& ParsingEnvironment::operator [](const std::string& iElementName)
{
	ElementVector_t::const_iterator ite;
	for (ite = elements.begin(); ite != elements.end(); ++ite)
	{
		if ((*ite).getElementName() == iElementName)
			return (*ite);
	}

	throw std::runtime_error("Element not found");
}

} /* namespace PhantomMenace */
