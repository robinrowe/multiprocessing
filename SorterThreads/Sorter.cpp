// Sorter.cpp
// Created by Robin Rowe 2019-01-22
// License MIT open source

#include <vector>
#include <algorithm>
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
		{	os << ", ";
		}
		os << sort.first;
	}
	return os;
} 

void Sorter::LowHighSort(std::vector<int> &v)
{	if(v.size()<=2)
	{	return;
	}
	int* vMin = &v[0];
	int* vMax = vMin;
	unsigned count = (unsigned) v.size();
	const unsigned half = count/2;
	for(unsigned i=0;i<half;++i)
	{	for(unsigned j=i;i<count;++j)
		{	if(v[j] < *vMin)
			{	vMin = &v[i];
			}
			if(v[j] >= *vMax)
			{	vMax = &v[i];
		}	}
		if(&v[i] != vMin)
		{	std::swap(v[i],*vMin);
		}
		--count;
		if(&v[count] != vMax)
		{	std::swap(v[count],*vMax);
}	}	}

void Sorter::BubbleSort(std::vector<int> &v)
{	bool isSorted = false;
	for (unsigned i = 1;!isSorted && i<v.size();++i) 
	{	isSorted = true;
		for (unsigned j = 0;j < v.size()-i;++j) 
		{	if (v[j] < v[j+1]) 
			{	isSorted = false;
				std::swap(v[j],v[j+1]);
}	}	}	}

// https://github.com/indy256/codelibrary/blob/master/cpp/sort/sort.cpp
// The Unlicense

void Sorter::merge_sort(vector<int> &a, int low, int high)
{	if(high - low < 2)
	{	return;
	}
	int mid = (low + high) >> 1;
	merge_sort(a, low, mid);
	merge_sort(a, mid, high);
	vector<int> b;
	copy(a.begin() + low, a.begin() + mid, back_inserter(b));
	for(int i = low, j = mid, k = 0; k < b.size(); i++)
	{	if(j == high || b[k] <= a[j])
		{	a[i] = b[k++];
		}
		else
		{	a[i] = a[j++];
		}
	}
}

void Sorter::counting_sort(vector<int> &a)
{	int max = *max_element(a.begin(), a.end());
	vector<int> cnt(max + 1);
	for(int x : a)
	{	++cnt[x];
	}
	for(int i = 1; i < cnt.size(); i++)
	{	cnt[i] += cnt[i - 1];
	}
	const int n = (int) a.size();
	vector<int> b(n);
	for(int i = 0; i < n; i++)
	{	b[--cnt[a[i]]] = a[i];
	}
	a = b;
}