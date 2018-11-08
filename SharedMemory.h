// SharedMemory.h
// Copyright 2018/11/2 Robin.Rowe@CinePaint.org
// License open source MIT

#ifndef SharedMemory_h
#define SharedMemory_h

#ifdef _WIN32

#include <Windows.h>
#include <stdio.h>
#include <string>
#include "MemoryPool.h"

namespace IPC {

class SharedMemory
:	public MemoryPool
{	HANDLE id;
	size_t size;
	std::string name;
	bool isAllocator;
	void Reset()
	{	id = 0;
		p = 0;
		size = 0;
		isAllocator = false;
	}
	void PrintError(const char* msg)
	{	printf("Error %s (%d)\n",msg,GetLastError());
	}
public:
	~SharedMemory()
	{	Close();
	}
	SharedMemory(const char* name,bool isAllocator)
	{	Reset();
		this->name = name;
		this->isAllocator = isAllocator;
	}
	bool Close()
	{	if(p)
		{	UnmapViewOfFile(p);
		}
		if(id > 0)
		{	CloseHandle(id);
		}
		Reset();
		return true;	
	}
	bool Open(const char* name,size_t size)
	{	HANDLE sharedMemory = INVALID_HANDLE_VALUE;
//hFile = CreateFile(argv[1],GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_ALWAYS,NULL,NULL);
		id = CreateFileMappingA(sharedMemory,0,PAGE_READWRITE,0,(DWORD)size,name);
		if (id == NULL || id == INVALID_HANDLE_VALUE)
		{	PrintError("CreateFileMappingA");
			return false;
		}
		p = MapViewOfFile(id,FILE_MAP_ALL_ACCESS,0,0,size);           
		if(!p)
		{	PrintError("MapViewOfFile");
			return false;
		}
		this->size = size;
		return true;
	}
	bool Create(const char* name,size_t size)
	{	isAllocator = true;
		return Open(name,size);
	}
	operator void*()
	{	return this;
	}
	void* Allocate(size_t size) override
	{	if(isAllocator)
		{	if(!Create(name.c_str(),size))
			{	return 0;
		}	}
		else
		{	if(!Open(name.c_str(),size))
			{	return 0;
		}	}		
		return p;
	}
	void Deallocate(void* p) override
	{	if(this->p == p)
		{	Close();
	}	}
};

#else

#include <sys/mman.h>

namespace IPC {

#define shm_ftruncate ftruncate
#define shm_close close

class SharedMemory
{	int fd;
	size_t size;
	void* p;
	void Reset()
	{	fd = 0;
		p = 0;
		size = 0;
	}
public:
	~SharedMemory()
	{	Close();
	}
	SharedMemory()
	{	Reset();
	}
	bool Close()
	{	if(p>0)
		{	close(p);
			p = 0;
		}
		return shm_close(fd);
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
	bool Open(const char* name,size_t size)
	{	int oflags=O_RDWR;
		fd = shm_open(name,oflags,0644);
		if(fd<=0)
		{	return false;
		}
		size = shm_size(fd)/sizeof(*this);
		p = mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		this->size = size;
		return true;
	}
	operator void*()
	{	return p;
	}
};

#endif

}

#endif