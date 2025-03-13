#include "./Interpreter.h"
#include <string>
#include <variant>

std::variant<int, std::string, char, double, bool>
visitLiteralExpr(const LiteralExprPtr &expr) {
  return expr->literal;
}
