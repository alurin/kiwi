
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
#line 4 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
 /*** C/C++ Declarations ***/

#include "kiwi/Config.hpp"
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
#line 145 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"


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
#line 137 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 257 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 25: /* "\"string constant\"" */

/* Line 480 of lalr1.cc  */
#line 141 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->ustringVal); };

/* Line 480 of lalr1.cc  */
#line 266 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 29: /* "\"local variable\"" */

/* Line 480 of lalr1.cc  */
#line 137 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 275 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 30: /* "\"instance attribute\"" */

/* Line 480 of lalr1.cc  */
#line 137 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 284 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 76: /* "statement" */

/* Line 480 of lalr1.cc  */
#line 140 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 293 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 77: /* "scope" */

/* Line 480 of lalr1.cc  */
#line 140 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 302 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 79: /* "scope_end" */

/* Line 480 of lalr1.cc  */
#line 140 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 311 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 80: /* "return_statement" */

/* Line 480 of lalr1.cc  */
#line 140 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 320 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 81: /* "print_statement" */

/* Line 480 of lalr1.cc  */
#line 140 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 329 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 82: /* "conditional_statement" */

/* Line 480 of lalr1.cc  */
#line 140 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 338 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 88: /* "expression" */

/* Line 480 of lalr1.cc  */
#line 138 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->rightnode); };

/* Line 480 of lalr1.cc  */
#line 347 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 93: /* "right" */

/* Line 480 of lalr1.cc  */
#line 138 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->rightnode); };

/* Line 480 of lalr1.cc  */
#line 356 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 94: /* "type" */

/* Line 480 of lalr1.cc  */
#line 139 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->typenode); };

/* Line 480 of lalr1.cc  */
#line 365 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 95: /* "type_complex" */

/* Line 480 of lalr1.cc  */
#line 139 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->typenode); };

/* Line 480 of lalr1.cc  */
#line 374 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 96: /* "type_primary" */

/* Line 480 of lalr1.cc  */
#line 139 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->typenode); };

/* Line 480 of lalr1.cc  */
#line 383 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
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
#line 43 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
{
    // initialize the initial location object
    yylloc.begin.filename = yylloc.end.filename = &driver.streamname;
}

/* Line 553 of lalr1.cc  */
#line 469 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"

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
#line 169 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.field(*(yysemantic_stack_[(3) - (2)].stringVal), (yysemantic_stack_[(3) - (1)].typenode)); yyfree((yysemantic_stack_[(3) - (2)].stringVal)); }
    break;

  case 3:

/* Line 678 of lalr1.cc  */
#line 176 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.func(*(yysemantic_stack_[(2) - (2)].stringVal), (yysemantic_stack_[(2) - (1)].typenode)); yyfree((yysemantic_stack_[(2) - (2)].stringVal)); }
    break;

  case 4:

/* Line 678 of lalr1.cc  */
#line 179 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.funcEnd();     }
    break;

  case 9:

/* Line 678 of lalr1.cc  */
#line 193 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.func()->declare(*(yysemantic_stack_[(2) - (2)].stringVal), (yysemantic_stack_[(2) - (1)].typenode)); }
    break;

  case 12:

/* Line 678 of lalr1.cc  */
#line 205 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.scope()->append((yysemantic_stack_[(1) - (1)].stmtnode)); }
    break;

  case 15:

/* Line 678 of lalr1.cc  */
#line 210 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createExpr((yysemantic_stack_[(2) - (1)].rightnode));       }
    break;

  case 20:

/* Line 678 of lalr1.cc  */
#line 215 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = 0; }
    break;

  case 21:

/* Line 678 of lalr1.cc  */
#line 219 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.scopeBegin();              }
    break;

  case 22:

/* Line 678 of lalr1.cc  */
#line 220 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = (yysemantic_stack_[(3) - (3)].stmtnode);                          }
    break;

  case 23:

/* Line 678 of lalr1.cc  */
#line 224 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.scopeEnd();           }
    break;

  case 24:

/* Line 678 of lalr1.cc  */
#line 228 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createReturn((yylocation_stack_[(1) - (1)]));     }
    break;

  case 25:

