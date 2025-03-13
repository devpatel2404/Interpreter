#include "../token/token.h"
#include <fstream>
#include <iostream>
#include <string>

class lexer {
public:
  lexer(std::ifstream *stream);
  std::vector<Token> getTokens();

private:
  void skipWhitespace();
  std::string readCharacter();
  std::string readString();
  TokenType findIdent(std::string s);
  bool isLetter(char c);
  std::string readNum();
  void readChar();
  Token NextToken();
  std::string readIdent();
  bool isNum(char c);
  bool next_line();
  std::ifstream *input;
  std::string current;
  char byte;
  int readPos;
  int pos;
  int line;
};
