This is a C++ Projects Based on The Book Crafting Interpreters
Although I am using a Book all of the code will be mine, I am only using the books as a reference to what i need to do.

BNF Currently:
  <S> ::= <ASSIGN><S> | <IF><S> | <FUNC><S> | <Return><S> | epsilon
  <ASSIGN> = <FASSIGN> | <REASSIGN> | epsilon
  <FASSIGN> ::= let <name> = <expr> | const <name> = <expr> | var <name> = <expr>
  <REASSIGN> ::= <name> = <expr>
  <expr> ::= <name> | <value> | <FUNCCALL> | (<expr> * <expr>) | (<expr> / <expr>) | (<expr> + <expr>) | (<expr> - <expr>)
  <FUNCCALL> ::= <name>(<arguments>)
  <arguments> ::= <name><morearguments> | <value><morearguments> | epsilon
  <morearguments> ::= ,<name><moreaguments> | ,<value><morearguments> | epsilon
  <IF> ::= if (<boolexpr>) { <IFINSIDE> } | if (<boolexpr>) { <IFINSIDE> } <else> | epsilon
  <else> ::= else { <IFINSIDE> } | else <IF>  | epsilon
  <boolExpr> ::= <boolexpr> && <moreboolexpr> | <boolexpr> || <moreboolexpr> | <boolexpr>
  <boolexpr> ::= <BMOD><

