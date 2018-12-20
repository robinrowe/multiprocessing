// SharedMemorySysV.h
// Copyright 2018/11/2 Robin.Rowe@CinePaint.org
// License open source MIT

#ifndef SharedMemorySysV_h
#define SharedMemorySysV_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "MemoryPool.h"

#define shm_ftruncate ftruncate
#define shm_close close

namespace IPC {

class SharedMemorySysV
:	public MemoryPool
{protected:
	int id;
	void Reset()
	{	id = 0;
		MemoryPool::Reset();
	}
	bool Close() override
	{	if(!p)
		{	return false;
		}
		if(shmdt(p) == -1)
		{	PrintError("shmdt");
			return false;
		}
		return true;
	}
	void* Create(size_t size) override
	{	key_t key = ftok(name.c_str(),65); 
		id = shmget(key,size,0644 | IPC_CREAT);
		if(id == -1) 
		{	PrintError("shmget");
			return 0;
		}
		p = shmat(id,0,0);
		if(p == (char *)(-1))
		{	PrintError("shmat");
			return 0;
		}
		SetInfo("SharedMemorySysV create: ",size);
		return p;
	}
	void* Open(size_t size) override
	{	key_t key = ftok(name.c_str(),65); 
		id = shmget(key,size,0644 | 0);
		if(id == -1) 
		{	PrintError("shmget");
			return 0;
		}
		p = shmat(id,0,0);
		if(p == (char *)(-1))
		{	PrintError("shmat");
			return 0;
		}
		SetInfo("SharedMemorySysV open: ",size);
		return p;
	}
public:
	SharedMemorySysV(const char* name,bool isAllocator)
	{	Init(name,isAllocator);
	}
	operator void*()
	{	return this;
	}
};

}

#endif

