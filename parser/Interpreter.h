#include "../AST/nodes.h"

std::variant<int, std::string, char, double, bool>
visitLiteralExpr(const LiteralExprPtr &expr);
