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

std::ostream& Producer::Print(std::ostream& os) const
{	return os << input << " " << output << sorters[sorter];
}
