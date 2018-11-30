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
	const int usefulCapacity;
	int head;
	int tail;
	RingQueueBase(int usefulCapacity)
	:	usefulCapacity(usefulCapacity)
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
		return usefulCapacity+spread+1;
	}
	size_t Capacity() const
	{	return usefulCapacity;
	}
	bool IsFull() const
	{	return Count() == usefulCapacity;
	}
};

template <typename T>
class RingQueueIterator
{protected:
	const RingQueueBase& q;
	const T* buffer;
	int i;
	bool OpEqEq(const RingQueueIterator& rhs) const
	{	if(rhs.i == i)
		{	return true;
		}	
		return false;
	}
	void OpPlusPlus()
	{	i++;
		if(i > q.Capacity())
		{	i = 0;
	}	}
public:
	RingQueueIterator<T>(const RingQueueBase& q,T* buffer,int i)
	:	q(q)
	,	buffer(buffer)
	,	i(i)
	{}
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
	{	return q[i];
	}
	typedef std::forward_iterator_tag iterator_category;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;
};

template <typename T>
class ConstRingQueueIterator
:	public RingQueueIterator<T>
{public:
	ConstRingQueueIterator(const RingQueueBase& q,const T* buffer,int i)
	:	RingQueueIterator(q,(T*)buffer,i)
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
	{	return (T*)buffer+i;
	}
};

template <typename T,int capacity>
class RingQueue
:	public RingQueueBase
{	T q[capacity+1];
	bool isGood;
public:
	RingQueue()
	:	RingQueueBase(capacity)
	,	isGood(false)
	{}
	RingQueueIterator<T> begin()
	{	return RingQueueIterator<T>(*this,q,head);
	}
	RingQueueIterator<T> end()
	{	return RingQueueIterator<T>(*this,q,tail);
	}
	ConstRingQueueIterator<T> begin() const
	{	return ConstRingQueueIterator<T>(*this,q,head);
	}
	ConstRingQueueIterator<T> end() const
	{	return ConstRingQueueIterator<T>(*this,q,tail);
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
	{	for(int i = 0;i<capacity;i++)
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
		tail++;
		if(tail > capacity)
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
	os	<< "(Count = " << q.Count() << ", Capacity = " << q.Capacity() << ")";
	return os;
}

#endif