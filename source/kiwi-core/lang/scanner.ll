/* $Id: scanner.ll 44 2008-10-23 09:03:19Z tb $ -*- mode: c++ -*- */
/** \file scanner.ll Define the example Flex lexical scanner */

%{ /*** C/C++ Declarations ***/

#include "kiwi/Config.hpp"
#include <string>
#include <sstream>
#include "scanner.h"

/* import the parser's token type into a local typedef */
typedef kiwi::lang::Parser::token token;
typedef kiwi::lang::Parser::token_type token_type;

/* By default yylex returns int, we use token_type. Unfortunately yyterminate
 * by default returns 0, which is not of token_type. */
#define yyterminate() return token::END

/* This disables inclusion of unistd.h, which is not available under Visual C++
 * on Win32. The C++ scanner uses STL streams instead. */
#define YY_NO_UNISTD_H

%}

/*** Flex Declarations and Options ***/

/* enable c++ scanner class generation */
%option c++

/* change the name of the scanner class. results in "ExampleFlexLexer" */
%option prefix="Example"

/* the manual says "somewhat more optimized" */
%option batch

/* enable scanner to generate debug output. disable this for release
 * versions. */
%option debug

/* no support for include files is planned */
%option yywrap nounput

/* enables the use of start condition stacks */
%option stack

/* The following paragraph suffices to track locations accurately. Each time
 * yylex is invoked, the begin position is moved onto the end position. */
%{
#define YY_USER_ACTION  yylloc->columns(yyleng);
%}

/* States */
%x comment
%x line_comment
%x string_state
%x char_state

%% /*** Regular Expressions Part ***/

 /* code to place at the beginning of yylex() */
%{
    // reset location
    yylloc->step();

    std::stringstream stringBuffer;
%}

 /*** BEGIN EXAMPLE - Change the example lexer rules below ***/

"<<"     { return token::OP_LSH;      }
">>"     { return token::OP_RSH;      }
"||"     { return token::OP_OR;       }
"&&"     { return token::OP_AND;      }
"=="     { return token::OP_EQ;       }
"!="     { return token::OP_NE;       }
">="     { return token::OP_GE;       }
"<="     { return token::OP_LE;       }
"++"     { return token::OP_INC;      }
"--"     { return token::OP_DEC;      }
"+="     { return token::OP_AADD;     }
"-="     { return token::OP_ASUB;     }
"/="     { return token::OP_ADIV;     }
"*="     { return token::OP_AMUL;     }
"<<="    { return token::OP_ASHL;     }
">>="    { return token::OP_ASHR;     }
"&="     { return token::OP_AAND;     }
"|="     { return token::OP_AOR;      }

"void"   { return token::TYPE_VOID;   }
"int"    { return token::TYPE_INT;    }
"bool"   { return token::TYPE_BOOL;   }
"string" { return token::TYPE_STRING; }
"char"   { return token::TYPE_CHAR;   }

"return" { return token::RETURN;      }
"if"     { return token::IF;          }
"else"   { return token::ELSE;        }
"ifelse" { return token::IFELSE;      }

"print"  { return token::PRINT;       }

 /* Unix command */
^#!.*$ {
    return token::UNIX_SCRIPT;
}

[A-Za-z][A-Za-z0-9]* {
    yylval->stringVal = new std::string(yytext, yyleng);
    return token::IDENT;
}

\$[A-Za-z][A-Za-z0-9_]* {
    yylval->stringVal = new std::string(yytext+1, yyleng-1);
    return token::VAR_LOCAL;
}

\@[A-Za-z][A-Za-z0-9_]* {
    yylval->stringVal = new std::string(yytext+1, yyleng-1);
    return token::VAR_INSTANCE;
}

[+-]?[0-9]+ {
    yylval->integerVal = atoi(yytext);
    return token::INTEGER;
}

 /* gobble up white-spaces */
[ \t]+ {
    yylloc->step();
}
[\n\r]+ {
    yylloc->lines(yyleng);
}

 /* comments and strings */
"/*"                    { BEGIN(comment);       }
"//"                    { BEGIN(line_comment);  }
"#"                     { BEGIN(line_comment);  }
"\""                    { BEGIN(string_state);  }
"\'"                    { BEGIN(char_state);    }

<comment>{
    [^*\n]*             { /* eat anything that's not a '*' */ }
    "*"+[^*/\n]*        { /* eat up '*'s not followed by '/'s */ }
    \n                  { yylloc->lines(yyleng);              }
    "*"+"/"             { BEGIN(INITIAL);                     }
}

<line_comment>{
    [\n\r]+             { yylloc->lines(yyleng); BEGIN(INITIAL); }
    .                   { }
}

<string_state>{
    "\""                {
                            /* saw closing quote - all done */
                             BEGIN(INITIAL);
                             yylval->ustringVal = new UnicodeString(stringBuffer.str().c_str());;
                             stringBuffer.str(std::string());
                             return token::STRING;
                        }

    \\n                 { stringBuffer << '\n';      }
    \\t                 { stringBuffer << '\t';      }
    \\r                 { stringBuffer << '\r';      }
    \\b                 { stringBuffer << '\b';      }
    \\f                 { stringBuffer << '\f';      }
    \\.                 { stringBuffer << yytext[1]; }
    .                   { stringBuffer << yytext[0]; }
}

<char_state>{
    \\n"'"              { yylval->charVal = '\n'; BEGIN(INITIAL); return token::CHAR;      }
    \\t"'"              { yylval->charVal = '\t'; BEGIN(INITIAL); return token::CHAR;      }
    \\r"'"              { yylval->charVal = '\r'; BEGIN(INITIAL); return token::CHAR;      }
    \\b"'"              { yylval->charVal = '\b'; BEGIN(INITIAL); return token::CHAR;      }
    \\f"'"              { yylval->charVal = '\f'; BEGIN(INITIAL); return token::CHAR;      }
    ."'"                { yylval->charVal = yytext[0]; BEGIN(INITIAL); return token::CHAR; }
}

 /* pass all other characters up to bison */
. {
    return static_cast<token_type>(*yytext);
}

 /*** END EXAMPLE - Change the example lexer rules above ***/

%% /*** Additional Code ***/

namespace kiwi {
namespace lang {

Scanner::Scanner(std::istream* in,
		 std::ostream* out)
    : ExampleFlexLexer(in, out)
{
}

Scanner::~Scanner()
{
}

void Scanner::set_debug(bool b)
{
    yy_flex_debug = b;
}

} // namespace lang
} // namespace kiwi

/* This implementation of ExampleFlexLexer::yylex() is required to fill the
 * vtable of the class ExampleFlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the Scanner class instead. */

#ifdef yylex
#undef yylex
#endif

int ExampleFlexLexer::yylex()
{
    std::cerr << "in ExampleFlexLexer::yylex() !" << std::endl;
    return 0;
}

/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */

int ExampleFlexLexer::yywrap()
{
    return 1;
}
