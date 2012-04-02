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

#define check_valid_string(s) \
	if (!validator.validateString(s)) {\
		std::cout << "String " << s "  should be valid!\n";\
		exit(EXIT_FAILURE); \
	}

#define check_not_valid_string(s) \
	if (validator.validateString(s)) {\
		std::cout << "String "  << s << "should not be valid!\n";\
		exit(EXIT_FAILURE);\
	}

int main(int argc, char *argv[])
{
	int exit_value = EXIT_SUCCESS;

	PhantomMenace::ParsingEnvironment pe;
	if (pe.parseFromFile(grammarFile))
	{
		try
		{
			PhantomMenace::Validator validator(pe);

			check_valid_string("555/123-456-789@Massimo|Gengarelli");
			check_valid_string("   981/123-456-789@Massimo|Gengarelli");
			check_valid_string("  245/123-456-789Massimo||||Gengarelli");
			check_valid_string(" 777/123-789-255Massimo|Gengarelli");

			// Get the elements of the last parsed string
			if (pe["TicketNumber"].getElementValue() != "777")
				exit(EXIT_FAILURE);
			if (pe["SerialCode"].getElementValue() != "123-789-255")
				exit(EXIT_FAILURE);
			if (pe["FirstName"].getElementValue() != "Massimo")
				exit(EXIT_FAILURE);
			if (pe["LastName"].getElementValue() != "Gengarelli")
				exit(EXIT_FAILURE);

			check_not_valid_string("666 / 12-3456-789@Massimo|Gengarelli");
			check_not_valid_string("123//123-456-000 @  Massimo/Gengarelli");
			check_not_valid_string("    444/321-434-123@Massimo&Gengarelli");
		}
		catch (...)
		{
			std::cerr << "Got exception\n";
		}
	}

	exit(exit_value);
}


