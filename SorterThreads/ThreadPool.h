// ThreadPool.h 
// Created by Robin Rowe 2019-01-27
// License MIT open source

#ifndef ThreadPool_h
#define ThreadPool_h

#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Task.h"

class ThreadPool
{	ThreadPool(const ThreadPool&) = delete;
	void operator=(const ThreadPool&) = delete;
    typedef std::unique_lock<std::mutex> Lock;
    std::mutex mPool;
    std::mutex mQueue;
    std::condition_variable cv;
	std::vector<std::thread> threads;
	std::queue<Task> tasks;
	static volatile bool isWake;
	static volatile bool isGo;
	void Wait()
	{	Lock lock(mPool);
		auto f = []{return isWake;};
		cv.wait(lock,f);
	}
	void Wake()
	{	isWake = true;
		cv.notify_one();
	}
    static void Main(ThreadPool* self,unsigned threadNo)
    {   self->Run(threadNo);
    }
	void Run(unsigned threadNo);
public:
	std::ostream& Print(std::ostream& os) const;
	~ThreadPool()
	{}
	ThreadPool(unsigned threadCount);
	bool operator!() const
	{	return !threads.size();
	}
	void Run(const Task& t)
	{	tasks.push(t);
		Wake();
	}
    void Stop()
    {   isGo=false;
		cv.notify_all();
    }
};

inline
std::ostream& operator<<(std::ostream& os,const ThreadPool& threadpool)
{	return threadpool.Print(os);
}

#endif
