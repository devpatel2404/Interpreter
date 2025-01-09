#include "../tokens/token.h"
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class parser {
public:
  parser(std::vector<std::pair<std::string, tokentype>>);
  void parse();
  bool parseFunc();
  bool parseExpression();
  bool setTokens(std::vector<std::pair<std::string, tokentype>>);
  std::pair<std::string, tokentype> next_token();
  void printError(int start, int end, std::string error);
  int lbp(std::string s, tokentype t);
  void bop(std::string op, std::string left, std::string right);
  void finishErrorParsing(tokentype delimiter);
  bool findNext();

private:
  std::vector<std::pair<std::string, tokentype>> tokens;
  long index;
  std::pair<std::string, tokentype> token;
  std::pmr::unordered_map<std::string, int> names;
};
