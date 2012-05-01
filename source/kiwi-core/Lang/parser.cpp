
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

// Take the name prefix into account.
#define yylex   kiwi::langlex

/* First part of user declarations.  */

/* Line 311 of lalr1.cc  */
#line 7 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
 /*** C/C++ Declarations ***/

#include "kiwi/config.hpp"
#include <stdio.h>
#include <string>
#include <vector>
#include "ExpressionNode.hpp"
#include "TypeNode.hpp"
#include "FunctionNode.hpp"



/* Line 311 of lalr1.cc  */
#line 56 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"


#include "parser.hpp"

/* User implementation prologue.  */

/* Line 317 of lalr1.cc  */
#line 161 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"


#include "Driver.hpp"
#include "scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

#define yyfree(__px1) delete __px1; __px1 = 0;



/* Line 317 of lalr1.cc  */
#line 81 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


/* Line 380 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

namespace kiwi { namespace lang {

/* Line 380 of lalr1.cc  */
#line 150 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
#if YYERROR_VERBOSE

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

#endif

  /// Build a parser object.
  Parser::Parser (class Driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {
  }

  Parser::~Parser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  Parser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  Parser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  Parser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
        case 23: /* "\"identifier\"" */

/* Line 480 of lalr1.cc  */
#line 151 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 257 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 25: /* "\"string constant\"" */

/* Line 480 of lalr1.cc  */
#line 156 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->ustringVal); };

/* Line 480 of lalr1.cc  */
#line 266 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 29: /* "\"local variable\"" */

/* Line 480 of lalr1.cc  */
#line 151 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 275 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 30: /* "\"instance attribute\"" */

/* Line 480 of lalr1.cc  */
#line 151 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 284 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 71: /* "field" */

/* Line 480 of lalr1.cc  */
#line 157 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->membernode); };

/* Line 480 of lalr1.cc  */
#line 293 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 72: /* "function" */

/* Line 480 of lalr1.cc  */
#line 157 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->membernode); };

/* Line 480 of lalr1.cc  */
#line 302 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 80: /* "statement" */

/* Line 480 of lalr1.cc  */
#line 154 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 311 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 81: /* "scope" */

/* Line 480 of lalr1.cc  */
#line 154 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 320 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 83: /* "scope_end" */

/* Line 480 of lalr1.cc  */
#line 154 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 329 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 84: /* "return_statement" */

/* Line 480 of lalr1.cc  */
#line 154 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 338 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 85: /* "print_statement" */

/* Line 480 of lalr1.cc  */
#line 154 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 347 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 86: /* "conditional_statement" */

/* Line 480 of lalr1.cc  */
#line 154 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 356 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 90: /* "variable_declare" */

/* Line 480 of lalr1.cc  */
#line 155 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 365 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 91: /* "expression" */

/* Line 480 of lalr1.cc  */
#line 152 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->rightnode); };

/* Line 480 of lalr1.cc  */
#line 374 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 97: /* "right" */

/* Line 480 of lalr1.cc  */
#line 152 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->rightnode); };

/* Line 480 of lalr1.cc  */
#line 383 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 103: /* "class_element" */

/* Line 480 of lalr1.cc  */
#line 157 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->membernode); };

/* Line 480 of lalr1.cc  */
#line 392 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 104: /* "type" */

/* Line 480 of lalr1.cc  */
#line 153 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->typenode); };

/* Line 480 of lalr1.cc  */
#line 401 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 105: /* "type_complex" */

/* Line 480 of lalr1.cc  */
#line 153 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->typenode); };

/* Line 480 of lalr1.cc  */
#line 410 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 106: /* "type_primary" */

/* Line 480 of lalr1.cc  */
#line 153 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->typenode); };

/* Line 480 of lalr1.cc  */
#line 419 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 108: /* "qualified_identifier" */

/* Line 480 of lalr1.cc  */
#line 156 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 428 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;

	default:
	  break;
      }
  }

  void
  Parser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  int
  Parser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    semantic_type yylval;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[2];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* User initialization code.  */
    
/* Line 553 of lalr1.cc  */
#line 46 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
{
    // initialize the initial location object
    yylloc.begin.filename = yylloc.end.filename = &driver.streamname;
    driver.prepareScript(yylloc);
}

/* Line 553 of lalr1.cc  */
#line 515 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"

    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yyn == yypact_ninf_)
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, &yylloc);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yyn == 0 || yyn == yytable_ninf_)
	goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 2:

/* Line 678 of lalr1.cc  */
#line 185 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.membernode) = driver.field(*(yysemantic_stack_[(3) - (2)].stringVal), (yysemantic_stack_[(3) - (1)].typenode)); yyfree((yysemantic_stack_[(3) - (2)].stringVal)); }
    break;

  case 3:

