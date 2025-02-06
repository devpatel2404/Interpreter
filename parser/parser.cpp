#include "./parser.h"
#include <iostream>
#include <vector>

parser::parser(std::vector<Token> toks)
    : tokens(toks), idx(0), scoping(), level(0) {}

void parser::construct() {
  int x = 1;
  std::cout << "Line " << x << ": ";
  for (Token t : tokens) {
    if (t.token == SEMICOLON || t.token == LCURLY) {
      std::cout << t.literal << std::endl;
      x++;
      std::cout << "Line " << x << ": ";

    } else
      std::cout << t.literal << ' ';
  }
  std::cout << "EOF" << std::endl;
  return;
}

void parser::parse() {
  // this will be a recursive descent parser
  if (tokens[idx].token == INT || tokens[idx].token == STRING ||
      tokens[idx].token == DECIMAL || tokens[idx].token == BOOL ||
      tokens[idx].token == CHARACTER || tokens[idx].token == IDENT) {
    if (parseExpression())
      parse();
    else
      std::cout << "Error" << std::endl;
  } else if (tokens[idx].token == FUNC) {
    if (!parseFunc())
      std::cout << "Error" << std::endl;
  } else {
    std::cout << "This is incorrect start to a line" << std::endl;
  }
}

bool parser::parseExpression() {}

bool parser::parseFunc() {
  level++;
  return true;
  level++;
}
