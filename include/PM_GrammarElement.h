/*
 * PM_GrammarElement.h
 *
 *  Created on: Mar 24, 2012
 *      Author: massi
 */

#ifndef PM_GRAMMARELEMENT_H_
#define PM_GRAMMARELEMENT_H_

#include "PM_Element.h"

namespace PhantomMenace {

class GrammarElement : public Element
{
public:
	GrammarElement(const std::string& name,
			const std::string& author = "",
			const std::string& authorEmail = "",
			const std::string& creationDate = "");
	virtual ~GrammarElement();

	const std::string& getAuthor() const;
	const std::string& getAuthorEmail() const;
	const std::string& getCreationDate() const;

private:
	std::string author;
	std::string authorEmail;
	std::string creationDate;
};

} /* namespace PhantomMenace */
#endif /* PM_GRAMMARELEMENT_H_ */
