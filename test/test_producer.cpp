// test/test_producer.cpp
// Copyright 2018/11/6 Robin.Rowe@CinePaint.org
// License open source MIT

#include "Producer.h"

enum 
{	ok,
	usage,
	shared_memory_failed,
	semaphore_failed
};

#define exit_msg(i) puts(#i); return i

int main()
{	puts("Producer: launched");
	const int maxCount = 10;//100
	Producer producer(maxCount);
	if(!producer.CreateSharedMemory())
	{	return exit_msg(shared_memory_failed);
	}
	if(!producer.CreateSemaphore())
	{	return exit_msg(semaphore_failed);
	}
	producer.Run();
	puts("Producer: done");
	return ok;
}

/* Producer Example Output

1 0.4395116517359974
2 0.07296093346964816
3 0.23989517451159492
4 0.9214004505330191
5 0.23692077473430806
6 0.5565227807496207
7 0.3635783890022559
9 0.8505558785920253
10 0.10421790588732671
12 0.3159450030396609
13 0.13638449049289925
DROPPED 13
14 0.8564636018393292
15 0.010106680565449055
*/
