// unix/Semaphore.h
// Copyright 2018/11/6 Robin.Rowe@CinePaint.org
// License open source MIT

#ifndef IPC_Unix_Semaphore_h
#define IPC_Unix_Semaphore_h

#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>

namespace IPC {

class Semaphore
{	int semid;
	void PrintError(const char* msg)
	{	printf("Error Semaphore %s - %s (%d)\n",msg,strerror(errno),errno);
	}
//Initalize the semaphore count to one to put it in the unlocked state
//The default semaphore count is zero. This will create an immediate
//deadlock if we request a lock.
	bool Set(int val)
	{	const int semnum = 0;
		const int err = semctl(semid,semnum,SETVAL,val);
		if(-1 == val)
		{	PrintError("semctl");
			return false;
		}
		return true;
	}
public:
	Semaphore()
	:	semid(0)
	{}
	~Semaphore()
	{	Close();
	}
	bool IsGood() const
	{	return semid>0;
	}
	void Close()
	{	if(!IsGood())
		{	return;
		}
		if(!Set(IPC_RMID))
		{	PrintError("Close semctl");
		}
		semid = 0;
	}
	bool Open(key_t key,int flag = 0)
	{	Close();
		const int nsems = 1;
		semid = semget(key,nsems,flag);
		if(-1 == semid)
		{	PrintError("semget");
			return false;
		}
		return true;
	}
	bool Create(key_t key)
	{	if(!Open(key,IPC_CREAT | 0666))
		{	return false;
		}
		if(!Set(0))
		{	return false;
		}
		return true;
	}
	bool Lock()
	{	sembuf op[2];
		enum {wait,lock};
		op[wait] = {0,0,0};
		op[lock] = {0,1,0};
		const size_t nsops = 2;
		if(-1 == semop(semid,op,nsops))
		{	PrintError("semop lock");
			return false;
		}
		return true;
	}
	bool Unlock()
	{	sembuf op = {0,-1,0};
		const size_t nsops = 1;
		if(-1 == semop(semid,&op,nsops))
		{	PrintError("semop unlock");
			return false;
		}
		return true;
	}
};

}

#endif