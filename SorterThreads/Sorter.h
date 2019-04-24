// Sorter.h 
// Created by Robin Rowe 2019-01-26
// License MIT open source

#ifndef Sorter_h
#define Sorter_h

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <random>

typedef char T;

class Sorter
{	Sorter(const Sorter&) = delete;
	void operator=(const Sorter&) = delete;
    std::random_device rd;
    std::mt19937 gen; 
	static void merge_sort(T* from,T* to,int low,int high);
	static void counting_sort(T* from,T* to);
	typedef void func(T* from,T* to);
	func* f;
	std::map<const char*,func*> sorts;
public:
	std::ostream& Print(std::ostream& os) const;
	void Generate(T* from,T* to,int low,int high);
	bool IsSorted(T* from,T* to);
	std::string Read(std::istream& is);
	bool Write(std::ostream& os,const T* from,const T* to,bool newline);
	static void LowHighSort(T* from,T* to);
	static void BubbleSort(T* from,T* to);
	static void MergeSort(T* from,T* to)
	{	const int low = *std::min_element(from,to);
		const int high = *std::max_element(from,to);
		merge_sort(from,to,low,high);
	};
	static void CountingSort(T* from,T* to)
	{	counting_sort(from,to);
	}
	static void HeapSort(T* from,T* to)
	{	std::make_heap(from,to);
		std::sort_heap(from,to);
	}
	static void StdSort(T* from,T* to)
	{	std::sort(from,to);
	}
	~Sorter()
	{}
	Sorter()
	:	gen(rd())
	{	sorts["merge"] = MergeSort;
		sorts["counting"] = CountingSort;
		sorts["low-high"] = LowHighSort;
		sorts["bubble"] = BubbleSort;
		sorts["heap"] = HeapSort;
		sorts["standard"] = StdSort;
	}
	bool operator!() const
	{	return false;
	}
	bool Sort(T* from,T* to)
	{	if(!f)
		{	return false;
		}
		f(from,to);
		return true;
	}
	bool SetSorter(const char* sortName)
	{	for(auto& sort:sorts)
		{	if(!strcmp(sort.first,sortName))
			{	f = sort.second;
				return true;
		}	}	
		return false;
	}
    std::mt19937& GetGen()
	{	return gen; 
	}
};

inline
std::ostream& operator<<(std::ostream& os,const Sorter& sorter)
{	return sorter.Print(os);
}

#endif
