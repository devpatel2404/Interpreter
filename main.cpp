#include "AST/nodes.h"
#include "AST/prettyprinter.h"
#include "error/errorReporting.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

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

    lexer l(&s);
    parser p(l.getTokens());
    std::cout << "Printing Tokens" << std::endl;
    p.printTokens();
    std::cout << "Reconstructing File" << std::endl;
    p.construct();
    p.reset();
    ExprVariantPtr parsedPtr = p.parse();
    PrettyPrinter printer;
    printer.print(std::move(parsedPtr));

    if (hasError) {
      std::cout << "Cannot be compiled" << std::endl;
      exit(65);
    }

    std::cout << "The parser finished." << std::endl;

    s.close();
  }
  return 0;
}

// What I want to do with this language:
// have a beginner friendly language that keeps memeory management and pointers
// allows for beginners to learn concepts and having C like syntax while making
// it less complicated
