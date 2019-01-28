// test_SortItem.cpp 
// Created by Robin Rowe 2019-01-27
// License MIT MIT open source

#include <iostream>
#include "../SortItem.h"
using namespace std;

int main(int argc,char* argv[])
{	cout << "Testing SortItem" << endl;
	SortItem sortitem;
	if(!sortitem)
	{	cout << "SortItem failed, operator! == true" << endl;
		return 1;
	}
	cout << sortitem << endl << "Done!" << endl;
	return 0;
}
