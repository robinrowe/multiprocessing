// test_queue.cpp

#include <iostream>
#include <sstream>
#include "RingQueue.h"
using namespace std;

// #define USE_CIN

int main()
{	const int size = 5;
	const int init = -1;
	RingQueue<int,size> q;
	q.Clear(init);
#ifdef USE_CIN
	istream& is(cin);
	cout << "Enter some integers (enter 0 to end):\n";
#else
	const char* data = "1 2 3 4 5 p q";
	cout << "Data: " << data << endl;
	istringstream istr(data);
	istream& is(istr);
#endif
	string s;
	for(;;)
	{	is >> s;
		if(is.fail() || s[0]=='q')// quit
		{	break;
		}
		if(s[0]=='p')// pop
		{	q.Pop();
		}
		else
		{	const int x = atoi(s.c_str());// push 0 on fail
			q.Push(x);
		}
		cout << q << endl;
	}
	cout << "Winding down... dequeue: ";
	while(!q.IsEmpty())
	{	cout << ' ' << q.Front();
		q.Pop();
	}
	cout << endl;
	return 0;
}

