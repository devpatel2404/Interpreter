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

  PLUS,
  MINUS,
  ASTERISK,
  ASSIGN,
  FSLASH,
  AND,
  OR,
  BITAND,
  BITOR,
  MODULOS,
  NOT,
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
};

struct Token {
  std::string literal;
  TokenType token;
};

Token makeToken(std::string s, TokenType t);

TokenType findToken(std::string s);

std::string TokentypeToString(TokenType t);

#endif // !TOKEN_H
