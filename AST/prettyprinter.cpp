#include "./prettyprinter.h"
#include "nodes.h"
#include <iterator>
#include <string>
#include <utility>
#include <vector>

std::string PrettyPrinter::parenthesize(std::string name) {
  return "( " + name + " )";
}

std::string PrettyPrinter::parenthesize(std::string name, ExprVariantPtr expr) {
  return "( " + name + " " + toString(std::move(expr)) + " )";
}

std::string PrettyPrinter::parenthesize(std::string name, ExprVariantPtr left,
                                        ExprVariantPtr right) {
  return "( " + name + " " + toString(std::move(left)) + " " +
         toString(std::move(right)) + " )";
}

std::string PrettyPrinter::toString(ExprVariantPtr expr) {
  switch (expr.index()) {
  case 0:
    return PrettyPrinter::printAssignExpr(std::get<0>(expr));
  case 1:
    return PrettyPrinter::printBinaryExpr(std::get<1>(expr));
  case 2:
    return PrettyPrinter::printCallExpr(std::get<2>(expr));
  case 3:
    return PrettyPrinter::printGetExpr(std::get<3>(expr));
  case 4:
    return PrettyPrinter::printLiteralExpr(std::get<4>(expr));
  case 5:
    return PrettyPrinter::printGroupingExpr(std::get<5>(expr));
  case 6:
    return PrettyPrinter::printUnaryExpr(std::get<6>(expr));
  case 7:
    return PrettyPrinter::printVariableExpr(std::get<7>(expr));
  default:
    std::cout << "Expr found that should not be possible" << std::endl;
    return "";
  }
}

std::string PrettyPrinter::printAssignExpr(const AssignExprPtr &expr) {
  return parenthesize(expr->name.literal, std::move(expr->value));
}

std::string PrettyPrinter::printBinaryExpr(const BinaryExprPtr &expr) {
  return parenthesize(expr->oper.literal, std::move(expr->left),
                      std::move(expr->right));
}

std::string PrettyPrinter::printCallExpr(const CallExprPtr &expr) {
  std::string result;
  for (int i = 0; i < expr->arguments.size(); i++) {
    if (i > 0 && i < expr->arguments.size())
      result +=
          ", "; // this make sure that the parenthesis don't get any commas
    result += "( " + toString(std::move(expr->arguments[i])) + " )";
  }
  return parenthesize("(" + result + ")", std::move(expr->callee));
}

std::string PrettyPrinter::printGetExpr(const GetExprPtr &expr) {
  return parenthesize(expr->name.literal, std::move(expr->object));
}

std::string PrettyPrinter::printLiteralExpr(const LiteralExprPtr &expr) {
  switch (expr->literal.index()) {
  case 0:
    return std::to_string(std::get<0>(expr->literal));
  case 1:
    return std::get<1>(expr->literal);
  case 2: {
    std::string str = "";
    str += std::get<2>(expr->literal);
    return str;
  }
  case 3:
    return std::to_string(std::get<3>(expr->literal));
  case 4:
    return (std::get<4>(expr->literal)) ? "true" : "false";
  default:
    return "";
  }
}

std::string PrettyPrinter::printGroupingExpr(const GroupingExprPtr &expr) {
  return parenthesize("group", std::move(expr->expr));
}

std::string PrettyPrinter::printUnaryExpr(const UnaryExprPtr &expr) {
  return parenthesize(expr->oper.literal, std::move(expr->right));
}

std::string PrettyPrinter::printVariableExpr(const VariableExprPtr &expr) {
  return parenthesize(expr->name.literal);
}

