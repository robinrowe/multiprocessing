// Consumer.cpp
// Copyright 2018/11/6 Robin.Rowe@CinePaint.org
// License open source MIT

#if 0
1. The consumer consumes numbered products 
1. The consumer consumes products at a slower rate than the producer
produces them, there may be multiple products produced before the consumer
consumes the task. 
1. Products are consumed at random intervals between 1.0 and 3.0 seconds
1. Products are printed to the screen
1. If a product number is skipped in sequence, the consumer outputs 0.0 for that sequence number

## Producer Example Output

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

## Consumer Example Output

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

#endif
int main()
{	return 0;
}

// producer.cpp
// Copyright 2018/11/6 Robin.Rowe@CinePaint.org
// License open source MIT

#include <random>
#include <iostream>
#include <thread>
#include "RingQueue.h"
#include "SharedMemory.h"
#include "Semaphore.h"
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
	for(unsigned i = 0;i<100;i++)
	{	Product product = producer.Generate();
		if(product.id % 19)// 1 in 20 per spec. Or, 13? Or, uniform_int_distribution? 
		{	cout << "IGNORING <" << product.id << ">" << endl;
			continue;
		}
		cout << product << endl;
		{	IPC::Lock lock(sem);
			if(!queue->Push(product))
			{	cout << "DROPPED <" << product.id << ">" << endl;
		}	} 
		std::this_thread::sleep_for(2s);
	}
	cout << "Done!" << endl;
	return 0;
}

/* Consumer Example Output

*/