/* Line 678 of lalr1.cc  */
#line 192 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.func(*(yysemantic_stack_[(2) - (2)].stringVal), (yysemantic_stack_[(2) - (1)].typenode)); yyfree((yysemantic_stack_[(2) - (2)].stringVal)); }
    break;

  case 4:

/* Line 678 of lalr1.cc  */
#line 194 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.membernode) = driver.funcEnd();            }
    break;

  case 9:

/* Line 678 of lalr1.cc  */
#line 208 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.func()->declare(*(yysemantic_stack_[(2) - (2)].stringVal), (yysemantic_stack_[(2) - (1)].typenode)); }
    break;

  case 12:

/* Line 678 of lalr1.cc  */
#line 220 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.scope()->append((yysemantic_stack_[(1) - (1)].stmtnode)); (yysemantic_stack_[(1) - (1)].stmtnode) = 0; }
    break;

  case 15:

/* Line 678 of lalr1.cc  */
#line 226 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createExpr((yysemantic_stack_[(2) - (1)].rightnode));       }
    break;

  case 21:

/* Line 678 of lalr1.cc  */
#line 235 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.scopeBegin();              }
    break;

  case 22:

/* Line 678 of lalr1.cc  */
#line 236 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = (yysemantic_stack_[(3) - (3)].stmtnode);                          }
    break;

  case 23:

/* Line 678 of lalr1.cc  */
#line 240 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.scopeEnd();           }
    break;

  case 24:

/* Line 678 of lalr1.cc  */
#line 244 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createReturn((yylocation_stack_[(1) - (1)]));     }
    break;

  case 25:

/* Line 678 of lalr1.cc  */
#line 245 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createReturn((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)])); }
    break;

  case 26:

/* Line 678 of lalr1.cc  */
#line 249 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createPrint((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)]));  }
    break;

  case 27:

/* Line 678 of lalr1.cc  */
#line 255 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createCond((yysemantic_stack_[(5) - (3)].rightnode), (yysemantic_stack_[(5) - (5)].stmtnode), 0,  (yylocation_stack_[(5) - (1)])); }
    break;

  case 28:

/* Line 678 of lalr1.cc  */
#line 256 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createCond((yysemantic_stack_[(7) - (3)].rightnode), (yysemantic_stack_[(7) - (5)].stmtnode), (yysemantic_stack_[(7) - (7)].stmtnode), (yylocation_stack_[(7) - (1)])); }
    break;

  case 33:

/* Line 678 of lalr1.cc  */
#line 273 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.call()->append(*(yysemantic_stack_[(3) - (1)].stringVal), (yysemantic_stack_[(3) - (3)].rightnode)); yyfree((yysemantic_stack_[(3) - (1)].stringVal)); (yysemantic_stack_[(3) - (3)].rightnode) = 0; }
    break;

  case 34:

/* Line 678 of lalr1.cc  */
#line 274 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.call()->append((yysemantic_stack_[(1) - (1)].rightnode)); (yysemantic_stack_[(1) - (1)].rightnode) = 0;          }
    break;

  case 35:

/* Line 678 of lalr1.cc  */
#line 282 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    {
                                                driver.scope()->declare(*(yysemantic_stack_[(2) - (2)].stringVal), (yysemantic_stack_[(2) - (1)].typenode));
                                                (yyval.stmtnode) = 0;
                                                yyfree((yysemantic_stack_[(2) - (2)].stringVal));
                                            }
    break;

  case 36:

/* Line 678 of lalr1.cc  */
#line 287 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    {
                                                VariableNode* node = driver.scope()->declare(*(yysemantic_stack_[(4) - (2)].stringVal), (yysemantic_stack_[(4) - (1)].typenode), (yysemantic_stack_[(4) - (4)].rightnode));
                                                (yyval.stmtnode) = driver.createInit(node, (yylocation_stack_[(4) - (3)]));
                                                yyfree((yysemantic_stack_[(4) - (2)].stringVal));
                                            }
    break;

  case 37:

/* Line 678 of lalr1.cc  */
#line 292 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    {
                                                VariableNode* node = driver.scope()->declare(*(yysemantic_stack_[(4) - (2)].stringVal), (yysemantic_stack_[(4) - (4)].rightnode));
                                                (yyval.stmtnode) = driver.createInit(node, (yylocation_stack_[(4) - (3)]));
                                                yyfree((yysemantic_stack_[(4) - (2)].stringVal));
                                            }
    break;

  case 38:

/* Line 678 of lalr1.cc  */
#line 300 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createNeg((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)])); }
    break;

  case 39:

/* Line 678 of lalr1.cc  */
#line 301 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createPos((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)])); }
    break;

  case 40:

