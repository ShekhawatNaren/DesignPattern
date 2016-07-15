#pragma once
#ifndef _Composite_Unary_Node_H
#define _Composite_Unary_Node_H

#include <memory>
#include "Component_Node.h"

/**
* @class Composite_Unary_Node
* @brief Defines a Unary node Composite Abstract class in Composite Hierarchy.
*/
template <typename T>
class Composite_Unary_Node : public Component_Node<T>
{
public:
	/// Ctor
	Composite_Unary_Node(Component_Node<T> *right = 0)
		:right_{right}
	{}

	/// Dtor
	virtual ~Composite_Unary_Node() 
	{}

	/// Return the right child.
	virtual Component_Node<T>  *right(void) const {
		return right_.get();
	}

protected:

	/// Right child.
	std::auto_ptr< Component_Node<T> > right_;
};

#endif /*_Composite_Unary_Node_H*/