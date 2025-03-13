#include <iostream>
#include <string>
#include <unistd.h>

#ifndef TOKEN_H
#define TOKEN_H

enum TokenType {
  IDENT,
  ILLEGAL,

  INT,
  STRING,
  DECIMAL,
  CHARACTER,
  BOOL,
  VOID,
  null,

  PLUS,
  MINUS,
  ASTERISK,
  BACKSLASH,
  ASSIGN,
  FSLASH,
  AND,
  OR,
  BITAND,
  BITOR,
  MODULOS,
  NOT,
  NOTEQ,
  GREATER,
  LESS,
  GRTOREQ,
  LESOREQ,
  CHECK,
  PIPE,
  COMMA,
  DOT,

  FUNC,
  IF,
  FOR,
  WHILE,
  RETURN,
  PRINT,

  SEMICOLON,
  COLON,
  TRUE,
  FALSE,

  APOSTRAPHE,
  QUOTATION,

  LCURLY,
  RCURLY,
  LBRACK,
  RBRACK,
  LPAREN,
  RPAREN,
  EoF
};

struct Token {
  std::string literal;
  TokenType token;
  int line;
};

Token makeToken(std::string s, TokenType t);

Token makeTokenI(std::string s, TokenType t, int line);

TokenType findToken(std::string s);

std::string TokentypeToString(TokenType t);

#endif // !TOKEN_H
