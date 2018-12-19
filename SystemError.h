// SystemError.h
// 2018/12/18 Copyright Robin.Rowe@Cinepaint.org
// License MIT open source

#ifndef SystemError_h
#define SystemError_h

#ifdef _WIN32

#include <Windows.h>
#include <stdio.h>

inline
void PrintSystemError(const char* msg)
{	DWORD e = GetLastError();
	if(!e)
	{	perror(msg);
		return;
	}
	const int bufsize = 120;
	char buffer[bufsize];	
	const DWORD num = FormatMessageA(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		0,
		buffer,
		bufsize-1,
		NULL);
		printf("Error %s (%s)\n",msg,buffer);
}

#else

inline
void PrintSystemError(const char* msg)
{	perror(msg);
}

#endif

#endif