// Producer.h
// Copyright 2018/11/6 Robin.Rowe@CinePaint.org
// License open source MIT

#ifndef Producer_h
#define Producer_h

#include <random>
#include <iostream>
#include <thread>
#include <chrono>
#include "RingQueue.h"
#include "SharedMemory.h"
#include "Semaphore.h"
#include "Product.h"

class Producer
{	unsigned count;
    std::random_device rd;  
    std::mt19937 gen; 
    std::uniform_real_distribution<> dis;
	int pid;
	IPC::SharedMemory memory;
	RingQueue<Product,queueSize>* queue;
	IPC::Semaphore sem;
	const unsigned maxCount;
public:
	Producer(unsigned maxCount)
	:	count(0)
	,	gen(rd()) 
    ,	dis(0.5,1.5)
	,	pid(0)
	,	queue(0)
	,	memory(memName,true)
	,	maxCount(maxCount)
	{}
	Product Generate()
	{	count++;
		return Product(count,dis(gen));
	}
	bool CreateSharedMemory()
	{	queue = new (memory) RingQueue<Product,queueSize>;
		if(!queue)
		{	return false;
		}
		return true;
	}
	bool CreateSemaphore()
	{	return sem.Create(semKey);
	}
	void Run()
	{	std::string s;
		for(unsigned i = 0;i<maxCount;i++)
		{	Product product = Generate();
			if(0 == (product.id % 19))// 1 in 20 per spec. Or, 13? Or, uniform_int_distribution? 
			{	s = "Producer: IGNORING <";
				s += std::to_string(product.id);
				s += ">";
				puts(s.c_str());
				continue;
			}
			std::string s = product;
			s.insert(0,"Producer: ");
			puts(s.c_str());
			{	IPC::Lock lock(sem);
				if(!queue->Push(product))
				{	s = "Producer: DROPPED <";
					s += std::to_string(product.id);
					s += ">";
					puts(s.c_str());
			}	} 
			using namespace std::chrono_literals;
			std::this_thread::sleep_for(2s);
	}	}
};

#endif