/* Line 678 of lalr1.cc  */
#line 302 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createNot((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)])); }
    break;

  case 41:

/* Line 678 of lalr1.cc  */
#line 305 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createAdd((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 42:

/* Line 678 of lalr1.cc  */
#line 306 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createSub((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 43:

/* Line 678 of lalr1.cc  */
#line 307 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createMul((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 44:

/* Line 678 of lalr1.cc  */
#line 308 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createDiv((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 45:

/* Line 678 of lalr1.cc  */
#line 309 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createLsh((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 46:

/* Line 678 of lalr1.cc  */
#line 310 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createRsh((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 47:

/* Line 678 of lalr1.cc  */
#line 312 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createOr ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), false, (yylocation_stack_[(3) - (2)])); }
    break;

  case 48:

/* Line 678 of lalr1.cc  */
#line 313 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createOr ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), true,  (yylocation_stack_[(3) - (2)])); }
    break;

  case 49:

/* Line 678 of lalr1.cc  */
#line 314 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createAnd((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), false, (yylocation_stack_[(3) - (2)])); }
    break;

  case 50:

/* Line 678 of lalr1.cc  */
#line 315 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createAnd((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), true,  (yylocation_stack_[(3) - (2)])); }
    break;

  case 51:

/* Line 678 of lalr1.cc  */
#line 317 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createEq ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 52:

/* Line 678 of lalr1.cc  */
#line 318 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createNeq((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 53:

/* Line 678 of lalr1.cc  */
#line 319 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createGe ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 54:

/* Line 678 of lalr1.cc  */
#line 320 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createLe ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 55:

/* Line 678 of lalr1.cc  */
#line 321 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createGt ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 56:

/* Line 678 of lalr1.cc  */
#line 322 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createLt ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 57:

/* Line 678 of lalr1.cc  */
#line 325 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.subBegin((yysemantic_stack_[(1) - (1)].rightnode), (yylocation_stack_[(1) - (1)]));           }
    break;

  case 58:

/* Line 678 of lalr1.cc  */
#line 326 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.callEnd((yylocation_stack_[(5) - (3)]) + (yylocation_stack_[(5) - (5)]));      }
    break;

  case 59:

/* Line 678 of lalr1.cc  */
#line 328 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.call(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal));  }
    break;

  case 60:

/* Line 678 of lalr1.cc  */
#line 329 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.callEnd((yylocation_stack_[(5) - (1)]));           }
    break;

  case 61:

/* Line 678 of lalr1.cc  */
#line 331 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.call((yysemantic_stack_[(3) - (1)].rightnode), *(yysemantic_stack_[(3) - (3)].stringVal), (yylocation_stack_[(3) - (1)]) + (yylocation_stack_[(3) - (3)])); yyfree((yysemantic_stack_[(3) - (3)].stringVal)); }
    break;

  case 62:

/* Line 678 of lalr1.cc  */
#line 332 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.callEnd((yylocation_stack_[(7) - (3)]));                   }
    break;

  case 63:

/* Line 678 of lalr1.cc  */
#line 334 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.newBegin((yysemantic_stack_[(2) - (2)].typenode), (yylocation_stack_[(2) - (1)]));              }
    break;

  case 64:

/* Line 678 of lalr1.cc  */
#line 335 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.callEnd((yylocation_stack_[(6) - (1)]) + (yylocation_stack_[(6) - (2)]));         }
    break;

  case 65:

/* Line 678 of lalr1.cc  */
#line 337 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createAssign((yysemantic_stack_[(3) - (1)].leftnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 67:

/* Line 678 of lalr1.cc  */
#line 342 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.leftnode) = driver.left(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal));          }
    break;

  case 68:

/* Line 678 of lalr1.cc  */
#line 343 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.leftnode) = driver.instanceLeft(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal));  }
    break;

  case 69:

/* Line 678 of lalr1.cc  */
#line 347 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.right(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal));         }
    break;

  case 70:

/* Line 678 of lalr1.cc  */
#line 348 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.instanceRight(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal)); }
    break;

  case 71:

/* Line 678 of lalr1.cc  */
#line 349 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createInt((yysemantic_stack_[(1) - (1)].integerVal), (yylocation_stack_[(1) - (1)]));                  }
    break;

  case 72:

/* Line 678 of lalr1.cc  */
#line 350 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createString(*(yysemantic_stack_[(1) - (1)].ustringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].ustringVal));  }
    break;

  case 73:

/* Line 678 of lalr1.cc  */
#line 351 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createBool(true, (yylocation_stack_[(1) - (1)]));               }
    break;

  case 74:

