// test_queue.cpp

#include <iostream>
#include <queue>
#include "RingQueue.h"
using namespace std;

//#define STD_QUEUE
#define RING_QUEUE

int main()
{	int myint;
#ifdef STD_QUEUE	
	queue<int> myqueue;
	cout << "Enter some integers (enter 0 to end):\n";
	do
	{	cin >> myint;
		myqueue.push(myint);
	}
	while(myint);
	cout << "queue contains: ";
	while(!myqueue.empty())
	{	cout << ' ' << myqueue.front();
		myqueue.pop();
	}
	cout << endl;
#endif
#ifdef RING_QUEUE
	RingQueue<int,5,-1> queue;
	queue.Clear();
	cout << "Enter some integers (enter 0 to end):\n";
	do
	{	cin >> myint;
		queue.Push(myint);
	}
	while(myint);
	cout << "queue contains (" << queue.Count() 
		<< ",max " << queue.Capacity()<<"): ";
	while(!queue.IsEmpty())
	{	cout << ' ' << queue.Front();
		queue.Pop();
	}
	cout << endl;
#endif
	return 0;
}

