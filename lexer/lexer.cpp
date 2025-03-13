#include "lexer.h"
#include "../error/errorReporting.h"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

// change to be line by line for better error parsing;

lexer::lexer(std::ifstream *stream)
    : input(stream), readPos(0), pos(-1), byte('\0'), current(), line(0) {};

void lexer::readChar() {
  if (readPos >= current.size()) {
    if (next_line())
      return;
    else
      byte = '\0';
  } else
    byte = current[readPos];
  pos = readPos;
  readPos++;
}

Token lexer::NextToken() {
  Token tok;

  switch (byte) {
  case '+':
    tok = makeTokenI("+", PLUS, line);
    break;
  case '-':
    tok = makeTokenI("-", MINUS, line);
    break;
  case '/':
    if (current[readPos] == '/') {
      next_line();
      return {"Comment", ILLEGAL, line};
    }
    tok = makeTokenI("/", FSLASH, line);
    break;
  case '*':
    tok = makeTokenI("*", ASTERISK, line);
    break;
  case '^':
    tok = makeTokenI("^", BITOR, line);
    break;
  case '%':
    tok = makeTokenI("%", MODULOS, line);
    break;
  case '|':
    if (current[readPos] == '|') {
      readChar();
      tok = makeTokenI("||", OR, line);
    } else
      tok = makeTokenI("|", PIPE, line);
    break;
  case '&':
    if (current[readPos] == '&') {
      readChar();
      tok = makeTokenI("&&", AND, line);
    } else
      tok = makeTokenI("&", BITAND, line);
    break;
  case '(':
    tok = makeTokenI("(", LPAREN, line);
    break;
  case ')':
    tok = makeTokenI(")", RPAREN, line);
    break;
  case '{':
    tok = makeTokenI("{", LCURLY, line);
    break;
  case '}':
    tok = makeTokenI("}", RCURLY, line);
    break;
  case '[':
    tok = makeTokenI("[", LBRACK, line);
    break;
  case ']':
    tok = makeTokenI("]", RBRACK, line);
    break;
  case '!':
    if (current[readPos] == '=') {
      readChar();
      tok = makeTokenI("!=", NOTEQ, line);
    } else
      tok = makeTokenI("!", NOT, line);
    break;
  case ';':
    tok = makeTokenI(";", SEMICOLON, line);
    break;
  case '=':
    if (current[readPos] == '=') {
      readChar();
      tok = makeTokenI("==", CHECK, line);
    } else
      tok = makeTokenI("=", ASSIGN, line);
    break;
  case ':':
    tok = makeTokenI(":", COLON, line);
  case '"':
    tok = makeTokenI(readString(), STRING, line);
    break;
  case '\'':
    tok = makeTokenI(readCharacter(), CHARACTER, line);
    break;
  case '<':
    if (current[readPos] == '=') {
      readChar();
      tok = makeTokenI("<=", LESOREQ, line);
    } else
      tok = makeTokenI("<", LESS, line);
    break;
  case '>':
    if (current[readPos] == '=') {
      readChar();
      tok = makeTokenI(">=", GRTOREQ, line);
    } else
      tok = makeTokenI(">", GREATER, line);
    break;
  default:
    if (isLetter(byte)) {
      tok.literal = readIdent();
      tok.token = findIdent(tok.literal);
      tok.line = line;
    } else if (isNum(byte)) {
      std::string n = readNum();
      if (n.find('.') != -1) {
        if (n.back() != '.')
          tok = makeTokenI(n, DECIMAL, line);
        else {
          tok = makeTokenI(n, ILLEGAL, line);
          errorI(line, "need atleast one trailing decimal point");
        }
      } else
        tok = makeTokenI(n, INT, line);
    } else {
      tok = makeTokenI(std::to_string(byte), ILLEGAL, line);
      std::string message("unexpected CHARACTER: ");
      message += byte;
      errorI(line, message);
    }
  }

  skipWhitespace();

  return tok;
}

TokenType lexer::findIdent(std::string s) {
  if (s == "int")
    return INT;
  if (s == "string")
    return STRING;
  if (s == "func")
    return FUNC;
  if (s == "char")
    return CHARACTER;
  if (s == "decimal")
    return DECIMAL;
  if (s == "void")
    return VOID;
  if (s == "null")
    return null;
  if (s == "true")
    return TRUE;
  if (s == "bool")
    return BOOL;
  if (s == "false")
    return FALSE;
  if (s == "for")
    return FOR;
  if (s == "while")
    return WHILE;
  if (s == "return")
    return RETURN;
  if (s == "print")
    return PRINT;
  return IDENT;
}

bool lexer::isLetter(char c) {
  switch (c) {
  case 65 ... 90:
  case 97 ... 122:
    return true;
  default:
    return false;
  }
}

bool lexer::isNum(char c) {
  switch (c) {
  case 48 ... 57:
    return true;
  default:
    return false;
    break;
  }
}

std::string lexer::readIdent() {
  std::string s;
  while (isLetter(byte) || isNum(byte) || byte == '-' || byte == '_') {
    s.push_back(byte);
    if (isLetter(current[readPos]) || isNum(current[readPos]) ||
        current[readPos] == '-' || current[readPos] == '_' ||
        current[readPos] == '\'')
      readChar();
    else
      break;
  }

  return s;
}

std::string lexer::readNum() {
  std::string s;
  bool foundDot = false;
  while (isNum(byte) || (byte == '.' && !foundDot)) {
    s.push_back(byte);
    if (byte == '.')
      foundDot = true;
    if (isNum(current[readPos]) || (current[readPos] == '.' && !foundDot)) {
      readChar();
    } else {
      break;
    }
  }

  return s;
}

std::vector<Token> lexer::getTokens() {
  std::cout << "Lexer Recieved the file." << std::endl;
  next_line();
  std::vector<Token> toks;
  while (!input->eof()) {
    Token b = NextToken();
    if (b.literal == "Comment")
      continue;
    else
      toks.push_back(b);
    if (input->eof())
      break;
  }

  input->close();

  return toks;
}

void lexer::skipWhitespace() {
  readChar();
  while (byte == ' ' || byte == '\n' || byte == '\t') {
    if (byte == '\r') {
      std::cout << "carriage return found" << std::endl;
    }
    if (byte == '\n')
      line++;
    readChar();
  }
  return;
}

std::string lexer::readString() {
  std::string s;
  s.push_back(byte);
  readChar();
  while (byte != '"') {
    if (readPos == current.size())
      break;
    s.push_back(byte);
    readChar();
  }

  if (byte == '"')
    s.push_back(byte);

  if (s.back() != '"') {
    errorI(line, "Missing closing quotationg mark");
  }

  return s;
}

std::string lexer::readCharacter() {
  std::string s;
  s.push_back(byte);
  readChar();
  s.push_back(byte);
  while (byte != '\'') {
    if (readPos == current.size())
      break;
    readChar();
    s.push_back(byte);
  }

  if (s.size() > 3)
    errorI(line, "A character can only have one value, cannot be assigned like "
                 "a string");

  if (s.back() != '\'')
    errorI(line, "Missing closing apostrophe");

  return s;
}

bool lexer::next_line() {
  if (std::getline(*input, current)) {
    line++;
    readPos = 0;
    pos = -1;
    readChar();
    return true;
  }
  return false;
}
