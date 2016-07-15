#pragma once
#ifndef _LQUEUE_H
#define _LQUEUE_H
#include "Queue.h"
//Defines an element in the <LQueue>.
template <typename T>
class LQueue_Node
{
public:
	// = Initialization methods
	LQueue_Node(LQueue_Node<T> *next,LQueue_Node<T> *prev);

	// Default constructor that doesn't initialize <item_>.
	LQueue_Node(void);

	~LQueue_Node(void);

	void *operator new (size_t);
	// Allocate a new <LQueue_Node>, trying first from the
	// <free_list_> and if that's empty try from the global <::operator new>.

	void operator delete (void *ptr);
	// Return <ptr> to the <free_list_>.

	static void free_list_allocate(size_t n);
	// Preallocate <n> <LQueue_Nodes> and store them on the
	// <free_list_>.

	static void free_list_release(void);
	// Returns all dynamic memory on the free list to the free store.

	static LQueue_Node<T> *free_list_;
	// Head of the "free list", which is a stack of
	// <LQueue_Nodes> used to speed up allocation.

	T item_;
	// Item in this node.

	LQueue_Node<T> *next_;
	// Pointer to the next node.

	LQueue_Node<T> *prev_;
	// Pointer to the prev node.
};

// Solve circular include problem via forward decls.
template <typename T, typename LQUEUE_NODE>
class LQueue_Iterator;

template <typename T, typename LQUEUE_NODE>
class Const_LQueue_Iterator;

/**
* @class LQueue
* @brief Defines a generic "first-in/first-out" (FIFO) Abstract Data
* Type (ADT) using a "circular list" with a dummy node.
*
* This queue is a circular linked list.  The <tail_> pointer points
* to a dummy node which makes implementation much easier
* (particularly iterator traversal).  When enqueuing an item, the
* dummy node contains the new item and points to a new dummy node.
* Therefore the head of the list is always <tail_ -> next_>.
* Dequeuing an object gets rid of the head node and makes the dummy
* node point to the new head.
*/
template <typename T, typename LQUEUE_NODE = LQueue_Node<T> >
class LQueue
{
	friend class LQueue_Iterator<T, LQUEUE_NODE>;
	friend class Const_LQueue_Iterator<T, LQUEUE_NODE>;
	/*friend class LQueue_Reverse_Iterator<T, LQUEUE_NODE>;
	friend class Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>;*/

public:
	// = Exceptions thrown by methods in this class.
	class Underflow {};
	class Overflow {};

	// = Initialization, assignment, and termination methods.

	// Constructor.
	LQueue(size_t size_hint = 0);

	// Copy constructor.
	LQueue(const LQueue<T, LQUEUE_NODE> &rhs);

	// Assignment operator.
	LQueue<T, LQUEUE_NODE> &operator = (const LQueue<T, LQUEUE_NODE> &rhs);

	// Perform actions needed when queue goes out of scope. 
	~LQueue(void);

	// = Classic Queue operations.

	// Place a <new_item> at the tail of the queue.  Throws the
	// <Overflow> exception if the queue is full, e.g., if memory is exhausted.
	void enqueue(const T &new_item);

	// Remove the front item on the queue.  Throws the <Underflow>
	// exception if the queue is empty.
	void dequeue(void);

	// Returns the front queue item without removing it. 
	// Throws the <Underflow> exception if the queue is empty. 
	T front(void) const;

	// = Check boundary conditions for Queue operations. 

	// Returns 1 if the queue is empty, otherwise returns 0. 
	bool is_empty(void) const {
		return count_ == 0;
	}

	// Returns 1 if the queue is full, otherwise returns 0. 
	bool is_full(void) const {
		return false;
	}

	// Returns the current number of elements in the queue.
	size_t size(void) const {
		return count_;
	}

	// Compare this queue with <rhs> for equality.  Returns true if the
	// size's of the two queues are equal and all the elements from 0
	// .. size are equal, else false.
	bool operator== (const LQueue<T, LQUEUE_NODE> &rhs) const;

	// Compare this queue with <rhs> for inequality such that <*this> !=
	// <s> is always the complement of the boolean return value of
	// <*this> == <s>.
	bool operator!= (const LQueue<T, LQUEUE_NODE> &s) const;

	// Efficiently swap the contents of this <LQueue> with <new_aqueue>.
	// Does not throw an exception.
	void swap(LQueue<T, LQUEUE_NODE> &new_queue);

	// = Traits for the class.

	typedef T value_type;
	typedef LQueue_Iterator<T, LQUEUE_NODE> iterator;
	typedef Const_LQueue_Iterator<T, LQUEUE_NODE> const_iterator;
	//typedef LQueue_Reverse_Iterator<T, LQUEUE_NODE> reverse_iterator;
	//typedef Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> const_reverse_iterator;

	// = Factory methods that create iterators.

	// Get an iterator that points to the beginning of the queue.
	iterator begin(void);