/* Line 678 of lalr1.cc  */
#line 352 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createBool(false, (yylocation_stack_[(1) - (1)]));              }
    break;

  case 75:

/* Line 678 of lalr1.cc  */
#line 353 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createChar((yysemantic_stack_[(1) - (1)].charVal), (yylocation_stack_[(1) - (1)]));                 }
    break;

  case 76:

/* Line 678 of lalr1.cc  */
#line 354 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createThis((yylocation_stack_[(1) - (1)]));                     }
    break;

  case 77:

/* Line 678 of lalr1.cc  */
#line 355 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = (yysemantic_stack_[(3) - (2)].rightnode);                                        }
    break;

  case 78:

/* Line 678 of lalr1.cc  */
#line 362 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.classBegin(*(yysemantic_stack_[(2) - (2)].stringVal), (yylocation_stack_[(2) - (2)])); yyfree((yysemantic_stack_[(2) - (2)].stringVal));   }
    break;

  case 79:

/* Line 678 of lalr1.cc  */
#line 363 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.classEnd();                        }
    break;

  case 81:

/* Line 678 of lalr1.cc  */
#line 368 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.classTop()->append((yysemantic_stack_[(1) - (1)].membernode)); (yysemantic_stack_[(1) - (1)].membernode) = 0;    }
    break;

  case 84:

/* Line 678 of lalr1.cc  */
#line 375 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.classTop()->inherit(*(yysemantic_stack_[(3) - (2)].stringVal));   yyfree((yysemantic_stack_[(3) - (2)].stringVal)); }
    break;

  case 85:

/* Line 678 of lalr1.cc  */
#line 376 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.classTop()->implement(*(yysemantic_stack_[(3) - (2)].stringVal)); yyfree((yysemantic_stack_[(3) - (2)].stringVal)); }
    break;

  case 90:

/* Line 678 of lalr1.cc  */
#line 390 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createVoidTy((yylocation_stack_[(1) - (1)]));    }
    break;

  case 91:

/* Line 678 of lalr1.cc  */
#line 394 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createArrayTy((yysemantic_stack_[(3) - (1)].typenode), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)])); }
    break;

  case 92:

/* Line 678 of lalr1.cc  */
#line 398 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createIntTy((yylocation_stack_[(1) - (1)]));    }
    break;

  case 93:

/* Line 678 of lalr1.cc  */
#line 399 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createBoolTy((yylocation_stack_[(1) - (1)]));   }
    break;

  case 94:

/* Line 678 of lalr1.cc  */
#line 400 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createStringTy((yylocation_stack_[(1) - (1)])); }
    break;

  case 95:

/* Line 678 of lalr1.cc  */
#line 401 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createCharTy((yylocation_stack_[(1) - (1)]));   }
    break;

  case 96:

/* Line 678 of lalr1.cc  */
#line 402 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createQualifiedTy(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal)); }
    break;

  case 98:

/* Line 678 of lalr1.cc  */
#line 407 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.classTop()->append((yysemantic_stack_[(1) - (1)].membernode)); (yysemantic_stack_[(1) - (1)].membernode) = 0; }
    break;



