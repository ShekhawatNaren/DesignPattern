#pragma once
#ifndef _Tree_Iterator_Impl_H
#define _Tree_Iterator_Impl_H

#include "Tree.h"
#include "Queue.h"
#include "LQueue.h"
#include "STLQueue.h"
#include "Typedefs.h"
#include "Refcounter.h"
#include "Options.h"
#include <stack>

/**
* @class Tree_Iterator_Impl
* @brief Abstract base class of the actual implementation of
*		  Tree_Iterator.
*
*/
template <typename T>
class Tree_Iterator_Impl
{
	friend class Tree_Iterator<T>;
	friend class Refcounter <Tree_Iterator_Impl<T> >; // allows refcounting
public:

	/// Unknown_Order class for exceptions when an unknown order
	/// name is passed to the begin or end methods

	class Unknown_Order
	{
	public:
		Unknown_Order(const std::string &msg)
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

	/// Default ctor - needed for reference counting, for ::end
	Tree_Iterator_Impl()
		:use_{ 1 }
	{}


	//Should these constructor methods be defined in the base class
	//The class is abstract

	//Constructor that takes in an entry
	Tree_Iterator_Impl(Tree<T> &tree)
		:use_{1}
	{}

	//Tree_Iterator_Impl(const Tree_Iterator_Impl<T>& rhs);

	virtual ~Tree_Iterator_Impl(void)
	{}

	/// Dereference operator returns a reference to the item contained
	/// at the current position
	virtual Tree<T>& operator* (void) = 0;

	/// Returns a const reference to the item contained at the current position
	virtual const Tree<T>& operator* (void) const = 0;

	/// Preincrement operator
	virtual Tree_Iterator_Impl<T> &operator++ (void) = 0;

	/// Equality operator
	virtual bool operator== (const Tree_Iterator_Impl<T> &rhs) const = 0;

	/// Nonequality operator
	virtual bool operator!= (const Tree_Iterator_Impl<T> &lhs) const = 0;

	virtual Tree_Iterator_Impl<T>* clone(void) = 0;

	// = Necessary traits
	typedef std::forward_iterator_tag iterator_category;
	typedef Tree<T> value_type;
	typedef Tree<T> *pointer;
	typedef Tree<T> &reference;
	typedef int difference_type;


private:
	/// Reference counter
	int use_;

};

/**
* @class Level_Order_Tree_Iterator_Impl
* @brief Implementation of the Tree_Iterator based on Level_Order traversal.
*/

template <typename T>
class Level_Order_Tree_Iterator_Impl :public Tree_Iterator_Impl<T>
{
public:

	/// Default ctor - needed for reference counting, for end
	Level_Order_Tree_Iterator_Impl()
		:queue_(make_queue_strategy()), front_(nullptr, false)
	{}

	/// Constructor that takes in an entry
	Level_Order_Tree_Iterator_Impl(Tree<T> &tree)
		:queue_(make_queue_strategy()),front_()
	{
		queue_->enqueue(tree);
		front_ = queue_->front();
	}

	//copy
	Level_Order_Tree_Iterator_Impl(const Level_Order_Tree_Iterator_Impl<T>& rhs)
		:queue_(rhs.queue_->clone()),front_(rhs.front_)
	{}

	virtual ~Level_Order_Tree_Iterator_Impl(void)
	{
		//The queue is held in an auto_ptr which will call the destructor
		//when moving out of scope
	}

	/// Dereference operator returns a reference to the item contained
	/// at the current position
	virtual Tree<T>& operator* (void) {
		return front_;
	}

	/// Returns a const reference to the item contained at the current position
	virtual const Tree<T>& operator* (void) const {
		return front_;
	}

	/// Preincrement operator
	virtual Level_Order_Tree_Iterator_Impl<T>& operator++ (void) {
		if (!queue_->is_empty()) {
			queue_->dequeue();
			
			if (!front_.left().is_null())
				queue_->enqueue(front_.left());

			if (!front_.right().is_null())
				queue_->enqueue(front_.right());

			if (!queue_->is_empty())
				front_ = queue_->front();
			else
				front_ = Tree<T>(nullptr, false);
		}
		return *this;
	}

	/// Equality operator
	virtual bool operator== (const Tree_Iterator_Impl<T> &rhs) const {
		return (front_ == *rhs);
	}

	/// Nonequality operator
	virtual bool operator!= (const Tree_Iterator_Impl<T> &rhs) const {
		return !(*this == rhs);
	}

