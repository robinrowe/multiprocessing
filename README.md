# C++ Multiprocessing with Shared Memory
By Robin.Rowe@cinepaint.org

Producer-consumer is a popular architecture for building multiprocessing or multithreaded software. This implementation demonstrates multiprocessing, shared memory, memory pools, fixed-size queues and semaphores. 

The Producer produces a Product object that contains a sequential id (int) and and random floating point number (double) at intervals of between 0.5 and 1.5 seconds each. The Consumer consumes Products at random intervals between 1.0 and 3.0 seconds. It is just an example to demonstrate MP concepts.

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

Simply run test_consumer. It will spawn test_producer automatically. For Windows, you must change the #define PRODUCER path in test_consumer.cpp to match where you build the test_producer executable. The Linux path should just work, spawns ./test_producer.

## System APIs Utilized

- System V
- POSIX BSD 
- Windows

## Single Codebase Design Using Cmake

- Windows
- Linux
- MacOS (untested)
- Solaris (untested)

## C++ Classes

1. SharedMemory classes encapsulate Windows, BSD and System V shared memory APIs
2. MemoryPool class is base class of SharedMemory
3. Semaphore class encapsulates Windows, BSD and System V APIs
4. RingQueue template is a fixed-size nothrow queue class inspired by std::queue
5. Product class contains a serial id and a floating point number
6. test/Producer class implements producer logic
7. test/Consumer class implements consumer logic

## Design

Shared memory has yet to be standardized in C++, althougth WG21 SC22 is considering std::memory_mappable and std::mapped_region:

http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2044.html

And Boost offers boost::interprocess:

https://www.boost.org/doc/libs/1_54_0/doc/html/interprocess/sharedmemorybetweenprocesses.html

Because it's not standard, not using either of those. Created class SharedMemory instead. Using placement operator new() to put RingQueue in shared memory. RingQueue running in a single producer-consumer shared memory configuration is designed to be lockfree, but hasn't been tested for that. The purpose of the semaphore is to wake.

C++ offers std::mutux for multi-threaded applications, but to work across processes encapsulated OS-specific semaphore API instead.

[Requirements Document](docs/Requirements.md)
