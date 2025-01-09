#include "../tokens/token.h"
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class lexer {
public:
  lexer();
  lexer(std::string name);
  bool setfile(std::string newfile);
  int getLineNum();
  std::string getCurrFile();
  bool isDone();
  bool prompt();
  std::vector<std::pair<std::string, tokentype>> scan();
  int findNext(std::string s);

private:
  std::string filename;
  int lineNum;
  std::fstream input;
  bool done;
};
