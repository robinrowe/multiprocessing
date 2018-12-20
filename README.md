# C++ Multiprocessing with Shared Memory
By Robin.Rowe@cinepaint.org

A producer/consumer architecture is the standard approach for building multiprocessing or multithreaded software. This example code demonstrates multiprocessing, shared memory, atomics, memory pools, fixed-size queues and semaphores. 

The Producer produces a Product object that contains a sequential id (int) and and random floating point number (double) at intervals of between 0.5 and 1.5 seconds. each. The Consumer consumes Products at random intervals between 1.0 and 3.0 seconds.

## Build

Win64:

    cmake .. -A x64

Linux:

    cmake -DCMAKE_BUILD_TYPE=Debug ..

If you want to run in debugger.

    cmake -DMEM_SYS_V ..

Builds with BSD shared memory by default. If you prefer System V, define MEM_SYS_V.

    ulimit -c unlimited

FYI, how to enable core dumps in Linux bash, if you need.

## Running

Simply run test_consumer. It will spawn test_producer automatically. For Windows, you must change the #define PRODUCER path in test_consumer.cpp to match where you build executable. The Linux build should just work, spawns ./test_producer.

## System APIs Utilized

- System V
- POSIX BSD 
- Windows

## Single Codebase Using Cmake

- Windows
- Linux
- MacOS (untested)
- Solaris (untested)

## C++ Classes

1. SharedMemory class encapsulates Windows, BSD and System V shared memory APIs
1. MemoryPool class is base class of SharedMemory
1. Semaphore class encapsulates Windows and System V APIs
1. RingQueue template is an atomic fixed-size nothrow queue class inspired by std::queue
1. Product class contains a serial id and a floating point number

## Design

Shared memory has yet to be standardized in C++, althougth WG21 SC22 is considering std::memory_mappable and std::mapped_region:

http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2044.html

And Boost offers boost::interprocess:

https://www.boost.org/doc/libs/1_54_0/doc/html/interprocess/sharedmemorybetweenprocesses.html

Because not standard, not using either of those. Created class SharedMemory instead.

C++ offers std::mutux. In order to play with System V (and Windows) APIs, I used those instead. However, because my RingQueue design uses std::atomic, the Semaphore seems unnecessary and has been disabled. In a more typical scenario there would be two semaphores, one to protect the queue from races, the other to wake the consumer process/thread.

Using placement operator new() to put RingQueue in shared memory. 

Using atomic to make RingQueue lockfree. However, it isn't designed to be safe for multiple concurrent consumers.

[Requirements Document](docs/Requirements.md)
