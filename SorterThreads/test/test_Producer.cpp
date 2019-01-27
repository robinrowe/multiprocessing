// test_Producer.cpp 
// Created by Robin Rowe 2019-01-26
// License MIT MIT open source

#include <iostream>
#include "../Producer.h"
using namespace std;

int main(int argc,char* argv[])
{	cout << "Testing Producer" << endl;
	Producer producer;
	if(!producer)
	{	cout << "Producer failed, operator! == true" << endl;
		return 1;
	}
	cout << producer << endl << "Done!" << endl;
	return 0;
}
