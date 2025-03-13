#ifndef TYPES
#define TYPES

#include "../token/token.h"
#include <cstddef>
#include <memory>
#include <string>
#include <variant>
#include <vector>

struct AssignExpr;
struct BinaryExpr;
struct CallExpr;
struct GetExpr;
struct GroupingExpr;
struct LiteralExpr;
struct UnaryExpr;
struct VariableExpr;

using AssignExprPtr = std::unique_ptr<AssignExpr>;
using BinaryExprPtr = std::unique_ptr<BinaryExpr>;
using CallExprPtr = std::unique_ptr<CallExpr>;
using GetExprPtr = std::unique_ptr<GetExpr>;
using LiteralExprPtr = std::unique_ptr<LiteralExpr>;
using GroupingExprPtr = std::unique_ptr<GroupingExpr>;
using UnaryExprPtr = std::unique_ptr<UnaryExpr>;
using VariableExprPtr = std::unique_ptr<VariableExpr>;

using ExprVariantPtr = std::variant<AssignExprPtr, BinaryExprPtr, CallExprPtr,
                                    GetExprPtr, LiteralExprPtr, GroupingExprPtr,
                                    UnaryExprPtr, VariableExprPtr, nullptr_t>;

struct BlockStmt;
struct ExpressionStmt;
struct FunctionStmt;
struct PrintStmt;
struct ReturnStmt;
struct IfStmt;
struct VariableStmt;
struct WhileStmt;

using BlockStmtPtr = std::unique_ptr<BlockStmt>;
using ExpressionStmtPtr = std::unique_ptr<ExpressionStmt>;
using FunctionStmtPtr = std::unique_ptr<FunctionStmt>;
using PrintStmtPtr = std::unique_ptr<PrintStmt>;
using IfStmtPtr = std::unique_ptr<IfStmt>;
using ReturnStmtPtr = std::unique_ptr<ReturnStmt>;
using VariableStmtPtr = std::unique_ptr<VariableStmt>;
using WhileStmtPtr = std::unique_ptr<WhileStmt>;

using StmtVariantPtr =
    std::variant<BlockStmtPtr, ExpressionStmtPtr, FunctionStmtPtr, PrintStmtPtr,
                 ReturnStmtPtr, VariableStmtPtr, WhileStmtPtr, IfStmtPtr,
                 nullptr_t>;

auto createAssignEVPTR(Token name, ExprVariantPtr value) -> ExprVariantPtr;
auto createBinaryEVPTR(ExprVariantPtr left, Token oper, ExprVariantPtr right)
    -> ExprVariantPtr;
auto createCallEVPTR(ExprVariantPtr callee, Token paren,
                     std::vector<ExprVariantPtr> arguments) -> ExprVariantPtr;
auto createGetEVPTR(ExprVariantPtr object, Token name) -> ExprVariantPtr;
auto createGroupingEVPTR(ExprVariantPtr expr) -> ExprVariantPtr;
auto createLiteralEVPTR(
    std::variant<int, std::string, char, double, bool> literal)
    -> ExprVariantPtr;
auto createUnaryEVPTR(Token oper, ExprVariantPtr right) -> ExprVariantPtr;
auto createVariableEVPTR(Token name) -> ExprVariantPtr;
auto createBlockSVPTR(std::vector<StmtVariantPtr> statements) -> StmtVariantPtr;
auto createExpressionSVPTR(ExprVariantPtr expression) -> StmtVariantPtr;
auto createFunctionSVPTR(Token name, std::vector<Token> params,
                         std::vector<StmtVariantPtr> body) -> StmtVariantPtr;
auto createIfSVPTR(ExprVariantPtr condition, StmtVariantPtr thenBranch,
                   StmtVariantPtr elseBranch) -> StmtVariantPtr;
auto createPrintSVPTR(ExprVariantPtr expression) -> StmtVariantPtr;
auto createReturnSVPTR(Token keyword, ExprVariantPtr value) -> StmtVariantPtr;
auto createVariableSVPTR(Token name, ExprVariantPtr initalizer)
    -> StmtVariantPtr;
auto createWhileSVPTR(ExprVariantPtr condition, StmtVariantPtr body)
    -> StmtVariantPtr;

struct AssignExpr {
  Token name;
  ExprVariantPtr value;
  AssignExpr(Token name, ExprVariantPtr value);
};

struct BinaryExpr {
  ExprVariantPtr left;
  Token oper;
  ExprVariantPtr right;
  BinaryExpr(ExprVariantPtr left, Token oper, ExprVariantPtr right);
};

struct CallExpr {
  ExprVariantPtr callee;
  Token paren;
  std::vector<ExprVariantPtr> arguments;
  CallExpr(ExprVariantPtr callee, Token paren,
           std::vector<ExprVariantPtr> arguments);
};

struct GetExpr {
  ExprVariantPtr object;
  Token name;
  GetExpr(ExprVariantPtr object, Token name);
};

struct GroupingExpr {
  ExprVariantPtr expr;
  GroupingExpr(ExprVariantPtr expr);
};

struct LiteralExpr {
  std::variant<int, std::string, char, double, bool> literal;
  LiteralExpr(std::variant<int, std::string, char, double, bool> literal);
};

struct LogicalExpr {
  ExprVariantPtr left;
  Token oper;
  ExprVariantPtr right;
  LogicalExpr(ExprVariantPtr left, Token oper, ExprVariantPtr right);
};

struct UnaryExpr {
  Token oper;
  ExprVariantPtr right;
  UnaryExpr(Token oper, ExprVariantPtr right);
};

struct VariableExpr {
  Token name;
  VariableExpr(Token name);
};

struct BlockStmt {
  std::vector<StmtVariantPtr> statements;
  BlockStmt(std::vector<StmtVariantPtr> statements);
};

struct ExpressionStmt {
  ExprVariantPtr expression;
  ExpressionStmt(ExprVariantPtr expression);
};

struct FunctionStmt {
  Token name;
  std::vector<Token> params;
  std::vector<StmtVariantPtr> body;
  FunctionStmt(Token name, std::vector<Token> params,
               std::vector<StmtVariantPtr> body);
};

struct IfStmt {
  ExprVariantPtr condition;
  StmtVariantPtr thenBranch;
  StmtVariantPtr elseBranch;
  IfStmt(ExprVariantPtr condition, StmtVariantPtr thenBranch,
         StmtVariantPtr elseBranch);
};

struct PrintStmt {
  ExprVariantPtr expression;
  PrintStmt(ExprVariantPtr expression);
};

struct ReturnStmt {
  Token keyword;
  ExprVariantPtr value;
  ReturnStmt(Token keyword, ExprVariantPtr value);
};

struct VariableStmt {
  Token name;
  ExprVariantPtr initalizer;
  VariableStmt(Token name, ExprVariantPtr initalizer);
};

struct WhileStmt {
  ExprVariantPtr condition;
  StmtVariantPtr body;
  WhileStmt(ExprVariantPtr condition, StmtVariantPtr body);
};

#endif
