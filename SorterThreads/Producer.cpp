// Producer.cpp
// Created by Robin Rowe 2019-01-22
// License MIT open source

#include "Producer.h"
#include "SortItem.h"
using namespace std;

bool Producer::Run()
{	if(!*this)
	{	return false;
	}
	SortItem item;
	while(is.good())
	{	is.getline(&item.line[0],item.line.size());
		if(is.bad())
		{	cout << "Error reading " << input << endl;
			return false;
		}
//		do
	//	{	
 // os.bad())
	}
	return true;
}

std::ostream& Producer::Print(std::ostream& os) const
{	return os << input << " => " << output << ", " << sorter << endl;
}
