#include "../AST/nodes.h"
#include "../error/errorReporting.h"
#include "../token/token.h"
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

class ParseError : public std::runtime_error {
public:
  explicit ParseError(const std::string &message)
      : std::runtime_error(message) {}
};

class parser {
public:
  parser(std::vector<Token> toks);
  ExprVariantPtr parse();
  void construct();
  void printTokens();
  void reset();

private:
  std::vector<Token> tokens;
  int idx;
  int level;
  Token curr;
  void fixLines(int first, int second);
  bool parseExpression();
  bool parseFunc();
  bool match(std::vector<TokenType> types);
  bool check(TokenType type);
  Token peekTok();
  Token next_token();
  Token previous();
  void sync();
  std::map<int, std::unordered_map<std::string, bool>> scoping;
  ExprVariantPtr expression();
  ExprVariantPtr equality();
  ExprVariantPtr comparison();
  ExprVariantPtr term();
  ExprVariantPtr factor();
  ExprVariantPtr unary();
  ExprVariantPtr primary();
  Token consume(TokenType type, std::string message);
  std::shared_ptr<ParseError> error(Token token, std::string message);
};

/*
Expression -> assign | reassign | equality
assign -> type name = expr;
reassign -> name = expr;
equality -> (name | expr) eq (name | expr);
type -> int | decimal | string | character | bool
expr -> term + expr | term - expr | term * expr | term /
expr term = name | value eq = > | >= | == | < | <= | !=
*/
