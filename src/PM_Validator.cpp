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

		if ((*ite).isPreSeparatorMandatory())
		{
			/* Preseparator is mandatory and multiple, the preseparator
			 * regex should look like "pp*?"
			 */
			if ((*ite).isPreSeparatorMultiple())
			{
				if ((*ite).shouldPreSeparatorBeEscaped())
					extendedFormat += '\\';

				extendedFormat += static_cast<char>((*ite).getPreSeparator());
				extendedFormat += "*?";
			}

			/* Preseparator is mandatory but not multiple, the preseparator
			 * regex should look like "p?"
			 */
			else
			{
				extendedFormat += "?";
			}
		}

		/* Preseparator is NOT mandatory but could be multiple
		 * regex should look like "p*?" (we honestly don't care)
		 */
		else
		{
			extendedFormat += "*?";
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
	catch (const boost::regex_error& e)
	{
		std::cerr << "Got boost::regex_error -> " << e.what() << std::endl;
	}

	return false;
}


} /* namespace PhantomMenace */