	virtual Level_Order_Tree_Iterator_Impl<T>* clone(void) {
		return new Level_Order_Tree_Iterator_Impl<T>(*this);
	}

private:
	std::auto_ptr<QUEUE> queue_;
	Tree<T> front_;
	static const size_t AQUEUE_SIZE = 50;
	QUEUE * make_queue_strategy()
	{
		//Using the option class leads to a linker error which I am unable to fix so hard coding it
		std::string queue_type = "STLQueue";// Options::instance()->queue_type();
		if (queue_type.compare("LQueue") == 0) {
			return new LQUEUE_ADAPTER(Level_Order_Tree_Iterator_Impl::AQUEUE_SIZE);
		}
		else if (queue_type.compare("AQueue") == 0) { //Don't have AQueue implemented
			return new LQUEUE_ADAPTER(Level_Order_Tree_Iterator_Impl::AQUEUE_SIZE);
		}
		else if (queue_type.compare("STLQueue") == 0) {
			return new STLQueue_Adapter<TREE>(Level_Order_Tree_Iterator_Impl::AQUEUE_SIZE);
		}
		else {
			throw typename Unknown_Order(queue_type + " is unknown queue strategy");
		}
	}
};

/**
* @class Pre_Order_Tree_Iterator_Impl
* @brief Implementation of the Tree_Iterator based on
*		  Pre_Order traversal.
*
*/

template <typename T>
class Pre_Order_Tree_Iterator_Impl :public Tree_Iterator_Impl<T>
{
public:

	/// Default ctor - needed for reference counting, for end
	Pre_Order_Tree_Iterator_Impl()
		:current_(nullptr,false),stack_()
	{}

	/// Constructor that takes in an entry
	Pre_Order_Tree_Iterator_Impl(Tree<T> &tree)
	{
		stack_.push(tree);
		current_ = stack_.top();
	}

	//copy
	Pre_Order_Tree_Iterator_Impl(const Pre_Order_Tree_Iterator_Impl<T>& rhs)
		:current_(rhs.current_)
	{
		stack_ = rhs.stack_;
	}

	virtual ~Pre_Order_Tree_Iterator_Impl(void) 
	{}

	/// Dereference operator returns a reference to the item contained
	/// at the current position
	virtual Tree<T>& operator* (void) {
		return current_;
	}

	/// Returns a const reference to the item contained at the current position
	virtual const Tree<T>& operator* (void) const {
		return current_;
	}

	/// Preincrement operator
	virtual Pre_Order_Tree_Iterator_Impl<T>& operator++ (void) {
		if (!stack_.empty()) {
			stack_.pop();//top_ already has this top object

			//Push the right tree first and then left tree
			//As we need to always traverse first left half and then right half
			if (!current_.right().is_null()) {
				stack_.push(current_.right());
			}
			if (!current_.left().is_null()) {
				stack_.push(current_.left());
			}
			if (!stack_.empty())
				current_ = stack_.top();
			else //very important to set this so that it matches the iterator end()
				current_ = Tree<T>(nullptr, false); 
		}
		return *this;
	}

	/// Equality operator
	virtual bool operator== (const Tree_Iterator_Impl<T> &rhs) const {
		return current_ == *rhs;
	}

	/// Nonequality operator
	virtual bool operator!= (const Tree_Iterator_Impl<T> &lhs) const{
		return !(*this == lhs);
	}

	virtual Pre_Order_Tree_Iterator_Impl<T>* clone(void) {
		return new Pre_Order_Tree_Iterator_Impl<T>(*this);
	}

private:
	Tree<T> current_;
	std::stack<Tree<T>> stack_;
};

/**
* @class Post_Order_Tree_Iterator_Impl
* @brief Implementation of the Tree_Iterator based on
*		  Post_Order traversal.
*
*/

template <typename T>
class Post_Order_Tree_Iterator_Impl :public Tree_Iterator_Impl<T>
{
public:

	/// Default ctor - needed for reference counting, for end
	Post_Order_Tree_Iterator_Impl()
		:current_(nullptr, false), stack_()
	{}

	/// Constructor that takes in an entry
	Post_Order_Tree_Iterator_Impl(const Tree<T> &tree)
	{
		traverseDown(tree);
		current_ = stack_.top();
	}

	//copy
	Post_Order_Tree_Iterator_Impl(const Post_Order_Tree_Iterator_Impl<T>& rhs)
		:current_(rhs.current_)
	{
		stack_ = rhs.stack_;
	}

