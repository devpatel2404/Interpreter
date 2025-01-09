#include "./lexer/lexer.h"
#include "./parser/parser.h"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    std::cout << "Nothing to Interpret" << std::endl;
  } else if (argc == 2) {
    std::string s(argv[1]);
    lexer l = lexer(s);
    std::vector<std::pair<std::string, tokentype>> t = l.scan();
    parser p = parser(t);
    p.parse();
  } else if (argc > 2) {
    std::cout << "Coming Soon" << std::endl;
  }

  return 0;
}
