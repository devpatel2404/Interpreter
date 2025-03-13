#include "nodes.h"

#ifndef PRINTER
#define PRINTER

class PrettyPrinter {
public:
  void print(ExprVariantPtr expr);
  std::string parenthesize(std::string name);
  std::string parenthesize(std::string oper, ExprVariantPtr expr);
  std::string parenthesize(std::string oper, ExprVariantPtr left,
                           ExprVariantPtr right);

private:
  std::string toString(ExprVariantPtr expr);
  std::vector<std::string> toString(StmtVariantPtr stmt);
  std::string printAssignExpr(const AssignExprPtr &expr);
  std::string printBinaryExpr(const BinaryExprPtr &expr);
  std::string printCallExpr(const CallExprPtr &expr);
  std::string printGetExpr(const GetExprPtr &expr);
  std::string printLiteralExpr(const LiteralExprPtr &expr);
  std::string printGroupingExpr(const GroupingExprPtr &expr);
  std::string printUnaryExpr(const UnaryExprPtr &expr);
  std::string printVariableExpr(const VariableExprPtr &expr);
  std::vector<std::string> printBlockStmt(const BlockStmtPtr &stmt);
  std::string printExpressionStmt(const ExpressionStmtPtr &stmt);
  std::vector<std::string> printFunctionStmt(const FunctionStmtPtr &stmt);
  std::vector<std::string> printIfStmt(const IfStmtPtr &stmt);
  std::string printPrintStmt(const PrintStmtPtr &stmt);
  std::string printReturnStmt(const ReturnStmtPtr &stmt);
  std::string printVariableStmt(const VariableStmtPtr &stmt);
  std::vector<std::string> printWhileStmt(const WhileStmtPtr &stmt);
};

#endif // PRINTER
