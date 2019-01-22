// producer_consumer.cpp 
// Created by Robin Rowe 2019-01-22
// License MIT MIT open source

#include <stdio.h>
#include "Producer.h"

void Usage()
{	puts("Usage: producer_consumer input_file output_file sorter\n"
		" sorter = bubble | merge | highlow");
}

enum 
{	ok,
	usage,
	bad_input,
	bad_output,
	bad_algorithm
};

int main(int argc,char* argv[])
{	if(argc<3)
	{	Usage();
		return usage;
	}
	Producer producer;
	if(!producer.OpenInput(argv[1]))
	{	printf("Can't open input %s\n",argv[1]);
		return bad_input;
	}
	if(!producer.OpenOutput(argv[2]))
	{	printf("Can't open output %s\n",argv[2]);
		return bad_output;
	}
	if(!producer.OpenSorter(argv[3]))
	{	printf("Can't access %s sorter\n",argv[3]);
		return bad_algorithm;
	}
	return producer.Run();
}
