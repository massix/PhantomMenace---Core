/*
 * PM_Element.h
 *
 *  Created on: Mar 24, 2012
 *      Author: massi
 */

#ifndef PM_ELEMENT_H_
#define PM_ELEMENT_H_

#include <string>

namespace PhantomMenace
{

class Element
{
public:
	Element(const std::string& name);
	virtual ~Element();

	const std::string& getElementName() const; //< non-virtual

	virtual bool operator== (const Element& right) const;
	virtual Element& operator= (const Element& right);

protected:
	std::string name;
};

} /* namespace PhantomMenace */
#endif /* PM_ELEMENT_H_ */
