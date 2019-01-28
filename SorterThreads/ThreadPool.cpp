// ThreadPool.cpp
// Created by Robin Rowe 2019-01-27
// License MIT open source

#include "ThreadPool.h"
using namespace std;

volatile bool ThreadPool::isWake;
volatile bool ThreadPool::isGo;

ostream& ThreadPool::Print(ostream& os) const
{	return os << "ThreadPool";
} 

ThreadPool::ThreadPool(unsigned threadCount)
:	threads(threadCount)
{	unsigned i = 1;
	for(auto& t:threads)
	{	t = thread(Main,this,i++);
		t.detach();
}	}

void ThreadPool::Run(unsigned threadNo)
{	while(isGo)
    {   Lock lock(mPool);
		cv.wait(lock);
		if(!isWake)
		{	// spurious thread wake
			continue;
		}
		isWake=false;
		Task task;
		{	Lock lock(mQueue);
			if(tasks.empty())
			{	continue;
			}
			task = tasks.front();
			tasks.pop();
		}
		task.Run();
	}
	cout << "Exiting thread #" << threadNo << endl;
}
