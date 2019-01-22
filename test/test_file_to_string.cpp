#include <iostream>

#include <fstream>
#include <sstream>
#include <string>

inline 
std::string ReadFile(const char* filename)
{  std::ifstream src(filename, std::ios::binary);
   std::ostringstream dst;
   dst << src.rdbuf() << std::ends;
   return std::move(dst.str());
}

int main(int argc,char* argv[])
{	const char* filename = argv[1];
	if(argc<2)
	{	filename = "/code/github/multiprocessing/test/hello_world.txt";
	}
	std::string s(ReadFile(filename));
#if 0
    std::ifstream  src(filename, std::ios::binary);
	if(src.bad())
	{	std::cout << "Can't open " << filename << std::endl;
		return 1;
	}
//	std::ofstream  dst("to.ogv",   std::ios::binary);
	std::ostringstream dst;
    dst << src.rdbuf() << std::ends;
	const std::string& s = dst.str();
#endif
	std::cout << "string: " << s << std::endl;
	return 0; 
}
