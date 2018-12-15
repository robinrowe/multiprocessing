// Launcher.h
// 2018/12/15

#ifndef Launcher_h
#define Launcher_h

#include <process.h>

#ifdef _WIN32
#define spawnl _spawnl
#define cwait _cwait
#endif

class Launcher
{	int pid;
public:
	Launcher()
	:	pid(0)
	{}
	bool Spawn(const char* programName)
	{	pid = spawnl(P_NOWAIT,programName,programName,NULL);
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
		cwait(&termstat, pid, WAIT_CHILD);
		if(!termstat)
		{	return false;
		}
		return true;
	}
};

#endif
