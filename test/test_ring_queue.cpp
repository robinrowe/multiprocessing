// test_queue.cpp

#include <iostream>
#include <sstream>
#include "RingQueue.h"
using namespace std;

// #define USE_CIN

template <typename T,int capacity>
void Dump(const RingQueue<T,capacity>& q)
{	cout << q 
		<< "(count = " << q.Count() 
		<< ", head = " << q.Head() 
		<< ", tail = "<< q.Tail() << ")" << endl;
}

int main()
{	const int size = 3;
	const int init = -1;
	RingQueue<int,size> q;
	q.Clear(init);
#ifdef USE_CIN
	istream& is(cin);
	cout << "Enter some integers (enter p to Pop, q to Quit):\n";
#else
//	const char* data = "1 2 3 4 5 p q";
	const char* data = "1 2 3 p p 4 5 p p 6 7 p p 8 9 q";
	cout << "Data: " << data << " (Capacity = " << q.Capacity() << ")" << endl;
	istringstream istr(data);
	istream& is(istr);
#endif
	Dump(q);
	string s;
	for(;;)
	{	is >> s;
		cout << s << ": ";
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
		Dump(q);
	}
	cout << endl << "Winding down... dequeue:";
	while(!q.IsEmpty())
	{	cout << ' ' << q.Front();
		q.Pop();
	}
	cout << endl;
	Dump(q);
	return 0;
}

/* output:

Data: 1 2 3 p p 4 5 p p 6 7 p p 8 9 q (Capacity = 3)
(count = 0, head = 0, tail = 0)
1: 1 (count = 1, head = 0, tail = 1)
2: 1 2 (count = 2, head = 0, tail = 2)
3: 1 2 3 (count = 3, head = 0, tail = 3)
p: 2 3 (count = 2, head = 1, tail = 3)
p: 3 (count = 1, head = 2, tail = 3)
4: 3 4 (count = 2, head = 2, tail = 0)
5: 3 4 5 (count = 3, head = 2, tail = 1)
p: 4 5 (count = 2, head = 3, tail = 1)
p: 5 (count = 1, head = 0, tail = 1)
6: 5 6 (count = 2, head = 0, tail = 2)
7: 5 6 7 (count = 3, head = 0, tail = 3)
p: 6 7 (count = 2, head = 1, tail = 3)
p: 7 (count = 1, head = 2, tail = 3)
8: 7 8 (count = 2, head = 2, tail = 0)
9: 7 8 9 (count = 3, head = 2, tail = 1)
q:
Winding down... dequeue: 7 8 9
(count = 0, head = 1, tail = 1)

*/