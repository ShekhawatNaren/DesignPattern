#pragma once
#ifndef _REFCOUNTER_H_
#define _REFCOUNTER_H_

/**
* @class Refcounter
* @brief This class does reference counting in its constructor and
*        destructor.  The template parameter T must have a member element
*        "int use_"
*/
template <class T>
class Refcounter
{
public:
	/// default Ctor
	Refcounter(void):ptr_{nullptr}	{}

	/// Ctor with refcounting functionality
	/// @param ptr of the object that should be managed
	/// @param own indicates if Refcounter should take ownership
	Refcounter(T* ptr, bool increase_count = false)
		: ptr_(ptr)
	{
		// by default we assume, the ptr will be created with use_ = 1 and
		// that the Refcounter is taking over ownership, meaning, that is
		// responsible for deletion of the ptr.  If this is not the case,
		// the user can set increase count to true, which results in
		// incrementing the reference count for a passed in object.
		if (increase_count)
			increment();
	}

	/// copy Ctor
	Refcounter(const Refcounter& rhs)
	{
		ptr_ = rhs.ptr_;
		increment();
	}

	/// Dtor will delete pointer if refcount becomes 0
	~Refcounter(void)
	{
		decrement();
	}

	/// assignment operator
	void operator= (const Refcounter& rhs)
	{
		if (this != &rhs)
		{
			//Decrease the reference count for the current pointer where this object is pointing to
			//This is to clear the object currently allocated to this refcounter object
			//This is very importance else there will be memory leaks in cases when the refcounter
			//pointer was already pointing to an object
			decrement();

			//Assign the new pointer
			ptr_ = rhs.ptr_;

			//increase the reference for this new pointer since one more pointer has reference to this now
			increment();
		}
	}

	/// dereference operator
	T* operator-> (void) const
	{
		return ptr_;
	}

	/// dereference operator
	const T &operator* (void) const
	{
		return *ptr_;
	}

	/// dereference operator
	T &operator* (void)
	{
		return *ptr_;
	}

	bool is_null(void) const
	{
		return ptr_ == nullptr;
	}

private:

	/// implementation of the increment operation
	void increment(void)
	{
		if (ptr_ != nullptr)
			ptr_->use_++;
	}

	/// implementation of the decrement operation
	void decrement(void)
	{
		if (ptr_ != nullptr)
		{
			ptr_->use_--;
			if (ptr_->use_ == 0) {
				delete ptr_;
				ptr_ = nullptr;
			}

		}
	}


private:
	/// reference to the refcounted object
	T *ptr_;
};

#endif /* _REFCOUNTER_H_ */