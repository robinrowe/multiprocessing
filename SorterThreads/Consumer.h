// Consumer.h 
// Created by Robin Rowe 2019-01-26
// License MIT open source

#ifndef Consumer_h
#define Consumer_h

#include <iostream>

class Consumer
{	Consumer(const Consumer&) = delete;
	void operator=(const Consumer&) = delete;

public:
	std::ostream& Print(std::ostream& os) const;
	~Consumer()
	{}
	Consumer()
	{}
	bool operator!() const
	{	return true;
	}
};

inline
std::ostream& operator<<(std::ostream& os,const Consumer& consumer)
{	return consumer.Print(os);
}

#endif
