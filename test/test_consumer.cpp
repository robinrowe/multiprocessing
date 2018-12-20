// test/test_consumer.cpp
// Copyright 2018/11/6 Robin.Rowe@CinePaint.org
// License open source MIT

#include "Consumer.h"

enum 
{	ok,
	usage,
	shared_memory_failed,
	spawn_failed,
	semaphore_failed,
	child_failed
};

#define exit_msg(i) puts(#i); return i

#ifdef _WIN32
#define PRODUCER "/code/github/multiprocessing/build-win64/Debug/test_producer.exe"
#else
//#define PRODUCER "/media/sf_code/github/multiprocessing/build-linux/test_producer"
#define PRODUCER "./test_producer"
#endif


int main()
{	puts("Consumer: launched");
	Consumer consumer;
	if(!consumer.Spawn(PRODUCER))
	{	return exit_msg(spawn_failed);
	}
	if(!consumer.OpenSharedMemory())
	{	return exit_msg(shared_memory_failed);
	}
	if(!consumer.OpenSemaphore())
	{	return exit_msg(semaphore_failed);
	}
	consumer.Run();
	puts("Consumer: done");
	return ok;
}

/* Consumer Example Output

1 0.4395116517359974
2 0.07296093346964816
3 0.23989517451159492
4 0.9214004505330191
5 0.23692077473430806
6 0.5565227807496207
7 0.3635783890022559
8 0.0
9 0.8505558785920253
10 0.10421790588732671
11 0.0
12 0.3159450030396609
13 0.0
14 0.8564636018393292
15 0.010106680565449055

*/

