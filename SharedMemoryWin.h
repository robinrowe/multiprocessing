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
	void PrintError(const char* msg) override
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
	bool Open(size_t size) override
	{	HANDLE sharedMemory = INVALID_HANDLE_VALUE;
//hFile = CreateFile(argv[1],GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_ALWAYS,NULL,NULL);
		id = CreateFileMappingA(sharedMemory,0,PAGE_READWRITE,0,0,/*(DWORD)size*/name.c_str());
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
	SharedMemoryWin(const char* name,bool isAllocator)
	{	Init(name,isAllocator);
	}
	operator void*()
	{	return this;
	}
};

}

#endif

/* Since WinXP SP2, CreateFileMapping is now significantly reduced in functionality and that only services are allowed to create global shared memory.

There are three workarounds:

Use the Microsoft Management Console (MMC) and the Local Security Policy Snap-In to give SeCreateGlobalPrivilege to the limited account.
Write a wrapper program that executes with elevated rights and and uses RtlAcquire/AdjustPrivilege to get the privilege before running your target program (Such as gcc).
Use the HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Kernel\ObUnsecureGlobalNames string array to add the name of the section to the list. Hopefully your program isn�t randomizing the name. Adding this name will disable the kernel protection check.

http://www.alex-ionescu.com/?p=16

*/
/*
User Rights Assignment:

https://docs.microsoft.com/en-us/windows/security/threat-protection/security-policy-settings/user-rights-assignment

Create global objects:	SeCreateGlobalPrivilege

https://docs.microsoft.com/en-us/windows/security/threat-protection/security-policy-settings/create-global-objects

By default, members of the Administrators group, the System account, and services that are started by the Service Control Manager are assigned the Create global objects user right. Users who are added to the Remote Desktop Users group also have this user right.

Countermeasure
When non-administrators need to access a server using Remote Desktop, add the users to the Remote Desktop Users group rather than assining them this user right.

Vulnerability
Caution: A user account that is given this user right has complete control over the system, and it can lead to the system being compromised. We highly recommend that you do not assign this right to any user accounts.

*/