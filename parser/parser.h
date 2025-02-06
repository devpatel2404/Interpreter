#include "../token/token.h"
#include <map>
#include <unordered_map>
#include <vector>

class parser {
public:
  parser(std::vector<Token> toks);
  void parse();
  void construct();
  bool parseExpression();
  bool parseFunc();

private:
  std::vector<Token> tokens;
  int idx;
  int level;
  // will represent levels and all the current variables in that level, will
  // allow for search through higher levels
  std::map<int, std::unordered_map<std::string, bool>> scoping;
};
