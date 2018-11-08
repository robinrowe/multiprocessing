// test_queue.cpp

#include <iostream>
#include <queue>
#include "RingQueue.h"

int main()
{	std::queue<int> myqueue;
	int myint;
	std::cout << "Enter some integers (enter 0 to end):\n";
	do
	{	std::cin >> myint;
		myqueue.push(myint);
	}
	while(myint);
	std::cout << "queue contains: ";
	while(!myqueue.empty())
	{	std::cout << ' ' << myqueue.front();
		myqueue.pop();
	}
	std::cout << '\n';

	RingQueue<int,5> fqueue;
	std::cout << "Enter some integers (enter 0 to end):\n";
	do
	{	std::cin >> myint;
		fqueue.Push(myint);
	}
	while(myint);
	std::cout << "queue contains: ";
	while(!myqueue.empty())
	{	std::cout << ' ' << myqueue.front();
		fqueue.Pop();
	}
	std::cout << '\n';

	return 0;
}

