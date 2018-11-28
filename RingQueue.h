// RingQueue.h
// Copyright 2018/11/2 Robin.Rowe@CinePaint.org
// License open source MIT

#ifndef RingQueue_h
#define RingQueue_h

#include <iostream>
#include <iterator>
#include <algorithm>
#include "MemoryPool.h"

template <typename T>
class RingQueueIterator
{protected:
	T* head;
	T* tail;
	T* buffer;
	T* fence;
	bool OpEqEq(const RingQueueIterator& rhs) const
	{	if(rhs.head == head)
		{	return true;
		}	
		return false;
	}
	void OpPlusPlus()
	{	head++;
		if(head>=fence)
		{	head = buffer;
	}	}
public:
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;
	RingQueueIterator(T* head,T* tail,T* buffer,unsigned capacity)
	:	head(head)
	,	tail(tail)
	,	buffer(buffer)
	,	fence(buffer+capacity)
	{}
	bool operator==(const RingQueueIterator& rhs) const
	{	return OpEqEq(rhs);
	}
	bool operator!=(const RingQueueIterator& rhs) const
	{	return !OpEqEq(rhs);
	}
	RingQueueIterator<T>& operator++()
	{	OpPlusPlus();
		return *this;
	}
	operator T*()
	{	return head;
	}
};

template <typename T>
class ConstRingQueueIterator
:	public RingQueueIterator<T>
{public:
	ConstRingQueueIterator(T* head,T* tail,T* buffer,unsigned capacity)
	:	RingQueueIterator(head,tail,buffer,capacity)
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
	{	return head;
	}
};

template <typename T,unsigned capacity>
class RingQueue
{	T q[capacity+1];
	int head;
	int tail;
	bool isGood;
public:
	RingQueue()
	:	head(0)
	,	tail(0)
	,	isGood(false)
	{}
	RingQueueIterator<T> begin()
	{	return RingQueueIterator<T>(q+head,q+tail,q,capacity);
	}
	RingQueueIterator<T> end()
	{	return RingQueueIterator<T>(q+tail,q+tail,q,capacity);
	}
	ConstRingQueueIterator<T> begin() const
	{	T* p = (T*) q;
		return ConstRingQueueIterator<T>(p+head,p+tail,p,capacity);
	}
	ConstRingQueueIterator<T> end() const
	{	T* p = (T*) q;
		return ConstRingQueueIterator<T>(p+tail,p+tail,p,capacity);
	}
	void Clear(int init = 0)
	{	for(unsigned i = 0;i<capacity;i++)
		{	q[i] = init;
	}	}
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