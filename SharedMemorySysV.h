// SharedMemorySysV.h
// Copyright 2018/11/2 Robin.Rowe@CinePaint.org
// License open source MIT

#ifndef SharedMemorySysV_h
#define SharedMemorySysV_h

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h> 
 #include <unistd.h>
#include <sys/types.h>
#include "MemoryPool.h"

#define shm_ftruncate ftruncate
#define shm_close close

namespace IPC {

class SharedMemory
:	public MemoryPool
{protected:
	int fd;
	size_t size;
	void* p;
	void Reset()
	{	fd = 0;
		p = 0;
		size = 0;
	}
	bool Create(const char* name,size_t size)
	{	int oflags = O_RDWR | O_CREAT;
		fd = shm_open(name,oflags,0644);
		if(fd<=0)
		{	return false;
		}
		shm_ftruncate(fd,size);
		p = mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		this->size = size;
		return true;
	}
	bool Close() override
	{	if(p>0)
		{	close(p);
			p = 0;
		}
		return shm_close(fd);
	}
	bool Open(const char* name,size_t size) override
	{	if(isAllocator)
		{	return Create(name,size);
		}
		int oflags=O_RDWR;
		fd = shm_open(name,oflags,0644);
		if(fd<=0)
		{	return false;
		}
		size = shm_size(fd)/sizeof(*this);
		p = mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		this->size = size;
		return true;
	}
public:
	~SharedMemory()
	{	Close();
	}
	SharedMemory()
	{	Reset();
	}
	operator void*()
	{	return this;
	}
};

}

#endif