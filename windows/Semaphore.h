// windows/Semaphore.h
// Copyright 2018/11/6 Robin.Rowe@CinePaint.org
// License open source MIT

#ifndef IPC_Windows_Semaphore_h
#define IPC_Windows_Semaphore_h

#include <Windows.h>
#include <string>
#include "../SystemError.h"

namespace IPC {

typedef int key_t;

class Semaphore
{	HANDLE id;
	DWORD waitResult;
	void PrintError(const char* msg)
	{	PrintSystemError(msg); 
	}
#define case_msg(x) case x: return "Lock: " #x
	const char* GetWaitResult() const
	{	switch(waitResult)
		{	default:
				return "Unknown";
			case_msg(WAIT_OBJECT_0);
			case_msg(WAIT_ABANDONED);
			case_msg(WAIT_TIMEOUT);
			case_msg(WAIT_FAILED);
		}
		return "None";
	}
#undef case_msg
public:
	Semaphore()
	:	id(0)
	{}
	~Semaphore()
	{	Close();
	}
	void Close()
	{	if(id>0)
		{	CloseHandle(id);
			id = 0;
	}	}
	bool Open(key_t key)
	{	Close();
		std::string s(std::to_string(key));
		id = OpenMutexA(MUTEX_ALL_ACCESS,FALSE,s.c_str());
		if(!id)
		{	PrintError("OpenMutex");
			return false;
		}
		return true;
	}
	bool Create(key_t key)
	{	std::string s(std::to_string(key));
		LPSECURITY_ATTRIBUTES security = NULL;
		BOOL isLocked = FALSE;
		id = CreateMutexA(security,isLocked,s.c_str());
		if(!id)
		{	if(GetLastError() == ERROR_INVALID_HANDLE)
			{	PrintError("Name of an existing event, semaphore, waitable timer, job, or file-mapping object");
			}
			else
			{	PrintError("CreateMutex");
			}
			return false;
		}
		return true;
	}
	bool Lock(int lockVal = -1)
	{	waitResult = WaitForSingleObject(id,INFINITE);  
		if(waitResult == WAIT_OBJECT_0)
		{	return true;
		}
		PrintError(GetWaitResult());
        return false;
    }
	bool Unlock()
	{	const BOOL ok = ReleaseMutex(id);
		if(!ok)
		{	PrintError("ReleaseMutex");
			return false;
		}
		return true;
	}
};

}

#endif