/* Line 678 of lalr1.cc  */
#line 1143 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	default:
          break;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[0] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
	  }
      }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[0] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (yyn != yypact_ninf_)
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[0] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[1] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyempty_)
      yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval, &yylloc);

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (int yystate, int tok)
  {
    std::string res;
    YYUSE (yystate);
#if YYERROR_VERBOSE
    int yyn = yypact_[yystate];
    if (yypact_ninf_ < yyn && yyn <= yylast_)
      {
	/* Start YYX at -YYN if negative to avoid negative indexes in
	   YYCHECK.  */
	int yyxbegin = yyn < 0 ? -yyn : 0;

	/* Stay within bounds of both yycheck and yytname.  */
	int yychecklim = yylast_ - yyn + 1;
	int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
	int count = 0;
	for (int x = yyxbegin; x < yyxend; ++x)
	  if (yycheck_[x + yyn] == x && x != yyterror_)
	    ++count;

	// FIXME: This method of building the message is not compatible
	// with internationalization.  It should work like yacc.c does it.
	// That is, first build a string that looks like this:
	// "syntax error, unexpected %s or %s or %s"
	// Then, invoke YY_ on this string.
	// Finally, use the string as a format to output
	// yytname_[tok], etc.
	// Until this gets fixed, this message appears in English only.
	res = "syntax error, unexpected ";
	res += yytnamerr_ (yytname_[tok]);
	if (count < 5)
	  {
	    count = 0;
	    for (int x = yyxbegin; x < yyxend; ++x)
	      if (yycheck_[x + yyn] == x && x != yyterror_)
		{
		  res += (!count++) ? ", expecting " : " or ";
		  res += yytnamerr_ (yytname_[x]);
		}
	  }
      }
    else
#endif
      res = YY_("syntax error");
    return res;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const short int Parser::yypact_ninf_ = -151;
  const short int
  Parser::yypact_[] =
  {
        55,  -151,  -151,  -151,  -151,  -151,  -151,   -10,  -151,  -151,
    -151,  -151,   -12,  -151,   -43,    55,  -151,    27,  -151,  -151,
      -9,   -14,    57,  -151,    -8,     0,  -151,  -151,  -151,    -4,
      62,    44,    46,    12,    -4,  -151,    16,  -151,    17,    52,
      21,    37,  -151,  -151,    -4,    36,    62,  -151,  -151,  -151,
    -151,   294,  -151,  -151,    42,  -151,  -151,  -151,  -151,  -151,
      59,    60,    75,    62,  -151,   382,    47,   382,   382,   382,
     382,   382,  -151,  -151,    43,  -151,  -151,    48,    49,  -151,
      58,   142,    76,    50,    93,    63,    78,  -151,  -151,   158,
     382,   158,  -151,  -151,  -151,    65,   294,  -151,   294,  -151,
    -151,  -151,   382,   382,   382,   382,   382,   382,   382,   382,
     382,   382,   382,   382,   382,   382,   382,   382,  -151,    66,
     382,   104,    91,   401,   382,    79,   125,  -151,    72,  -151,
    -151,    10,    10,   176,   210,   235,   235,   261,   261,   227,
     243,   261,   261,   -18,   -18,  -151,  -151,   401,   158,  -151,
     382,    73,    80,  -151,    77,   158,   158,   401,   338,  -151,
      86,    84,   158,   382,  -151,   401,    82,   112,  -151,   401,
     158,  -151,  -151,   338,    94,  -151,  -151
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
       100,    99,    90,    92,    93,    95,    94,     0,    87,    86,
      97,    98,     0,    88,    89,   100,    96,     0,    78,     3,
       0,     0,     0,     1,     0,     0,     2,    91,   101,    80,
       5,     0,     0,     0,    80,    81,     0,     6,     8,     0,
       0,     0,    79,    83,    80,     0,     0,     9,    84,    85,
      82,    11,     4,     7,    99,    71,    72,    75,    73,    74,
      69,    70,     0,     0,    76,    24,     0,     0,     0,     0,
       0,     0,    14,    21,     0,    12,    16,     0,     0,    17,
       0,    57,     0,    66,     0,     0,     0,    63,    59,    25,
       0,    26,    38,    39,    40,    57,    11,    10,    11,    18,
      19,    20,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    15,     0,
       0,     0,    35,    29,     0,     0,    57,    77,     0,    22,
      13,    45,    46,    48,    50,    51,    52,    53,    54,    47,
      49,    56,    55,    42,    41,    43,    44,     0,    65,    61,
       0,    59,     0,    30,    32,    34,    37,    29,     0,    23,
       0,     0,    36,     0,    60,     0,     0,    27,    58,    29,
      33,    31,    64,     0,     0,    28,    62
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -151,  -151,  -151,  -151,  -151,   111,  -151,  -151,   -84,  -151,
    -150,  -151,  -151,  -151,  -151,  -151,  -151,  -147,  -145,  -151,
    -151,   -64,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,
     -19,  -151,  -151,     9,   -30,  -151,  -151,  -151,  -151,   144
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     8,     9,    25,    36,    37,    38,    52,    74,    98,
      75,    76,    96,   129,    77,    78,    79,   152,   153,   154,
      80,    81,   119,    85,   161,   125,    82,    83,    10,    24,
      33,    44,    34,    35,    12,    13,    14,    15,    16,    17
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -69;
  const short int
  Parser::yytable_[] =
  {
        39,    89,   160,    91,    92,    93,    94,    95,   167,    11,
     166,    19,   128,    18,   130,    43,    39,    21,    20,     1,
     171,    84,   174,   175,    11,    50,   126,    23,     2,     3,
       4,     5,     6,    87,    31,    32,   116,   117,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,    26,    27,   148,    28,    29,   155,
     156,    30,   114,   115,   116,   117,    84,    40,    84,    41,
     102,   103,   104,   105,   106,   107,   108,   109,     1,    42,
      45,    47,    46,   155,    48,     1,   162,     2,     3,     4,
       5,     6,     7,   155,     2,     3,     4,     5,     6,   170,
      49,   155,    51,   -59,    86,   155,   -67,   -68,    90,   121,
      97,    99,   100,   110,   111,   112,   113,   114,   115,   116,
     117,   101,   122,   120,   123,   124,   147,   149,    84,   127,
     102,   103,   104,   105,   106,   107,   108,   109,   150,   159,
     157,   163,   165,    84,   164,   169,   172,   102,   103,   104,
     105,   106,   107,   108,   109,   168,   173,    53,   176,    22,
       0,     0,     0,   102,   103,   104,   105,   106,   107,   108,
     109,     0,     0,   110,   111,   112,   113,   114,   115,   116,
     117,   102,   103,     0,   105,   106,   107,   108,   109,   158,
     110,   111,   112,   113,   114,   115,   116,   117,     0,     0,
       0,     0,     0,     0,     0,   118,   110,   111,   112,   113,
     114,   115,   116,   117,     0,   102,   103,     0,   -57,   106,
     107,   108,   109,     0,   110,   111,   112,   113,   114,   115,
     116,   117,   102,   103,     0,     0,   106,   107,   108,   109,
     102,   103,     0,     0,   -69,   -69,   108,   109,   102,   103,
       0,     0,   106,   107,   108,   109,     0,     0,   110,   111,
     112,   113,   114,   115,   116,   117,   102,   103,     0,     0,
       0,     0,   -69,   -69,     0,     0,   111,   112,   113,   114,
     115,   116,   117,     0,     0,   112,   113,   114,   115,   116,
     117,     0,     0,   112,   113,   114,   115,   116,   117,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -69,   -69,   114,   115,   116,   117,    54,    55,    56,
      57,    58,    59,    60,    61,    62,     2,     3,     4,     5,
       6,     0,     0,     0,    63,    64,    65,    66,     0,     0,
      67,     0,     0,     0,     0,     0,    68,    69,     0,     0,
       0,    70,     0,     0,     0,    71,     0,    72,     0,     0,
      73,    54,    55,    56,    57,    58,    59,    60,    61,    62,
       2,     3,     4,     5,     6,     0,     0,     0,    63,    64,
      65,    66,     0,     0,    67,     0,     0,     0,     0,     0,
      68,    69,     0,     0,     0,    70,     0,     0,     0,    71,
       0,     0,     0,     0,    73,    88,    55,    56,    57,    58,
      59,    60,    61,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    63,    64,   151,    55,    56,    57,    58,    59,
      60,    61,     0,     0,    68,    69,     0,     0,     0,    70,
       0,    63,    64,    71,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    68,    69,     0,     0,     0,    70,     0,
       0,     0,    71
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
        30,    65,   147,    67,    68,    69,    70,    71,   158,     0,
     157,    23,    96,    23,    98,    34,    46,    60,    30,    23,
     165,    51,   169,   173,    15,    44,    90,     0,    32,    33,
      34,    35,    36,    63,    38,    39,    54,    55,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,    63,    69,   120,     0,    66,   123,
     124,    61,    52,    53,    54,    55,    96,    23,    98,    23,
       5,     6,     7,     8,     9,    10,    11,    12,    23,    67,
      64,    29,    65,   147,    63,    23,   150,    32,    33,    34,
      35,    36,    37,   157,    32,    33,    34,    35,    36,   163,
      63,   165,    66,    61,    29,   169,    47,    47,    61,    59,
      67,    63,    63,    48,    49,    50,    51,    52,    53,    54,
      55,    63,    29,    47,    61,    47,    60,    23,   158,    64,
       5,     6,     7,     8,     9,    10,    11,    12,    47,    67,
      61,    68,    65,   173,    64,    61,    64,     5,     6,     7,
       8,     9,    10,    11,    12,    69,    44,    46,    64,    15,
      -1,    -1,    -1,     5,     6,     7,     8,     9,    10,    11,
      12,    -1,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,     5,     6,    -1,     8,     9,    10,    11,    12,    64,
      48,    49,    50,    51,    52,    53,    54,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    48,    49,    50,    51,
      52,    53,    54,    55,    -1,     5,     6,    -1,    60,     9,
      10,    11,    12,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,     5,     6,    -1,    -1,     9,    10,    11,    12,
       5,     6,    -1,    -1,     9,    10,    11,    12,     5,     6,
      -1,    -1,     9,    10,    11,    12,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,     5,     6,    -1,    -1,
      -1,    -1,    11,    12,    -1,    -1,    49,    50,    51,    52,
      53,    54,    55,    -1,    -1,    50,    51,    52,    53,    54,
      55,    -1,    -1,    50,    51,    52,    53,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    54,    55,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    -1,    40,    41,    42,    43,    -1,    -1,
      46,    -1,    -1,    -1,    -1,    -1,    52,    53,    -1,    -1,
      -1,    57,    -1,    -1,    -1,    61,    -1,    63,    -1,    -1,
      66,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    -1,    40,    41,
      42,    43,    -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,
      52,    53,    -1,    -1,    -1,    57,    -1,    -1,    -1,    61,
      -1,    -1,    -1,    -1,    66,    23,    24,    25,    26,    27,
      28,    29,    30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    41,    23,    24,    25,    26,    27,    28,
      29,    30,    -1,    -1,    52,    53,    -1,    -1,    -1,    57,
      -1,    40,    41,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    53,    -1,    -1,    -1,    57,    -1,
      -1,    -1,    61
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    23,    32,    33,    34,    35,    36,    37,    71,    72,
      98,   103,   104,   105,   106,   107,   108,   109,    23,    23,
      30,    60,   109,     0,    99,    73,    63,    69,     0,    66,
      61,    38,    39,   100,   102,   103,    74,    75,    76,   104,
      23,    23,    67,   100,   101,    64,    65,    29,    63,    63,
     100,    66,    77,    75,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    40,    41,    42,    43,    46,    52,    53,
      57,    61,    63,    66,    78,    80,    81,    84,    85,    86,
      90,    91,    96,    97,   104,    93,    29,   104,    23,    91,
      61,    91,    91,    91,    91,    91,    82,    67,    79,    63,
      63,    63,     5,     6,     7,     8,     9,    10,    11,    12,
      48,    49,    50,    51,    52,    53,    54,    55,    63,    92,
      47,    59,    29,    61,    47,    95,    91,    64,    78,    83,
      78,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    60,    91,    23,
      47,    23,    87,    88,    89,    91,    91,    61,    64,    67,
      88,    94,    91,    68,    64,    65,    87,    80,    69,    61,
      91,    88,    64,    44,    87,    80,    64
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  Parser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,    61,   124,    38,
      60,    62,    45,    43,    42,    47,    37,    33,   302,    46,
      91,    40,   303,    59,    41,    44,   123,   125,    58,    93
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    70,    71,    73,    72,    74,    74,    75,    75,    76,
      77,    78,    79,    78,    78,    80,    80,    80,    80,    80,
      80,    82,    81,    83,    84,    84,    85,    86,    86,    87,
      87,    88,    88,    89,    89,    90,    90,    90,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    92,    91,    93,
      91,    94,    91,    95,    91,    91,    91,    96,    96,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    99,    98,
     100,   101,   100,   100,   102,   102,   103,   103,   104,   104,
     104,   105,   106,   106,   106,   106,   106,   107,   107,   108,
     109,   109
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     3,     0,     7,     0,     1,     3,     1,     2,
       3,     0,     0,     3,     1,     2,     1,     1,     2,     2,
       2,     0,     3,     2,     1,     2,     2,     5,     7,     0,
       1,     3,     1,     3,     1,     2,     4,     4,     2,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     0,     5,     0,
       5,     0,     7,     0,     6,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     6,
       0,     0,     3,     2,     3,     3,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     3
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const Parser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "\"end of line\"",
  "\"unix script\"", "\"<<\"", "\">>\"", "\"||\"", "\"&&\"", "\"==\"",
  "\"!=\"", "\">=\"", "\"<=\"", "\"++\"", "\"--\"", "\"+=\"", "\"-=\"",
  "\"/=\"", "\"*=\"", "\"<<=\"", "\">>=\"", "\"&=\"", "\"|=\"",
  "\"identifier\"", "\"integer constant\"", "\"string constant\"",
  "\"char constant\"", "\"true\"", "\"false\"", "\"local variable\"",
  "\"instance attribute\"", "\"auto type\"", "\"void type\"",
  "\"int type\"", "\"bool type\"", "\"char type\"", "\"string type\"",
  "\"class\"", "\"inherit\"", "\"implement\"", "\"new\"", "\"this\"",
  "\"return\"", "\"if\"", "\"else\"", "\"ifelse\"", "\"print\"", "'='",
  "'|'", "'&'", "'<'", "'>'", "'-'", "'+'", "'*'", "'/'", "'%'", "'!'",
  "UNARY", "'.'", "'['", "'('", "PRE", "';'", "')'", "','", "'{'", "'}'",
  "':'", "']'", "$accept", "field", "function", "$@1",
  "function_arguments", "function_arguments_required", "function_argument",
  "function_statement", "statements", "$@2", "statement", "scope", "$@3",
  "scope_end", "return_statement", "print_statement",
  "conditional_statement", "call_arguments", "call_arguments_required",
  "call_argument", "variable_declare", "expression", "$@4", "$@5", "$@6",
  "$@7", "left", "right", "class_definition", "$@8", "class_body", "$@9",
  "class_modificator", "class_element", "type", "type_complex",
  "type_primary", "script_elements", "qualified_identifier", "start", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
       109,     0,    -1,   104,    30,    63,    -1,    -1,   104,    23,
      73,    61,    74,    64,    77,    -1,    -1,    75,    -1,    76,
      65,    75,    -1,    76,    -1,   104,    29,    -1,    66,    78,
      67,    -1,    -1,    -1,    80,    79,    78,    -1,    63,    -1,
      91,    63,    -1,    81,    -1,    86,    -1,    84,    63,    -1,
      85,    63,    -1,    90,    63,    -1,    -1,    66,    82,    83,
      -1,    78,    67,    -1,    42,    -1,    42,    91,    -1,    46,
      91,    -1,    43,    61,    91,    64,    80,    -1,    43,    61,
      91,    64,    80,    44,    80,    -1,    -1,    88,    -1,    89,
      65,    88,    -1,    89,    -1,    23,    68,    91,    -1,    91,
      -1,   104,    29,    -1,   104,    29,    47,    91,    -1,    31,
      29,    47,    91,    -1,    52,    91,    -1,    53,    91,    -1,
      57,    91,    -1,    91,    53,    91,    -1,    91,    52,    91,
      -1,    91,    54,    91,    -1,    91,    55,    91,    -1,    91,
       5,    91,    -1,    91,     6,    91,    -1,    91,    48,    91,
      -1,    91,     7,    91,    -1,    91,    49,    91,    -1,    91,
       8,    91,    -1,    91,     9,    91,    -1,    91,    10,    91,
      -1,    91,    11,    91,    -1,    91,    12,    91,    -1,    91,
      51,    91,    -1,    91,    50,    91,    -1,    -1,    91,    92,
      60,    88,    69,    -1,    -1,    23,    93,    61,    87,    64,
      -1,    -1,    97,    59,    23,    94,    61,    87,    64,    -1,
      -1,    40,   104,    95,    61,    87,    64,    -1,    96,    47,
      91,    -1,    97,    -1,    29,    -1,    30,    -1,    29,    -1,
      30,    -1,    24,    -1,    25,    -1,    27,    -1,    28,    -1,
      26,    -1,    41,    -1,    61,    91,    64,    -1,    -1,    37,
      23,    99,    66,   100,    67,    -1,    -1,    -1,   103,   101,
     100,    -1,   102,   100,    -1,    38,    23,    63,    -1,    39,
      23,    63,    -1,    72,    -1,    71,    -1,   105,    -1,   106,
      -1,    32,    -1,   106,    60,    69,    -1,    33,    -1,    34,
      -1,    36,    -1,    35,    -1,   108,    -1,    98,    -1,   103,
      -1,    23,    -1,    -1,   107,   109,     0,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     7,     8,    16,    17,    19,    23,    25,
      28,    32,    33,    34,    38,    40,    43,    45,    47,    50,
      53,    56,    57,    61,    64,    66,    69,    72,    78,    86,
      87,    89,    93,    95,    99,   101,   104,   109,   114,   117,
     120,   123,   127,   131,   135,   139,   143,   147,   151,   155,
     159,   163,   167,   171,   175,   179,   183,   187,   188,   194,
     195,   201,   202,   210,   211,   218,   222,   224,   226,   228,
     230,   232,   234,   236,   238,   240,   242,   244,   248,   249,
     256,   257,   258,   262,   265,   269,   273,   275,   277,   279,
     281,   283,   287,   289,   291,   293,   295,   297,   299,   301,
     303,   304
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   185,   185,   192,   192,   197,   199,   203,   204,   208,
     212,   218,   220,   220,   222,   226,   227,   228,   229,   230,
     231,   235,   235,   240,   244,   245,   249,   255,   256,   262,
     264,   268,   269,   273,   274,   282,   287,   292,   300,   301,
     302,   305,   306,   307,   308,   309,   310,   312,   313,   314,
     315,   317,   318,   319,   320,   321,   322,   325,   325,   328,
     328,   331,   331,   334,   334,   337,   338,   342,   343,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   362,   362,
     366,   368,   368,   370,   375,   376,   380,   381,   388,   389,
     390,   394,   398,   399,   400,   401,   402,   406,   407,   411,
     415,   417
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    57,     2,     2,     2,    56,    49,     2,
      61,    64,    54,    53,    65,    52,    59,    55,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    68,    63,
      50,    47,    51,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    60,     2,    69,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    66,    48,    67,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    58,    62
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 462;
  const int Parser::yynnts_ = 40;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 23;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 70;

  const unsigned int Parser::yyuser_token_number_max_ = 303;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


/* Line 1054 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

} } // kiwi::lang

/* Line 1054 of lalr1.cc  */
#line 1799 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"


/* Line 1056 of lalr1.cc  */
#line 422 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
 /*** Additional Code ***/

void kiwi::lang::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}

