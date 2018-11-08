// MemoryPool.h
// Copyright 2018/11/7 Robin.Rowe@CinePaint.org
// License open source MIT

#ifndef MemoryPool_h
#define MemoryPool_h

class MemoryPool
{protected:
	void* p;
public:
	MemoryPool()
	:	p(0)
	{}
	virtual ~MemoryPool()
	{}
	virtual void* Allocate(size_t size)
	{	return 0;
	}
	virtual void Deallocate(void*)
	{}
};

#endif
