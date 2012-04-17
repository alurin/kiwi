/* $Id: parser.yy 48 2009-09-05 08:07:10Z tb $ -*- mode: c++ -*- */
/** \file parser.yy Contains the example Bison parser source */

%{ /*** C/C++ Declarations ***/

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

%token  <integerVal>    INTEGER             "integer"
%token  <stringVal>     VAR_LOCAL           "local variable"
%token  <stringVal>     VAR_INSTANCE        "instance attribute"

%token                  TYPE_VOID           "void"
%token                  TYPE_INT            "int"
%token                  TYPE_STRING         "string"

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
%type   <rightnode>     expression right
%type   <leftnode>      left
%type   <stmtnode>      scope

%destructor { delete $$; } IDENT VAR_LOCAL VAR_INSTANCE
%destructor { delete $$; } type type_complex type_primary
%destructor { delete $$; } scope

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

//==------------------------------------------------------------------------==//
//      Expressions
//==------------------------------------------------------------------------==//

variable_declare
    : type VAR_LOCAL                { driver.scope()->declare(*$2, $1); }
    ;

expression
    : '-' expression %prec UNARY    { $$ = driver.expr()->getNeg($2); }
    | '+' expression %prec UNARY    { $$ = driver.expr()->getAdd($2); }
    | '!' expression %prec UNARY    { $$ = driver.expr()->getNot($2); }


    | expression '+'   expression   { $$ = driver.expr()->getAdd($1, $3); }
    | expression '-'   expression   { $$ = driver.expr()->getSub($1, $3); }
    | expression '*'   expression   { $$ = driver.expr()->getMul($1, $3); }
    | expression '/'   expression   { $$ = driver.expr()->getDiv($1, $3); }
    | expression "<<"  expression   { $$ = driver.expr()->getLsh($1, $3); }
    | expression ">>"  expression   { $$ = driver.expr()->getRsh($1, $3); }

    | expression '|'   expression   { $$ = driver.expr()->getOr($1, $3); }
    | expression "||"  expression   { $$ = driver.expr()->getOr($1, $3, true); }
    | expression '&'   expression   { $$ = driver.expr()->getAnd($1, $3); }
    | expression "&&"  expression   { $$ = driver.expr()->getAnd($1, $3, true); }

    | expression "=="  expression   { $$ = driver.expr()->getEq($1, $3); }
    | expression "!="  expression   { $$ = driver.expr()->getNeq($1, $3); }
    | expression ">="  expression   { $$ = driver.expr()->getGe($1, $3); }
    | expression "<="  expression   { $$ = driver.expr()->getLe($1, $3); }
    | expression ">"   expression   { $$ = driver.expr()->getGt($1, $3); }
    | expression "<"   expression   { $$ = driver.expr()->getLt($1, $3); }

    | left       '='   expression   { $$ = driver.expr()->getAssign($1, $3); }
    | right
    ;

left
    : VAR_LOCAL                     { $$ = driver.scope()->get(*$1)->getLeft(); }
    ;

right
    : VAR_LOCAL                     { $$ = driver.scope()->get(*$1)->getRight(); }
    | INTEGER                       { $$ = driver.expr()->getInt($1);            }
    | '(' expression ')'            { $$ = $2; }
    ;


//==------------------------------------------------------------------------==//
//      Types
//==------------------------------------------------------------------------==//
type
    : type_complex
    | type_primary
    | TYPE_VOID             { $$ = driver.type()->getVoid();    }
    ;

type_complex
    : type_primary '[' ']'  { $$ = driver.type()->getArray($1); }
    ;

type_primary
    : TYPE_INT              { $$ = driver.type()->getInt();     }
    | TYPE_STRING           { $$ = driver.type()->getString();  }
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
