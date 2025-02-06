#include "./errorReporting.h"

bool hasError = false;

void report(int line, std::string place, std::string message) {
  std::cout << "|| line: " << line << " Place: " << place << " : " << message
            << " ||" << std::endl;
  hasError = true;
}

void error(int line, std::string message) { report(line, "", message); }
