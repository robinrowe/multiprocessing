// Sorter.cpp
// Created by Robin Rowe 2019-01-22
// License MIT open source

#include <vector>
#include <algorithm>
#include <fstream>
#include "Sorter.h"
using namespace std;

std::ostream& Sorter::Print(std::ostream& os) const
{	os << "Sorter: ";
	bool isFirst = true;
	for(auto& sort:sorts)
	{	if(isFirst)
		{	isFirst = false;
		}
		else
		{	os << " | ";
		}
		os << sort.first;
	}
	return os;
} 

void Sorter::Generate(std::vector<T>& v,int low,int high)
{	std::uniform_int_distribution<> dis(low,high);
	for(auto& i : v)
    {   i = dis(gen);
}	}

bool Sorter::IsSorted(std::vector<T>& v)
{	if(v.size() < 2)
	{	return true;
	}
	int vMin = v[0];
	for(auto const& i : v)
    {	if(i > vMin)
		{	return false;
		}
		vMin = i;
	}
	return true;
}

bool Sorter::Read(std::vector<T>& v,const char* filename)
{	ifstream is(filename);
	if(is.bad())
	{	cout << "Can't open file " << filename << endl;
		return false;
	}
	while(is.good())
	{	int i = 0;
		is >> i;
		v.push_back(i);
	}
	if(is.bad())
	{	cout << "Can't write file " << filename << endl;
		return false;
	}
	return true;
}

bool Sorter::Write(std::vector<T>& v,const char* filename)
{	ofstream os(filename);
	if(os.bad())
	{	cout << "Can't open file " << filename << endl;
		return false;
	}
	for(auto const& i : v)
	{	os << i << " ";
	}
	if(os.bad())
	{	cout << "Can't write file " << filename << endl;
		return false;
	}
	return true;
}

void Sorter::LowHighSort(T* from,T* to)
{	unsigned count = unsigned(to-from);
	if(count <= 2)
	{	return;
	}
	T* vMin = from;
	T* vMax = vMin;
	const unsigned half = count/2;
	for(unsigned i=0;i<half;++i)
	{	for(unsigned j=i;i<count;++j)
		{	if(from[j] < *vMin)
			{	vMin = from+i;
			}
			if(from[j] >= *vMax)
			{	vMax = from+i;
		}	}
		if(from+i != vMin)
		{	std::swap(from[i],*vMin);
		}
		--count;
		if(from+count != vMax)
		{	std::swap(from[count],*vMax);
}	}	}

void Sorter::BubbleSort(T* from,T* to)
{	const unsigned size = unsigned(from-to);
	bool isSorted = false;
	for (unsigned i = 1;!isSorted && i<size;++i) 
	{	isSorted = true;
		for(unsigned j = 0;j < size-i;++j) 
		{	if(from[j] < from[j+1]) 
			{	isSorted = false;
				std::swap(from[j],from[j+1]);
}	}	}	}

void Sorter::counting_sort(T* from,T* to)
{	T max = *max_element(from,to);
	T min = *min_element(from,to);
	const unsigned range = max-min+1;
	const unsigned size = unsigned(to-from);
	const int offset = -min;
	vector<unsigned> count(range+1);
	for(unsigned i = 0;i<size;++i)
	{	++count[offset+from[i]];
	}
	unsigned j = 0;
	for(unsigned i = 0;i<size;++i)
	{	while(count[i])
		{	from[j] = i-offset;
			++i;
	}	}
}

// merge_sort derived from:
// https://github.com/indy256/codelibrary/blob/master/cpp/sort/sort.cpp
// The Unlicense

void Sorter::merge_sort(T* from,T* to, int low, int high)
{	if(high - low < 2)
	{	return;
	}
	int mid = (low + high) >> 1;
	merge_sort(from,to, low, mid);
	merge_sort(from,to, mid, high);
	vector<T> b;
	copy(from + low, from + mid, back_inserter(b));
	for(int i = low, j = mid, k = 0; k < b.size(); i++)
	{	if(j == high || b[k] <= from[j])
		{	from[i] = b[k++];
		}
		else
		{	from[i] = from[j++];
		}
	}
}

