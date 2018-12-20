// MemoryPool.h
// Copyright 2018/11/7 Robin.Rowe@CinePaint.org
// License open source MIT

#ifndef MemoryPool_h
#define MemoryPool_h

#include <string>
#include <stdio.h>

namespace IPC {

class MemoryPool
{protected:
	void* p;
	bool isAllocator;
	std::string name;
	std::string info;
	void Reset()
	{	p = 0;
		isAllocator = false;
		name.clear();
		info.clear();
	}
	void Init(const char* name,bool isAllocator)
	{	Reset();
		this->name = name;
		this->isAllocator = isAllocator;
	}
	void SetInfo(const char* msg,size_t size)
	{	info = "Memory pool ";
		info += name;
		info += ": ";
		info += msg;
		info += " ";
		info += std::to_string(size);
		info += " bytes";
	}
	virtual void PrintError(const char* msg)
	{	perror(msg);
	}
	virtual bool Close()
	{	return false;
	}
	virtual void* Create(size_t size)
	{	return 0;
	}
	virtual void* Open(size_t size)
	{	return 0;
	}
public:
	MemoryPool()
	:	p(0)
	{}
	virtual ~MemoryPool()
	{	Close();
	}
	void* Allocate(size_t size)
	{	return isAllocator? Create(size):Open(size);
	}
	void Deallocate(void* p)
	{	if(this->p == p)
		{	Close();
	}	}
	virtual const char* to_string() const
	{	return info.c_str();
	}
};

}

#endif
