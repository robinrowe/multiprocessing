// RingQueue.h
// Copyright 2018/11/2 Robin.Rowe@CinePaint.org
// License open source MIT

#ifndef RingQueue_h
#define RingQueue_h

#include <atomic>
#include "MemoryPool.h"

template <typename T,unsigned size>
class RingQueue
{	T q[size];
	std::atomic<unsigned> head;
	std::atomic<unsigned> tail;
	std::atomic<bool> isGood;
public:
	RingQueue()
	:	head(0)
	,	tail(0)
	,	isGood(false)
	{}
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
	{	if(head<=tail)
		{	return tail-head;
		}
		return size-head+tail;
	}
	bool IsFull() const
	{	return Count() == size;
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
		if(tail < size-1)
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
		if(head < size-1)
		{	head++;
		}
		else
		{	head = 0;
		}
		return true;
	}
	void* operator new(size_t size,void* pool)
	{	if(!pool)
		{	return 0;
		}
		MemoryPool* p = static_cast<MemoryPool*>(pool); 
		return p->Allocate(size);
	}
};

#endif