	virtual ~Post_Order_Tree_Iterator_Impl(void)
	{}

	/// Dereference operator returns a reference to the item contained
	/// at the current position
	virtual Tree<T>& operator* (void) {
		return current_;
	}

	/// Returns a const reference to the item contained at the current position
	virtual const Tree<T>& operator* (void) const {
		return current_;
	}

	/// Preincrement operator
	virtual Post_Order_Tree_Iterator_Impl<T>& operator++ (void) {
		if (!stack_.empty()) {
			if (stack_.top() == current_) //If the node is already visited then pop it out
				stack_.pop();

			if (!stack_.empty()) {
				if (!stack_.top().right().is_null() && stack_.top().right() != current_) {
					traverseDown(stack_.top().right());
					current_ = stack_.top();
				}
				else {
					current_ = stack_.top();
					stack_.pop();
				}
			}
			else {
				current_ = Tree<T>(nullptr, false);
			}
		}
		else {
			current_ = Tree<T>(nullptr, false);
		}
		return *this;
	}

	/// Equality operator
	virtual bool operator== (const Tree_Iterator_Impl<T> &rhs) const {
		return current_ == *rhs;
	}

	/// Nonequality operator
	virtual bool operator!= (const Tree_Iterator_Impl<T> &lhs) const {
		return !(*this == lhs);
	}

	virtual Post_Order_Tree_Iterator_Impl<T>* clone(void) {
		return new Post_Order_Tree_Iterator_Impl<T>(*this);
	}

private:
	Tree<T> current_;
	std::stack<Tree<T>> stack_;
	void traverseDown(Tree<T> tempTree) {
		bool continueFlag = true;
		while (!tempTree.is_null() && continueFlag) {
			stack_.push(tempTree);

			if (!tempTree.left().is_null()) {
				tempTree = tempTree.left();
				continue;
			}
			if (!tempTree.right().is_null()) {
				tempTree = tempTree.right();
				continue;
			}
			continueFlag = false;
		}
	}
};

template <typename T>
class In_Order_Tree_Iterator_Impl :public Tree_Iterator_Impl<T>
{
public:

	/// Default ctor - needed for reference counting, for end
	In_Order_Tree_Iterator_Impl()
		:current_(nullptr, false), stack_()
	{}

	/// Constructor that takes in an entry
	In_Order_Tree_Iterator_Impl(const Tree<T> &tree)
	{
		traverseDown(tree);
		current_ = stack_.top();
		stack_.pop();
	}

	//copy
	In_Order_Tree_Iterator_Impl(const In_Order_Tree_Iterator_Impl<T>& rhs)
		:current_(rhs.current_)
	{
		stack_ = rhs.stack_;
	}

	virtual ~In_Order_Tree_Iterator_Impl(void)
	{}

	/// Dereference operator returns a reference to the item contained
	/// at the current position
	virtual Tree<T>& operator* (void) {
		return current_;
	}

	/// Returns a const reference to the item contained at the current position
	virtual const Tree<T>& operator* (void) const {
		return current_;
	}

	/// Preincrement operator
	virtual In_Order_Tree_Iterator_Impl<T>& operator++ (void) {
		//Check the right tree first for in order traversal
		if (!current_.right().is_null()) {
			traverseDown(current_.right());
		}

		//either the right traversal above has inserted a node in stack
		//or pick up the next node if available
		if (!stack_.empty()) {
			current_ = stack_.top();
			stack_.pop();
		}
		else {
			//We are here means stack is empty and no more nodes left
			current_ = Tree<T>(nullptr, false);
		}
		return *this;
	}

	/// Equality operator
	virtual bool operator== (const Tree_Iterator_Impl<T> &rhs) const {
		return current_ == *rhs;
	}

	/// Nonequality operator
	virtual bool operator!= (const Tree_Iterator_Impl<T> &lhs) const {
		return !(*this == lhs);
	}

	virtual In_Order_Tree_Iterator_Impl<T>* clone(void) {
		return new In_Order_Tree_Iterator_Impl<T>(*this);
	}

private:
	Tree<T> current_;
	std::stack<Tree<T>> stack_;
	void traverseDown(Tree<T> tempTree) {
		bool continueFlag = true;
		while (!tempTree.is_null() && continueFlag) {
			stack_.push(tempTree);

			if (!tempTree.left().is_null()) {
				tempTree = tempTree.left();
				continue;
			}
			continueFlag = false;
		}
	}
};
#endif /* __Tree_Iterator_Impl_H */