// MemoryPool.h
// Copyright 2018/11/7 Robin.Rowe@CinePaint.org
// License open source MIT

#ifndef MemoryPool_h
#define MemoryPool_h

#include <string>

namespace IPC {

class MemoryPool
{protected:
	void* p;
	bool isAllocator;
	std::string name;
	void Reset()
	{	p = 0;
		isAllocator = false;
		name.clear();
	}
	void Init(const char* name,bool isAllocator)
	{	Reset();
		this->name = name;
		this->isAllocator = isAllocator;
	}
	virtual bool Close() = 0;
	virtual bool Open(const char* name,size_t size) = 0;
public:
	MemoryPool()
	:	p(0)
	{}
	virtual ~MemoryPool()
	{}
	void* Allocate(size_t size)
	{	if(!Open(name.c_str(),size))
		{	return 0;
		}		
		return p;
	}
	void Deallocate(void* p)
	{	if(this->p == p)
		{	Close();
	}	}
};

}

#endif