std::vector<std::string> PrettyPrinter::toString(StmtVariantPtr stmt) {
  switch (stmt.index()) {
  case 0:
    return printBlockStmt(std::get<0>(stmt));
  case 1:
    return std::vector(1, printExpressionStmt(std::get<1>(stmt)));
  case 2:
    return printFunctionStmt(std::get<2>(stmt));
  case 3:
    return std::vector(1, printPrintStmt(std::get<3>(stmt)));
  case 4:
    return std::vector(1, printReturnStmt(std::get<4>(stmt)));
  case 5:
    return std::vector(1, printVariableStmt(std::get<5>(stmt)));
  case 6:
    return printWhileStmt(std::get<6>(stmt));
  case 7:
    return printIfStmt(std::get<7>(stmt));
  default:
    std::cout << "Unexpected statement was encountered" << std::endl;
    return {""};
  }
}

std::vector<std::string>
PrettyPrinter::printBlockStmt(const BlockStmtPtr &stmt) {
  std::vector<std::string> blockstring;
  blockstring.push_back("{");
  for (StmtVariantPtr &svp : stmt->statements) {
    std::vector<std::string> s = toString(std::move(svp));
    if (!s.empty())
      std::move(s.begin(), s.end(), std::back_insert_iterator(s));
  }

  return blockstring;
}

std::string PrettyPrinter::printExpressionStmt(const ExpressionStmtPtr &stmt) {
  return parenthesize("Expression", std::move(stmt->expression));
}

std::string PrettyPrinter::printPrintStmt(const PrintStmtPtr &stmt) {
  return parenthesize("Print: ", std::move(stmt->expression)) + ";";
}

std::string PrettyPrinter::printReturnStmt(const ReturnStmtPtr &stmt) {
  std::string retVal = toString(std::move(stmt->value));
  return "{ return: " + retVal + " }";
}

std::string PrettyPrinter::printVariableStmt(const VariableStmtPtr &stmt) {
  return parenthesize(stmt->name.literal, std::move(stmt->initalizer));
}

std::vector<std::string>
PrettyPrinter::printFunctionStmt(const FunctionStmtPtr &stmt) {
  std::vector<std::string> functionStrVec;
  functionStrVec.emplace_back("{ func (" + stmt->name.literal + ") {");
  std::string s;
  for (Token t : stmt->params) {
    s += (t.literal + ' ');
  }
  functionStrVec.emplace_back(s);
  for (StmtVariantPtr &svp : stmt->body) {
    std::vector<std::string> svpstr = toString(std::move(svp));
    if (!svpstr.empty())
      std::move(svpstr.begin(), svpstr.end(),
                std::back_insert_iterator(functionStrVec));
  }
  functionStrVec.emplace_back("} )");
  return functionStrVec;
}

std::vector<std::string>
PrettyPrinter::printWhileStmt(const WhileStmtPtr &stmt) {
  std::vector<std::string> whileStrVec;
  whileStrVec.emplace_back("{ while (" + toString(std::move(stmt->condition)) +
                           ") {");
  std::vector<std::string> svpstr = toString(std::move(stmt->body));
  if (!svpstr.empty())
    std::move(svpstr.begin(), svpstr.end(),
              std::back_insert_iterator(whileStrVec));
  whileStrVec.emplace_back("}");
  return whileStrVec;
}

std::vector<std::string> PrettyPrinter::printIfStmt(const IfStmtPtr &stmt) {
  std::vector<std::string> ifStrVec;
  ifStrVec.emplace_back("{ if ( " + toString(std::move(stmt->condition)) +
                        " )");
  std::vector<std::string> stmtsvp = toString(std::move(stmt->thenBranch));
  if (!stmtsvp.empty())
    std::move(stmtsvp.begin(), stmtsvp.end(),
              std::back_insert_iterator(ifStrVec));
  stmtsvp = toString(std::move(stmt->elseBranch));
  if (!stmtsvp.empty())
    std::move(stmtsvp.begin(), stmtsvp.end(),
              std::back_insert_iterator(ifStrVec));
  ifStrVec.emplace_back(" )");
  return ifStrVec;
}

void PrettyPrinter::print(ExprVariantPtr expr) {
  std::cout << toString(std::move(expr)) << std::endl;
  std::cout << "PrettyPrinter Finished" << std::endl;
}
