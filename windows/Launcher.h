// windows/Launcher.h
// Copyright 2018/12/15 Robin.Rowe@Cinepaint.org
// License MIT open source

#ifndef Launcher_h
#define Launcher_h

#include <process.h>

namespace IPC {

class Launcher
{	intptr_t pid;
public:
	Launcher()
	:	pid(0)
	{}
	bool Spawn(const char* programName)
	{	pid = _spawnl(P_NOWAIT,programName,programName,NULL);
		if(pid == -1)
		{	return false;
		}
		return true;
	}
	bool WaitChild()
	{	/* Wait until spawned program is done processing. */
		if(!pid)
		{	return false;
		}
		int termstat;
		_cwait(&termstat, pid, WAIT_CHILD);
		if(!termstat)
		{	return false;
		}
		return true;
	}
};
}

#endif
