/*
 * validate_grammar.cpp
 *
 *  Created on: Apr 1, 2012
 *      Author: massi
 */

#include "PM_ParsingEnvironment.h"
#include "PM_GrammarElement.h"
#include <iostream>
#include <cstdlib>

const char *grammarFile = "../../test/GrammarExample.ini";

int main(int argc, char *argv[])
{
	PhantomMenace::ParsingEnvironment pe;
	if (pe.parseFromFile(grammarFile))
	{
		const ElementVector_t& tokens = pe.getElements();

		PhantomMenace::TokenElement elem = tokens[0];

		if (tokens[0].getElementName() != "SerialCode")
			exit(EXIT_FAILURE);

		if (tokens[0].getElementFormat() != "000-000-000")
			exit(EXIT_FAILURE);

		if (tokens[0].getPreSeparator() != ' ')
			exit(EXIT_FAILURE);

		if (tokens[0].isPreSeparatorMandatory() != false)
			exit(EXIT_FAILURE);

		if (tokens[0].isPreSeparatorMultiple() != true)
			exit(EXIT_FAILURE);

		exit(EXIT_SUCCESS);
	}

	exit(EXIT_FAILURE);
}


