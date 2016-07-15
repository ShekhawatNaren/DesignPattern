#include "stdafx.h"
#if !defined (_LQUEUE_CPP)
#define _LQUEUE_CPP


#include <functional>
#include <algorithm>
#include "LQueue.h"
#include <iterator>
/* static needs t*/
template <typename T> LQueue_Node<T> *
LQueue_Node<T>::free_list_ = nullptr;

// Allocate a new <LQueue_Node>, trying first from the
// <free_list_> and if that's empty try from the global <::operator new>.
template <typename T> void *
LQueue_Node<T>::operator new (size_t)
{
	if (free_list_ != nullptr) {
		LQueue_Node<T>* temp = free_list_;
		free_list_ = free_list_->next_;
		return temp;
	}else{
		return ::new LQueue_Node<T>();
	}
}

// Return <ptr> to the <free_list_>.
template <typename T> void
LQueue_Node<T>::operator delete (void *ptr)
{
	if (ptr != nullptr) {
		LQueue_Node<T>* tempNode = static_cast<LQueue_Node<T>*>(ptr);
		tempNode->next_ = free_list_;
		free_list_ = tempNode;
	}
}

// Returns all dynamic memory on the free list to the free store.
template <typename T> void
LQueue_Node<T>::free_list_release(void)
{
	while (free_list_ != nullptr) {
		LQueue_Node<T>* temp = free_list_;
		free_list_ = free_list_->next_;
		::operator delete(temp);
	}
}

// Preallocate <n> <LQueue_Nodes> and store them on the
// <free_list_>
template <typename T> void
LQueue_Node<T>::free_list_allocate(size_t n)
{
	while (n > 0) {
		--n;
		LQueue_Node<T> *tempNode = (LQueue_Node<T> *)::operator new(sizeof(LQueue_Node<T>));
		tempNode->next_ = free_list_;
		free_list_ = tempNode;
	}
}

template <typename T>
LQueue_Node<T>::LQueue_Node(LQueue_Node<T> *next,LQueue_Node<T> *prev)
	: next_(next),prev_(prev)
{
	next_->prev_ = this;
	prev_->next_ = this;
}

// this is helpful to implement the dummy node in a concise way.
template <typename T>
LQueue_Node<T>::LQueue_Node(void) :item_{}, next_(this), prev_(this) {}

template <typename T>
LQueue_Node<T>::~LQueue_Node(void)
{
	next_->prev_ = prev_;
	prev_->next_ = next_;
}


//-------- defination for LQueue class-----------
template <typename T, typename LQUEUE_NODE = LQueue_Node<T> >
LQueue<T, LQUEUE_NODE>::LQueue(size_t size_hint = 0) :tail_{ new LQUEUE_NODE() }, count_{ 0 } {
	LQUEUE_NODE::free_list_allocate(size_hint);
}

template <typename T, typename LQUEUE_NODE = LQueue_Node<T> >
LQueue<T, LQUEUE_NODE>::LQueue(const LQueue<T, LQUEUE_NODE> &rhs)
	:tail_(new LQUEUE_NODE()),count_{0}
{
	LQueue<T,LQUEUE_NODE> temp;
	std::for_each(rhs.cbegin(), rhs.cend(), [&temp](T item) {temp.enqueue(item); });
	swap(temp);
}

//Assignment operator 
template<typename T, typename LQUEUE_NODE = LQueue_Node<T>>
LQueue<T, LQUEUE_NODE>& LQueue<T, LQUEUE_NODE>::operator=(const LQueue<T, LQUEUE_NODE> &rhs) {
	if (this != &rhs) {
		LQueue<T, LQUEUE_NODE> temp(rhs);
		swap(temp);
	}
	return *this;
}

