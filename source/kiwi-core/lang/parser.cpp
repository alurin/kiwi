
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
#line 4 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
 /*** C/C++ Declarations ***/

#include "kiwi/Config.hpp"
#include <stdio.h>
#include <string>
#include <vector>
#include "ExpressionNode.hpp"
#include "TypeNode.hpp"
#include "FunctionNode.hpp"



/* Line 311 of lalr1.cc  */
#line 56 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"


#include "parser.hpp"

/* User implementation prologue.  */

/* Line 317 of lalr1.cc  */
#line 144 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"


#include "Driver.hpp"
#include "scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

#define yyfree(__px1) delete __px1; __px1 = 0;



/* Line 317 of lalr1.cc  */
#line 81 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"

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
#line 150 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
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
#line 136 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 257 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 25: /* "\"string constant\"" */

/* Line 480 of lalr1.cc  */
#line 140 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->ustringVal); };

/* Line 480 of lalr1.cc  */
#line 266 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 29: /* "\"local variable\"" */

/* Line 480 of lalr1.cc  */
#line 136 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 275 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 30: /* "\"instance attribute\"" */

/* Line 480 of lalr1.cc  */
#line 136 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 284 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 77: /* "scope" */

/* Line 480 of lalr1.cc  */
#line 139 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 293 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 79: /* "scope_end" */

/* Line 480 of lalr1.cc  */
#line 139 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 302 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 80: /* "return_statement" */

/* Line 480 of lalr1.cc  */
#line 139 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 311 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 81: /* "print_statement" */

/* Line 480 of lalr1.cc  */
#line 139 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 320 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 86: /* "expression" */

/* Line 480 of lalr1.cc  */
#line 137 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->rightnode); };

/* Line 480 of lalr1.cc  */
#line 329 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 89: /* "right" */

/* Line 480 of lalr1.cc  */
#line 137 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->rightnode); };

/* Line 480 of lalr1.cc  */
#line 338 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 90: /* "type" */

/* Line 480 of lalr1.cc  */
#line 138 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->typenode); };

/* Line 480 of lalr1.cc  */
#line 347 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 91: /* "type_complex" */

/* Line 480 of lalr1.cc  */
#line 138 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->typenode); };

/* Line 480 of lalr1.cc  */
#line 356 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 92: /* "type_primary" */

/* Line 480 of lalr1.cc  */
#line 138 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->typenode); };

/* Line 480 of lalr1.cc  */
#line 365 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
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
#line 43 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
{
    // initialize the initial location object
    yylloc.begin.filename = yylloc.end.filename = &driver.streamname;
}

/* Line 553 of lalr1.cc  */
#line 451 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"

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
#line 168 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.field(*(yysemantic_stack_[(3) - (2)].stringVal), (yysemantic_stack_[(3) - (1)].typenode)); yyfree((yysemantic_stack_[(3) - (2)].stringVal)); }
    break;

  case 3:

/* Line 678 of lalr1.cc  */
#line 175 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.func(*(yysemantic_stack_[(2) - (2)].stringVal), (yysemantic_stack_[(2) - (1)].typenode)); yyfree((yysemantic_stack_[(2) - (2)].stringVal)); }
    break;

  case 4:

/* Line 678 of lalr1.cc  */
#line 178 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.funcEnd();     }
    break;

  case 9:

/* Line 678 of lalr1.cc  */
#line 192 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.func()->declare(*(yysemantic_stack_[(2) - (2)].stringVal), (yysemantic_stack_[(2) - (1)].typenode)); }
    break;

  case 12:

/* Line 678 of lalr1.cc  */
#line 204 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.scope()->append((yysemantic_stack_[(2) - (1)].rightnode)); }
    break;

  case 14:

/* Line 678 of lalr1.cc  */
#line 205 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.scope()->append((yysemantic_stack_[(1) - (1)].stmtnode)); }
    break;

  case 16:

/* Line 678 of lalr1.cc  */
#line 206 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.scope()->append((yysemantic_stack_[(1) - (1)].stmtnode)); }
    break;

  case 18:

/* Line 678 of lalr1.cc  */
#line 207 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.scope()->append((yysemantic_stack_[(1) - (1)].stmtnode)); }
    break;

  case 22:

/* Line 678 of lalr1.cc  */
#line 213 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.scopeBegin();    }
    break;

  case 23:

