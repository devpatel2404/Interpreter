#include <string>

#ifndef token_types
#define token_types
enum tokentype {
  LBRACKET,
  RBRACKET,
  LPAREN,
  RPAREN,
  LCURLY,
  RCURLY,
  SEMICOLON,
  eof,
  COMMA,
  // VARIABLES
  LET,
  VAR,
  CONST,
  NAME,
  ASSIGN,
  // NUMBERS
  MULT,
  DIV,
  SUB,
  ADD,
  MODULO,
  BITAND,
  BITOR,
  NUMBER,
  // STRINGS
  APOS,
  QUOTE,
  EXIT,
  // BOOLEAN
  TRUE,
  FALSE,
  NOT,
  CHECK,
  IF,
  AND,
  OR,
  GREATER,
  GTOREQ,
  LESS,
  LSOREQ,
  // TERIARY,
  // ACCESS TYPE
  PUBLIC,
  PRIVATE,
  PROTECTED,
  // FUNCTIONS
  FUNC,
  FUNCPARAM,
  RETURN,
  INVALID,
};

#endif

tokentype getTokenType(std::string t);
tokentype getTokenType2(char val);
bool isName(std::string t);
bool isNum(std::string t);
std::string tokenToString(tokentype token);