/* Line 678 of lalr1.cc  */
#line 229 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createReturn((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)])); }
    break;

  case 26:

/* Line 678 of lalr1.cc  */
#line 233 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createPrint((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)]));  }
    break;

  case 27:

/* Line 678 of lalr1.cc  */
#line 239 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createCond((yysemantic_stack_[(5) - (3)].rightnode), (yysemantic_stack_[(5) - (5)].stmtnode), 0,  (yylocation_stack_[(5) - (1)])); }
    break;

  case 28:

/* Line 678 of lalr1.cc  */
#line 240 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createCond((yysemantic_stack_[(7) - (3)].rightnode), (yysemantic_stack_[(7) - (5)].stmtnode), (yysemantic_stack_[(7) - (7)].stmtnode), (yylocation_stack_[(7) - (1)])); }
    break;

  case 33:

/* Line 678 of lalr1.cc  */
#line 257 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.call()->append(*(yysemantic_stack_[(3) - (1)].stringVal), (yysemantic_stack_[(3) - (3)].rightnode)); yyfree((yysemantic_stack_[(3) - (1)].stringVal)); }
    break;

  case 34:

/* Line 678 of lalr1.cc  */
#line 258 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.call()->append((yysemantic_stack_[(1) - (1)].rightnode));      }
    break;

  case 35:

/* Line 678 of lalr1.cc  */
#line 262 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.sub()->append((yysemantic_stack_[(3) - (1)].rightnode)); }
    break;

  case 36:

/* Line 678 of lalr1.cc  */
#line 263 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.sub()->append((yysemantic_stack_[(1) - (1)].rightnode)); }
    break;

  case 37:

/* Line 678 of lalr1.cc  */
#line 271 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.scope()->declare(*(yysemantic_stack_[(2) - (2)].stringVal), (yysemantic_stack_[(2) - (1)].typenode));     yyfree((yysemantic_stack_[(2) - (2)].stringVal)); }
    break;

  case 38:

/* Line 678 of lalr1.cc  */
#line 272 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.scope()->declare(*(yysemantic_stack_[(4) - (2)].stringVal), (yysemantic_stack_[(4) - (1)].typenode), (yysemantic_stack_[(4) - (4)].rightnode)); yyfree((yysemantic_stack_[(4) - (2)].stringVal)); }
    break;

  case 39:

/* Line 678 of lalr1.cc  */
#line 273 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.scope()->declare(*(yysemantic_stack_[(4) - (2)].stringVal), (yysemantic_stack_[(4) - (4)].rightnode));     yyfree((yysemantic_stack_[(4) - (2)].stringVal)); }
    break;

  case 40:

/* Line 678 of lalr1.cc  */
#line 277 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createNeg((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)])); }
    break;

  case 41:

/* Line 678 of lalr1.cc  */
#line 278 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createPos((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)])); }
    break;

  case 42:

/* Line 678 of lalr1.cc  */
#line 279 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createNot((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)])); }
    break;

  case 43:

/* Line 678 of lalr1.cc  */
#line 282 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createAdd((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 44:

/* Line 678 of lalr1.cc  */
#line 283 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createSub((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 45:

/* Line 678 of lalr1.cc  */
#line 284 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createMul((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 46:

/* Line 678 of lalr1.cc  */
#line 285 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createDiv((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 47:

/* Line 678 of lalr1.cc  */
#line 286 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createLsh((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 48:

/* Line 678 of lalr1.cc  */
#line 287 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createRsh((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 49:

/* Line 678 of lalr1.cc  */
#line 289 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createOr ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), false, (yylocation_stack_[(3) - (2)])); }
    break;

  case 50:

/* Line 678 of lalr1.cc  */
#line 290 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createOr ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), true,  (yylocation_stack_[(3) - (2)])); }
    break;

  case 51:

/* Line 678 of lalr1.cc  */
#line 291 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createAnd((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), false, (yylocation_stack_[(3) - (2)])); }
    break;

  case 52:

/* Line 678 of lalr1.cc  */
#line 292 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createAnd((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), true,  (yylocation_stack_[(3) - (2)])); }
    break;

  case 53:

/* Line 678 of lalr1.cc  */
#line 294 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createEq ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 54:

/* Line 678 of lalr1.cc  */
#line 295 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createNeq((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 55:

/* Line 678 of lalr1.cc  */
#line 296 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createGe ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 56:

/* Line 678 of lalr1.cc  */
#line 297 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createLe ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 57:

/* Line 678 of lalr1.cc  */
#line 298 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createGt ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 58:

/* Line 678 of lalr1.cc  */
#line 299 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createLt ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 59:

/* Line 678 of lalr1.cc  */
#line 301 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.subBegin((yysemantic_stack_[(1) - (1)].rightnode));               }
    break;

  case 60:

/* Line 678 of lalr1.cc  */
#line 302 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.subEnd((yylocation_stack_[(5) - (2)]));            }
    break;

  case 61:

/* Line 678 of lalr1.cc  */
#line 304 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.call(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal));  }
    break;

  case 62:

/* Line 678 of lalr1.cc  */
#line 305 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.callEnd();             }
    break;

  case 63:

/* Line 678 of lalr1.cc  */
#line 307 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.call((yysemantic_stack_[(3) - (1)].rightnode), *(yysemantic_stack_[(3) - (3)].stringVal), (yylocation_stack_[(3) - (1)]) + (yylocation_stack_[(3) - (3)])); yyfree((yysemantic_stack_[(3) - (3)].stringVal)); }
    break;

  case 64:

/* Line 678 of lalr1.cc  */
#line 308 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.callEnd();                     }
    break;

  case 65:

/* Line 678 of lalr1.cc  */
#line 310 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createAssign((yysemantic_stack_[(3) - (1)].leftnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 67:

/* Line 678 of lalr1.cc  */
#line 315 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.leftnode) = driver.left(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal));          }
    break;

  case 68:

/* Line 678 of lalr1.cc  */
#line 316 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.leftnode) = driver.instanceLeft(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal));  }
    break;

  case 69:

/* Line 678 of lalr1.cc  */
#line 320 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.right(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal));         }
    break;

  case 70:

/* Line 678 of lalr1.cc  */
#line 321 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.instanceRight(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal)); }
    break;

  case 71:

/* Line 678 of lalr1.cc  */
#line 322 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createInt((yysemantic_stack_[(1) - (1)].integerVal), (yylocation_stack_[(1) - (1)]));                  }
    break;

  case 72:

/* Line 678 of lalr1.cc  */
#line 323 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createString(*(yysemantic_stack_[(1) - (1)].ustringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].ustringVal));  }
    break;

  case 73:

/* Line 678 of lalr1.cc  */
#line 324 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createBool(true, (yylocation_stack_[(1) - (1)]));               }
    break;

  case 74:

/* Line 678 of lalr1.cc  */
#line 325 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createBool(false, (yylocation_stack_[(1) - (1)]));              }
    break;

  case 75:

/* Line 678 of lalr1.cc  */
#line 326 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createChar((yysemantic_stack_[(1) - (1)].charVal), (yylocation_stack_[(1) - (1)]));                 }
    break;

  case 76:

/* Line 678 of lalr1.cc  */
#line 327 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createThis((yylocation_stack_[(1) - (1)]));                     }
    break;

  case 77:

/* Line 678 of lalr1.cc  */
#line 328 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = (yysemantic_stack_[(3) - (2)].rightnode);                                        }
    break;

  case 80:

/* Line 678 of lalr1.cc  */
#line 338 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createVoidTy((yylocation_stack_[(1) - (1)]));    }
    break;

  case 81:

/* Line 678 of lalr1.cc  */
#line 342 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createArrayTy((yysemantic_stack_[(3) - (1)].typenode), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)])); }
    break;

  case 82:

/* Line 678 of lalr1.cc  */
#line 346 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createIntTy((yylocation_stack_[(1) - (1)]));     }
    break;

  case 83:

/* Line 678 of lalr1.cc  */
#line 347 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createBoolTy((yylocation_stack_[(1) - (1)]));    }
    break;

  case 84:

