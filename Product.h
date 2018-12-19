// Product.h
// Copyright 2018/11/6 Robin.Rowe@CinePaint.org
// License open source MIT

#ifndef Product_h
#define Product_h

#include <string>

static const char* memName = "mem1234";
static const int semKey = 1234;// must not be same as memName, global namespace
static const int queueSize = 5;

struct Product
{	unsigned id;
	double number;
	Product(unsigned id,double number)
	:	id(id)
	,	number(number)
	{}
	Product()
	:	id(0)
	,	number(0.)
	{}
	operator std::string() const
	{	std::string s(std::to_string(id));
		s += " ";
		s += std::to_string(number);
		return std::move(s);
	}
};

#if 0
std::ostream& operator<<(std::ostream& os,const Product& product)
{	os << product.id << " " << product.number;
	return os;
}
#endif
#endif