template <typename T, typename LQUEUE_NODE = LQueue_Node<T> >
LQueue<T, LQUEUE_NODE>::~LQueue() {
	LQUEUE_NODE::free_list_release();
	while (count_ > 0) {
		dequeue();
	}
}
// Place a <new_item> at the tail of the queue.  Throws the
// <Overflow> exception if the queue is full, e.g., if memory is exhausted.
template <typename T, typename LQUEUE_NODE = LQueue_Node<T> >
void LQueue<T, LQUEUE_NODE>::enqueue(const T &new_item) {
	//Create a new node
	try
	{
		tail_->item_ = new_item;
		LQUEUE_NODE *temp = new LQUEUE_NODE();

		//Add it to the end of the queue
		temp->next_ = tail_->next_;
		tail_->next_ = temp;
		temp->prev_ = tail_;
		temp->next_->prev_ = temp;
		tail_ = temp;

		++count_;
	}
	catch (...)
	{
		throw(Overflow());
	}
	
}

// Remove the front item on the queue.  Throws the <Underflow>
// exception if the queue is empty.
template <typename T, typename LQUEUE_NODE = LQueue_Node<T> >
void LQueue<T, LQUEUE_NODE>::dequeue(void) {
	if (count_ > 0) {
		//get the head element
		LQUEUE_NODE * head = tail_->next_;

		//make the next element as head
		tail_->next_ = head->next_;
		head->next_->prev_ = tail_; //point it to the dummy node

		--count_;
		delete head;
	}
	else {
		throw Underflow();
	}
}

// Returns the front queue item without removing it. 
// Throws the <Underflow> exception if the queue is empty. 
template <typename T, typename LQUEUE_NODE = LQueue_Node<T> >
T LQueue<T, LQUEUE_NODE>::front(void) const {
	if (count_ > 0)
		return tail_->next_->item_;
	else
		throw(Underflow());
}

// Efficiently swap the contents of this <LQueue> with <new_aqueue>.
// Does not throw an exception.
template<typename T, typename LQUEUE_NODE = LQueue_Node<T>>
void LQueue<T, LQUEUE_NODE>::swap(LQueue<T, LQUEUE_NODE> &new_queue) {
	std::swap(tail_, new_queue.tail_); //pointer swaps doesn't throw exception
	std::swap(count_, new_queue.count_);
}



// Get an iterator to the begining of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::iterator
LQueue<T, LQUEUE_NODE>::begin(void) {
	return LQueue_Iterator<T, LQUEUE_NODE>(tail_->next_);
}

// Get an iterator pointing past the end of the queue
template <typename T, typename LQUEUE_NODE> typename LQueue<T, LQUEUE_NODE>::iterator
LQueue<T, LQUEUE_NODE>::end(void) {
	return LQueue_Iterator<T, LQUEUE_NODE>(tail_);
}

// Get a const iterator that points to the beginning of the queue.
template<typename T, typename LQUEUE_NODE = LQueue_Node<T>>
Const_LQueue_Iterator<T, LQUEUE_NODE> LQueue<T, LQUEUE_NODE>::cbegin(void) const {
	return const_iterator(tail_->next_);
}

// Get a const iterator that points to the end of the queue.
template<typename T, typename LQUEUE_NODE = LQueue_Node<T>>
Const_LQueue_Iterator<T, LQUEUE_NODE> LQueue<T, LQUEUE_NODE>::cend(void) const {
	return const_iterator(tail_);
}

// Compare this queue with <rhs> for equality.  Returns true if the
// size's of the two queues are equal and all the elements from 0
// .. size are equal, else false.
template<typename T, typename LQUEUE_NODE = LQueue_Node<T>>
bool LQueue<T, LQUEUE_NODE>::operator== (const LQueue<T, LQUEUE_NODE> &rhs) const {
	return count_ == rhs.count_ && std::equal(cbegin(),cend(),rhs.cbegin());
}

template<typename T, typename LQUEUE_NODE = LQueue_Node<T>>
bool LQueue<T, LQUEUE_NODE>::operator!= (const LQueue<T, LQUEUE_NODE> &rhs) const {
	return !(*this == rhs);
}
#endif /* _LQUEUE_CPP */