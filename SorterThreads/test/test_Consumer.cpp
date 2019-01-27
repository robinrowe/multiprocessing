// test_Consumer.cpp 
// Created by Robin Rowe 2019-01-26
// License MIT MIT open source

#include <iostream>
#include "../Consumer.h"
using namespace std;

int main(int argc,char* argv[])
{	cout << "Testing Consumer" << endl;
	Consumer consumer;
	if(!consumer)
	{	cout << "Consumer failed, operator! == true" << endl;
		return 1;
	}
	cout << consumer << endl << "Done!" << endl;
	return 0;
}
