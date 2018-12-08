// Pipes.h
// Copyright 2018/12/8 Robin.Rowe@Cinepaint.org
// License open source MIT

#ifndef Pipes_h
#define Pipes_h

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <process.h>
#include <math.h>
#include <string>

class Pipes
{	int fdpipe[2];
	intptr_t pid;
	enum PIPES { READ, WRITE }; /* Constants 0 and 1 for READ and WRITE */
	std::string s;
public:
	Pipes(int bufsize = 0)
	{	fdpipe[0]=-1;
		fdpipe[1]=-1;
		pid=-1;
		if(bufsize)
		{	s.reserve(bufsize);
	}	}
	bool Open()
	{	if(_pipe(fdpipe, 256, O_BINARY) == -1)
		{	return false;
		}
		setvbuf(stdout, NULL, _IONBF, 0);
		fflush(stdout);
		_dup2(fdpipe[WRITE],1);
		return true;
	}
	bool Open(const char* pipeRead,const char* pipeWrite)
	{	fdpipe[READ] = atoi(pipeRead);
		fdpipe[WRITE] = atoi(pipeRead);
		return true;
	}
	bool Spawn(const char* program)
	{	/* Convert pipe read descriptor to string and pass as argument
		 * to spawned program. Program spawns itself (argv[0]).
		 */
		const std::string s = std::to_string(fdpipe[READ]);
		pid = _spawnl(P_NOWAIT,program,program,s.c_str(), NULL);
		if(pid == -1)
		{	return false;
		}
		return true;
	}
	bool WaitChild()
	{	/* Wait until spawned program is done processing. */
		int termstat;
		_cwait(&termstat, pid, WAIT_CHILD);
		if(!termstat)
		{	return false;
		}
		_close(fdpipe[READ]);
		_close(fdpipe[WRITE]);
		return true;
	}
	bool Write(const std::string& s)
	{	const int bytes = _write(fdpipe[WRITE],s.c_str(),(unsigned)s.size());
		return bytes == s.size();
	}
	bool Read(char* buffer,size_t bufsize)
	{	const int bytes = _read(fdpipe[READ],buffer,(unsigned)bufsize);
		return -1 != bytes;
	}
};

#endif