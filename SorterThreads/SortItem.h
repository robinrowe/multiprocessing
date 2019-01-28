// SortItem.h 
// Created by Robin Rowe 2019-01-27
// License MIT open source

#ifndef SortItem_h
#define SortItem_h

#include <iostream>
#include <vector>

class SortItem
{	SortItem(const SortItem&) = delete;
	void operator=(const SortItem&) = delete;
	static const unsigned bufsize = 100 + 1;
public:
//	Data: 15423123 931234 1
	std::vector<char> line;
	std::ostream& Print(std::ostream& os) const;
	~SortItem()
	{}
	SortItem()
	:	line(bufsize)
	{}
	bool operator!() const
	{	return !line.size();
	}
};

inline
std::ostream& operator<<(std::ostream& os,const SortItem& sortitem)
{	return sortitem.Print(os);
}

#endif
