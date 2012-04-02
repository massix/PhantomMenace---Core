/*
 * PM_Validator.cpp
 *
 *  Created on: Apr 2, 2012
 *      Author: massi
 */

#include "PM_ParsingEnvironment.h"
#include "PM_Validator.h"
#include "PM_TokenElement.h"

#include <vector>
#include <string>
#include <exception>
#include <stdexcept>

#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

namespace PhantomMenace
{

Validator::Validator(ParsingEnvironment& iEnvironment)
	throw (std::runtime_error)
	: anEnvironment(iEnvironment)
{
	if (!anEnvironment.isEnvironmentValid())
		throw std::runtime_error("Provided environment is not valid!");

}

Validator::~Validator()
{

}

bool Validator::validateString(const std::string& iString)
{
	/*
	 * The idea now is to use boost::regex to manipulate the format of the
	 * elements and get a regular expression which may be validated against
	 * the given string
	 * p.e. given the extended format like 000-000-000 n+|n+, this should
	 * become ^[0-9][0-9][0-9] [A-z]*?|[A-z]*?$
	 * btw: extended format means the format built by every TokenElement in the
	 * given ParsingEnvironment
	 */

	std::string extendedFormat("^");
	ElementVector_t::const_iterator ite;
	for (ite = anEnvironment.getElements().begin();
			ite != anEnvironment.getElements().end(); ++ite)
	{
		if ((*ite).shouldPreSeparatorBeEscaped())
			extendedFormat += '\\';

		extendedFormat += static_cast<char>((*ite).getPreSeparator());

		switch ((*ite).isPreSeparatorMandatory())
		{
		case true:
			switch ((*ite).isPreSeparatorMultiple())
			{
			/* Preseparator is mandatory and multiple, the preseparator
			 * regex should look like "pp*?"
			 */
			case true:
				if ((*ite).shouldPreSeparatorBeEscaped())
							extendedFormat += '\\';
				extendedFormat += static_cast<char>((*ite).getPreSeparator());
				extendedFormat += "*?";
				break;
				/* Preseparator is mandatory but not multiple, the preseparator
				 * regex should look like "p?"
				 */
			case false:
				extendedFormat += "?";
				break;
			}
			break;
			/* Preseparator is NOT mandatory but could be multiple
			 * regex should look like "p*?" (we honestly don't care)
			 */
		case false:
			extendedFormat += "*?";

			break;
		}

		extendedFormat += "(";
		extendedFormat += (*ite).getElementFormat();
		extendedFormat += ")";
	}

	extendedFormat += "$";

	// Now do the changes!
	boost::algorithm::replace_all(extendedFormat, "0+", "[0-9]*");
	boost::algorithm::replace_all(extendedFormat, "0", "[0-9]");

	boost::algorithm::replace_all(extendedFormat, "n+", "[A-z]*?");
	boost::algorithm::replace_all(extendedFormat, "n", "[A-z]");

	try
	{
		boost::regex regex(extendedFormat);
		boost::cmatch cmatch;
		if (boost::regex_match(iString, regex))
		{
			boost::regex_match(iString.data(), cmatch, regex);
			for (size_t i = 1; i < cmatch.size(); i++)
				anEnvironment.setValueForElement(i-1, cmatch[i]);

			return true;
		}

		return false;
	}
	catch (boost::regex_error& e)
	{
		std::cerr << "Got boost::regex_error -> " << e.what() << std::endl;
	}

	return false;
}


} /* namespace PhantomMenace */



