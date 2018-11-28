// test_queue.cpp

#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

template <typename T>
ostream& operator<<(ostream& os,const deque<T>& q)
{	auto print = [&](const T& n)
	{	os << n << " ";
	};
	for_each(q.begin(),q.end(),print);
	return os;
}

int main()
{	deque<int> q;
	cout << "Enter some integers (enter 0 to pop, -1 to end):\n";
	int x = 0;	
	do
	{	cin >> x;
		if(!x)
		{	q.pop_front();
		}
		else
		{	q.push_back(x);
		}
		cout << q << endl;
	}
	while(x != -1);
	cout << "Winding down... dequeue: ";
	while(!q.empty())
	{	cout << ' ' << q.front();
		q.pop_front();
	}
	cout << endl;
	return 0;
}

