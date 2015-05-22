#include "Error.h"

void printGLError(std::string str, char *file, int line)
{
	std::cerr << str << " in file " << file << " at line " << line << "." << std::endl;
}