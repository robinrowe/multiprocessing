// Semaphore.h
// Copyright 2018/11/6 Robin.Rowe@CinePaint.org
// License open source MIT

#ifndef IPC_Semaphore_h
#define IPC_Semaphore_h

#ifdef _WIN32

#include <Windows.h>
#include <string>

namespace IPC {

typedef int key_t;

class Semaphore
{	HANDLE id;
	void PrintError(const char* msg)
	{	printf("%s error: %d\n",msg,GetLastError()); 
	}
//Initalize the semaphore count to one to put it in the unlocked state
//The default semaphore count is zero. This will create an immediate
//deadlock if we request a lock.
public:
	Semaphore()
	:	id(0)
	{}
	bool Close()
	{	if(id>0)
		{	CloseHandle(id);
			id = 0;
		}
		return true;
	}
	bool Open(key_t key)
	{	Close();
		std::string s = std::to_string(key);
		id = OpenMutexA(MUTEX_ALL_ACCESS,FALSE,s.c_str());
		if(!id)
		{	PrintError("OpenMutex");
			return false;
		}
		return true;
	}
	bool Create(key_t key)
	{	std::string s = std::to_string(key);
		id = CreateMutexA(0,FALSE,s.c_str());
		if(!id)
		{	PrintError("CreateMutex");
			return false;
		}
		return true;
	}
	bool Lock(int lockVal = -1)
	{	const DWORD dwWaitResult = WaitForSingleObject(id,INFINITE);  
		if(WAIT_OBJECT_0 == dwWaitResult) 
        {	return true;
		}
        PrintError("WaitForSingleObject");
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

#else

namespace IPC {

#include <sys/ipc.h>
#include <sys/sem.h>

class Semaphore
{	int id;
	void PrintError(const char* msg)
	{	printf("Error %s - %s (%d)\n",msg,strerror(errno),errno);
	}
//Initalize the semaphore count to one to put it in the unlocked state
//The default semaphore count is zero. This will create an immediate
//deadlock if we request a lock.
	bool Set(int val)
	{	const int err = semctl(id,0,SETVAL,val);
		if(-1 == val)
		{	PrintError("semctl");
			return false;
		}
		return true;
	}
public:
	Semaphore()
	:	id(0)
	{}
	bool Close()
	{	int err = semctl(id,0,IPC_RMID);
		if(-1 == id)
		{	PrintError("semctl");
			return false;
		}
		return true;
	}
	bool Open(key_t key,int flag = 0)
	{	Close();
		id = semget(key,1,flag);
		if(-1 == id)
		{	PrintError("semget");
			return false;
		}
		if(!Set(1))
		{	return false;
		}
		return true;
	}
	bool Create(key_t key)
	{	return Open(key,IPC_CREAT | 0666);
	}
	bool Lock(int lockVal = -1)
	{	semun op;
		op.sem_num = 0;
		op.sem_op = lockVal;
		op.sem_flg = 0;
		const int err = semop(id,&op,1);
		if(!err)
		{	PrintError("semop");
			return true;
		}	
		return false;
	}
	bool Unlock()
	{	return Lock(1);
	}
};
#endif

class Lock
{	Semaphore& s;
public:
	~Lock()
	{	s.Unlock();
	}
	Lock(Semaphore& s)
	:	s(s)
	{	s.Lock();
	}
};

}

#endif