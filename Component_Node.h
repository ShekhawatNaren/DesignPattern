#pragma once

#ifndef _Component_Node_H
#define _Component_Node_H
#include <stdlib.h>
#include <stdexcept>

#include "Typedefs.h"
#include "Visitor.h"

template <typename T>
class Refcounter;

/**
* @class Component_Node
* @brief Defines the abstract base class of Composite Hierarchy.
*/
template <typename T>
class Component_Node
{
	/// Needed for reference counting.
	//Naren:TODO
	//friend class Tree<T>;
	friend class Refcounter<Component_Node<T> >;

public:

	/// NoImplementation class for exceptions when there is no implementation
	class NoImplementation
	{
	public:
		NoImplementation(const std::string &msg)
		{
			msg_ = msg;
		}

		const std::string what(void)
		{
			return msg_;
		}
	private:
		std::string msg_;
	};

	/// Ctor
	Component_Node()
		:use_{1}
	{}

	/// Dtor
	virtual ~Component_Node() {
	}

	/// Accept method for visitor
	virtual void accept(Visitor& v) {
		//throw an exception if this method is called where it should not be
		std::string errormsg = "No implementation for Component_Node<T>::accept  ";
		throw typename Component_Node<T>::NoImplementation(errormsg);
	}

	/// Return the item stored in the node.
	virtual const T& item(void) const {
		//throw an exception if this method is called where it should not be
		std::string errormsg = "No implementation for Component_Node<T>::item  ";
		throw typename Component_Node<T>::NoImplementation(errormsg);
	}

	/// Return the left child.
	virtual Component_Node* left(void) const {
		return nullptr;
	}

	/// Return the right child.
	virtual Component_Node* right(void) const {
		return nullptr;
	}

private:

	/// Reference counter
	int use_;
};

#endif /* _Component_Node_H */