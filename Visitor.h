#pragma once
#ifndef _Visitor_H
#define _Visitor_H

#include "Typedefs.h"
/**
* @class Visitor
* @brief Defines an abstract base class for all Visitor classes
*/

class Visitor
{
public:

	/// Dtor
	virtual ~Visitor(){}

	/// Visit method for LEAF_NODE instances
	/// Pure virtual function.
	virtual void visit(const LEAF_NODE& node) = 0;

	/// Visit method for COMPOSITE_NEGATE_NODE instances
	/// Pure virtual function.
	virtual void visit(const COMPOSITE_NEGATE_NODE& node) = 0;

	/// Visit method for COMPOSITE_ADD_NODE instances
	/// Pure virtual function.
	virtual void visit(const COMPOSITE_ADD_NODE& node) = 0;

	/// Visit method for COMPOSITE_SUBTRACT_NODE instances
	/// Pure virtual function.
	virtual void visit(const COMPOSITE_SUBTRACT_NODE& node) = 0;

	/// Visit method for COMPOSITE_MULTIPLY_NODE instances
	/// Pure virtual function.
	virtual void visit(const COMPOSITE_MULTIPLY_NODE& node) = 0;

	/// Visit method for COMPOSITE_DIVIDE_NODE instances
	/// Pure virtual function.
	virtual void visit(const COMPOSITE_DIVIDE_NODE& node) = 0;
};

#endif /* _Visitor_H */