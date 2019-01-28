// Task.h 
// Created by Robin Rowe 2019-01-27
// License MIT open source

#ifndef Task_h
#define Task_h

#include <iostream>
#include "Sorter.h"

class Task
{//	Task(const Task&) = delete;
//	void operator=(const Task&) = delete;
	Sorter* sorter;
	const char* algorithm;
	std::vector<T>* v;
	unsigned taskId;
public:
	std::ostream& Print(std::ostream& os) const;
	~Task()
	{}
	Task()
	:	sorter(0)
	,	v(0)
	,	algorithm(0)
	,	taskId(0)
	{}
	Task(Sorter* s,std::vector<T>* v,const char* algorithm)
	:	sorter(sorter)
	,	v(v)
	,	algorithm(algorithm)
	,	taskId(taskId)
	{}
	bool operator!() const
	{	return !sorter;
	}
	bool Run()
	{	if(!*this)
		{	return false;
		}
		return sorter->Sort(*v,algorithm);
	}
};

inline
std::ostream& operator<<(std::ostream& os,const Task& Task)
{	return Task.Print(os);
}

#endif
