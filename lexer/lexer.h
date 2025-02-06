#include "../token/token.h"
#include <iostream>
#include <string>

class lexer {
public:
  lexer(std::string s);
  void readChar();
  Token NextToken();
  std::string readNum();
  std::string readIdent();
  bool isLetter(char c);
  bool isNum(char c);
  TokenType findIdent(std::string s);
  std::vector<Token> getTokens();
  void skipWhitespace();
  std::string readString();
  std::string readCharacter();

private:
  std::string input;
  char byte;
  int readPos;
  int pos;
  int line;
};