/* Line 678 of lalr1.cc  */
#line 348 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createStringTy((yylocation_stack_[(1) - (1)]));  }
    break;

  case 85:

/* Line 678 of lalr1.cc  */
#line 349 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createCharTy((yylocation_stack_[(1) - (1)]));    }
    break;



/* Line 678 of lalr1.cc  */
#line 1043 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
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
  const short int Parser::yypact_ninf_ = -132;
  const short int
  Parser::yypact_[] =
  {
       -24,  -132,  -132,  -132,  -132,  -132,  -132,  -132,   -16,  -132,
     -23,   -24,    32,  -132,   -25,   -14,    52,  -132,    -3,  -132,
    -132,  -132,   -24,    -5,  -132,    -2,    29,    -1,   -24,  -132,
     279,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,    17,
      28,    33,  -132,   359,    15,   359,   359,   359,   359,   359,
    -132,  -132,    10,  -132,  -132,    18,    22,  -132,    34,   105,
      31,    21,    49,    35,    48,   125,   359,   125,  -132,  -132,
    -132,    78,   279,  -132,   279,  -132,  -132,  -132,   359,   359,
     359,   359,   359,   359,   359,   359,   359,   359,   359,   359,
     359,   359,   359,   359,  -132,    38,   359,    73,    55,   374,
     359,    97,  -132,    36,  -132,  -132,   -31,   -31,   174,   156,
     203,   203,   250,   250,   182,   229,   250,   250,   -29,   -29,
    -132,  -132,   359,   125,  -132,   359,    54,    59,  -132,    60,
     125,   125,   319,  -132,    74,    19,    63,   125,   359,  -132,
     374,   100,  -132,   359,   374,   125,  -132,   319,  -132,    98,
    -132,  -132
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
        88,    80,    82,    83,    85,    84,    87,    86,     0,    78,
      79,    88,     0,     3,     0,     0,     0,     1,     0,     2,
      81,    89,     5,     0,     6,     8,     0,     0,     0,     9,
      11,     4,     7,    61,    71,    72,    75,    73,    74,    69,
      70,     0,    76,    24,     0,     0,     0,     0,     0,     0,
      14,    21,     0,    12,    16,     0,     0,    17,     0,    59,
       0,    66,     0,     0,     0,    25,     0,    26,    40,    41,
      42,    59,    11,    10,    11,    18,    19,    20,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    15,     0,     0,     0,    37,    29,
       0,    59,    77,     0,    22,    13,    47,    48,    50,    52,
      53,    54,    55,    56,    49,    51,    58,    57,    44,    43,
      45,    46,     0,    65,    63,     0,    61,     0,    30,    32,
      34,    39,     0,    23,     0,    36,     0,    38,     0,    62,
       0,    27,    60,     0,    29,    33,    31,     0,    35,     0,
      28,    64
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -132,  -132,  -132,  -132,  -132,   131,  -132,  -132,   -59,  -132,
    -131,  -132,  -132,  -132,  -132,  -132,  -132,    16,    23,  -132,
      46,  -132,   -43,  -132,  -132,  -132,  -132,  -132,   236,  -132,
    -132,  -132,   166
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     6,     7,    18,    23,    24,    25,    31,    52,    74,
      53,    54,    72,   104,    55,    56,    57,   127,   128,   129,
     134,    58,    59,    95,    63,   136,    60,    61,    62,     9,
      10,    11,    12
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -69;
  const short int
  Parser::yytable_[] =
  {
        65,   141,    67,    68,    69,    70,    71,    13,     1,     2,
       3,     4,     5,   103,    14,   105,   150,    90,    91,    92,
      93,    92,    93,   101,    78,    79,    80,    81,    82,    83,
      84,    85,    17,    15,    19,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,    20,    21,   123,    22,    27,   130,   131,    29,    28,
     -67,    30,    64,    86,    87,    88,    89,    90,    91,    92,
      93,   -68,    66,    73,    96,   -59,    97,    75,    98,   135,
     143,    76,   137,    78,    79,    80,    81,    82,    83,    84,
      85,   100,    99,    77,   122,   145,   124,   130,   125,   133,
     135,   130,    78,    79,    80,    81,    82,    83,    84,    85,
      78,    79,    80,    81,    82,    83,    84,    85,   138,   139,
     144,   140,    86,    87,    88,    89,    90,    91,    92,    93,
      78,    79,    80,    81,    82,    83,    84,    85,   102,   142,
     147,    86,    87,    88,    89,    90,    91,    92,    93,    86,
      87,    88,    89,    90,    91,    92,    93,   132,   151,    32,
     149,    78,    79,   146,    94,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    16,     0,    78,
      79,   -59,    81,    82,    83,    84,    85,    78,    79,   148,
       0,    82,    83,    84,    85,     0,     0,     0,     0,     0,
      86,    87,    88,    89,    90,    91,    92,    93,    78,    79,
       0,     0,   -69,   -69,    84,    85,     0,     0,    86,    87,
      88,    89,    90,    91,    92,    93,     0,    87,    88,    89,
      90,    91,    92,    93,    78,    79,     8,     0,    82,    83,
      84,    85,     0,     0,     0,     0,     0,     8,     0,    88,
      89,    90,    91,    92,    93,    78,    79,     0,    26,     0,
       0,   -69,   -69,     0,    26,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    88,    89,    90,    91,    92,
      93,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -69,   -69,    90,    91,
      92,    93,    33,    34,    35,    36,    37,    38,    39,    40,
      41,     1,     2,     3,     4,     5,    42,    43,    44,     0,
       0,    45,     0,     0,     0,     0,     0,    46,    47,     0,
       0,     0,    48,     0,     0,     0,    49,     0,    50,     0,
       0,    51,    33,    34,    35,    36,    37,    38,    39,    40,
      41,     1,     2,     3,     4,     5,    42,    43,    44,     0,
       0,    45,     0,     0,     0,     0,     0,    46,    47,     0,
       0,     0,    48,     0,     0,     0,    49,     0,     0,     0,
       0,    51,    33,    34,    35,    36,    37,    38,    39,    40,
       0,     0,     0,     0,     0,     0,    42,   126,    34,    35,
      36,    37,    38,    39,    40,     0,     0,    46,    47,     0,
       0,    42,    48,     0,     0,     0,    49,     0,     0,     0,
       0,     0,    46,    47,     0,     0,     0,    48,     0,     0,
       0,    49
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
        43,   132,    45,    46,    47,    48,    49,    23,    32,    33,
      34,    35,    36,    72,    30,    74,   147,    48,    49,    50,
      51,    50,    51,    66,     5,     6,     7,     8,     9,    10,
      11,    12,     0,    56,    59,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    65,     0,    96,    57,    60,    99,   100,    29,    61,
      43,    62,    29,    44,    45,    46,    47,    48,    49,    50,
      51,    43,    57,    63,    43,    56,    55,    59,    29,   122,
      61,    59,   125,     5,     6,     7,     8,     9,    10,    11,
      12,    43,    57,    59,    56,   138,    23,   140,    43,    63,
     143,   144,     5,     6,     7,     8,     9,    10,    11,    12,
       5,     6,     7,     8,     9,    10,    11,    12,    64,    60,
      57,    61,    44,    45,    46,    47,    48,    49,    50,    51,
       5,     6,     7,     8,     9,    10,    11,    12,    60,    65,
      40,    44,    45,    46,    47,    48,    49,    50,    51,    44,
      45,    46,    47,    48,    49,    50,    51,    60,    60,    28,
     144,     5,     6,   140,    59,     9,    10,    11,    12,    44,
      45,    46,    47,    48,    49,    50,    51,    11,    -1,     5,
       6,    56,     8,     9,    10,    11,    12,     5,     6,   143,
      -1,     9,    10,    11,    12,    -1,    -1,    -1,    -1,    -1,
      44,    45,    46,    47,    48,    49,    50,    51,     5,     6,
      -1,    -1,     9,    10,    11,    12,    -1,    -1,    44,    45,
      46,    47,    48,    49,    50,    51,    -1,    45,    46,    47,
      48,    49,    50,    51,     5,     6,     0,    -1,     9,    10,
      11,    12,    -1,    -1,    -1,    -1,    -1,    11,    -1,    46,
      47,    48,    49,    50,    51,     5,     6,    -1,    22,    -1,
      -1,    11,    12,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    47,    48,    49,
      50,    51,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    -1,
      -1,    42,    -1,    -1,    -1,    -1,    -1,    48,    49,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    57,    -1,    59,    -1,
      -1,    62,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    -1,
      -1,    42,    -1,    -1,    -1,    -1,    -1,    48,    49,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    57,    -1,    -1,    -1,
      -1,    62,    23,    24,    25,    26,    27,    28,    29,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    23,    24,    25,
      26,    27,    28,    29,    30,    -1,    -1,    48,    49,    -1,
      -1,    37,    53,    -1,    -1,    -1,    57,    -1,    -1,    -1,
      -1,    -1,    48,    49,    -1,    -1,    -1,    53,    -1,    -1,
      -1,    57
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    32,    33,    34,    35,    36,    67,    68,    94,    95,
      96,    97,    98,    23,    30,    56,    98,     0,    69,    59,
      65,     0,    57,    70,    71,    72,    94,    60,    61,    29,
      62,    73,    71,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    37,    38,    39,    42,    48,    49,    53,    57,
      59,    62,    74,    76,    77,    80,    81,    82,    87,    88,
      92,    93,    94,    90,    29,    88,    57,    88,    88,    88,
      88,    88,    78,    63,    75,    59,    59,    59,     5,     6,
       7,     8,     9,    10,    11,    12,    44,    45,    46,    47,
      48,    49,    50,    51,    59,    89,    43,    55,    29,    57,
      43,    88,    60,    74,    79,    74,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    56,    88,    23,    43,    23,    83,    84,    85,
      88,    88,    60,    63,    86,    88,    91,    88,    64,    60,
      61,    76,    65,    61,    57,    88,    84,    40,    86,    83,
      76,    60
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
     295,   296,   297,    61,   124,    38,    60,    62,    45,    43,
      42,    47,    37,    33,   298,    46,    91,    40,   299,    59,
      41,    44,   123,   125,    58,    93
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    66,    67,    69,    68,    70,    70,    71,    71,    72,
      73,    74,    75,    74,    74,    76,    76,    76,    76,    76,
      76,    78,    77,    79,    80,    80,    81,    82,    82,    83,
      83,    84,    84,    85,    85,    86,    86,    87,    87,    87,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    89,
      88,    90,    88,    91,    88,    88,    88,    92,    92,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    94,    94,
      94,    95,    96,    96,    96,    96,    97,    97,    98,    98
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     3,     0,     7,     0,     1,     3,     1,     2,
       3,     0,     0,     3,     1,     2,     1,     1,     2,     2,
       2,     0,     3,     2,     1,     2,     2,     5,     7,     0,
       1,     3,     1,     3,     1,     3,     1,     2,     4,     4,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     0,
       5,     0,     5,     0,     7,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     0,     3
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
  "\"this\"", "\"return\"", "\"if\"", "\"else\"", "\"ifelse\"",
  "\"print\"", "'='", "'|'", "'&'", "'<'", "'>'", "'-'", "'+'", "'*'",
  "'/'", "'%'", "'!'", "UNARY", "'.'", "'['", "'('", "PRE", "';'", "')'",
  "','", "'{'", "'}'", "':'", "']'", "$accept", "field", "function", "$@1",
  "function_arguments", "function_arguments_required", "function_argument",
  "function_statement", "statements", "$@2", "statement", "scope", "$@3",
  "scope_end", "return_statement", "print_statement",
  "conditional_statement", "call_arguments", "call_arguments_required",
  "call_argument", "subtraction_args", "variable_declare", "expression",
  "$@4", "$@5", "$@6", "left", "right", "type", "type_complex",
  "type_primary", "elements", "start", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        98,     0,    -1,    94,    30,    59,    -1,    -1,    94,    23,
      69,    57,    70,    60,    73,    -1,    -1,    71,    -1,    72,
      61,    71,    -1,    72,    -1,    94,    29,    -1,    62,    74,
      63,    -1,    -1,    -1,    76,    75,    74,    -1,    59,    -1,
      88,    59,    -1,    77,    -1,    82,    -1,    80,    59,    -1,
      81,    59,    -1,    87,    59,    -1,    -1,    62,    78,    79,
      -1,    74,    63,    -1,    38,    -1,    38,    88,    -1,    42,
      88,    -1,    39,    57,    88,    60,    76,    -1,    39,    57,
      88,    60,    76,    40,    76,    -1,    -1,    84,    -1,    85,
      61,    84,    -1,    85,    -1,    23,    64,    88,    -1,    88,
      -1,    88,    61,    86,    -1,    88,    -1,    94,    29,    -1,
      94,    29,    43,    88,    -1,    31,    29,    43,    88,    -1,
      48,    88,    -1,    49,    88,    -1,    53,    88,    -1,    88,
      49,    88,    -1,    88,    48,    88,    -1,    88,    50,    88,
      -1,    88,    51,    88,    -1,    88,     5,    88,    -1,    88,
       6,    88,    -1,    88,    44,    88,    -1,    88,     7,    88,
      -1,    88,    45,    88,    -1,    88,     8,    88,    -1,    88,
       9,    88,    -1,    88,    10,    88,    -1,    88,    11,    88,
      -1,    88,    12,    88,    -1,    88,    47,    88,    -1,    88,
      46,    88,    -1,    -1,    88,    89,    56,    86,    65,    -1,
      -1,    23,    90,    57,    83,    60,    -1,    -1,    93,    55,
      23,    91,    57,    83,    60,    -1,    92,    43,    88,    -1,
      93,    -1,    29,    -1,    30,    -1,    29,    -1,    30,    -1,
      24,    -1,    25,    -1,    27,    -1,    28,    -1,    26,    -1,
      37,    -1,    57,    88,    60,    -1,    95,    -1,    96,    -1,
      32,    -1,    96,    56,    65,    -1,    33,    -1,    34,    -1,
      36,    -1,    35,    -1,    68,    -1,    67,    -1,    -1,    97,
      98,     0,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     7,     8,    16,    17,    19,    23,    25,
      28,    32,    33,    34,    38,    40,    43,    45,    47,    50,
      53,    56,    57,    61,    64,    66,    69,    72,    78,    86,
      87,    89,    93,    95,    99,   101,   105,   107,   110,   115,
     120,   123,   126,   129,   133,   137,   141,   145,   149,   153,
     157,   161,   165,   169,   173,   177,   181,   185,   189,   193,
     194,   200,   201,   207,   208,   216,   220,   222,   224,   226,
     228,   230,   232,   234,   236,   238,   240,   242,   246,   248,
     250,   252,   256,   258,   260,   262,   264,   266,   268,   269
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   169,   169,   176,   176,   182,   184,   188,   189,   193,
     197,   203,   205,   205,   206,   210,   211,   212,   213,   214,
     215,   219,   219,   224,   228,   229,   233,   239,   240,   246,
     248,   252,   253,   257,   258,   262,   263,   271,   272,   273,
     277,   278,   279,   282,   283,   284,   285,   286,   287,   289,
     290,   291,   292,   294,   295,   296,   297,   298,   299,   301,
     301,   304,   304,   307,   307,   310,   311,   315,   316,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   336,   337,
     338,   342,   346,   347,   348,   349,   353,   354,   358,   360
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
       2,     2,     2,    53,     2,     2,     2,    52,    45,     2,
      57,    60,    50,    49,    61,    48,    55,    51,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    64,    59,
      46,    43,    47,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    56,     2,    65,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    62,    44,    63,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    54,    58
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 431;
  const int Parser::yynnts_ = 33;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 17;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 66;

  const unsigned int Parser::yyuser_token_number_max_ = 299;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


/* Line 1054 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

} } // kiwi::lang

/* Line 1054 of lalr1.cc  */
#line 1673 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"


/* Line 1056 of lalr1.cc  */
#line 365 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
 /*** Additional Code ***/

void kiwi::lang::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}

