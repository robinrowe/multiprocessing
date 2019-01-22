// Sorter.h 
// Created by Robin Rowe 2019-01-22
// License MIT open source

#ifndef Sorter_h
#define Sorter_h

class Sorter
{	Sorter(const Sorter&) = delete;
	void operator=(const Sorter&) = delete;

public:
	~Sorter()
	{}
	Sorter()
	{}
	bool operator!() const
	{	return true;
	}
	
	void Print() const
	{}
};

#endif
