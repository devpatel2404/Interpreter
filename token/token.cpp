#include "token.h"
#include <string>

Token makeToken(std::string s, TokenType t) { return {s, t}; }

Token makeTokenI(std::string s, TokenType t, int line) { return {s, t, line}; }

std::string TokentypeToString(TokenType t) {
  switch (t) {
  case IDENT:
    return "IDENT";
  case INT:
    return "INT";
  case STRING:
    return "STRING";
  case DECIMAL:
    return "DECIMAL";
  case CHARACTER:
    return "CHARACTER";
  case BOOL:
    return "BOOL";
  case PLUS:
    return "PLUS";
  case MINUS:
    return "MINUS";
  case ASTERISK:
    return "ASTERISK";
  case ASSIGN:
    return "ASSIGN";
  case FSLASH:
    return "FSLASH";
  case AND:
    return "AND";
  case OR:
    return "OR";
  case BITAND:
    return "BITAND";
  case BITOR:
    return "BITOR";
  case MODULOS:
    return "MODULOS";
  case NOT:
    return "NOT";
  case FUNC:
    return "FUNC";
  case IF:
    return "IF";
  case SEMICOLON:
    return "SEMICOLON";
  case TRUE:
    return "TRUE";
  case FALSE:
    return "FALSE";
  case LCURLY:
    return "LCURLY";
  case RCURLY:
    return "RCURLY";
  case LBRACK:
    return "LBRACK";
  case RBRACK:
    return "RBRACK";
  case LPAREN:
    return "LPAREN";
  case RPAREN:
    return "RPAREN";
  case APOSTRAPHE:
    return "APOSTRAPHE";
  case QUOTATION:
    return "QUOTATION";
  case GREATER:
    return "GREATER";
  case GRTOREQ:
    return "GRTOREQ";
  case LESS:
    return "LESS";
  case LESOREQ:
    return "LESOREQ";
  case PIPE:
    return "PIPE";
  case DOT:
    return "DOT";
  case RETURN:
    return "RETURN";
  case FOR:
    return "FOR";
  case WHILE:
    return "WHILE";
  case PRINT:
    return "PRINT";
  case COMMA:
    return "COMMA";
  case COLON:
    return "COLON";
  case VOID:
    return "VOID";
  case NOTEQ:
    return "NOTEQ";
  case null:
    return "null";
  default:
    return "ILLEGAL";
  }
}
