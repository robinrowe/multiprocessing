// generate.cpp 
// Created by Robin Rowe 2019-01-26
// License MIT MIT open source

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include "Sorter.h"
using namespace std;

void Usage()
{	cout << "Creates a file filled with random integers." << endl;
	cout << "    Usage: generate filename min max count" << endl;
}

enum
{	ok,
	invalid_args,
	invalid_filename,
	invalid_range,
	invalid_count,
	cant_write_file
};
	
int main(int argc,char* argv[])
{	cout << "generate starting..." << endl;
#if 0
	if(argc < 5)
	{	Usage();
		return invalid_args;
	}
	const char* filename = argv[1];
	const int low = atoi(argv[2]);
	const int high = atoi(argv[2]);
	const int count = atoi(argv[2]);
#else
	const char* filename = "random_generate.txt";
	const int low = '0';
	const int high = '9';
	const int count = 101;
#endif
	if(!*filename)
	{	cout << "Invalid filename" << endl;
		Usage();
		return invalid_filename;
	}
	if(!(low < high))
	{	cout << "Invalid low high" << endl;
		Usage();
		return invalid_range;
	}
	if(count < 1)
	{	cout << "Invalid count" << endl;
		Usage();
		return invalid_count;
	}
	std::ofstream os(filename);
	if(os.bad())
	{	cout << "Can't open file " << filename << endl;
		return false;
	}
	std::vector<T> v(count);
	T* line = &v[0];
	Sorter sorter;
	// output: 15423123 931234 1
	const unsigned maxLength = 100; //Requirement is 100;
	const unsigned lines = 100; //Requirement is <10000;
	std::uniform_int_distribution<> dis(1,maxLength);	
	for(unsigned i = 0;i<lines;++i)
	{	unsigned length = 0;
		for(;;)
		{	const int width = dis(sorter.GetGen());
			if(length + width + 1 > maxLength)
			{	break;
			}
			if(length)
			{	line[length] = ' ';
				length++;
			}
			T* from = line+length;
			T* to = line+length+width;
			sorter.Generate(from,to,low,high);
			length += width;
		}
		if(!sorter.Write(os,&v[0],&v[length],true))
		{	cout << "Can't write file " << filename << endl;
			return cant_write_file;
	}	}
	cout << "generate done!" << endl;
	return ok;
}

