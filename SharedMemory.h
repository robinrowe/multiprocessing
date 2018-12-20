// SharedMemory.h
// Copyright 2018/11/2 Robin.Rowe@CinePaint.org
// License open source MIT

#ifdef _WIN32

#include "windows/SharedMemoryWin.h"
namespace IPC
{	typedef SharedMemoryWin SharedMemory;
}

#else

#ifdef MEM_SYS_V
#include "unix/SharedMemorySysV.h"
namespace IPC
{	typedef SharedMemorySysV SharedMemory;
}
#else
#include "unix/SharedMemoryBSD.h"
namespace IPC
{	typedef SharedMemoryBSD SharedMemory;
}
#endif
#endif
