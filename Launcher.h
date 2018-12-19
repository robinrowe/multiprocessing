// Launcher.h
// 2018/12/15

#ifndef Launcher_h
#define Launcher_h

#ifdef _WIN32
#include <process.h>
#define spawnl _spawnl
#define cwait _cwait

class Launcher
{	intptr_t pid;
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

#else

#include <spawn.h>
#include <sys/wait.h>

extern char **environ;

class Launcher
{	pid_t pid;
public:
	Launcher()
	:	pid(0)
	{}
	bool Spawn(const char* programName)
	{	char* cmd = (char*) programName;
		char sh[] = {'s','h',0};
		char c[] = {'-','c',0};
		char* const argv[] = {sh,c,cmd,0};
		const int error = posix_spawn(&pid,"/bin/sh",NULL,NULL,argv,environ);
		return !error;
	}
	bool WaitChild()
	{	/* Wait until spawned program is done processing. */
		if(!pid)
		{	return false;
		}
		int status;
		const int retval = waitpid(pid,&status,0);
		return -1 != retval;
	}
};

#endif
#endif