/* Line 678 of lalr1.cc  */
#line 214 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.stmtnode) = (yysemantic_stack_[(3) - (3)].stmtnode);                }
    break;

  case 24:

/* Line 678 of lalr1.cc  */
#line 218 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.stmtnode) = driver.scopeEnd(); }
    break;

  case 25:

/* Line 678 of lalr1.cc  */
#line 222 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.stmtnode) = driver.createReturn((yylocation_stack_[(2) - (1)]));     }
    break;

  case 26:

/* Line 678 of lalr1.cc  */
#line 223 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.stmtnode) = driver.createReturn((yysemantic_stack_[(3) - (2)].rightnode), (yylocation_stack_[(3) - (1)])); }
    break;

  case 27:

/* Line 678 of lalr1.cc  */
#line 227 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.stmtnode) = driver.createPrint((yysemantic_stack_[(3) - (2)].rightnode), (yylocation_stack_[(3) - (1)]));  }
    break;

  case 32:

/* Line 678 of lalr1.cc  */
#line 243 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.call()->append(*(yysemantic_stack_[(3) - (1)].stringVal), (yysemantic_stack_[(3) - (3)].rightnode)); yyfree((yysemantic_stack_[(3) - (1)].stringVal)); }
    break;

  case 33:

/* Line 678 of lalr1.cc  */
#line 244 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.call()->append((yysemantic_stack_[(1) - (1)].rightnode));      }
    break;

  case 34:

/* Line 678 of lalr1.cc  */
#line 252 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.scope()->declare(*(yysemantic_stack_[(2) - (2)].stringVal), (yysemantic_stack_[(2) - (1)].typenode)); yyfree((yysemantic_stack_[(2) - (2)].stringVal)); }
    break;

  case 35:

/* Line 678 of lalr1.cc  */
#line 256 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createNeg((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)])); }
    break;

  case 36:

/* Line 678 of lalr1.cc  */
#line 257 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createPos((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)])); }
    break;

  case 37:

/* Line 678 of lalr1.cc  */
#line 258 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createNot((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)])); }
    break;

  case 38:

/* Line 678 of lalr1.cc  */
#line 261 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createAdd((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 39:

/* Line 678 of lalr1.cc  */
#line 262 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createSub((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 40:

/* Line 678 of lalr1.cc  */
#line 263 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createMul((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 41:

/* Line 678 of lalr1.cc  */
#line 264 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createDiv((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 42:

/* Line 678 of lalr1.cc  */
#line 265 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createLsh((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 43:

/* Line 678 of lalr1.cc  */
#line 266 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createRsh((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 44:

/* Line 678 of lalr1.cc  */
#line 268 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createOr ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), false, (yylocation_stack_[(3) - (2)])); }
    break;

  case 45:

/* Line 678 of lalr1.cc  */
#line 269 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createOr ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), true,  (yylocation_stack_[(3) - (2)])); }
    break;

  case 46:

/* Line 678 of lalr1.cc  */
#line 270 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createAnd((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), false, (yylocation_stack_[(3) - (2)])); }
    break;

  case 47:

/* Line 678 of lalr1.cc  */
#line 271 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createAnd((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), true,  (yylocation_stack_[(3) - (2)])); }
    break;

  case 48:

/* Line 678 of lalr1.cc  */
#line 273 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createEq ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 49:

/* Line 678 of lalr1.cc  */
#line 274 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createNeq((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 50:

/* Line 678 of lalr1.cc  */
#line 275 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createGe ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 51:

/* Line 678 of lalr1.cc  */
#line 276 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createLe ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 52:

/* Line 678 of lalr1.cc  */
#line 277 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createGt ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 53:

/* Line 678 of lalr1.cc  */
#line 278 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createLt ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 54:

/* Line 678 of lalr1.cc  */
#line 280 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.call(*(yysemantic_stack_[(1) - (1)].stringVal)); yyfree((yysemantic_stack_[(1) - (1)].stringVal));      }
    break;

  case 55:

/* Line 678 of lalr1.cc  */
#line 281 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.callEnd();             }
    break;

  case 56:

/* Line 678 of lalr1.cc  */
#line 289 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createAssign((yysemantic_stack_[(3) - (1)].leftnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 58:

/* Line 678 of lalr1.cc  */
#line 294 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.leftnode) = driver.left(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal));          }
    break;

  case 59:

