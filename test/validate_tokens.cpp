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
		PhantomMenace::TokenElement elem = pe.getElements()[1];

		if (elem.getElementName() != "SerialCode")
			exit(EXIT_FAILURE);

		if (elem.getElementFormat() != "000-000-000")
			exit(EXIT_FAILURE);

		if (elem.getPreSeparator() != '/')
			exit(EXIT_FAILURE);

		if (elem.isPreSeparatorMandatory() != true)
			exit(EXIT_FAILURE);

		if (elem.isPreSeparatorMultiple() != false)
			exit(EXIT_FAILURE);

		exit(EXIT_SUCCESS);
	}

	exit(EXIT_FAILURE);
}


