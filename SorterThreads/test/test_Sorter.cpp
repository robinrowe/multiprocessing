// test_Sorter.cpp 
// Created by Robin Rowe 2019-01-26
// License MIT MIT open source

#include <iostream>
#include "../Sorter.h"
using namespace std;

int main(int argc,char* argv[])
{	cout << "Testing Sorter" << endl;
	Sorter sorter;
	if(!sorter)
	{	cout << "Sorter failed, operator! == true" << endl;
		return 1;
	}
	cout << sorter << endl << "Done!" << endl;
	return 0;
}
