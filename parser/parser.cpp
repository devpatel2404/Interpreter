#include "./parser.h"
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

parser::parser(std::vector<std::pair<std::string, tokentype>> t)
    : tokens(t), index(0), token(), names() {
  token = tokens[index];
}

bool parser::setTokens(std::vector<std::pair<std::string, tokentype>> t) {
  tokens = t;
  index = 0;
  token = tokens[index];
  names.clear();
  return tokens == t;
}

std::pair<std::string, tokentype> parser::next_token() {
  if (index >= tokens.size() - 1) {
    return {"", eof};
  }
  index++;
  token = tokens[index];
  return token;
}

void parser::printError(int start, int end, std::string error) {
  std::cout << "\tError with the Line: ";
  if (start < 0) {
    std::cout << "\tprintError recieved an invalid start index";
  }
  if (end >= tokens.size() || start > end) {
    std::cout << "\tPrintError recieved an invalid end index";
  }

  while (start <= end) {
    std::cout << tokens[start++].first << ' ';
  }

  std::cout << std::endl << "\t" << error << std::endl;

  return;
}

void parser::finishErrorParsing(tokentype delimiter) {
  next_token();
  while (token.second != delimiter) {
    std::cout << token.first << ' ';
    next_token();
  }
  std::cout << token.first << std::endl;
  next_token();

  return;
}

bool parser::findNext() {
  next_token();
  if (token.second == CONST || token.second == LET || token.second == VAR ||
      token.second == IF || token.second == FUNC || token.second == RETURN) {
    return true;
  }
  std::cout << "\t\t\tThrew away tokens: ";
  while (token.second != eof &&
         (token.second != CONST && token.second != LET && token.second != VAR &&
          token.second != IF && token.second != FUNC &&
          token.second != RETURN)) {
    std::cout << token.first << ' ';
    next_token();
  }
  std::cout << std::endl;
  if (token.second == eof) {
    std::cout << "\t\tNo Tokens Found";
    return false;
  } else {
    std::cout << "\t\tFound token: " << token.first << std::endl;
    return true;
  }
}

void parser::parse() {
  // this will be the start of the recursive desent parser;
  while (token.second != eof) {
    if (token.second == VAR || token.second == CONST || token.second == LET ||
        token.second == NAME) {
      if (!parseExpression()) {
        std::cout << "\tSyntax Error " << std::endl;
      }
    } else if (token.second == FUNC) {
      if (!parseFunc()) {
        std::cout << "\tSyntax Error " << std::endl;
      }
    } else if (token.second == IF) {
      if (!parseExpression()) {
        std::cout << "\tSyntax Error " << std::endl;
      }
    } else {
      int idx = index;
      std::cout << "\tSyntax Error Not a Correct Start to a line with: "
                << token.first;
      if (!findNext())
        break;
    }
  }
}

int parser::lbp(std::string s, tokentype t) {
  switch (t) {
  case MULT:
  case DIV:
    return 3;
  case ADD:
  case SUB:
    return 2;
  case NAME:
    if (names[s] <= 0)
      return -1;
    else
      return 0;
  case NUMBER:
  case LPAREN:
  case RPAREN:
  case COMMA:
    return 0;
  default:
    return -1;
  }
}

bool parser::parseExpression() {
  // this will be a pratt parser
  int start = index;
  std::pair<std::string, tokentype> st = token;
  std::string final;
  std::cout << token.first << ' ';
  if (st.second == NAME && names[st.first] <= 0) {
    findNext();
    std::cout << "\tThis has no previous definition: " << st.first << std::endl;
    return false;
  }
  next_token();
  std::cout << token.first << ' ';
  if (token.second != NAME && st.second != NAME) {
    finishErrorParsing(SEMICOLON);
    int idx = index;
    printError(idx, idx, "This is not a correct value");
    return false;
  }
  if (token.second == NAME) {
    if (names[token.first] > 0) {

      int idx = index;
      finishErrorParsing(SEMICOLON);
      printError(start, idx, "Cannot Redefine a variable with a definition");
      std::cout << "\tSyntax Error" << std::endl;
    }
    names[token.first] = 1;
    next_token();
    std::cout << token.first << ' ';
    if (token.second != ASSIGN) {
      int idx = index;
      finishErrorParsing(SEMICOLON);
      printError(start, idx, "No equal sign for assignment");
      return false;
    }
  }
  tokentype previous = token.second;
  next_token();
  // if we get a value with -1 then instant return
  while (token.second != SEMICOLON) {
    if (lbp(token.first, token.second) == -1 || token.second == previous) {
      int idx = index;
      std::cout << token.first << ' ';
      finishErrorParsing(SEMICOLON);
      printError(start, idx, "Unexpected value");
      return false;
    }
    std::cout << token.first << " ";
    previous = token.second;
    next_token();
  }
  std::cout << token.first;
  std::cout << std::endl;
  next_token();
  return true;
}

bool parser::parseFunc() { return true; }
