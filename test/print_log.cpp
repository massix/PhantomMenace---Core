/*
 * validate_grammar.cpp
 *
 *  Created on: Apr 1, 2012
 *      Author: massi
 */

#include "PM_ParsingEnvironment.h"
#include "PM_GrammarElement.h"
#include "PM_Validator.h"
#include <iostream>
#include <cstdlib>

const char *grammarFile = "../../test/GrammarExample.ini";

int main(int argc, char *argv[])
{
	PhantomMenace::ParsingEnvironment pe;
	pe.setLogFile("./print_log.log");
	if (pe.parseFromFile(grammarFile))
	{
		try
		{
			pe.logElements();
		}
		catch (...)
		{
			std::cerr << "Got exception\n";
		}
	}

	exit(EXIT_FAILURE);
}


