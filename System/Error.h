#ifndef ERROR_H_
#define ERROR_H_

#include <iostream>
#include <string>

#define printError(str) printGLError(str, __FILE__, __LINE__)

void printGLError(std::string str, char *file, int line);

#endif // !ERROR_H_
