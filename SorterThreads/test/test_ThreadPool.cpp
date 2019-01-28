// test_ThreadPool.cpp 
// Created by Robin Rowe 2019-01-27
// License MIT MIT open source

#include <iostream>
#include "../ThreadPool.h"
using namespace std;

int main(int argc,char* argv[])
{	cout << "Testing ThreadPool" << endl;
	unsigned threadCount = 4;
	ThreadPool threadpool(threadCount);
	if(!threadpool)
	{	cout << "ThreadPool failed, operator! == true" << endl;
		return 1;
	}
	cout << threadpool << endl << "Done!" << endl;
	return 0;
}