/* Line 678 of lalr1.cc  */
#line 295 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.leftnode) = driver.instanceLeft(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal));  }
    break;

  case 60:

/* Line 678 of lalr1.cc  */
#line 299 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.right(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal));         }
    break;

  case 61:

/* Line 678 of lalr1.cc  */
#line 300 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.instanceRight(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal)); }
    break;

  case 62:

/* Line 678 of lalr1.cc  */
#line 301 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createInt((yysemantic_stack_[(1) - (1)].integerVal), (yylocation_stack_[(1) - (1)]));                  }
    break;

  case 63:

/* Line 678 of lalr1.cc  */
#line 302 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createString(*(yysemantic_stack_[(1) - (1)].ustringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].ustringVal));  }
    break;

  case 64:

/* Line 678 of lalr1.cc  */
#line 303 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createBool(true, (yylocation_stack_[(1) - (1)]));               }
    break;

  case 65:

/* Line 678 of lalr1.cc  */
#line 304 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createBool(false, (yylocation_stack_[(1) - (1)]));              }
    break;

  case 66:

/* Line 678 of lalr1.cc  */
#line 305 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createChar((yysemantic_stack_[(1) - (1)].charVal), (yylocation_stack_[(1) - (1)]));                 }
    break;

  case 67:

/* Line 678 of lalr1.cc  */
#line 306 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = (yysemantic_stack_[(3) - (2)].rightnode);                                        }
    break;

  case 70:

/* Line 678 of lalr1.cc  */
#line 316 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.typenode) = driver.createVoidTy((yylocation_stack_[(1) - (1)]));    }
    break;

  case 71:

/* Line 678 of lalr1.cc  */
#line 320 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.typenode) = driver.createArrayTy((yysemantic_stack_[(3) - (1)].typenode), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)])); }
    break;

  case 72:

/* Line 678 of lalr1.cc  */
#line 324 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.typenode) = driver.createIntTy((yylocation_stack_[(1) - (1)]));     }
    break;

  case 73:

/* Line 678 of lalr1.cc  */
#line 325 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.typenode) = driver.createBoolTy((yylocation_stack_[(1) - (1)]));    }
    break;

  case 74:

/* Line 678 of lalr1.cc  */
#line 326 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.typenode) = driver.createStringTy((yylocation_stack_[(1) - (1)]));  }
    break;

  case 75:

/* Line 678 of lalr1.cc  */
#line 327 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.typenode) = driver.createCharTy((yylocation_stack_[(1) - (1)]));    }
    break;



