// Consumer.h
// Copyright 2018/11/6 Robin.Rowe@CinePaint.org
// License open source MIT

#ifndef Consumer_h
#define Consumer_h

#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include "RingQueue.h"
#include "SharedMemory.h"
#include "Semaphore.h"
#include "Product.h"
#include "Launcher.h"

class Consumer
{	unsigned count;
    std::random_device rd;  
    std::mt19937 gen; 
    std::uniform_real_distribution<> dist;
	volatile bool isGo;
	Launcher launcher;
	IPC::SharedMemory memory;
	RingQueue<Product,queueSize>* queue;
	IPC::Semaphore sem;
public:
	Consumer()
	:	count(0)
	,	gen(rd()) 
    ,	dist(1.,3.)
	,	isGo(true)
	,	memory(memName,false)
	,	queue(0)
	{}
	void Sleep()
	{	using Delay = std::chrono::duration<double,std::milli>;
		std::this_thread::sleep_for(Delay(dist(gen)));
	}
	bool SpawnProducer()
	{	const char* childProgramName = "/code/github/multiprocessing/build/Debug/producer.exe";
		if(!launcher.Spawn(childProgramName))
		{	return false;
		}
		// Give producer time for creating shared resources
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(2s);
		std::thread check(WaitForProducer,this);
		check.detach();
		return true;
	}
	static void WaitForProducer(void* p)
	{	Consumer* self = (Consumer*) p;
		self->StopWithProducer();
	}
	bool OpenSharedMemory()
	{	queue = new (memory) RingQueue<Product,queueSize>;
		if(!queue)
		{	return false;
		}
		return true;
	}
	bool OpenSemaphore()
	{	return sem.Open(semKey);
	}
	void StopWithProducer()
	{	launcher.WaitChild();
		puts("Consumer: Producer quit");
		isGo = false;
	}
	bool IsGo() const
	{	return isGo;
	}
	void Run()
	{	unsigned id = 0;
		Product product;
		while(IsGo() || !queue->IsEmpty())
		{	{	IPC::Lock lock(sem);
				if(queue->IsEmpty())
				{	Sleep();
					continue;
				}
				product = queue->Front();	
				queue->Pop();
			}
			for(unsigned i=id+1;i<product.id;i++)
			{	puts("Consumer: 0.0");
			}
			std::string s = product;
			s.insert(0,"Consumer: ");
			puts(s.c_str());
			id = product.id;
	}	}
};

#endif