/*
The following is the code for the child process. It uses the inherited handles for STDIN and STDOUT to access the pipe created by the parent. The parent process reads from its input file and writes the information to a pipe. The child receives text through the pipe using STDIN and writes to the pipe using STDOUT. The parent reads from the read end of the pipe and displays the information to its STDOUT.
*/

#include <windows.h>
#include <stdio.h>

#define BUFSIZE 4096

int main(void)
{	CHAR chBuf[BUFSIZE];
	DWORD dwRead, dwWritten;
	HANDLE hStdin, hStdout;
	BOOL bSuccess;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if(
	    (hStdout == INVALID_HANDLE_VALUE) ||
	    (hStdin == INVALID_HANDLE_VALUE)
	)
	{	ExitProcess(1);
	}
	// Send something to this process's stdout using printf.
	printf("\n ** This is a message from the child process. ** \n");
	// This simple algorithm uses the existence of the pipes to control execution.
	// It relies on the pipe buffers to ensure that no data is lost.
	// Larger applications would use more advanced process control.
	for(;;)
	{	// Read from standard input and stop on error or no data.
		bSuccess = ReadFile(hStdin, chBuf, BUFSIZE, &dwRead, NULL);
		if(! bSuccess || dwRead == 0)
		{	break;
		}
		// Write to standard output and stop on error.
		bSuccess = WriteFile(hStdout, chBuf, dwRead, &dwWritten, NULL);
		if(! bSuccess)
		{	break;
		}
	}
	return 0;
}