/* Real output:

Consumer: launched
Producer: launched
Producer: 1 1.479144
Producer: 2 0.957892
Consumer: 0.0
Consumer: 2 0.957892
Producer: 3 1.461817
Consumer: 3 1.461817
Producer: 4 1.257796
Consumer: 4 1.257796
Producer: 5 0.767268
Consumer: 5 0.767268
Producer: 6 0.793101
Consumer: 6 0.793101
Producer: 7 0.520554
Consumer: 7 0.520554
Producer: 8 1.034704
Consumer: 8 1.034704
Producer: 9 1.191231
Consumer: 9 1.191231
Producer: 10 0.751919
Consumer: 10 0.751919
Producer: 11 0.983479
Consumer: 11 0.983479
Producer: 12 1.419414
Consumer: 12 1.419414
Producer: 13 0.525216
Consumer: 13 0.525216
Producer: 14 0.619666
Consumer: 14 0.619666
Producer: 15 0.897806
Consumer: 15 0.897806
Producer: 16 0.929980
Consumer: 16 0.929980
Producer: 17 0.838533
Consumer: 17 0.838533
Producer: 18 1.305833
Consumer: 18 1.305833
Producer: IGNORING <19>
Producer: 20 0.680971
Consumer: 0.0
Consumer: 20 0.680971
Producer: 21 0.863871
Consumer: 21 0.863871
Producer: 22 0.760846
Consumer: 22 0.760846
Producer: 23 1.433420
Consumer: 23 1.433420
Producer: 24 1.345077
Consumer: 24 1.345077
Producer: 25 1.275804
Consumer: 25 1.275804
Producer: 26 0.982319
Consumer: 26 0.982319
Producer: 27 1.409068
Consumer: 27 1.409068
Producer: 28 0.716296
Consumer: 28 0.716296
Producer: 29 0.904948
Consumer: 29 0.904948
Producer: 30 0.704989
Consumer: 30 0.704989
Producer: 31 0.766488
Consumer: 31 0.766488
Producer: 32 0.627995
Consumer: 32 0.627995
Producer: 33 1.126528
Consumer: 33 1.126528
Producer: 34 1.277158
Consumer: 34 1.277158
Producer: 35 0.860109
Consumer: 35 0.860109
Producer: 36 0.653038
Consumer: 36 0.653038
Producer: 37 1.071831
Consumer: 37 1.071831
Producer: IGNORING <38>
Producer: 39 0.922652
Consumer: 0.0
Consumer: 39 0.922652
Producer: 40 0.631330
Consumer: 40 0.631330
Producer: 41 0.745618
Consumer: 41 0.745618
Producer: 42 0.746943
Consumer: 42 0.746943
Producer: 43 0.632180
Consumer: 43 0.632180
Producer: 44 0.599308
Consumer: 44 0.599308
Producer: 45 1.477474
Consumer: 45 1.477474
Producer: 46 1.128295
Consumer: 46 1.128295
Producer: 47 0.502434
Consumer: 47 0.502434
Producer: 48 0.707410
Consumer: 48 0.707410
Producer: 49 1.354145
Consumer: 49 1.354145
Producer: 50 1.315409
Consumer: 50 1.315409
Producer: 51 1.386386
Consumer: 51 1.386386
Producer: 52 0.879381
Consumer: 52 0.879381
Producer: 53 0.890149
Consumer: 53 0.890149
Producer: 54 1.303770
Consumer: 54 1.303770
Producer: 55 0.913031
Consumer: 55 0.913031
Producer: 56 0.872106
Consumer: 56 0.872106
Producer: IGNORING <57>
Producer: 58 0.963864
Consumer: 0.0
Consumer: 58 0.963864
Producer: 59 1.167702
Consumer: 59 1.167702
Producer: 60 1.283995
Consumer: 60 1.283995
Producer: 61 0.744358
Consumer: 61 0.744358
Producer: 62 1.441839
Consumer: 62 1.441839
Producer: 63 0.948155
Consumer: 63 0.948155
Producer: 64 1.200732
Consumer: 64 1.200732
Producer: 65 1.239065
Consumer: 65 1.239065
Producer: 66 1.186745
Consumer: 66 1.186745
Producer: 67 0.982233
Consumer: 67 0.982233
Producer: 68 1.039823
Consumer: 68 1.039823
Producer: 69 1.241123
Consumer: 69 1.241123
Producer: 70 0.936888
Consumer: 70 0.936888
Producer: 71 0.668365
Consumer: 71 0.668365
Producer: 72 1.235543
Consumer: 72 1.235543
Producer: 73 1.085028
Consumer: 73 1.085028
Producer: 74 0.643240
Consumer: 74 0.643240
Producer: 75 1.401156
Consumer: 75 1.401156
Producer: IGNORING <76>
Producer: 77 1.025361
Consumer: 0.0
Consumer: 77 1.025361
Producer: 78 1.037398
Consumer: 78 1.037398
Producer: 79 1.103690
Consumer: 79 1.103690
Producer: 80 0.632831
Consumer: 80 0.632831
Producer: 81 1.408440
Consumer: 81 1.408440
Producer: 82 0.572920
Consumer: 82 0.572920
Producer: 83 0.696044
Consumer: 83 0.696044
Producer: 84 1.287276
Consumer: 84 1.287276
Producer: 85 0.642252
Consumer: 85 0.642252
Producer: 86 1.238360
Consumer: 86 1.238360
Producer: 87 0.880945
Consumer: 87 0.880945
Producer: 88 0.687861
Consumer: 88 0.687861
Producer: 89 1.020582
Consumer: 89 1.020582
Producer: 90 1.145725
Consumer: 90 1.145725
Producer: 91 1.038906
Consumer: 91 1.038906
Producer: 92 1.116036
Consumer: 92 1.116036
Producer: 93 0.792131
Consumer: 93 0.792131
Producer: 94 1.063952
Consumer: 94 1.063952
Producer: IGNORING <95>
Producer: 96 1.481120
Consumer: 0.0
Consumer: 96 1.481120
Producer: 97 0.607913
Consumer: 97 0.607913
Producer: 98 0.935075
Consumer: 98 0.935075
Producer: 99 1.385912
Consumer: 99 1.385912
Producer: 100 1.283981
Consumer: 100 1.283981
Producer: done
Consumer: Producer quit
Consumer: done

*/