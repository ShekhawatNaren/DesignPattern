#pragma once
#ifndef _Tree_Iterator_H
#define _Tree_Iterator_H

#include "Tree.h"
#include "Tree_Iterator_Impl.h"
#include "Refcounter.h"

/**
* @class Tree_Iterator
* @brief Defines a bridge to the Tree_Iterator_Impl that
*        contains the implementation of the iterator.
*
*/
template <typename T>
class Tree_Iterator
{
public:
	/// Construct a Tree_Iterator 
	Tree_Iterator(Tree_Iterator_Impl<T>* impl)
		:tree_iterator_impl_{ impl }
	{}

	/// Copy ctor - needed for reference counting.
	Tree_Iterator(const Tree_Iterator<T> &tree_iterator)
		:tree_iterator_impl_{tree_iterator.tree_iterator_impl_}
	{}

	/// Assignment operator - needed for reference counting.
	void operator= (const Tree_Iterator<T> &tree_iterator) {
		if (this != &tree_iterator) {
			tree_iterator_impl_ = tree_iterator.tree_iterator_impl_;
		}
	}

	/// Dereference operator returns a reference to the item contained
	/// at the current position
	Tree<T>& operator* (void) {
		return (*(*tree_iterator_impl_));
	}

	/// Returns a const reference to the item contained at the current position
	const Tree<T>& operator* (void) const {
		return (*(*tree_iterator_impl_));
	}

	/// Preincrement operator
	Tree_Iterator<T> &operator++ (void) {
		++(*tree_iterator_impl_);
		return *this;
	}

	/// Postincrement operator
	Tree_Iterator<T> operator++ (int) {
		Tree_Iterator<T> temp(tree_iterator_impl_->clone());
		++(*tree_iterator_impl_);
		return temp;
	}

	/// Equality operator
	bool operator== (const Tree_Iterator<T> &rhs) const {
		return ((this == &rhs) || ((*tree_iterator_impl_) == *(rhs.tree_iterator_impl_)));
	}

	/// Nonequality operator
	bool operator!= (const Tree_Iterator<T> &lhs) const {
		return !((*this) == lhs);
	}

	// = Necessary traits
	typedef std::forward_iterator_tag iterator_category;
	typedef Tree<T> value_type;
	typedef Tree<T> *pointer;
	typedef Tree<T> &reference;
	typedef int difference_type;

private:
	/// reference counted Pointer to the tree_iterator_impln.
	Refcounter <Tree_Iterator_Impl<T> > tree_iterator_impl_;
};
/*
/**
* @class Const_Tree_Iterator
* @brief Defines a bridge to the Const_Tree_Iterator_Impl that
*        actually contains the implementation of the const_iterator.
*
*/
template <typename T>
class Const_Tree_Iterator
{
public:
	/// Construct a Const_Tree_Iterator
	Const_Tree_Iterator(Tree_Iterator_Impl<T>* impl)
		:tree_iterator_impl_{impl}
	{}

	/// Copy ctor - needed for reference counting.
	Const_Tree_Iterator(const Const_Tree_Iterator<T> &tree_iterator)
		:tree_iterator_impl_{tree_iterator.tree_iterator_impl_}
	{}

	/// Assignment operator - needed for reference counting.
	void operator= (const Const_Tree_Iterator<T> &tree_iterator) {
		if (this != &tree_iterator) {
			tree_iterator_impl_ = tree_iterator.tree_iterator_impl_;
		}
	}


	/// Returns a const reference to the item contained at the current position
	const Tree<T>& operator* (void) const {
		return (*(*tree_iterator_impl_));
	}

	/// Preincrement operator
	Const_Tree_Iterator<T> &operator++ (void) {
		++(*tree_iterator_impl_);
		return (*this);
	}

	/// Postincrement operator
	Const_Tree_Iterator<T> operator++ (int) {
		Const_Tree_Iterator<T> temp(tree_iterator_impl_->clone());
		++*tree_iterator_impl_;
		return temp;
	}


	/// Equality operator
	bool operator== (const Const_Tree_Iterator<T> &rhs) const {
		return ((this == &rhs) || ((*tree_iterator_impl_) == *(rhs.tree_iterator_impl_)));
	}

	/// Nonequality operator
	bool operator!= (const Const_Tree_Iterator<T> &lhs) const {
		return !(*this == lhs);
	}

	// = Necessary traits
	typedef std::forward_iterator_tag iterator_category;
	typedef Tree<T> value_type;
	typedef Tree<T> *pointer;
	typedef Tree<T> &reference;
	typedef int difference_type;

private:
	/// reference counted Pointer to the tree_iterator_impln.
	Refcounter <Tree_Iterator_Impl<T> > tree_iterator_impl_;

};
#endif /* _Tree_Iterator_H */