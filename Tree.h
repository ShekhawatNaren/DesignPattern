#pragma once
#ifndef _Tree_H
#define _Tree_H
#include <string>

#include "Component_Node.h"
#include "Refcounter.h"
#include "Typedefs.h"


//Forward Declaration
template <typename T>
class Tree_Iterator;

template <typename T>
class Const_Tree_Iterator;

class Visitor;

/**
* @class Tree
* @brief Defines a bridge to the node implementation that
*        actually contains the data items for the tree.
*/


template <typename T>
class Tree
{
	friend class Tree_Iterator<T>;
	friend class Const_Tree_Iterator<T>;
public:
	/// Default ctor
	Tree()
	{}

	/// Ctor that takes a Node<T> *.
	Tree(Component_Node<T> *root, bool count = false)
		:root_{ root,count }
	{}

	// Copy ctor
	Tree(const Tree &t)
		:root_{ t.root_ }
	{}

	/// Assignment operator
	void operator= (const Tree &t) {
		root_ = t.root_;
	}

	//Equality operator
	bool operator == (const Tree& rhs)const {
		//Check if the pointer stored in both the refcounter objects are same
		return (this == &rhs) || root_.operator->() == rhs.root_.operator->();
	}

	//Inequality operator
	bool operator != (const Tree& rhs)const {
		return !(*this == rhs);
	}

	//Dtor
	//Nothing to do much here refcounter takes care of deleting the root node
	//And all the nodes under root are auto poninter so they get cleaned up fine.
	~Tree(void)
	{}

	/// Check if tree is null tree.
	bool is_null(void) const {
		return root_.is_null();
	}

	/// Return the item in the tree.
	const T &item(void) const {
		return root_->item();
	}

	Component_Node<T>* get_root() const {
		return root_.operator->();
	}

	/// Return the left child.
	Tree<T> left(void) const {
		// wrap the Node* in a tree object and increase reference count by one.
		return Tree<T>(root_->left(), true);
	}

	/// Return the right child.
	Tree<T> right(void) const {
		return Tree<T>(root_->right(), true);
	}

	// = Traits for the class.
	typedef T value_type;
	typedef Tree_Iterator<T> iterator;
	typedef Const_Tree_Iterator<T> const_iterator;

	// = Factory methods that create iterators.

	// Get an iterator that points to the beginning of the Tree 
	// based on the traversal order
	Tree_Iterator<T> begin(const std::string &traversal_order){
		if (traversal_order.compare("Levelorder") == 0) {
			return Tree_Iterator<T>(new Level_Order_Tree_Iterator_Impl<T>(*this));
		}
		else if (traversal_order.compare("Preorder") == 0) {
			return Tree_Iterator<T>(new Pre_Order_Tree_Iterator_Impl<T>(*this));
		}
		else if (traversal_order.compare("Postorder") == 0) {
			return Tree_Iterator<T>(new Post_Order_Tree_Iterator_Impl<T>(*this));
		}
		else if (traversal_order.compare("Inorder") == 0) {
			return Tree_Iterator<T>(new In_Order_Tree_Iterator_Impl<T>(*this));
		}
		else {
			//throw an exception if the traversal strategy name is unknown
			std::string errormsg = "Unknown/None Implemented Traversal Order - " + traversal_order;
			throw typename Tree_Iterator_Impl<T>::Unknown_Order(errormsg);
		}
	}

	// Get an iterator that points to the end of the Tree 
	// based on the traversal order
	Tree_Iterator<T> end(const std::string &traversal_order) {
		if (traversal_order.compare("Levelorder") == 0) {
			return Tree_Iterator<T>(new Level_Order_Tree_Iterator_Impl<T>());
		}
		else if (traversal_order.compare("Preorder") == 0) {
			return Tree_Iterator<T>(new Pre_Order_Tree_Iterator_Impl<T>());
		}
		else if (traversal_order.compare("Postorder") == 0) {
			return Tree_Iterator<T>(new Post_Order_Tree_Iterator_Impl<T>());
		}
		else if (traversal_order.compare("Inorder") == 0) {
			return Tree_Iterator<T>(new In_Order_Tree_Iterator_Impl<T>());
		}
		else {
			//throw an exception if the traversal strategy name is unknown
			std::string errormsg = "Unknown/None Implemented Traversal Order - " + traversal_order;
			throw typename Tree_Iterator_Impl<T>::Unknown_Order(errormsg);
		}
	}

	// Get a const iterator that points to the beginning of the Tree 
	// based on the traversal order
	Const_Tree_Iterator<T> begin(const std::string &traversal_order) const {
		if (traversal_order.compare("Levelorder") == 0) {
			return Const_Tree_Iterator<T>(new Level_Order_Tree_Iterator_Impl<T>(*this));
		}
		else if (traversal_order.compare("Preorder") == 0) {
			return Const_Tree_Iterator<T>(new Pre_Order_Tree_Iterator_Impl<T>(*this));
		}
		else if (traversal_order.compare("Postorder") == 0) {
			return Const_Tree_Iterator<T>(new Post_Order_Tree_Iterator_Impl<T>(*this));
		}
		else if (traversal_order.compare("Inorder") == 0) {
			return Const_Tree_Iterator<T>(new In_Order_Tree_Iterator_Impl<T>(*this));
		}
		else {
			//throw an exception if the traversal strategy name is unknown
			std::string errormsg = "Unknown/None Implemented Traversal Order - " + traversal_order;
			throw typename Tree_Iterator_Impl<T>::Unknown_Order(errormsg);
		}
	}

	// Get a const iterator that points to the end of the Tree 
	// based on the traversal order
	Const_Tree_Iterator<T> end(const std::string &traversal_order) const {
		if (traversal_order.compare("Levelorder") == 0) {
			return Const_Tree_Iterator<T>(new Level_Order_Tree_Iterator_Impl<T>());
		}
		else if (traversal_order.compare("Preorder") == 0) {
			return Const_Tree_Iterator<T>(new Pre_Order_Tree_Iterator_Impl<T>());
		}
		else if (traversal_order.compare("Postorder") == 0) {
			return Const_Tree_Iterator<T>(new Post_Order_Tree_Iterator_Impl<T>());
		}
		else if (traversal_order.compare("Inorder") == 0) {
			return Const_Tree_Iterator<T>(new In_Order_Tree_Iterator_Impl<T>());
		}
		else {
			//throw an exception if the traversal strategy name is unknown
			std::string errormsg = "Unknown/None Implemented Traversal Order - " + traversal_order;
			throw typename Tree_Iterator_Impl<T>::Unknown_Order(errormsg);
		}
	}

	//Accept method for the Visitor 
	void accept(Visitor&v) {
		root_->accept(v);
	}
	
private:
	/// The underlying pointer to the implementation. These are
	/// reference counted.
	Refcounter <Component_Node<T> > root_;
};

#include "Tree_Iterator.h"

#endif /* _Tree_H */