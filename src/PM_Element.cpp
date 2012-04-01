/*
 * PM_Element.cpp
 *
 *  Created on: Mar 24, 2012
 *      Author: massi
 */

#include "PM_Element.h"

namespace PhantomMenace {

Element::Element(const std::string& name) : name(name)
{
}

Element::~Element()
{
}

const std::string& Element::getElementName() const
{
	return this->name;
}

bool Element::operator ==(const Element& right) const
{
	return (this->name == right.name);
}

Element& Element::operator=(const Element& right)
{
	this->name = right.name;
	return *(this);
}

} /* namespace PhantomMenace */
