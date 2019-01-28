// test_Task.cpp 
// Created by Robin Rowe 2019-01-27
// License MIT MIT open source

#include <iostream>
#include "../Task.h"
using namespace std;

int main(int argc,char* argv[])
{	cout << "Testing Task" << endl;
	Task task;
	if(!task)
	{	cout << "Task failed, operator! == true" << endl;
		return 1;
	}
	cout << task << endl << "Done!" << endl;
	return 0;
}
