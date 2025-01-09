#include "./lexer.h"
#include <iostream>
#include <string>
#include <utility>

lexer::lexer() : filename(""), lineNum(-1), input(""), done(false) {}

lexer::lexer(std::string name)
    : filename(name), lineNum(0), input(""), done(false) {
  this->input.open(name);
  if (!input.is_open())
    this->lineNum = -1;
}

bool lexer::isDone() { return done; }

int lexer::getLineNum() { return lineNum; }

std::string lexer::getCurrFile() { return filename; }

bool lexer::setfile(std::string newfile) {
  if (!isDone()) {
    if (!prompt())
      return false;
  }

  filename = newfile;
  input.open(filename);

  if (!input.is_open()) {
    std::cout << "This File is not avaliable." << std::endl;
    return false;
  }

  return true;
}

bool lexer::prompt() {
  std::string s;
  while (s != "n" || s != "y") {
    std::cout << "Do you want to stop lexing this file? [y/n] ";
    std::cin >> s;
    std::cout << std::endl;
  }

  return (s == "y") ? true : false;
}

std::vector<std::pair<std::string, tokentype>> lexer::scan() {
  // std::cout << "This is lexer: " << std::endl;
  std::string s;
  std::vector<std::pair<std::string, tokentype>> tokens;
  while (input >> s) {
    std::string z = s;
    int a = findNext(z);
    while (a < z.size()) {
      tokens.push_back(
          std::make_pair(z.substr(0, a), getTokenType(z.substr(0, a))));
      /*std::cout << "\tString: " << tokens.back().first
                << " Token: " << tokenToString(tokens.back().second)
                << std::endl;
                */
      z = z.substr(a);
      a = findNext(z);
      if (z.size() <= 1)
        break;
    }
    if (z.size() > 0) {
      tokens.push_back(std::make_pair(z, getTokenType(z)));
      /*
       std::cout << "\tString: " << tokens.back().first
                << " Token: " << tokenToString(tokens.back().second)
                << std::endl;
                */
    }
  }

  tokens.push_back(std::make_pair("", eof));

  return tokens;
}

int lexer::findNext(std::string s) {
  int a = s.size();
  std::string delimiters = "[](){};,";

  for (char delimiter : delimiters) {
    int z = s.find(delimiter);
    if (z >= 0 && z < a) {
      a = z;
    }
  }

  if (a == 0)
    return 1;

  return a;
}
