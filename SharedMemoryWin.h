// SharedMemoryWin.h
// Copyright 2018/11/2 Robin.Rowe@CinePaint.org
// License open source MIT

#ifndef SharedMemoryWin_h
#define SharedMemoryWin_h

#include <Windows.h>
#include <stdio.h>
#include <string>
#include "MemoryPool.h"

namespace IPC {

class SharedMemoryWin
:	public MemoryPool
{	HANDLE id;
	void Reset()
	{	id = 0;
		MemoryPool::Reset();
	}
	void PrintError(const char* msg)
	{	printf("Error %s (%d)\n",msg,GetLastError());
	}
	bool Close() override
	{	if(p)
		{	UnmapViewOfFile(p);
		}
		if(id > 0)
		{	CloseHandle(id);
		}
		Reset();
		return true;	
	}
	bool Open(const char* name,size_t size) override
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
		return true;
	}
public:
	~SharedMemoryWin()
	{	Close();
	}
	SharedMemoryWin(const char* name,bool isAllocator)
	{	Init(name,isAllocator);
	}
	operator void*()
	{	return this;
	}
};

}

#endif