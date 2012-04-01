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
	}

	exit(EXIT_FAILURE);
}


