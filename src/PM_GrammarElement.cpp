/*
 * PM_GrammarElement.cpp
 *
 *  Created on: Mar 24, 2012
 *      Author: massi
 */

#include "PM_GrammarElement.h"

namespace PhantomMenace {

GrammarElement::GrammarElement(const std::string& name,
		const std::string& author,
		const std::string& authorEmail,
		const std::string& creationDate) :
		Element(name), author(author),
		authorEmail(authorEmail), creationDate(creationDate)
{

}

GrammarElement::~GrammarElement()
{

}

const std::string& GrammarElement::getAuthor() const
{
	return author;
}

const std::string& GrammarElement::getAuthorEmail() const
{
	return authorEmail;
}

const std::string& GrammarElement::getCreationDate() const
{
	return creationDate;
}

} /* namespace PhantomMenace */
