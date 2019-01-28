// generate.cpp 
// Created by Robin Rowe 2019-01-26
// License MIT MIT open source

#include <iostream>
#include <stdlib.h>
#include <vector>
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
	if(argc < 5)
	{	Usage();
		return invalid_args;
	}
	const char* filename = argv[1];
	const int low = atoi(argv[2]);
	const int high = atoi(argv[2]);
	const int count = atoi(argv[2]);
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
	std::vector<T> v(count);
	Sorter sorter;
	sorter.Generate(v,low,high);
	if(!sorter.Write(v,filename))
	{	cout << "Can't write file " << filename << endl;
		Usage();
		return cant_write_file;
	}
	cout << "generate done!" << endl;
	return ok;
}

