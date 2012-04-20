/* $Id: parser.yy 48 2009-09-05 08:07:10Z tb $ -*- mode: c++ -*- */
/** \file parser.yy Contains the example Bison parser source */

%{ /*** C/C++ Declarations ***/

#include "kiwi/Config.hpp"
#include <stdio.h>
#include <string>
#include <vector>
#include "ExpressionNode.hpp"
#include "TypeNode.hpp"
#include "FunctionNode.hpp"

%}

/*** yacc/bison Declarations ***/

/* Require bison 2.3 or later */
%require "2.3"

/* add debug output code to generated parser. disable this for release
 * versions. */
%debug

/* start symbol is named "start" */
%start start

/* write out a header file containing the token defines */
%defines

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"

/* namespace to enclose parser in */
%name-prefix="kiwi::lang"

/* set the parser's class identifier */
%define "parser_class_name" "Parser"

/* keep track of the current position within the input */
%locations
%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &driver.streamname;
};

/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class Driver& driver }

/* verbose error messages */
%error-verbose

 /*** BEGIN EXAMPLE - Change the example grammar's tokens below ***/

%union {
    int                  integerVal;
    double               doubleVal;
    std::string*		 stringVal;
    String*              ustringVal;
    UChar                charVal;

    class TypeNode*		 typenode;
    class LeftNode*      leftnode;
    class RightNode*     rightnode;
    class StatementNode* stmtnode;
}

%token                  END             0   "end of file"
%token                  EOL                 "end of line"
%token                  UNIX_SCRIPT         "unix script"

%token                  OP_LSH              "<<"
%token                  OP_RSH              ">>"
%token                  OP_OR               "||"
%token                  OP_AND              "&&"
%token                  OP_EQ               "=="
%token                  OP_NE               "!="
%token                  OP_GE               ">="
%token                  OP_LE               "<="
%token                  OP_INC              "++"
%token                  OP_DEC              "--"
%token                  OP_AADD             "+="
%token                  OP_ASUB             "-="
%token                  OP_ADIV             "/="
%token                  OP_AMUL             "*="
%token                  OP_ASHL             "<<="
%token                  OP_ASHR             ">>="
%token                  OP_AAND             "&="
%token                  OP_AOR              "|="

%token  <stringVal>     IDENT               "identifier"

%token  <integerVal>    INTEGER             "integer constant"
%token  <ustringVal>    STRING              "string constant"
%token  <charVal>       CHAR                "char constant"
%token  <stringVal>     VAR_LOCAL           "local variable"
%token  <stringVal>     VAR_INSTANCE        "instance attribute"

%token                  TYPE_VOID           "void type"
%token                  TYPE_INT            "int type"
%token                  TYPE_BOOL           "bool type"
%token                  TYPE_CHAR           "char type"
%token                  TYPE_STRING         "string type"

%token                  RETURN              "return"
%token                  IF                  "if"
%token                  ELSE                "else"
%token                  IFELSE              "ifelse"
%token                  PRINT               "print"

%left       '=' "+=" "-=" "/=" "*=" "<<=" ">>=" "&=" "|="
%left       "||"
%left       "&&"
%left       '|'
//%left       '^'
%left       '&'
%nonassoc   "==" "!="
%nonassoc   '<' '>' "<=" ">="
%left       ">>" "<<"
%left       '-' '+'
%left       '*' '/' '%'
%right      UNARY '!'
%right      PRE '.' '[' '('

%type   <typenode>      type type_complex type_primary
%type   <rightnode>     expression right call_expression
%type   <leftnode>      left
%type   <stmtnode>      scope return_statement print_statement

%destructor { delete $$; } IDENT VAR_LOCAL VAR_INSTANCE
%destructor { delete $$; } expression right call_expression
%destructor { delete $$; } type type_complex type_primary
%destructor { delete $$; } scope return_statement print_statement
%destructor { delete $$; } STRING

 /*** END EXAMPLE - Change the example grammar's tokens above ***/

%{

#include "Driver.hpp"
#include "scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

%}

%% /*** Grammar Rules ***/

 /*** BEGIN GRAMAR - Change the example grammar rules below ***/

//==------------------------------------------------------------------------==//
//      Functions
//==------------------------------------------------------------------------==//
function
    : type IDENT                    { driver.func(*$2, $1); }
      '(' function_arguments ')'
      function_statement
                                    { driver.funcEnd();     }
    ;

function_arguments
    : /* empty */
    | function_arguments_required
    ;

function_arguments_required
    : function_arguments_required ',' function_argument
    | function_argument
    ;

function_argument
    : type VAR_LOCAL                { driver.func()->declare(*$2, $1); }
    ;

function_statement
    : '{' statements '}'
    ;

