// Semaphore.h
// Copyright 2018/11/6 Robin.Rowe@CinePaint.org
// License open source MIT

#ifndef IPC_Semaphore_h
#define IPC_Semaphore_h

#ifdef _WIN32
#include "windows/Semaphore.h"
#else
#include "unix/Semaphore.h"
#endif

namespace IPC {

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