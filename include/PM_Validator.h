/*
 * PM_Validator.h
 *
 *  Created on: Apr 2, 2012
 *      Author: massi
 */

#ifndef PM_VALIDATOR_H_
#define PM_VALIDATOR_H_

#include "PM_ParsingEnvironment.h"
#include <vector>
#include <string>
#include <exception>
#include <stdexcept>

typedef std::vector<std::string> StringVector_t;

namespace PhantomMenace
{

class Validator
{
public:
	Validator(const ParsingEnvironment& iEnvironment)
		throw (std::runtime_error);
	virtual ~Validator();

	bool validateString(const std::string& iString);

private:
	const ParsingEnvironment& anEnvironment;
	StringVector_t aVectorValidatedStrings;

protected:
};

} /* namespace PhantomMenace */


#endif /* PM_VALIDATOR_H_ */
