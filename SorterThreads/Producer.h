// Producer.h 
// Created by Robin Rowe 2019-01-22
// License MIT open source

#ifndef Producer_h
#define Producer_h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Sorter.h"
#include "ThreadPool.h"

class Producer
{	Producer(const Producer&) = delete;
	void operator=(const Producer&) = delete;
	std::ifstream is;
	std::ofstream os;
	std::string input;
	std::string output;
	std::string algorithm;
	Sorter sorter;
	ThreadPool threadPool;
	static const unsigned threadCount = 4;
public:
	bool Run();	
	std::ostream& Print(std::ostream& os) const;
	~Producer()
	{}
	Producer()
	:	f(0)
	,	threadPool(threadCount)
	{}
	bool operator!() const
	{	return !output.size();
	}
	bool OpenInput(const char* filename)
	{	is.open(filename);
		if(!is.good())
		{	return false;
		}
		input = filename;
		return true;
	}
	bool OpenOutput(const char* filename)
	{	os.open(filename);
		if(!os.good())
		{	return false;
		}
		output = filename;
		return true;
	}
	bool OpenSorter(const char* algorithm)
	{	f = sorter.GetSorter(algorithm);
		if(!f)
		{	return false;
		}
		this->algorithm = algorithm;
		return true;
	}
};

inline
std::ostream& operator<<(std::ostream& os,const Producer& producer)
{	return producer.Print(os);
}

#endif
