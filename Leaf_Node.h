#pragma once
#ifndef _Leaf_Node_H
#define _Leaf_Node_H


#include "Component_Node.h"
#include <iostream>
/**
* @class Leaf_Node
* @brief Defines the leaf node of Composite Hierarchy.
*/
template <typename T>
class Leaf_Node : public Component_Node<T>
{
public:
	/// Ctor
	Leaf_Node(const T &item)
		:item_{item}
	{
		//std::cout << "Dtor for:" << item_ << std::endl;
	}

	/// Dtor
	virtual ~Leaf_Node()
	{}

	/// Accept method for visitor
	virtual void accept(Visitor& v) {
		v.visit(*this);
	}

	/// Return the item stored in the node.
	virtual const T &item(void) const {
		return item_;
	}

protected:

	/// Item stored in the node.
	T item_;
};

#endif /* _Leaf_Node_H */