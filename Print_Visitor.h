#pragma once
#ifndef _Print_Visitor_H
#define _Print_Visitor_H

#include "Visitor.h"
#include "Typedefs.h"

/**
* @class Print_Visitor is a subclass of Visitor
* @brief Defines a Print_Visitor - prints the contents of the visited entity.
*/

class Print_Visitor : public Visitor
{
public:

	/// Visit method for LEAF_NODE instances
	/// Pure virtual function.
	virtual void visit(const LEAF_NODE& node);

	/// Visit method for COMPOSITE_NEGATE_NODE instances
	/// Pure virtual function.
	virtual void visit(const COMPOSITE_NEGATE_NODE& node);

	/// Visit method for COMPOSITE_ADD_NODE instances
	/// Pure virtual function.
	virtual void visit(const COMPOSITE_ADD_NODE& node);

	/// Visit method for COMPOSITE_SUBTRACT_NODE instances
	/// Pure virtual function.
	virtual void visit(const COMPOSITE_SUBTRACT_NODE& node);

	/// Visit method for COMPOSITE_MULTIPLY_NODE instances
	/// Pure virtual function.
	virtual void visit(const COMPOSITE_MULTIPLY_NODE& node);

	/// Visit method for COMPOSITE_DIVIDE_NODE instances
	/// Pure virtual function.
	virtual void visit(const COMPOSITE_DIVIDE_NODE& node);
};

//#include "Print_Visitor.cpp"

#endif /* _Print_Visitor_H */