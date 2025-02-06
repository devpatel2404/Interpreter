#include <iostream>
#include <string.h>
#include <vector>

#ifndef ERRORREPORTING
#define ERRORREPORTING

extern bool hasError;

void report(int line, std::string place, std::string message);

void error(int line, std::string message);

#endif // !a
