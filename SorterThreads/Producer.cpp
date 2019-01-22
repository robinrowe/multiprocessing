// Producer.cpp
// Created by Robin Rowe 2019-01-22
// License MIT open source

#include "Producer.h"

bool Producer::OpenSorter(const char* sorter)
{	for(unsigned i = 1;i<sorters.size();i++)
	{	if(sorters[i] == sorter)
		{	this->sorter = i;
			return true;
	}	}
	return false;
}

int Producer::Run()
{
	return -1;
}

void Producer::Print() const
{	printf("%s %s%s",input.c_str(),output.c_str(),sorters[sorter].c_str());
}
