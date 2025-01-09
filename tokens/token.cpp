#include "./token.h"
#include <cctype>
#include <stdexcept>
#include <string>

bool isNum(std::string t) {
  try {
    std::stod(t);
    return true;
  } catch (const std::invalid_argument &) {
    return false;
  } catch (const std::out_of_range &) {
    return false;
  }
}

bool isName(std::string t) {
  int i = 0;
  while (i < t.size()) {
    i++;
    if (isalpha(t[i - 1]))
      continue;
    else if (t[i - 1] == '-' || t[i - 1] == '_')
      continue;
    else if (t[i - 1] - '0' >= 0 && t[i - 1] - '9' <= 0)
      continue;
    else
      return false;
  }
  return true;
}

tokentype getTokenType(std::string t) {
  if (t.size() == 0)
    return INVALID;
  if (t.size() == 1)
    return getTokenType2(t[0]);
  else if (t == "&&")
    return AND;
  else if (t == "||")
    return OR;
  else if (t == ">=")
    return GTOREQ;
  else if (t == "<=")
    return LSOREQ;
  else if (t == "let")
    return LET;
  else if (t == "const")
    return CONST;
  else if (t == "var")
    return VAR;
  else if (t == "return")
    return RETURN;
  else if (t == "true")
    return TRUE;
  else if (t == "false")
    return FALSE;
  else if (t == "==")
    return CHECK;
  else if (t == "if")
    return IF;
  else if (t == "public")
    return PUBLIC;
  else if (t == "private")
    return PRIVATE;
  else if (t == "protected")
    return PROTECTED;
  else if (t == "func")
    return FUNC;
  else if (isalpha(t[0]) && isName(t))
    return NAME;
  else if (isNum(t))
    return NUMBER;
  return INVALID;
}

tokentype getTokenType2(char val) {
  switch (val) {
  case 33:
    return NOT;
  case 34:
    return QUOTE;
  case 37:
    return MODULO;
  case 38:
    return BITAND;
  case 39:
    return APOS;
  case 40:
    return LPAREN;
  case 41:
    return RPAREN;
  case 42:
    return MULT;
  case 43:
    return ADD;
  case 44:
    return COMMA;
  case 45:
    return SUB;
  case 47:
    return DIV;
  case 59:
    return SEMICOLON;
  case 60:
    return GREATER;
  case 61:
    return ASSIGN;
  case 62:
    return LESS;
  case 92:
    return EXIT;
  case 123:
    return LCURLY;
  case 124:
    return BITOR;
  case 125:
    return RCURLY;
  case 48 ... 57:
    return NUMBER;
  case 65 ... 90:
  case 97 ... 122:
    return NAME;
  default:
    return INVALID;
  }
}

std::string tokenToString(tokentype token) {
  switch (token) {
  case LBRACKET:
    return "LBRACKET";
  case RBRACKET:
    return "RBRACKET";
  case LPAREN:
    return "LPAREN";
  case RPAREN:
    return "RPAREN";
  case LCURLY:
    return "LCURLY";
  case RCURLY:
    return "RCURLY";
  case SEMICOLON:
    return "SEMICOLON";
  case eof:
    return "EOF";
  case COMMA:
    return "COMMA";
  case LET:
    return "LET";
  case VAR:
    return "VAR";
  case CONST:
    return "CONST";
  case NAME:
    return "NAME";
  case ASSIGN:
    return "ASSIGN";
  case MULT:
    return "MULT";
  case DIV:
    return "DIV";
  case SUB:
    return "SUB";
  case ADD:
    return "ADD";
  case MODULO:
    return "MODULO";
  case BITAND:
    return "BITAND";
  case BITOR:
    return "BITOR";
  case NUMBER:
    return "NUMBER";
  case APOS:
    return "APOS";
  case QUOTE:
    return "QUOTE";
  case EXIT:
    return "EXIT";
  case TRUE:
    return "TRUE";
  case FALSE:
    return "FALSE";
  case NOT:
    return "NOT";
  case CHECK:
    return "CHECK";
  case IF:
    return "IF";
  case AND:
    return "AND";
  case OR:
    return "OR";
  case GREATER:
    return "GREATER";
  case GTOREQ:
    return "GTOREQ";
  case LESS:
    return "LESS";
  case LSOREQ:
    return "LSOREQ";
  case PUBLIC:
    return "PUBLIC";
  case PRIVATE:
    return "PRIVATE";
  case PROTECTED:
    return "PROTECTED";
  case FUNCPARAM:
    return "FUNCPARAM";
  case RETURN:
    return "RETURN";
  case FUNC:
    return "FUNC";
  case INVALID:
    return "INVALID";
  default:
    return "UNKNOWN";
  }
}
