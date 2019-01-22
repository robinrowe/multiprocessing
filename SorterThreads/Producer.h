// Producer.h 
// Created by Robin Rowe 2019-01-22
// License MIT open source

#ifndef Producer_h
#define Producer_h

#include <fstream>
#include <string>
#include <vector>

class Producer
{	Producer(const Producer&) = delete;
	void operator=(const Producer&) = delete;
	std::ifstream is;
	std::ofstream os;
	std::string input;
	std::string output;
	int sorter;
	std::vector<std::string> sorters;
	enum
	{	none,
		bubble,
		merge,
		highlow
	};
public:
	bool OpenSorter(const char* sorter);
	int Run();	
	void Print() const;
	~Producer()
	{}
	Producer()
	:	sorter(-1)
	,	sorters(4)
	{	sorters.assign(std::initializer_list<std::string>({ "","bubble","merge","highlow"}));
	}
	bool operator!() const
	{	return !sorter;
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
};

#endif
