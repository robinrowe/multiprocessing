// unix/Launcher.h
// Copyright 2018/12/15 Robin.Rowe@Cinepaint.org
// License MIT open source

#ifndef Launcher_h
#define Launcher_h

#include <spawn.h>
#include <sys/wait.h>

extern char **environ;

namespace IPC {

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

}

#endif
