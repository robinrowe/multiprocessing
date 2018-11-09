// SharedMemoryBSD.h
// Copyright 2018/11/2 Robin.Rowe@CinePaint.org
// License open source MIT

#ifndef SharedMemoryBSD_h
#define SharedMemoryBSD_h

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <sys/types.h>
#include "MemoryPool.h"

#define shm_ftruncate ftruncate
#define shm_close close

namespace IPC {

class SharedMemoryBSD
:	public MemoryPool
{	inline
	size_t shm_size(int fd)
	{	if(fd<=0)
		{	return 0;
		}
		struct stat status;
		if(stat(name.c_str(),&status) == -1)
		{	PrintError("stat");
			return 0;
		}
		return status.st_size;
	}
protected:
	int fd;
	void Reset()
	{	fd = 0;
		MemoryPool::Reset();
	}
	bool Create(size_t size)
	{	int oflags = O_RDWR | O_CREAT;
		fd = shm_open(name.c_str(),oflags,0644);
		if(fd<=0)
		{	PrintError("shm_open");
			return false;
		}
		shm_ftruncate(fd,size);
		p = mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		return true;
	}
	bool Close() override
	{	int err = 0;
		if(p>0)
		{	err = munmap(p,shm_size(fd));
			p = 0;
		}
		return (err == 0) && shm_close(fd);
	}
	bool Open(size_t size) override
	{	if(isAllocator)
		{	return Create(size);
		}
		int oflags=O_RDWR;
		fd = shm_open(name.c_str(),oflags,0644);
		if(fd<=0)
		{	PrintError("shm_open");
			return false;
		}
		size = shm_size(fd)/sizeof(*this);
		p = mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		return true;
	}
public:
	SharedMemoryBSD(const char* name,bool isAllocator)
	{	Init(name,isAllocator);
	}
	operator void*()
	{	return this;
	}
};

}

#endif