// crt_pipe.c
/* This program uses the _pipe function to pass streams of
* text to spawned processes.
*/

#include "Pipes.h"

class Status
{	int status;
	const char* statusMsg;
public:
	enum 
	{	ok,
		usage,
		cannot_open_pipes,
		cannot_spawn,
		child_failed
	};
	Status()
	:	status(ok)
	,	statusMsg("ok")
	{}
	void Set(int status,const char* statusMsg)
	{	this->status = status;
		this->statusMsg = statusMsg;
	}
	operator int() const
	{	puts(statusMsg);
		return status;
	}
	operator const char*() const
	{	return statusMsg;
	}
};

static Status status;
#define SetStatus(m) status.Set(Status::m,#m)

class Server
{	Pipes server;
public:
	bool Open(const char* child)
	{	if(!server.Open())
		{	SetStatus(cannot_open_pipes);
			return false;
		}
		if(!server.Spawn(child))
		{	SetStatus(cannot_spawn);
			return false;
		}
		return true;
	}
	bool Run()
	{	std::string s;
		for(int i = 1; i <= 100; i++)
		{	s = std::to_string(i);
			s+=' ';
			server.Write(s);
			printf("Server: %d \n",i);
		}
		if(!server.WaitChild())		
		{	SetStatus(child_failed);
			return false;
		}
		SetStatus(ok);
		return true;
	}
};

class Child
{	Pipes child;
	std::string s;
public:
	Child()
	{	const size_t bufsize = 80;
		s.reserve(bufsize);
	}
	bool Open(const char* pipeRead,const char* pipeWrite)
	{	return child.Open(pipeRead,pipeWrite);
	}
	bool Run()
	{	/* Read problem from pipe and calculate solution. */
		for(int i = 0; i<100; i++)
		{	child.Read((char*) s.c_str(),s.capacity());
			printf("Child: square root of %d is %3.2f.\n",i, sqrt((double)i));
		}
		SetStatus(ok);
		return true;
	}
};

void Usage()
{	puts("Invalid input");
	SetStatus(usage);
}

int main(int argc, char *argv[])
{	enum 
	{	parentProcess = 1,
		childProcess = 3
	};
	switch(argc)
	{	default:
		{	Usage();
			return status;
		}
		case parentProcess:
		{	Server server;
			if(server.Open(argv[0]))
			{	server.Run();
			}
			return status;
		}
		case childProcess:
		{	Child child;
			if(!child.Open(argv[1],argv[2]))
			{	return status;
			}
			child.Run();
			return status;	
	}	}
	return status;
}

#if 0
/*Example 2
This is a basic filter application. It spawns the application crt_pipe_beeper after it creates a pipe that directs the spawned application's stdout to the filter. The filter removes ASCII 7 (beep) characters.
*/
// crt_pipe_beeper.c

#include <stdio.h>
#include <string.h>

int main()
{
   int   i;
   for(i=0;i<10;++i)
      {
         printf("This is speaker beep number %d...\n\7", i+1);
      }
   return 0;
}

// crt_pipe_BeepFilter.C
// arguments: crt_pipe_beeper.exe

#include <windows.h>
#include <process.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>

#define   OUT_BUFF_SIZE 512
#define   READ_FD 0
#define   WRITE_FD 1
#define   BEEP_CHAR 7

char szBuffer[OUT_BUFF_SIZE];

int Filter(char* szBuff, ULONG nSize, int nChar)
{
   char* szPos = szBuff + nSize -1;
   char* szEnd = szPos;
   int nRet = nSize;

   while (szPos > szBuff)
   {
      if (*szPos == nChar)
         {
            memmove(szPos, szPos+1, szEnd - szPos);
            --nRet;
         }
      --szPos;
   }
   return nRet;
}

int main(int argc, char** argv)
{
   int nExitCode = STILL_ACTIVE;
   if (argc >= 2)
   {
      HANDLE hProcess;
      int fdStdOut;
      int fdStdOutPipe[2];

      // Create the pipe
      if(_pipe(fdStdOutPipe, 512, O_NOINHERIT) == -1)
         return   1;

      // Duplicate stdout file descriptor (next line will close original)
      fdStdOut = _dup(_fileno(stdout));

      // Duplicate write end of pipe to stdout file descriptor
      if(_dup2(fdStdOutPipe[WRITE_FD], _fileno(stdout)) != 0)
         return   2;

      // Close original write end of pipe
      _close(fdStdOutPipe[WRITE_FD]);

      // Spawn process
      hProcess = (HANDLE)_spawnvp(P_NOWAIT, argv[1],
       (const char* const*)&argv[1]);

      // Duplicate copy of original stdout back into stdout
      if(_dup2(fdStdOut, _fileno(stdout)) != 0)
         return   3;

      // Close duplicate copy of original stdout
      _close(fdStdOut);

      if(hProcess)
      {
         int nOutRead;
         while   (nExitCode == STILL_ACTIVE)
         {
            nOutRead = _read(fdStdOutPipe[READ_FD],
             szBuffer, OUT_BUFF_SIZE);
            if(nOutRead)
            {
               nOutRead = Filter(szBuffer, nOutRead, BEEP_CHAR);
               fwrite(szBuffer, 1, nOutRead, stdout);
            }

            if(!GetExitCodeProcess(hProcess,(unsigned long*)&nExitCode))
               return 4;
         }
      }
   }
   return nExitCode;
}
#endif
#if 0
/*A tricky use of dup2() system call: As in dup2(), in place of newfd any file descriptor can be put. Below is a C implementation in which the file descriptor of Standard output (stdout) is used. This will lead all the printf() statements to be written in the file referred by the old file descriptor.
*/
// CPP program to illustrate dup2()  
#include<stdlib.h> 
#include<unistd.h> 
#include<stdio.h> 
#include<fcntl.h> 
  
int main() 
{ 
    int file_desc = open("tricky.txt",O_WRONLY | O_APPEND); 
      
    // here the newfd is the file descriptor of stdout (i.e. 1) 
    dup2(file_desc, 1) ;  
          
    // All the printf statements will be written in the file 
    // "tricky.txt" 
    printf("I will be printed in the file tricky.txt\n"); 
      
return 0; 
} 
#endif

#if 0

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int
main(int argc, char *argv[])
{	int pipefd[2];
	pid_t cpid;
	char buf;
	if(argc != 2)
	{	fprintf(stderr, "Usage: %s <string>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if(pipe(pipefd) == -1)
	{	perror("pipe");
		exit(EXIT_FAILURE);
	}
	cpid = fork();
	if(cpid == -1)
	{	perror("fork");
		exit(EXIT_FAILURE);
	}
	if(cpid == 0)
		/* Child reads from pipe */
	{	close(pipefd[1]);          /* Close unused write end */
		while(read(pipefd[0], &buf, 1) > 0)
		{	write(STDOUT_FILENO, &buf, 1);
		}
		write(STDOUT_FILENO, "\n", 1);
		close(pipefd[0]);
		_exit(EXIT_SUCCESS);
	}
	else
		/* Parent writes argv[1] to pipe */
	{	close(pipefd[0]);          /* Close unused read end */
		write(pipefd[1], argv[1], strlen(argv[1]));
		close(pipefd[1]);          /* Reader will see EOF */
		wait(NULL);                /* Wait for child */
		exit(EXIT_SUCCESS);
	}
}



#endif