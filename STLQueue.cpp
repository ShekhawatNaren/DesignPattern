#include "stdafx.h"
#if !defined (_STLQUEUE_CPP)
#define _STLQUEUE_CPP

#include "STLQueue.h"

template <typename T, typename QUEUE>
STLQueue_Adapter<T, QUEUE>::STLQueue_Adapter(size_t)
	:Q_{}
{
}

template <typename T, typename QUEUE>
STLQueue_Adapter<T, QUEUE>::STLQueue_Adapter(const STLQueue_Adapter<T, QUEUE> &rhs)
	:Q_{rhs.Q_}
{
}

template <typename T, typename QUEUE> STLQueue_Adapter<T, QUEUE> &
STLQueue_Adapter<T, QUEUE>::operator= (const STLQueue_Adapter &rhs)
{
	if (this != &rhs) {
		this->Q_ = rhs.Q_;
	}
	return *this;
}

// Place a <new_item> at the tail of the queue.  Throws the
// <Overflow> exception if the queue is full, e.g., if memory is
// exhausted.
template <typename T, typename QUEUE>
void STLQueue_Adapter<T, QUEUE>::enqueue(const T &new_item)
{
	try {
		Q_.push(new_item);
	}
	catch (...) {
		throw Overflow();
	}
}

// Remove the front item on the queue.  Throws the <Underflow>
// exception if the queue is empty.
template <typename T, typename QUEUE>
void STLQueue_Adapter<T, QUEUE>::dequeue(void)
{
	if (!Q_.empty()) {
		return Q_.pop();
	}
	else {
		throw Underflow();
	}
}

// Returns the front queue item without removing it. 
// Throws the <Underflow> exception if the queue is empty. 
template <typename T, typename QUEUE>
T STLQueue_Adapter<T, QUEUE>::front(void) const
{
	if(!Q_.empty()){
		return Q_.front();
	}
	else {
		throw Underflow();
	}
}

// = Check boundary conditions for Queue operations. 

// Returns 1 if the queue is empty, otherwise returns 0. 
template <typename T, typename QUEUE>
bool
STLQueue_Adapter<T, QUEUE>::is_empty(void) const
{
	return Q_.empty();
}

// Returns 1 if the queue is full, otherwise returns 0. 
template <typename T, typename QUEUE>
bool
STLQueue_Adapter<T, QUEUE>::is_full(void) const
{
	return false;
}

// Returns the current number of elements in the queue.
template <typename T, typename QUEUE>
size_t STLQueue_Adapter<T, QUEUE>::size(void) const
{
	return Q_.size();
}

#endif /* _STLQUEUE_CPP */