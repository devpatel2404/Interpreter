#include "../token/token.h"
#include <map>
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
  std::map<int, std::unordered_map<std::string, bool>> scoping;
};
