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
		pe.logElements();

		std::cout << "Is grammar loaded? ";
		if (pe.isGrammarLoaded())
		{
			std::cout << "yes!\n";

			std::cout << "Checking grammar's name... ";
			if (pe.getGrammar().getElementName() != "Example Grammar")
			{
				std::cout << " WRONG! Got \"" << pe.getGrammar().getElementName() << "\"\n";
				exit(EXIT_FAILURE);
			}
			std::cout << "correct!\n";
		}
		else
		{
			std::cout << "no\n";
			exit(EXIT_FAILURE);
		}

		std::cout << "Is environment valid? ";
		if (pe.isEnvironmentValid())
			std::cout << "yes!\n";

		else
		{
			std::cout << "no!\n";
			exit(EXIT_FAILURE);
		}

		exit(EXIT_SUCCESS);
	}

	exit(EXIT_FAILURE);
}


