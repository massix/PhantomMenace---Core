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
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

namespace PhantomMenace {

ParsingEnvironment::ParsingEnvironment() :
		grammar(0), parser(IniParser::Parser::getInstancePtr()), valid(false)
{

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
	std::cout << "====[ PARSER LOG STARTING ]====\n";

	// Log the grammar
	std::cout << "GRAMMAR ELEMENT:\n";
	std::cout << "    NAME  : \"" << grammar->getElementName() << "\"\n";
	std::cout << "    AUTHOR: \"" << (*grammar).getAuthor() << "\"\n";
	std::cout << "    EMAIL : \"" << grammar->getAuthorEmail() << "\"\n";
	std::cout << "    DATE  : \"" << grammar->getCreationDate() << "\"\n";

	// Log the tokens
	ElementVector_t::const_iterator ite;
	for (ite = this->elements.begin(); ite != this->elements.end(); ++ite)
	{
		std::cout << "TOKEN ELEMENT:\n";
		std::cout << "    NAME        : \"" << ite->getElementName() << "\"\n";
		std::cout << "    PRESEPARATOR: \"" << ite->getPreSeparator() << "\"\n";
		std::cout << "       MANDATORY: \"" << ite->isPreSeparatorMandatory() << "\"\n";
		std::cout << "       MULTIPLE : \"" << ite->isPreSeparatorMultiple() << "\"\n";
		std::cout << "    FORMAT      : \"" << ite->getElementFormat() << "\"\n";
	}

	std::cout << "====[ PARSER LOG FINISHED ]====\n";
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

} /* namespace PhantomMenace */