//==------------------------------------------------------------------------==//
//      Statements
//==------------------------------------------------------------------------==//
statements
    : /** empty */
    | expression ';'        { driver.scope()->append($1); } statements
    | scope                 { driver.scope()->append($1); } statements
    | return_statement      { driver.scope()->append($1); } statements
    | print_statement       { driver.scope()->append($1); } statements
    | variable_declare ';' statements
    | ';'
    ;

scope
    : '{'               { driver.scopeBegin(); }
        scope_end
    ;

scope_end
    : statements '}'    { driver.scopeEnd(); }
    ;

return_statement
    : RETURN ';'                    { $$ = driver.createReturn(@1);     }
    | RETURN expression ';'         { $$ = driver.createReturn($2, @1); }
    ;

print_statement
    : PRINT expression  ';'         { $$ = driver.createPrint($2, @1);  }

//==------------------------------------------------------------------------==//
//      Calls
//==------------------------------------------------------------------------==//
call_expression
    : IDENT                         { driver.call();                }
        '(' call_arguments ')'      { $$ = driver.callEnd();        }
    ;

call_arguments
    : /* empty */
    | call_arguments_required
    ;

call_arguments_required
    : call_argument ',' call_arguments_required
    | call_argument
    ;

call_argument
    : IDENT ':' expression          { driver.call()->append(*$1, $3); }
    | expression                    { driver.call()->append($1);      }
    ;

//==------------------------------------------------------------------------==//
//      Expressions
//==------------------------------------------------------------------------==//

variable_declare
    : type VAR_LOCAL                { driver.scope()->declare(*$2, $1); }
    ;

expression
    : '-' expression %prec UNARY    { $$ = driver.createNeg($2, @1); }
    | '+' expression %prec UNARY    { $$ = driver.createPos($2, @1); }
    | '!' expression %prec UNARY    { $$ = driver.createNot($2, @1); }


    | expression '+'   expression   { $$ = driver.createAdd($1, $3, @2); }
    | expression '-'   expression   { $$ = driver.createSub($1, $3, @2); }
    | expression '*'   expression   { $$ = driver.createMul($1, $3, @2); }
    | expression '/'   expression   { $$ = driver.createDiv($1, $3, @2); }
    | expression "<<"  expression   { $$ = driver.createLsh($1, $3, @2); }
    | expression ">>"  expression   { $$ = driver.createRsh($1, $3, @2); }

    | expression '|'   expression   { $$ = driver.createOr ($1, $3, false, @2); }
    | expression "||"  expression   { $$ = driver.createOr ($1, $3, true,  @2); }
    | expression '&'   expression   { $$ = driver.createAnd($1, $3, false, @2); }
    | expression "&&"  expression   { $$ = driver.createAnd($1, $3, true,  @2); }

    | expression "=="  expression   { $$ = driver.createEq ($1, $3, @2); }
    | expression "!="  expression   { $$ = driver.createNeq($1, $3, @2); }
    | expression ">="  expression   { $$ = driver.createGe ($1, $3, @2); }
    | expression "<="  expression   { $$ = driver.createLe ($1, $3, @2); }
    | expression ">"   expression   { $$ = driver.createGt ($1, $3, @2); }
    | expression "<"   expression   { $$ = driver.createLt ($1, $3, @2); }

    | left       '='   expression   { $$ = driver.createAssign($1, $3, @2); }
    | right
    ;

left
    : VAR_LOCAL                     { $$ = driver.left(*$1, @1); }
    ;

right
    : VAR_LOCAL                     { $$ = driver.right(*$1, @1);           }
    | INTEGER                       { $$ = driver.createInt($1, @1);        }
    | STRING                        { $$ = driver.createString(*$1, @1);    }
    | CHAR                          { $$ = driver.createChar($1, @1);       }
    | '(' expression ')'            { $$ = $2;                              }
    | call_expression               { $$ = $1;                              }
    ;


//==------------------------------------------------------------------------==//
//      Types
//==------------------------------------------------------------------------==//
type
    : type_complex
    | type_primary
    | TYPE_VOID             { $$ = driver.createVoidTy(@1);    }
    ;

type_complex
    : type_primary '[' ']'  { $$ = driver.createArrayTy($1, @2 + @3); }
    ;

type_primary
    : TYPE_INT              { $$ = driver.createIntTy(@1);     }
    | TYPE_BOOL             { $$ = driver.createBoolTy(@1);    }
    | TYPE_STRING           { $$ = driver.createStringTy(@1);  }
    | TYPE_CHAR             { $$ = driver.createCharTy(@1);    }
    ;

/** START POINT **/
start
    : /* empty */
    | function start END
    ;

/*** END GRAMAR - Change the example grammar rules above ***/

%% /*** Additional Code ***/

void kiwi::lang::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}
