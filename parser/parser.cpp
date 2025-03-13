#include "./parser.h"
#include <cstddef>
#include <iterator>

parser::parser(std::vector<Token> toks)
    : tokens(toks), idx(0), scoping(), level(0) {
  next_token();
}

void parser::reset() {
  idx = 0;
  level = 0;
  next_token();
}

void parser::printTokens() {
  for (Token t : tokens) {
    std::cout << "\t Token: " << TokentypeToString(t.token)
              << " Line: " << t.line << " Literal: " << t.literal << std::endl;
  }
}

void parser::fixLines(int first, int second) {
  std::cout << std::endl;
  for (int i = first + 1; i <= second; i++) {
    std::cout << "\tLine " << i << " : ";
    if (second - i > 0)
      std::cout << std::endl;
  }

  return;
}

void parser::construct() {
  int x = tokens[0].line;
  std::cout << "\tLine " << x << " : ";
  for (Token t : tokens) {
    if (t.line > x) {
      fixLines(x, t.line);
      x = t.line;
    }
    std::cout << t.literal << ' ';
  }
  std::cout << std::endl;
  return;
}

bool parser::match(std::vector<TokenType> types) {
  for (TokenType t : types) {
    if (check(t)) {
      next_token();
      return true;
    }
  }

  return false;
}

bool parser::check(TokenType type) {
  if (peekTok().token == EoF)
    return false;
  return peekTok().token == type;
}

bool parser::parseFunc() {
  next_token();
  if (curr.token != IDENT) {
    errorI(level, "No function name");
  }

  return true;
}

Token parser::peekTok() {
  if (idx == tokens.size() - 1)
    return {NULL, EoF};
  return tokens[idx + 1];
}

Token parser::next_token() {
  if (idx == tokens.size() - 1)
    return {NULL, EoF};
  curr = tokens[++idx];
  return curr;
}

Token parser::previous() {
  if (idx == 0)
    return {NULL, ILLEGAL};
  else
    return tokens[idx - 1];
}

void parser::sync() {
  next_token();
  while (curr.token != EoF) {
    if (curr.token == SEMICOLON)
      return;

    switch (peekTok().token) {
    case FUNC:
    case INT:
    case STRING:
    case BOOL:
    case DECIMAL:
    case VOID:
    case CHARACTER:
    case FOR:
    case WHILE:
    case IF:
    case PRINT:
      return;
    default:
      next_token();
    }
  }
}

ExprVariantPtr parser::parse() {
  try {
    std::cout << "Trying to parse the Expression" << std::endl;
    return expression();
  } catch (ParseError error) {
    return nullptr;
  }
}

ExprVariantPtr parser::expression() {
  ExprVariantPtr expr = comparison();

  while (match({NOTEQ, CHECK})) {
    Token oper = previous();
    std::cout << " " << oper.literal << " ";
    expr = createAssignEVPTR(oper, comparison());
  }

  return expr;
}

ExprVariantPtr parser::comparison() {
  ExprVariantPtr expr = term();

  while (match({GREATER, GRTOREQ, LESS, LESOREQ})) {
    Token oper = previous();
    std::cout << " " << oper.literal << " ";
    ExprVariantPtr right = term();
    expr = createBinaryEVPTR(std::move(expr), oper, std::move(right));
  }

  return expr;
}

ExprVariantPtr parser::term() {
  ExprVariantPtr expr = factor();

  while (match({MINUS, PLUS})) {
    Token oper = previous();
    std::cout << " " << oper.literal << " ";
    ExprVariantPtr right = factor();
    expr = createBinaryEVPTR(std::move(expr), oper, std::move(right));
  }

  return expr;
}

ExprVariantPtr parser::factor() {
  ExprVariantPtr expr = unary();

  while (match({ASTERISK, FSLASH})) {
    Token oper = previous();
    std::cout << " " << oper.literal << " ";
    ExprVariantPtr right = unary();
    expr = createBinaryEVPTR(std::move(expr), oper, std::move(right));
  }

  return expr;
}

ExprVariantPtr parser::unary() {
  if (match({NOT, MINUS})) {
    Token oper = previous();
    std::cout << " " << oper.literal << " ";
    ExprVariantPtr right = unary();
    return createUnaryEVPTR(oper, std::move(right));
  }

  return primary();
}

ExprVariantPtr parser::primary() {
  if (match({FALSE})) {
    std::cout << " false";
    return createLiteralEVPTR(false);
  }
  if (match({TRUE})) {
    std::cout << " true";
    return createLiteralEVPTR(true);
  }

  if (match({INT, DECIMAL, STRING, CHARACTER})) {
    std::cout << " " << previous().literal;
    return createLiteralEVPTR(previous().literal);
  }

  if (match({LPAREN})) {
    ExprVariantPtr expr = expression();
    consume(RPAREN, "Expect ')' after expression.");
    return createGroupingEVPTR(std::move(expr));
  }

  errorT(peekTok(), "Expect Expression.");
  return nullptr;
}

Token parser::consume(TokenType type, std::string message) {
  if (check(type))
    return next_token();

  throw error(peekTok(), message);
}

std::shared_ptr<ParseError> parser::error(Token token, std::string message) {
  errorT(token, message);
  std::cout << "Returning error" << std::endl;
  return std::make_shared<ParseError>("An error occured");
}

// make the Printer for the Parser.
