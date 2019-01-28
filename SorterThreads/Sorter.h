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
public:
	typedef void func(T* from,T* to);
private:
	std::map<const char*,func*> sorts;
public:
	std::ostream& Print(std::ostream& os) const;
	void Generate(std::vector<T>& v,int low,int high);
	bool IsSorted(std::vector<T>& v);
	bool Read(std::vector<T>& v,const char* filename);
	bool Write(std::vector<T>& v,const char* filename);
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
	bool Sort(std::vector<T>& v,const char* sortName)
	{	func* f = GetSorter(sortName);
		if(!f)
		{	return false;
		}
		f(&v[0],&v[v.size()-1]);
		return true;
	}
	func* GetSorter(const char* sortName)
	{	for(auto& sort:sorts)
		{	if(!strcmp(sort.first,sortName))
			{	return sort.second;
		}	}	
		return 0;
	}
};

inline
std::ostream& operator<<(std::ostream& os,const Sorter& sorter)
{	return sorter.Print(os);
}

#endif
