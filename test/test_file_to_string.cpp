#include <fstream>
#include <sstream>
#include <iostream>

int main(int argc,char* argv[])
{	const char* filename = argv[1];
	if(argc<2)
	{	filename = "/code/github/multiprocessing/test/hello_world.txt";
	}
    std::ifstream  src(filename, std::ios::binary);
	if(src.bad())
	{	std::cout << "Can't open " << filename << std::endl;
		return 1;
	}
//	std::ofstream  dst("to.ogv",   std::ios::binary);
	std::ostringstream dst;
    dst << src.rdbuf() << std::ends;
	const std::string& s = dst.str();
	std::cout << "string: " << s << std::endl;
	return 0; 
}
