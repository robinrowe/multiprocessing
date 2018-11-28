// RingQueue.h
// Copyright 2018/11/2 Robin.Rowe@CinePaint.org
// License open source MIT

#ifndef RingQueue_h
#define RingQueue_h

#include <atomic>
#include "MemoryPool.h"

template <typename T,unsigned capacity,int init = 0>
class RingQueue
{	T q[capacity+1];
	std::atomic<unsigned> head;
	std::atomic<unsigned> tail;
	std::atomic<bool> isGood;
public:
	RingQueue()
	:	head(0)
	,	tail(0)
	,	isGood(false)
	{}
	void Clear()
	{	for(unsigned i = 0;i<=capacity;i++)
		{	q[i] = init;
	}	}
	void Set(bool isGood = true)
	{	this->isGood = isGood;
	}
	bool IsGood() const
	{	return isGood;
	}
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
};

#endif