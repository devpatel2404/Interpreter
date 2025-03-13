#include "./errorReporting.h"
#include <string>

bool hasError = false;

void report(int line, std::string place, std::string message) {
  std::cout << "\t|| line: " << line << " Place: " << place << " : " << message
            << " ||" << std::endl;
  hasError = true;
}

void errorI(int line, std::string message) { report(line, "", message); }

void errorT(Token token, std::string message) {
  if (token.token == EoF) {
    report(token.line, " at end ", message);
  } else
    report(token.line, " at '", message);
}
