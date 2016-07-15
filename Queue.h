#pragma once
#if !defined (_Queue_H)
#define _Queue_H

// This header defines "size_t"
#include <stdlib.h>

#include <stdexcept>

/**
* @class Queue
* @brief Defines a Queue interface for subclasses that have generic
* "first-in/first-out" (FIFO) semantics.
*/
template <class T>
class Queue
{
public:
	/// Trait to use when freeing up memory from LQueue.
	typedef T value_type;

	/// Dtor - make this virtual since we subclass from this interface.
	virtual ~Queue(void) = 0;

	class Underflow {};
	class Overflow {};

	/// Classic Queue operations.

	// Place a <new_item> at the tail of the queue.  Throws
	// the <Overflow> exception if the queue is full, e.g., if memory is
	// exhausted.  
	virtual void enqueue(const T &new_item) = 0;

	// Remove the front item on the queue.  Throws the <Underflow>
	// exception if the queue is empty.
	virtual void dequeue(void) = 0;

	// Returns the front queue item without removing it. 
	// Throws the <Underflow> exception if the queue is empty. 
	virtual T front(void) const = 0;

	// = Check boundary conditions for Queue operations. 

	// Returns 1 if the queue is empty, otherwise returns 0. 
	virtual bool is_empty(void) const = 0;

	// Returns 1 if the queue is full, otherwise returns 0. 
	virtual bool is_full(void) const = 0;

	// Returns the current number of elements in the queue.
	virtual size_t size(void) const = 0;

	// Clone the Queue.
	virtual Queue<T> *clone(void) = 0;

};

/**
* @class Queue_Adapter
* @brief Defines a parameterized Queue subclass that have generic
* "first-in/first-out" (FIFO) semantics. This uses the adapter
* pattern. This class delegates the method calls to its
* parameterized type.
*/

template <typename T, typename QUEUE>
class Queue_Adapter : public Queue<T>
{
public:
	/// Default constructor
	Queue_Adapter(size_t size);

	/// Copy ctor
	Queue_Adapter(const Queue_Adapter<T, QUEUE> &rhs);

	/// Dtor
	virtual ~Queue_Adapter(void);

	/// Assignment operator
	Queue_Adapter<T, QUEUE> &operator= (const Queue_Adapter<T, QUEUE> &rhs);

	/// Equality/Inequality operators
	bool operator== (const Queue_Adapter<T, QUEUE> &rhs) const;
	bool operator!= (const Queue_Adapter<T, QUEUE> &rhs) const;

	/// Classic Queue operations.

	/// Place a <new_item> at the tail of the queue.  Throws
	/// the <Overflow> exception if the queue is full, e.g., if memory is
	/// exhausted.  
	virtual void enqueue(const T &new_item);

	/// Remove the front item on the queue.  Throws the <Underflow>
	/// exception if the queue is empty.
	virtual void dequeue(void);

	/// Returns the front queue item without removing it. 
	/// Throws the <Underflow> exception if the queue is empty. 
	virtual T front(void) const;

	/// Returns 1 if the queue is empty, otherwise returns 0. 
	virtual bool is_empty(void) const;

	/// Returns 1 if the queue is full, otherwise returns 0. 
	virtual bool is_full(void) const;

	/// Returns the current number of elements in the queue.
	virtual size_t size(void) const;

	/// Clone the Queue.
	virtual Queue_Adapter<T, QUEUE> *clone(void);

private:
	/// The queue implementation that does all the real work.
	QUEUE Q_;
};

#include "Queue.cpp"

#endif /* _Queue_H */