// Consumer.cpp
// Copyright 2018/11/6 Robin.Rowe@CinePaint.org
// License open source MIT

#include <iostream>
#include <random>
#include <thread>
#include "RingQueue.h"
#include "SharedMemory.h"
#include "Semaphore.h"
#include "Product.h"
#include "Launcher.h"
using namespace std;

// #define USE_SEMAPHORE

class Consumer
{	unsigned count;
    std::random_device rd;  
    std::mt19937 gen; 
    std::uniform_real_distribution<> dist;
public:
	Consumer()
	:	count(0)
	,	gen(rd()) 
    ,	dist(1.,3.)
	{}
	void Sleep()
	{	using Delay = std::chrono::duration<double,std::milli>;
		std::this_thread::sleep_for(Delay(dist(gen)));
	}
};

int main()
{	cout << "Consumer..." << endl;
	IPC::SharedMemory memory(memName,false);
	RingQueue<Product,5>* queue = new (memory) RingQueue<Product,5>;
	if(!queue)
	{	cout << "Shared memory failed!" << endl;
		return 1;
	}
	IPC::Semaphore sem;
	if(!sem.Open(semKey))
	{	cout << "Semaphore failed!" << endl;
		return 2;
	}
	Consumer consumer;
	unsigned id = 0;
	queue->SetConsumer();
	Launcher launcher;
	const char* childProgramName = "";
	if(!launcher.Spawn(childProgramName))
	{	cout << "Spawn failed!" << endl;
		return 3;
	}
	while(sem.Lock() || !queue->IsEmpty())
	{	sem.Unlock();
		consumer.Sleep();
#ifdef USE_SEMAPHORE
		IPC::Lock lock(sem);
#endif
		if(queue->IsEmpty())
		{	continue;
		}
		Product product = queue->Front();	
		queue->Pop();
		if(0!=id && product.id != id+1)
		{	cout << "0.0" << endl;
		}
		else
		{	cout << product << endl;
		}
		id = product.id;
	}
	launcher.WaitChild();
	cout << "Done!" << endl;
	return 0;
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

