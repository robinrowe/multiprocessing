// Sorter.h 
// Created by Robin Rowe 2019-01-26
// License MIT open source

#ifndef Sorter_h
#define Sorter_h

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

class Sorter
{	Sorter(const Sorter&) = delete;
	void operator=(const Sorter&) = delete;
	static void merge_sort(std::vector<int> &a, int low, int high);
	static void counting_sort(std::vector<int> &a);
	typedef void func(std::vector<int> &a);
	std::map<const char*,func*> sorts;
public:
	static void LowHighSort(std::vector<int>& v);
	static void BubbleSort(std::vector<int>& v);
	std::ostream& Print(std::ostream& os) const;
	~Sorter()
	{}
	Sorter()
	{	sorts["merge"] = MergeSort;
		sorts["counting"] = CountingSort;
		sorts["low-high"] = LowHighSort;
		sorts["bubble"] = BubbleSort;
		sorts["heap"] = HeapSort;
		sorts["std"] = StdSort;
	}
	bool operator!() const
	{	return false;
	}
	bool Sort(std::vector<int>& v,const char* sortName)
	{	for(auto& sort:sorts)
		{	if(!strcmp(sort.first,sortName))
			{	sort.second(v);
				return true;
		}	}	
		return false;
	}
	static void MergeSort(std::vector<int>& v)
	{	const int low = *std::min_element(v.begin(),v.end());
		const int high = *std::max_element(v.begin(),v.end());
		merge_sort(v,low,high);
	};
	static void CountingSort(std::vector<int>& v)
	{	counting_sort(v);
	}
	static void HeapSort(std::vector<int>& v)
	{	std::make_heap(v.begin(),v.end());
		std::sort_heap(v.begin(),v.end());
	}
	static void StdSort(std::vector<int>& v)
	{	std::sort(v.begin(),v.end());
	}
};

inline
std::ostream& operator<<(std::ostream& os,const Sorter& sorter)
{	return sorter.Print(os);
}

#endif
