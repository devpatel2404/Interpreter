#include "error/errorReporting.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>

int main(int argc, char **argv) {
  if (argc < 2)
    std::cout << "Invalid arguements no file provided or found" << std::endl;
  else if (argc > 2)
    std::cout << "This is coming soon" << std::endl;
  else {
    std::ifstream s(argv[1]);
    std::cout << "Opening " << argv[1] << std::endl;
    if (!s.is_open()) {
      std::cout << "File cannot be opened";
      return -1;
    }

    std::cout << "File was successfully opened." << std::endl;
    std::string data((std::istreambuf_iterator<char>(s)),
                     std::istreambuf_iterator<char>());
    //  std::cout << data;
    lexer l(data);
    parser p(l.getTokens());
    p.construct();
    /*

    if (hasError) {
      std::cout << "Cannot be compiled" << std::endl;
      exit(65);
    }
    */

    s.close();
  }
  return 0;
}

// Long Goal make a full working programming language that has less boilerplate
// and has a library that is created from the language itself, like std Current
// goals: make the program running and parsing correctly eventually i have setup
// for scoping and going to select a type of scoping that I want then I will
// start making arrays, maps, and other datastructures in the language and allow
// for a heap and etc, approximately 256 MB to be safe.
//
