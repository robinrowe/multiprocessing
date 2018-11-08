// Product.h
// Copyright 2018/11/6 Robin.Rowe@CinePaint.org
// License open source MIT

#ifndef Product_h
#define Product_h

#include <ostream>

static const char* memName = "1234";
static const int semKey = 1234;

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
};

std::ostream& operator<<(std::ostream& os,const Product& product)
{	os << product.id << " " << product.number;
	return os;
}

#endif
