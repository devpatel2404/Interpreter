#include "nodes.h"
#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

AssignExpr::AssignExpr(Token name, ExprVariantPtr value)
    : name(name), value(std::move(value)) {}

BinaryExpr::BinaryExpr(ExprVariantPtr left, Token oper, ExprVariantPtr right)
    : left(std::move(left)), oper(oper), right(std::move(right)) {}

CallExpr::CallExpr(ExprVariantPtr callee, Token paren,
                   std::vector<ExprVariantPtr> arguments)
    : callee(std::move(callee)), paren(paren), arguments(std::move(arguments)) {
}

GetExpr::GetExpr(ExprVariantPtr object, Token name)
    : object(std::move(object)), name(name) {}

GroupingExpr::GroupingExpr(ExprVariantPtr expr) : expr(std::move(expr)) {}

LiteralExpr::LiteralExpr(
    std::variant<int, std::string, char, double, bool> literal)
    : literal(literal) {}

LogicalExpr::LogicalExpr(ExprVariantPtr left, Token oper, ExprVariantPtr right)
    : left(std::move(left)), oper(oper), right(std::move(right)) {}

UnaryExpr::UnaryExpr(Token oper, ExprVariantPtr right)
    : oper(oper), right(std::move(right)) {}

VariableExpr::VariableExpr(Token name) : name(name) {}

BlockStmt::BlockStmt(std::vector<StmtVariantPtr> statements)
    : statements(std::move(statements)) {}

ExpressionStmt::ExpressionStmt(ExprVariantPtr expression)
    : expression(std::move(expression)) {}

FunctionStmt::FunctionStmt(Token name, std::vector<Token> params,
                           std::vector<StmtVariantPtr> body)
    : name(name), params(params), body(std::move(body)) {}

IfStmt::IfStmt(ExprVariantPtr condition, StmtVariantPtr thenBranch,
               StmtVariantPtr elseBranch)
    : condition(std::move(condition)), thenBranch(std::move(thenBranch)),
      elseBranch(std::move(elseBranch)) {}

PrintStmt::PrintStmt(ExprVariantPtr expression)
    : expression(std::move(expression)) {}

ReturnStmt::ReturnStmt(Token keyword, ExprVariantPtr value)
    : keyword(keyword), value(std::move(value)) {}

VariableStmt::VariableStmt(Token name, ExprVariantPtr initalizer)
    : name(name), initalizer(std::move(initalizer)) {}

WhileStmt::WhileStmt(ExprVariantPtr condition, StmtVariantPtr body)
    : condition(std::move(condition)), body(std::move(body)) {}

// make the createBinaryEVPTR
//
auto createAssignEVPTR(Token name, ExprVariantPtr value) -> ExprVariantPtr {
  return std::make_unique<AssignExpr>(name, std::move(value));
}

auto createBinaryEVPTR(ExprVariantPtr left, Token oper, ExprVariantPtr right)
    -> ExprVariantPtr {
  return std::make_unique<BinaryExpr>(std::move(left), oper, std::move(right));
}

auto createCallEVPTR(ExprVariantPtr object, Token paren,
                     std::vector<ExprVariantPtr> arguments) -> ExprVariantPtr {
  return std::make_unique<CallExpr>(std::move(object), paren,
                                    std::move(arguments));
}

auto createGetEVPTR(ExprVariantPtr object, Token name) -> ExprVariantPtr {
  return std::make_unique<GetExpr>(std::move(object), name);
}

auto createGroupingEVPTR(ExprVariantPtr expr) -> ExprVariantPtr {
  return std::make_unique<GroupingExpr>(std::move(expr));
}

auto createLiteralEVPTR(
    std::variant<int, std::string, char, double, bool> literal)
    -> ExprVariantPtr {
  return std::make_unique<LiteralExpr>(literal);
}

auto createUnaryEVPTR(Token oper, ExprVariantPtr right) -> ExprVariantPtr {
  return std::make_unique<UnaryExpr>(oper, std::move(right));
}

auto createVariableEVPTR(Token name) -> ExprVariantPtr {
  return std::make_unique<VariableExpr>(name);
}

auto createBlockSVPTR(std::vector<StmtVariantPtr> statements)
    -> StmtVariantPtr {
  return std::make_unique<BlockStmt>(std::move(statements));
}

auto createExpressionSVPTR(ExprVariantPtr expression) -> StmtVariantPtr {
  return std::make_unique<ExpressionStmt>(std::move(expression));
}

auto createFunctionSVPTR(Token name, std::vector<Token> params,
                         std::vector<StmtVariantPtr> body) -> StmtVariantPtr {
  return std::make_unique<FunctionStmt>(name, params, std::move(body));
}

auto createIfSVPTR(ExprVariantPtr condition, StmtVariantPtr thenBranch,
                   StmtVariantPtr elseBranch) -> StmtVariantPtr {
  return std::make_unique<IfStmt>(std::move(condition), std::move(thenBranch),
                                  std::move(elseBranch));
}

auto createPrintSVPTR(ExprVariantPtr expression) -> StmtVariantPtr {
  return std::make_unique<PrintStmt>(std::move(expression));
}

auto createReturnSVPTR(Token keyword, ExprVariantPtr value) -> StmtVariantPtr {
  return std::make_unique<ReturnStmt>(keyword, std::move(value));
}

auto createVariableEVPTR(Token name, ExprVariantPtr initalizer)
    -> StmtVariantPtr {
  return std::make_unique<VariableStmt>(name, std::move(initalizer));
}

auto createWhileSVPTR(ExprVariantPtr condition, StmtVariantPtr body)
    -> StmtVariantPtr {
  return std::make_unique<WhileStmt>(std::move(condition), std::move(body));
}
