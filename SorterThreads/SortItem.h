// SortItem.h 
// Created by Robin Rowe 2019-01-27
// License MIT open source

#ifndef SortItem_h
#define SortItem_h

#include <iostream>
#include <string_view>
#include <string.h>

class SortItem
{	SortItem(const SortItem&) = delete;
	void operator=(const SortItem&) = delete;
	static const unsigned bufsize = 100 + 1;
public:
//	Data: 15423123 931234 1
	const char* from;
	const char* to;
	std::ostream& Print(std::ostream& os) const;
	~SortItem()
	{}
	SortItem(const char* from,const char* to)
	:	from(from)
	,	to(to)
	{	if(!to || !from || to<from)
		{	Zero();
	}	}
	void Zero()
	{	to = 0;
		from = 0;
	}
	size_t Length() const
	{	if(!*this)
		{	return 0;
		}
		return to-from+1;
	}
	std::string_view GetNext()
	{	const char* space = (const char*) memchr(from,' ',Length());
		if(!space)
		{	std::string_view s(from,Length());
			Zero();
			return s;
		}
		std::string_view s(from,space-from);
		from = space;
	}
	bool SkipSpace()
	{	if(!*this)
		{	return false;
		}
		if(' ' == *from)
		{	from++;
			return true;
		}
		return false;
	}		
	bool operator!() const
	{	return !from;
	}
};

inline
std::ostream& operator<<(std::ostream& os,const SortItem& sortitem)
{	return sortitem.Print(os);
}

#endif
