// SharedMemory.h
// Copyright 2018/11/2 Robin.Rowe@CinePaint.org
// License open source MIT

#ifdef _WIN32
#include "SharedMemoryWin.h"
namespace IPC
{	typedef SharedMemoryWin SharedMemory;
}
#else
#ifdef MEM_SYS_V
#include "SharedMemorySysV.h"
namespace IPC
{	typedef SharedMemorySysV SharedMemory;
}
#else
#include "SharedMemoryBSD.h"
namespace IPC
{	typedef SharedMemoryBSD SharedMemory;
}
#endif
#endif
