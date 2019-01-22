// Consumer.h 
// Created by Robin Rowe 2019-01-22
// License MIT open source

#ifndef Consumer_h
#define Consumer_h

class Consumer
{	Consumer(const Consumer&) = delete;
	void operator=(const Consumer&) = delete;

public:
	~Consumer()
	{}
	Consumer()
	{}
	bool operator!() const
	{	return true;
	}
	
	void Print() const
	{}
};

#endif
