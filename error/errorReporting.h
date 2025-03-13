#include "../token/token.h"
#include <iostream>
#include <string.h>
#include <string>
#include <vector>

#ifndef ERRORREPORTING
#define ERRORREPORTING

extern bool hasError;

void report(int line, std::string place, std::string message);

void errorI(int line, std::string message);

void errorT(Token token, std::string message);

#endif // !a
