// RingQueue.h
// Copyright 2018/11/2 Robin.Rowe@CinePaint.org
// License open source MIT

#ifndef RingQueue_h
#define RingQueue_h

#include <iostream>
#include <iterator>
#include <algorithm>
#include "MemoryPool.h"

class RingQueueBase
{protected:
	const unsigned capacity;
	unsigned head;
	unsigned tail;
	RingQueueBase(int capacity)
	:	capacity(capacity)
	,	head(0)
	,	tail(0)
	{}
public:
	bool IsEmpty() const
	{	return head == tail;
	}
	size_t Count() const
	{	const int spread = tail-head;
		if(spread>=0)
		{	return spread;
		}
		return capacity+spread;
	}
	size_t Capacity() const
	{	return capacity;
	}
	bool IsFull() const
	{	return Count() == capacity;
	}
	unsigned Head() const
	{	return head;
	}
	unsigned Tail() const
	{	return tail;
	}
};

template <typename T>
class RingQueueIterator
{protected:
	const RingQueueBase& q;
	const T* buffer;
	unsigned head;
	bool OpEqEq(const RingQueueIterator& rhs) const
	{	if(rhs.head == head)
		{	return true;
		}	
		return false;
	}
	void OpPlusPlus()
	{	head++;
		if(head>=q.Capacity())
		{	head = 0;
	}	}
public:
	RingQueueIterator<T>(const RingQueueBase& q,T* buffer)
	:	q(q)
	,	buffer(buffer)
	{	head = q.Head();
	}
	bool operator==(const RingQueueIterator<T>& rhs) const
	{	return OpEqEq(rhs);
	}
	bool operator!=(const RingQueueIterator<T>& rhs) const
	{	return !OpEqEq(rhs);
	}
	RingQueueIterator<T>& operator++()
	{	OpPlusPlus();
		return *this;
	}
	operator T*()
	{	return q[head];
	}
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;
};

template <typename T>
class ConstRingQueueIterator
:	public RingQueueIterator<T>
{public:
	ConstRingQueueIterator(const RingQueueBase& q,const T* buffer)
	:	RingQueueIterator(q,(T*)buffer)
	{}
	bool operator==(const ConstRingQueueIterator& rhs) const
	{	return OpEqEq(rhs);
	}
	bool operator!=(const ConstRingQueueIterator& rhs) const
	{	return !OpEqEq(rhs);
	}
	ConstRingQueueIterator<T>& operator++()
	{	OpPlusPlus();
		return *this;
	}
	operator T*() const
	{	return (T*)buffer+head;
	}
};

template <typename T,unsigned capacity2>
class RingQueue
:	public RingQueueBase
{	T q[capacity2+1];
	bool isGood;
public:
	RingQueue()
	:	RingQueueBase(capacity2+1)
	,	isGood(false)
	{}
	RingQueueIterator<T> begin()
	{	return RingQueueIterator<T>(*this,q);
	}
	RingQueueIterator<T> end()
	{	return RingQueueIterator<T>(*this,q);
	}
	ConstRingQueueIterator<T> begin() const
	{	return ConstRingQueueIterator<T>(*this,q);
	}
	ConstRingQueueIterator<T> end() const
	{	return ConstRingQueueIterator<T>(*this,q);
	}
	void* operator new(size_t size,void* pool) throw()
	{	if(!pool)
		{	return 0;
		}
		IPC::MemoryPool* p = static_cast<IPC::MemoryPool*>(pool); 
		return p->Allocate(size);
	}
	void operator delete(void* pool,void* ptr) throw()
	{	if(!pool)
		{	return;
		}
		IPC::MemoryPool* p = static_cast<IPC::MemoryPool*>(pool); 
		p->Deallocate(ptr);
	}
	void Set(bool isGood = true)
	{	this->isGood = isGood;
	}
	bool IsGood() const
	{	return isGood;
	}
	const T* Fence() const
	{	return q+capacity;
	}
	void Clear(int init = 0)
	{	for(unsigned i = 0;i<capacity;i++)
		{	q[i] = init;
	}	}
	T& Front()
	{	return q[head];
	}
	const T& Front() const
	{	return q[head];
	}
	bool Push(const T& v)
	{	if(IsFull())
		{	return false;
		}
		q[tail] = v;
		if(tail < capacity)
		{	tail++;
		}
		else
		{	tail = 0;
		}
		return true;
	}
	bool Pop()
	{	if(IsEmpty())
		{	return false;
		}
		if(head < capacity)
		{	head++;
		}
		else
		{	head = 0;
		}
		return true;
	}
};

template <typename T,int size>
std::ostream& operator<<(std::ostream& os,const RingQueue<T,size>& q)
{	auto print = [&](const T& n)
	{	os << n << " ";
	};
	for_each(q.begin(),q.end(),print);
	os << endl << "Count = " << q.Count() 
		<< ", Max = " << q.Capacity();
	return os;
}

#endif