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
	string s = sorter.Read(is);
	if(is.bad())
	{	cout << "Can't read file " << input << endl;
		return false;
	}
	char* data = (char*) s.c_str();
	size_t size = s.size();
	while(size)
	{	Task task(sorter,data,size);
		threadPool.Run(task);
		size -= task.Size();
	}
	return true;
}

std::ostream& Producer::Print(std::ostream& os) const
{	return os << input << " => " << output << ", " << sorter << endl;
}
