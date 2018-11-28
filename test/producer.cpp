// producer.cpp
// Copyright 2018/11/6 Robin.Rowe@CinePaint.org
// License open source MIT

#include <random>
#include <iostream>
#include <thread>
#include "RingQueue.h"
#include "SharedMemory.h"
#ifdef SEMAPHORE
#include "Semaphore.h"
#endif
#include "Product.h"
using namespace std;

class Producer
{	unsigned count;
    std::random_device rd;  
    std::mt19937 gen; 
    std::uniform_real_distribution<> dis;
public:
	Producer()
	:	count(0)
	,	gen(rd()) 
    ,	dis(0.5,1.5)
	{}
	Product Generate()
	{	count++;
		return Product(count,dis(gen));
	}
};

int main()
{	cout << "Producer..." << endl;
	IPC::SharedMemory memory(memName,true);
	RingQueue<Product,5>* queue = new (memory) RingQueue<Product,5>;
	if(!queue)
	{	cout << "Shared memory failed!" << endl;
		return 1;
	}
#ifdef SEMAPHORE
	IPC::Semaphore sem;
	if(!sem.Open(semKey))
	{	cout << "Semaphore failed!" << endl;
		return 2;
	}
#endif
	Producer producer;
	for(unsigned i = 0;i<100;i++)
	{	Product product = producer.Generate();
		if(product.id % 19)// 1 in 20 per spec. Or, 13? Or, uniform_int_distribution? 
		{	cout << "IGNORING <" << product.id << ">" << endl;
			continue;
		}
		cout << product << endl;
		{	
#ifdef SEMAPHORE
			IPC::Lock lock(sem);
#endif
			if(!queue->Push(product))
			{	cout << "DROPPED <" << product.id << ">" << endl;
		}	} 
		std::this_thread::sleep_for(2s);
	}
	queue->Set(false);
	cout << "Done!" << endl;
	return 0;
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
