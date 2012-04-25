/* $Id: parser.yy 48 2009-09-05 08:07:10Z tb $ -*- mode: c++ -*- */
/** \file parser.yy Contains the example Bison parser source */

%{ /*** C/C++ Declarations ***/

#include "kiwi/config.hpp"
#include "kiwi/assert.hpp"
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
    driver.prepareScript(@$);
};

/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class Driver& driver }

/* verbose error messages */
%error-verbose

 /*** BEGIN EXAMPLE - Change the example grammar's tokens below ***/

%union {
    int                     integerVal;
    double                  doubleVal;
    std::string*            stringVal;
    String*                 ustringVal;
    UChar                   charVal;

    class TypeNode*         typenode;
    class MutableNode*      leftnode;
    class ExpressionNode*   rightnode;
    class StatementNode*    stmtnode;
    class MemberNode*       membernode;
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
%token                  BOOL_TRUE           "true"
%token                  BOOL_FALSE          "false"

%token  <stringVal>     VAR_LOCAL           "local variable"
%token  <stringVal>     VAR_INSTANCE        "instance attribute"

%token                  TYPE_AUTO           "auto type"
%token                  TYPE_VOID           "void type"
%token                  TYPE_INT            "int type"
%token                  TYPE_BOOL           "bool type"
%token                  TYPE_CHAR           "char type"
%token                  TYPE_STRING         "string type"

%token                  CLASS               "class"
%token                  INHERIT             "inherit"
%token                  IMPLEMENT           "implement"

%token                  NEW                 "new"

%token                  THIS                "this"
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
%type   <rightnode>     expression right
%type   <leftnode>      left
%type   <stmtnode>      statement scope scope_end return_statement print_statement conditional_statement
%type   <stmtnode>      variable_declare
%type   <membernode>    function field class_element
%type   <stringVal>     qualified_identifier

%destructor { delete $$; } IDENT VAR_LOCAL VAR_INSTANCE
%destructor { delete $$; } expression right
%destructor { delete $$; } type type_complex type_primary
%destructor { delete $$; } statement scope scope_end return_statement print_statement conditional_statement
%destructor { delete $$; } variable_declare
%destructor { delete $$; } STRING qualified_identifier
%destructor { delete $$; } function field class_element

 /*** END EXAMPLE - Change the example grammar's tokens above ***/

%{

#include "Driver.hpp"
#include "scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

#define yyfree(__px1) delete __px1; __px1 = 0;

%}

%% /*** Grammar Rules ***/

 /*** BEGIN GRAMAR - Change the example grammar rules below ***/

//==------------------------------------------------------------------------==//
//      Functions
//==------------------------------------------------------------------------==//

field
    : type VAR_INSTANCE ';'         { $$ = driver.field(*$2, $1); yyfree($2); }
    ;

//==------------------------------------------------------------------------==//
//      Functions
//==------------------------------------------------------------------------==//
function
    : type IDENT                    { driver.func(*$2, $1); yyfree($2); }
      '(' function_arguments ')'
      function_statement            { $$ = driver.funcEnd();            }
    ;

function_arguments
    : /* empty */
    | function_arguments_required
    ;

function_arguments_required
    : function_argument ',' function_arguments_required
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
    | statement                  { driver.scope()->append($1); $1 = 0; }
        statements
    | ';'
    ;

statement
    : expression       ';'       { $$ = driver.createExpr($1);       }
    | scope
    | conditional_statement
    | return_statement ';'
    | print_statement  ';'
    | variable_declare ';'
    ;

scope
    : '{'                        { driver.scopeBegin();              }
        scope_end                { $$ = $3;                          }
    ;

scope_end
    : statements '}'             { $$ = driver.scopeEnd();           }
    ;

return_statement
    : RETURN                     { $$ = driver.createReturn(@1);     }
    | RETURN expression          { $$ = driver.createReturn($2, @1); }
    ;

print_statement
    : PRINT expression           { $$ = driver.createPrint($2, @1);  }

//==------------------------------------------------------------------------==//
//      Conditional statement
//==------------------------------------------------------------------------==//
conditional_statement
    : IF '(' expression ')' statement                { $$ = driver.createCond($3, $5, 0,  @1); }
    | IF '(' expression ')' statement ELSE statement { $$ = driver.createCond($3, $5, $7, @1); }
    ;

//==------------------------------------------------------------------------==//
//      Calls
//==------------------------------------------------------------------------==//
call_arguments
    : /* empty */
    | call_arguments_required
    ;

call_arguments_required
    : call_argument ',' call_arguments_required
    | call_argument
    ;

call_argument
    : IDENT ':' expression          { driver.call()->append(*$1, $3); yyfree($1); $3 = 0; }
    | expression                    { driver.call()->append($1); $1 = 0;          }
    ;

//==------------------------------------------------------------------------==//
//      Expressions
//==------------------------------------------------------------------------==//

variable_declare
    : type      VAR_LOCAL                   {
                                                driver.scope()->declare(*$2, $1);
                                                $$ = 0;
                                                yyfree($2);
                                            }
    | type      VAR_LOCAL '=' expression    {
                                                driver.scope()->declare(*$2, $1, $4);
                                                KIWI_DUMP("Not implement!!! Variable init expression");
                                                $$ = 0;
                                                yyfree($2);
                                            }
    | TYPE_AUTO VAR_LOCAL '=' expression    {
                                                driver.scope()->declare(*$2, $4);
                                                KIWI_DUMP("Not implement!!! Variable init expression");
                                                $$ = 0;
                                                yyfree($2);
                                            }
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
    | expression '>'   expression   { $$ = driver.createGt ($1, $3, @2); }
    | expression '<'   expression   { $$ = driver.createLt ($1, $3, @2); }

    //==-------- Call and multinary operators ------------------------------==//
    | expression                        { driver.subBegin($1, @1);           }
        '[' call_arguments_required ']' { $$ = driver.callEnd(@3 + @5);      }

    | IDENT                             { driver.call(*$1, @1); yyfree($1);  }
        '(' call_arguments ')'          { $$ = driver.callEnd(@1);           }

    | right '.' IDENT                   { driver.call($1, *$3, @1 + @3); yyfree($3); }
        '(' call_arguments ')'          { $$ = driver.callEnd(@1);                   }

    | NEW type                          { driver.newBegin($2, @1);              }
        '(' call_arguments ')'          { $$ = driver.callEnd(@1);              }

    | left       '='   expression   { $$ = driver.createAssign($1, $3, @2); }
    | right
    ;

left
    : VAR_LOCAL                     { $$ = driver.left(*$1, @1); yyfree($1);          }
    | VAR_INSTANCE                  { $$ = driver.instanceLeft(*$1, @1); yyfree($1);  }
    ;

right
    : VAR_LOCAL                     { $$ = driver.right(*$1, @1); yyfree($1);         }
    | VAR_INSTANCE                  { $$ = driver.instanceRight(*$1, @1); yyfree($1); }
    | INTEGER                       { $$ = driver.createInt($1, @1);                  }
    | STRING                        { $$ = driver.createString(*$1, @1); yyfree($1);  }
    | BOOL_TRUE                     { $$ = driver.createBool(true, @1);               }
    | BOOL_FALSE                    { $$ = driver.createBool(false, @1);              }
    | CHAR                          { $$ = driver.createChar($1, @1);                 }
    | THIS                          { $$ = driver.createThis(@1);                     }
    | '(' expression ')'            { $$ = $2;                                        }
    ;

//==------------------------------------------------------------------------==//
//      Types definition
//==------------------------------------------------------------------------==//
class_definition
    : CLASS IDENT                   { driver.classBegin(*$2, @2); yyfree($2);   }
        '{' class_body '}'          { driver.classEnd();                        }
    ;

class_body
    : /* empty */
    | class_element                 { driver.classTop()->append($1); $1 = 0;    }
        class_body
    | class_modificator
        class_body
    ;

class_modificator
    : INHERIT   IDENT ';'           { driver.classTop()->inherit(*$2);   yyfree($2); }
    | IMPLEMENT IDENT ';'           { driver.classTop()->implement(*$2); yyfree($2); }
    ;

class_element
    : function
    | field
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
    : TYPE_INT              { $$ = driver.createIntTy(@1);    }
    | TYPE_BOOL             { $$ = driver.createBoolTy(@1);   }
    | TYPE_STRING           { $$ = driver.createStringTy(@1); }
    | TYPE_CHAR             { $$ = driver.createCharTy(@1);   }
    | qualified_identifier  { $$ = driver.createQualifiedTy(*$1, @1); yyfree($1); }
    ;

script_elements
    : class_definition
    | class_element         { driver.classTop()->append($1); $1 = 0; }
    ;

qualified_identifier
    : IDENT
    ;

/** START POINT **/
start
    : /* empty */
    | script_elements start END
    ;

/*** END GRAMAR - Change the example grammar rules above ***/

%% /*** Additional Code ***/

void kiwi::lang::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}