	// Get a const iterator that points to the beginning of the queue.
	const_iterator cbegin(void) const;

	// Get an iterator that points to the end of the queue.
	iterator end(void);

	// Get a const iterator that points to the end of the queue.
	const_iterator cend(void) const;

	// Get an iterator that points to the end of the queue.
	//reverse_iterator rbegin(void);

	// Get a const iterator that points to the end of the queue.
	//const_reverse_iterator rbegin(void) const;

	// Get an iterator that points one before the beginning of the queue.
	//reverse_iterator rend(void);

	// Get a const iterator that points one before the beginning of the queue.
	//const_reverse_iterator rend(void) const;*/

protected:
	// Remove the front item on the queue without checking if the queue is empty.
	//void dequeue_i(void);

private:
	LQUEUE_NODE *tail_;
	// We only need to keep a single pointer for the circular linked
	// list.  This points to the tail of the queue.  Since the list is
	// circular, the head of the queue is always this->tail_->next_;

	size_t count_;
	// Number of items that are currently in the queue.
};
/**
* @class LQueue_Iterator
* @brief Implements a bidirectional iterator for LQueue type classes.
*/
template <typename T, typename LQUEUE_NODE>
class LQueue_Iterator
{
public:
	friend class LQueue<T, LQUEUE_NODE>;

	/// Dereference operator returns a reference to the item contained
	/// at the current position
	T& operator* (void) {
		return pos_->item_;
	}

	/// Returns a const reference to the item contained at the current position
	const T& operator* (void) const {
		return pos_->item_;
	}

	/// Preincrement operator
	LQueue_Iterator<T, LQUEUE_NODE> &operator++ (void) {
		pos_ = post_->next_;
		return *this;
	}

	/// Postincrement operator
	LQueue_Iterator<T, LQUEUE_NODE> operator++ (int) {
		LQueue_Iterator<T, LQUEUE_NODE> temp = *this;
		pos_->pos_->next_;
		return temp;
	}

	/// Predecrement operator
	LQueue_Iterator<T, LQUEUE_NODE> &operator-- (void) {
		pos_ = pos_->prev_;
		return *this;
	}

	/// Posdecrement operator
	LQueue_Iterator<T, LQUEUE_NODE> operator-- (int) {
		LQueue_Iterator<T, LQUEUE_NODE> temp = *this;
		--*this;
		return temp;
	}

	/// Equality operator
	bool operator== (const LQueue_Iterator<T, LQUEUE_NODE> &rhs) const {
		return pos_ == rhs.pos_;
	}

	/// Nonequality operator
	bool operator!= (const LQueue_Iterator<T, LQUEUE_NODE> &lhs) const {
		return !(*this == rhs);
	}

	// = Necessary traits
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef T *pointer;
	typedef T &reference;
	typedef int difference_type;

protected:
	/// Construct an LQueue_Iterator at node pos.  
	LQueue_Iterator(LQUEUE_NODE *pos) :pos_{ pos } {}

private:
	// the position in the linked list
	mutable LQUEUE_NODE *pos_;
};
/**
* @class Const_LQueue_Iterator
* @brief Implements a bidirectional iterator for LQueue type classes.
*
* Note:  Having a const Iterator does not guarantee that the current
* *position* that it points to will not change, it only guarantees that
* you cannot change the underlying queue!
*/
template<typename T, typename LQUEUE_NODE = LQueue_Node<T>>
class Const_LQueue_Iterator {
public:
	Const_LQueue_Iterator(LQUEUE_NODE * t) {
		current_ = t;
	}
	//pre increment
	const Const_LQueue_Iterator<T,LQUEUE_NODE>& operator++() {
		current_ = current_->next_;
		return *this;
	}
	//post increment
	const Const_LQueue_Iterator<T, LQUEUE_NODE>& operator++(int) {
		Const_LQueue_Iterator<T, LQUEUE_NODE> temp = *this;
		current_ = current_->next_;
		return temp;
	}
	//pre decrement
	const Const_LQueue_Iterator<T, LQUEUE_NODE>& operator--() {
		current_ = current_->prev_;
		return *this;
	}

	//post decrement
	const Const_LQueue_Iterator<T, LQUEUE_NODE>& operator--(int) {
		Const_LQueue_Iterator<T, LQUEUE_NODE> temp = *this;
		current_ = current_->prev_;
		return temp;
	}

	// Equality operator
	bool operator== (const Const_LQueue_Iterator<T, LQUEUE_NODE> &rhs) const {
		return this->current_ == rhs.current_;
	}

	// Nonequality operator
	bool operator!= (const Const_LQueue_Iterator<T, LQUEUE_NODE> &rhs) const {
		return this->current_ != rhs.current_;
	}

	const T& operator* (void) const{
		return current_->item_;
	}
	// = Necessary traits
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef T *pointer;
	typedef T &reference;
	typedef int difference_type;
private:
	LQUEUE_NODE* current_;
};


#include "LQueue.cpp"
#endif /* _LQUEUE_H */