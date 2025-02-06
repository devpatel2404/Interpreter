#include "lexer.h"
#include "../error/errorReporting.h"
#include <cstddef>
#include <string>
#include <unistd.h>
#include <vector>

lexer::lexer(std::string s) : input(s), readPos(0), pos(-1), byte('\0') {
  readChar();
};

void lexer::readChar() {
  if (readPos >= input.size()) {
    byte = '\0';
  } else
    byte = input[readPos];
  pos = readPos;
  readPos++;
}

Token lexer::NextToken() {
  Token tok;

  // std::cout << "Byte Read: " << byte << " ";

  switch (byte) {
  // add double and or equal.
  case '+':
    tok = makeToken("+", PLUS);
    break;
  case '-':
    tok = makeToken("-", MINUS);
    break;
  case '/':
    if (input[readPos] == '/') {
      while (byte != '\n') {
        readChar();
      }
      skipWhitespace();
      return {"\0", ILLEGAL};
    }
    tok = makeToken("/", FSLASH);
    break;
  case '*':
    tok = makeToken("*", ASTERISK);
    break;
  case '^':
    tok = makeToken("^", BITOR);
    break;
  case '%':
    tok = makeToken("%", MODULOS);
    break;
  case '|':
    if (input[readPos] == '|') {
      readChar();
      tok = makeToken("||", OR);
    } else
      tok = makeToken("|", PIPE);
    break;
  case '&':
    if (input[readPos] == '&') {
      readChar();
      tok = makeToken("&&", AND);
    } else
      tok = makeToken("&", BITAND);
    break;
  case '(':
    tok = makeToken("(", LPAREN);
    break;
  case ')':
    tok = makeToken(")", RPAREN);
    break;
  case '{':
    tok = makeToken("{", LCURLY);
    break;
  case '}':
    tok = makeToken("}", RCURLY);
    break;
  case '[':
    tok = makeToken("[", LBRACK);
    break;
  case ']':
    tok = makeToken("]", RBRACK);
    break;
  case '!':
    tok = makeToken("!", NOT);
    break;
  case ';':
    tok = makeToken(";", SEMICOLON);
    break;
  case '=':
    if (input[readPos] == '=') {
      readChar();
      tok = makeToken("==", CHECK);
    } else
      tok = makeToken("=", ASSIGN);
    break;
  case '"':
    tok = makeToken(readString(), STRING);
    break;
  case '\'':
    tok = makeToken(readCharacter(), CHARACTER);
    break;
  default:
    if (isLetter(byte)) {
      tok.literal = readIdent();
      tok.token = findIdent(tok.literal);
    } else if (isNum(byte)) {
      std::string n = readNum();
      if (n.find('.') != -1)
        tok = makeToken(n, DECIMAL);
      else
        tok = makeToken(readNum(), INT);
    } else {
      tok = makeToken(std::to_string(byte), ILLEGAL);
      std::string message("unexpected CHARACTER: ");
      message += byte;
      error(line, message);
    }
  }

  std::cout << "Token: " << TokentypeToString(tok.token)
            << " String: " << tok.literal << std::endl;

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
  // std::cout << "\tReading IDENT Starting byte: " << byte;
  std::string s;
  while (isLetter(byte) || isNum(byte) || byte == '-' || byte == '_' ||
         byte == '\'') {
    s.push_back(byte);
    if (isLetter(input[readPos]) || isNum(input[readPos]) ||
        input[readPos] == '-' || input[readPos] == '_' ||
        input[readPos] == '\'')
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
    if (byte == '.') {
      foundDot = true;
      readChar();
      continue;
    }
    if (isNum(input[readPos]) || (input[readPos] == '.' && !foundDot))
      readChar();
    else
      break;
  }

  return s;
}

std::vector<Token> lexer::getTokens() {
  std::vector<Token> toks;
  while (byte != '\0') {
    Token b = NextToken();
    if (b.literal == "\0")
      continue;
    else
      toks.push_back(b);
  }

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
  // add more advanced error handling if missing a parenthesis make sure
  std::string s;
  s.push_back(byte);
  readChar();
  while (byte != '"') {
    s.push_back(byte);
    readChar();
  }

  s.push_back(byte);

  return s;
}

std::string lexer::readCharacter() { return "hello"; }