/* Line 678 of lalr1.cc  */
#line 955 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
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
  const signed char Parser::yypact_ninf_ = -43;
  const short int
  Parser::yypact_[] =
  {
       -24,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -17,   -43,
     -42,   -24,    30,   -43,   -10,   -14,    83,   -43,    29,   -43,
     -43,   -43,   -24,    28,    31,   -43,    59,    40,   -24,   -43,
     250,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,    48,
      64,   288,   300,   300,   300,   300,   300,   -43,   -43,    45,
     -43,   -43,   -43,    50,    17,    67,   -43,    80,    55,   -43,
      70,    86,   -43,   -43,   -43,     9,   250,   -43,   250,   250,
     250,   250,   300,   300,   300,   300,   300,   300,   300,   300,
     300,   300,   300,   300,   300,   300,   300,   300,   -43,   300,
     -43,   333,   -43,   -43,   -43,    60,   -43,   -43,   -43,   -43,
     -43,    22,    22,   136,   154,   207,   207,   223,   223,   162,
     215,   223,   223,    24,    24,   -43,   -43,   250,   146,    49,
      62,   -43,    63,   146,   -43,   -43,   300,   -43,   333,   146,
     -43
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
        78,    70,    72,    73,    75,    74,    77,    76,     0,    68,
      69,    78,     0,     3,     0,     0,     0,     1,     0,     2,
      71,    79,     5,     0,     6,     8,     0,     0,     0,     9,
      11,     4,     7,    54,    62,    63,    66,    64,    65,    60,
      61,     0,     0,     0,     0,     0,     0,    21,    22,     0,
      14,    16,    18,     0,     0,     0,    57,     0,     0,    25,
       0,     0,    35,    36,    37,     0,    11,    10,    11,    11,
      11,    11,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    12,     0,
      34,    28,    26,    27,    67,     0,    23,    15,    17,    19,
      20,    42,    43,    45,    47,    48,    49,    50,    51,    44,
      46,    53,    52,    39,    38,    40,    41,    11,    56,    54,
       0,    29,    31,    33,    24,    13,     0,    55,     0,    32,
      30
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
       -43,   -43,   -43,   -43,   -43,   -43,    95,   -43,    33,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,    -4,
     -43,   -43,   -41,   -43,   -43,   -43,   222,   -43,   -43,   -43,
     114
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  Parser::yydefgoto_[] =
  {
        -1,     6,     7,    18,    23,    24,    25,    31,    49,   117,
      68,    69,    70,    50,    66,    96,    51,    52,   120,   121,
     122,    53,    54,    58,    55,    56,    57,     9,    10,    11,
      12
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -60;
  const short int
  Parser::yytable_[] =
  {
        60,    61,    62,    63,    64,    65,    13,     1,     2,     3,
       4,     5,    15,    14,    72,    73,    74,    75,    76,    77,
      78,    79,    72,    73,    74,    75,    76,    77,    78,    79,
      17,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,    19,   118,    20,
     123,    80,    81,    82,    83,    84,    85,    86,    87,    80,
      81,    82,    83,    84,    85,    86,    87,    94,    84,    85,
      86,    87,    86,    87,    88,    72,    73,    74,    75,    76,
      77,    78,    79,    21,    22,   129,    27,   123,    29,   -58,
      28,    72,    73,    74,    75,    76,    77,    78,    79,    95,
      30,    97,    98,    99,   100,   -59,    67,    71,    89,    90,
      91,   126,    80,    81,    82,    83,    84,    85,    86,    87,
     127,   124,   128,    32,   130,    16,     0,    92,    80,    81,
      82,    83,    84,    85,    86,    87,     0,     0,     0,     0,
       0,    72,    73,    93,    75,    76,    77,    78,    79,     0,
     125,    72,    73,    74,    75,    76,    77,    78,    79,    72,
      73,     0,     0,    76,    77,    78,    79,    72,    73,     0,
       0,    76,    77,    78,    79,     0,     0,     0,    80,    81,
      82,    83,    84,    85,    86,    87,     0,     0,    80,    81,
      82,    83,    84,    85,    86,    87,    80,    81,    82,    83,
      84,    85,    86,    87,     0,    81,    82,    83,    84,    85,
      86,    87,    72,    73,     0,     0,   -60,   -60,    78,    79,
      72,    73,     8,     0,    76,    77,    78,    79,    72,    73,
       0,     0,     0,     8,   -60,   -60,     0,     0,     0,     0,
       0,     0,     0,     0,    26,     0,     0,     0,     0,     0,
      26,    82,    83,    84,    85,    86,    87,     0,     0,    82,
      83,    84,    85,    86,    87,     0,     0,   -60,   -60,    84,
      85,    86,    87,    33,    34,    35,    36,    37,    38,    39,
      40,     1,     2,     3,     4,     5,    41,     0,     0,     0,
      42,     0,     0,     0,     0,     0,    43,    44,     0,     0,
       0,    45,     0,     0,     0,    46,     0,    47,     0,     0,
      48,    33,    34,    35,    36,    37,    38,    39,    40,     0,
       0,     0,     0,    33,    34,    35,    36,    37,    38,    39,
      40,     0,     0,     0,    43,    44,     0,     0,     0,    45,
       0,     0,     0,    46,     0,    59,    43,    44,     0,     0,
       0,    45,     0,     0,     0,    46,   119,    34,    35,    36,
      37,    38,    39,    40,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    43,
      44,     0,     0,     0,    45,     0,     0,     0,    46
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
        41,    42,    43,    44,    45,    46,    23,    31,    32,    33,
      34,    35,    54,    30,     5,     6,     7,     8,     9,    10,
      11,    12,     5,     6,     7,     8,     9,    10,    11,    12,
       0,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    57,    89,    63,
      91,    42,    43,    44,    45,    46,    47,    48,    49,    42,
      43,    44,    45,    46,    47,    48,    49,    58,    46,    47,
      48,    49,    48,    49,    57,     5,     6,     7,     8,     9,
      10,    11,    12,     0,    55,   126,    58,   128,    29,    41,
      59,     5,     6,     7,     8,     9,    10,    11,    12,    66,
      60,    68,    69,    70,    71,    41,    61,    57,    41,    29,
      55,    62,    42,    43,    44,    45,    46,    47,    48,    49,
      58,    61,    59,    28,   128,    11,    -1,    57,    42,    43,
      44,    45,    46,    47,    48,    49,    -1,    -1,    -1,    -1,
      -1,     5,     6,    57,     8,     9,    10,    11,    12,    -1,
     117,     5,     6,     7,     8,     9,    10,    11,    12,     5,
       6,    -1,    -1,     9,    10,    11,    12,     5,     6,    -1,
      -1,     9,    10,    11,    12,    -1,    -1,    -1,    42,    43,
      44,    45,    46,    47,    48,    49,    -1,    -1,    42,    43,
      44,    45,    46,    47,    48,    49,    42,    43,    44,    45,
      46,    47,    48,    49,    -1,    43,    44,    45,    46,    47,
      48,    49,     5,     6,    -1,    -1,     9,    10,    11,    12,
       5,     6,     0,    -1,     9,    10,    11,    12,     5,     6,
      -1,    -1,    -1,    11,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,
      28,    44,    45,    46,    47,    48,    49,    -1,    -1,    44,
      45,    46,    47,    48,    49,    -1,    -1,    44,    45,    46,
      47,    48,    49,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    46,    47,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    55,    -1,    57,    -1,    -1,
      60,    23,    24,    25,    26,    27,    28,    29,    30,    -1,
      -1,    -1,    -1,    23,    24,    25,    26,    27,    28,    29,
      30,    -1,    -1,    -1,    46,    47,    -1,    -1,    -1,    51,
      -1,    -1,    -1,    55,    -1,    57,    46,    47,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    55,    23,    24,    25,    26,
      27,    28,    29,    30,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      47,    -1,    -1,    -1,    51,    -1,    -1,    -1,    55
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    31,    32,    33,    34,    35,    65,    66,    90,    91,
      92,    93,    94,    23,    30,    54,    94,     0,    67,    57,
      63,     0,    55,    68,    69,    70,    90,    58,    59,    29,
      60,    71,    70,    23,    24,    25,    26,    27,    28,    29,
      30,    36,    40,    46,    47,    51,    55,    57,    60,    72,
      77,    80,    81,    85,    86,    88,    89,    90,    87,    57,
      86,    86,    86,    86,    86,    86,    78,    61,    74,    75,
      76,    57,     5,     6,     7,     8,     9,    10,    11,    12,
      42,    43,    44,    45,    46,    47,    48,    49,    57,    41,
      29,    55,    57,    57,    58,    72,    79,    72,    72,    72,
      72,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    73,    86,    23,
      82,    83,    84,    86,    61,    72,    62,    58,    59,    86,
      83
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
     295,    61,   124,    38,    60,    62,    45,    43,    42,    47,
      37,    33,   296,    46,    91,    40,   297,    59,    41,    44,
     123,   125,    58,    93
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    64,    65,    67,    66,    68,    68,    69,    69,    70,
      71,    72,    73,    72,    74,    72,    75,    72,    76,    72,
      72,    72,    78,    77,    79,    80,    80,    81,    82,    82,
      83,    83,    84,    84,    85,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    87,    86,    86,    86,    88,    88,
      89,    89,    89,    89,    89,    89,    89,    89,    90,    90,
      90,    91,    92,    92,    92,    92,    93,    93,    94,    94
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     3,     0,     7,     0,     1,     3,     1,     2,
       3,     0,     0,     4,     0,     3,     0,     3,     0,     3,
       3,     1,     0,     3,     2,     2,     3,     3,     0,     1,
       3,     1,     3,     1,     2,     2,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     5,     3,     1,     1,     1,
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
  "\"instance attribute\"", "\"void type\"", "\"int type\"",
  "\"bool type\"", "\"char type\"", "\"string type\"", "\"return\"",
  "\"if\"", "\"else\"", "\"ifelse\"", "\"print\"", "'='", "'|'", "'&'",
  "'<'", "'>'", "'-'", "'+'", "'*'", "'/'", "'%'", "'!'", "UNARY", "'.'",
  "'['", "'('", "PRE", "';'", "')'", "','", "'{'", "'}'", "':'", "']'",
  "$accept", "field", "function", "$@1", "function_arguments",
  "function_arguments_required", "function_argument", "function_statement",
  "statements", "$@2", "$@3", "$@4", "$@5", "scope", "$@6", "scope_end",
  "return_statement", "print_statement", "call_arguments",
  "call_arguments_required", "call_argument", "variable_declare",
  "expression", "$@7", "left", "right", "type", "type_complex",
  "type_primary", "elements", "start", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        94,     0,    -1,    90,    30,    57,    -1,    -1,    90,    23,
      67,    55,    68,    58,    71,    -1,    -1,    69,    -1,    69,
      59,    70,    -1,    70,    -1,    90,    29,    -1,    60,    72,
      61,    -1,    -1,    -1,    86,    57,    73,    72,    -1,    -1,
      77,    74,    72,    -1,    -1,    80,    75,    72,    -1,    -1,
      81,    76,    72,    -1,    85,    57,    72,    -1,    57,    -1,
      -1,    60,    78,    79,    -1,    72,    61,    -1,    36,    57,
      -1,    36,    86,    57,    -1,    40,    86,    57,    -1,    -1,
      83,    -1,    84,    59,    83,    -1,    84,    -1,    23,    62,
      86,    -1,    86,    -1,    90,    29,    -1,    46,    86,    -1,
      47,    86,    -1,    51,    86,    -1,    86,    47,    86,    -1,
      86,    46,    86,    -1,    86,    48,    86,    -1,    86,    49,
      86,    -1,    86,     5,    86,    -1,    86,     6,    86,    -1,
      86,    42,    86,    -1,    86,     7,    86,    -1,    86,    43,
      86,    -1,    86,     8,    86,    -1,    86,     9,    86,    -1,
      86,    10,    86,    -1,    86,    11,    86,    -1,    86,    12,
      86,    -1,    86,    45,    86,    -1,    86,    44,    86,    -1,
      -1,    23,    87,    55,    82,    58,    -1,    88,    41,    86,
      -1,    89,    -1,    29,    -1,    30,    -1,    29,    -1,    30,
      -1,    24,    -1,    25,    -1,    27,    -1,    28,    -1,    26,
      -1,    55,    86,    58,    -1,    91,    -1,    92,    -1,    31,
      -1,    92,    54,    63,    -1,    32,    -1,    33,    -1,    35,
      -1,    34,    -1,    66,    -1,    65,    -1,    -1,    93,    94,
       0,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned char
  Parser::yyprhs_[] =
  {
         0,     0,     3,     7,     8,    16,    17,    19,    23,    25,
      28,    32,    33,    34,    39,    40,    44,    45,    49,    50,
      54,    58,    60,    61,    65,    68,    71,    75,    79,    80,
      82,    86,    88,    92,    94,    97,   100,   103,   106,   110,
     114,   118,   122,   126,   130,   134,   138,   142,   146,   150,
     154,   158,   162,   166,   170,   171,   177,   181,   183,   185,
     187,   189,   191,   193,   195,   197,   199,   201,   205,   207,
     209,   211,   215,   217,   219,   221,   223,   225,   227,   228
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   168,   168,   175,   175,   181,   183,   187,   188,   192,
     196,   202,   204,   204,   205,   205,   206,   206,   207,   207,
     208,   209,   213,   213,   218,   222,   223,   227,   232,   234,
     238,   239,   243,   244,   252,   256,   257,   258,   261,   262,
     263,   264,   265,   266,   268,   269,   270,   271,   273,   274,
     275,   276,   277,   278,   280,   280,   289,   290,   294,   295,
     299,   300,   301,   302,   303,   304,   305,   306,   314,   315,
     316,   320,   324,   325,   326,   327,   331,   332,   336,   338
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
       2,     2,     2,    51,     2,     2,     2,    50,    43,     2,
      55,    58,    48,    47,    59,    46,    53,    49,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    62,    57,
      44,    41,    45,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    54,     2,    63,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    60,    42,    61,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    52,    56
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 388;
  const int Parser::yynnts_ = 31;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 17;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 64;

  const unsigned int Parser::yyuser_token_number_max_ = 297;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


/* Line 1054 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

} } // kiwi::lang

/* Line 1054 of lalr1.cc  */
#line 1560 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"


/* Line 1056 of lalr1.cc  */
#line 343 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
 /*** Additional Code ***/

void kiwi::lang::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}

