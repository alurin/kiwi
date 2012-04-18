
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
#line 128 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"


#include "Driver.hpp"
#include "scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex



/* Line 317 of lalr1.cc  */
#line 79 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"

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
#line 148 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
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
#line 122 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 255 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 25: /* "\"local variable\"" */

/* Line 480 of lalr1.cc  */
#line 122 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 264 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 26: /* "\"instance attribute\"" */

/* Line 480 of lalr1.cc  */
#line 122 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 273 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 65: /* "scope" */

/* Line 480 of lalr1.cc  */
#line 124 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 282 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 72: /* "type" */

/* Line 480 of lalr1.cc  */
#line 123 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->typenode); };

/* Line 480 of lalr1.cc  */
#line 291 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 73: /* "type_complex" */

/* Line 480 of lalr1.cc  */
#line 123 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->typenode); };

/* Line 480 of lalr1.cc  */
#line 300 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 74: /* "type_primary" */

/* Line 480 of lalr1.cc  */
#line 123 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->typenode); };

/* Line 480 of lalr1.cc  */
#line 309 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
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
#line 395 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"

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
#line 149 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.func(*(yysemantic_stack_[(2) - (2)].stringVal), (yysemantic_stack_[(2) - (1)].typenode)); }
    break;

  case 3:

/* Line 678 of lalr1.cc  */
#line 152 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.funcEnd();     }
    break;

  case 8:

/* Line 678 of lalr1.cc  */
#line 166 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.func()->declare(*(yysemantic_stack_[(2) - (2)].stringVal), (yysemantic_stack_[(2) - (1)].typenode)); }
    break;

  case 11:

/* Line 678 of lalr1.cc  */
#line 178 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.scope()->append((yysemantic_stack_[(2) - (1)].rightnode)); }
    break;

  case 13:

/* Line 678 of lalr1.cc  */
#line 179 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.scope()->append((yysemantic_stack_[(1) - (1)].stmtnode)); }
    break;

  case 17:

/* Line 678 of lalr1.cc  */
#line 186 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.scopeBegin(); }
    break;

  case 19:

/* Line 678 of lalr1.cc  */
#line 191 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.scopeEnd(); }
    break;

  case 20:

/* Line 678 of lalr1.cc  */
#line 199 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.scope()->declare(*(yysemantic_stack_[(2) - (2)].stringVal), (yysemantic_stack_[(2) - (1)].typenode)); }
    break;

  case 21:

/* Line 678 of lalr1.cc  */
#line 203 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.expr()->getNeg((yysemantic_stack_[(2) - (2)].rightnode)); }
    break;

  case 22:

/* Line 678 of lalr1.cc  */
#line 204 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.expr()->getPos((yysemantic_stack_[(2) - (2)].rightnode)); }
    break;

  case 23:

/* Line 678 of lalr1.cc  */
#line 205 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.expr()->getNot((yysemantic_stack_[(2) - (2)].rightnode)); }
    break;

  case 24:

/* Line 678 of lalr1.cc  */
#line 208 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.expr()->getAdd((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode)); }
    break;

  case 25:

/* Line 678 of lalr1.cc  */
#line 209 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.expr()->getSub((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode)); }
    break;

  case 26:

/* Line 678 of lalr1.cc  */
#line 210 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.expr()->getMul((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode)); }
    break;

  case 27:

/* Line 678 of lalr1.cc  */
#line 211 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.expr()->getDiv((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode)); }
    break;

  case 28:

/* Line 678 of lalr1.cc  */
#line 212 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.expr()->getLsh((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode)); }
    break;

  case 29:

/* Line 678 of lalr1.cc  */
#line 213 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.expr()->getRsh((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode)); }
    break;

  case 30:

/* Line 678 of lalr1.cc  */
#line 215 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.expr()->getOr((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode)); }
    break;

  case 31:

/* Line 678 of lalr1.cc  */
#line 216 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.expr()->getOr((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), true); }
    break;

  case 32:

/* Line 678 of lalr1.cc  */
#line 217 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.expr()->getAnd((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode)); }
    break;

  case 33:

/* Line 678 of lalr1.cc  */
#line 218 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.expr()->getAnd((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), true); }
    break;

  case 34:

/* Line 678 of lalr1.cc  */
#line 220 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.expr()->getEq((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode)); }
    break;

  case 35:

/* Line 678 of lalr1.cc  */
#line 221 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.expr()->getNeq((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode)); }
    break;

  case 36:

/* Line 678 of lalr1.cc  */
#line 222 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.expr()->getGe((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode)); }
    break;

  case 37:

/* Line 678 of lalr1.cc  */
#line 223 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.expr()->getLe((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode)); }
    break;

  case 38:

/* Line 678 of lalr1.cc  */
#line 224 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.expr()->getGt((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode)); }
    break;

  case 39:

/* Line 678 of lalr1.cc  */
#line 225 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.expr()->getLt((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode)); }
    break;

  case 40:

/* Line 678 of lalr1.cc  */
#line 227 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.expr()->getAssign((yysemantic_stack_[(3) - (1)].leftnode), (yysemantic_stack_[(3) - (3)].rightnode)); }
    break;

  case 42:

/* Line 678 of lalr1.cc  */
#line 232 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.leftnode) = driver.scope()->get(*(yysemantic_stack_[(1) - (1)].stringVal))->getLeft(); }
    break;

  case 43:

/* Line 678 of lalr1.cc  */
#line 236 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.scope()->get(*(yysemantic_stack_[(1) - (1)].stringVal))->getRight(); }
    break;

  case 44:

/* Line 678 of lalr1.cc  */
#line 237 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.expr()->getInt((yysemantic_stack_[(1) - (1)].integerVal));            }
    break;

  case 45:

/* Line 678 of lalr1.cc  */
#line 238 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = (yysemantic_stack_[(3) - (2)].rightnode); }
    break;

  case 48:

/* Line 678 of lalr1.cc  */
#line 248 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.typenode) = driver.type()->getVoid();    }
    break;

  case 49:

/* Line 678 of lalr1.cc  */
#line 252 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.typenode) = driver.type()->getArray((yysemantic_stack_[(3) - (1)].typenode)); }
    break;

  case 50:

/* Line 678 of lalr1.cc  */
#line 256 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.typenode) = driver.type()->getInt();     }
    break;

  case 51:

/* Line 678 of lalr1.cc  */
#line 257 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.typenode) = driver.type()->getBool();  }
    break;

  case 52:

/* Line 678 of lalr1.cc  */
#line 258 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.typenode) = driver.type()->getString();  }
    break;



/* Line 678 of lalr1.cc  */
#line 773 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
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
  const signed char Parser::yypact_ninf_ = -32;
  const short int
  Parser::yypact_[] =
  {
       -11,   -32,   -32,   -32,   -32,   -11,     0,   -32,   -20,    26,
      29,   -32,   -24,   -32,   -32,    -7,   -32,   -11,    -3,     1,
     -32,    27,    -4,   -11,   -32,   192,   -32,   -32,   -32,    22,
     199,   199,   199,   199,   -32,   -32,     4,   -32,    16,    -5,
      42,   -32,    49,   -31,   -31,   -31,     3,   192,   -32,   192,
     192,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   -32,   199,   199,   199,   -32,
     -32,    28,   -32,   -32,   -32,   209,   209,    60,    70,   115,
     115,   134,   134,   105,   123,    48,    48,   -31,   -31,   192,
      52,    52,    52,   -32,   -32
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
        53,    48,    50,    51,    52,    53,     0,    46,    47,     0,
       0,     2,     0,     1,    54,     0,    49,     4,     0,     5,
       7,     0,     0,     0,     8,    10,     3,     6,    44,    43,
       0,     0,     0,     0,    17,    16,     0,    13,     0,     0,
       0,    41,     0,    21,    22,    23,     0,    10,     9,    10,
      10,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    11,     0,     0,     0,    20,
      45,     0,    18,    14,    15,    28,    29,    31,    33,    34,
      35,    36,    37,    30,    32,    25,    24,    26,    27,    10,
      38,    39,    40,    19,    12
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
       -32,   -32,   -32,   -32,   -32,    54,   -32,   100,   -32,   -32,
     -32,   -32,   -32,   -32,   147,   -32,   -32,    20,   -32,   -32,
      46
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  Parser::yydefgoto_[] =
  {
        -1,     5,    15,    18,    19,    20,    26,    36,    89,    49,
      37,    47,    72,    38,    39,    40,    41,    42,     7,     8,
       9
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -43;
  const signed char
  Parser::yytable_[] =
  {
        51,    52,    53,    54,    55,    56,    57,    58,    51,    52,
      53,    54,    55,    56,    57,    58,     1,     2,     3,     4,
       6,    66,    67,    11,    12,     6,    13,    59,    60,    14,
      16,    61,    62,    63,    64,    59,    60,    21,    17,    61,
      62,    63,    64,    21,    22,    25,    65,    66,    67,    23,
      70,    10,    24,   -42,    48,    66,    67,    51,    52,    53,
      54,    55,    56,    57,    58,    51,    52,    50,    54,    55,
      56,    57,    58,    68,    69,    51,    52,    27,    93,    55,
      56,    57,    58,     0,    59,    60,    63,    64,    61,    62,
      63,    64,    59,    60,     0,     0,    61,    62,    63,    64,
      66,    67,    59,    60,    66,    67,    61,    62,    63,    64,
      51,    52,    66,    67,    55,    56,    57,    58,     0,     0,
      51,    52,    66,    67,   -43,   -43,    57,    58,    51,    52,
       0,     0,    55,    56,    57,    58,     0,     0,    60,    51,
      52,    61,    62,    63,    64,   -43,   -43,    71,     0,    73,
      74,    61,    62,    63,    64,     0,     0,    66,    67,    61,
      62,    63,    64,     0,     0,     0,     0,    66,    67,     0,
      61,    62,    63,    64,     0,    66,    67,    43,    44,    45,
      46,     0,     0,     0,     0,     0,    66,    67,     0,    94,
       0,     0,     0,     0,     0,     0,     0,     0,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,     0,    90,    91,    92,    28,    29,     0,     1,
       2,     3,     4,    28,    29,     0,     0,     0,    30,    31,
       0,     0,     0,    32,     0,    30,    31,    33,     0,     0,
      32,    34,     0,    35,    33,    61,    62,    63,    64,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    66,    67
  };

  /* YYCHECK.  */
  const signed char
  Parser::yycheck_[] =
  {
         5,     6,     7,     8,     9,    10,    11,    12,     5,     6,
       7,     8,     9,    10,    11,    12,    27,    28,    29,    30,
       0,    52,    53,    23,    44,     5,     0,    32,    33,     0,
      54,    36,    37,    38,    39,    32,    33,    17,    45,    36,
      37,    38,    39,    23,    47,    49,    51,    52,    53,    48,
      47,     5,    25,    31,    50,    52,    53,     5,     6,     7,
       8,     9,    10,    11,    12,     5,     6,    51,     8,     9,
      10,    11,    12,    31,    25,     5,     6,    23,    50,     9,
      10,    11,    12,    -1,    32,    33,    38,    39,    36,    37,
      38,    39,    32,    33,    -1,    -1,    36,    37,    38,    39,
      52,    53,    32,    33,    52,    53,    36,    37,    38,    39,
       5,     6,    52,    53,     9,    10,    11,    12,    -1,    -1,
       5,     6,    52,    53,     9,    10,    11,    12,     5,     6,
      -1,    -1,     9,    10,    11,    12,    -1,    -1,    33,     5,
       6,    36,    37,    38,    39,    11,    12,    47,    -1,    49,
      50,    36,    37,    38,    39,    -1,    -1,    52,    53,    36,
      37,    38,    39,    -1,    -1,    -1,    -1,    52,    53,    -1,
      36,    37,    38,    39,    -1,    52,    53,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    -1,    52,    53,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    -1,    66,    67,    68,    24,    25,    -1,    27,
      28,    29,    30,    24,    25,    -1,    -1,    -1,    36,    37,
      -1,    -1,    -1,    41,    -1,    36,    37,    45,    -1,    -1,
      41,    49,    -1,    51,    45,    36,    37,    38,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    27,    28,    29,    30,    56,    72,    73,    74,    75,
      75,    23,    44,     0,     0,    57,    54,    45,    58,    59,
      60,    72,    47,    48,    25,    49,    61,    60,    24,    25,
      36,    37,    41,    45,    49,    51,    62,    65,    68,    69,
      70,    71,    72,    69,    69,    69,    69,    66,    50,    64,
      51,     5,     6,     7,     8,     9,    10,    11,    12,    32,
      33,    36,    37,    38,    39,    51,    52,    53,    31,    25,
      47,    62,    67,    62,    62,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    63,
      69,    69,    69,    50,    62
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
     285,    61,   124,    38,    60,    62,    45,    43,    42,    47,
      37,    33,   286,    46,    91,    40,   287,    41,    44,   123,
     125,    59,   288,   289,    93
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    55,    57,    56,    58,    58,    59,    59,    60,    61,
      62,    63,    62,    64,    62,    62,    62,    66,    65,    67,
      68,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    70,    71,    71,    71,    72,    72,    72,    73,
      74,    74,    74,    75,    75
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     0,     7,     0,     1,     3,     1,     2,     3,
       0,     0,     4,     0,     3,     3,     1,     0,     3,     2,
       2,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     1,     1,     3,     1,     1,     1,     3,
       1,     1,     1,     0,     3
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
  "\"identifier\"", "\"integer\"", "\"local variable\"",
  "\"instance attribute\"", "\"void\"", "\"int\"", "\"bool\"",
  "\"string\"", "'='", "'|'", "'&'", "'<'", "'>'", "'-'", "'+'", "'*'",
  "'/'", "'%'", "'!'", "UNARY", "'.'", "'['", "'('", "PRE", "')'", "','",
  "'{'", "'}'", "';'", "\">\"", "\"<\"", "']'", "$accept", "function",
  "$@1", "function_arguments", "function_arguments_required",
  "function_argument", "function_statement", "statements", "$@2", "$@3",
  "scope", "$@4", "scope_end", "variable_declare", "expression", "left",
  "right", "type", "type_complex", "type_primary", "start", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        75,     0,    -1,    -1,    72,    23,    57,    45,    58,    47,
      61,    -1,    -1,    59,    -1,    59,    48,    60,    -1,    60,
      -1,    72,    25,    -1,    49,    62,    50,    -1,    -1,    -1,
      69,    51,    63,    62,    -1,    -1,    65,    64,    62,    -1,
      68,    51,    62,    -1,    51,    -1,    -1,    49,    66,    67,
      -1,    62,    50,    -1,    72,    25,    -1,    36,    69,    -1,
      37,    69,    -1,    41,    69,    -1,    69,    37,    69,    -1,
      69,    36,    69,    -1,    69,    38,    69,    -1,    69,    39,
      69,    -1,    69,     5,    69,    -1,    69,     6,    69,    -1,
      69,    32,    69,    -1,    69,     7,    69,    -1,    69,    33,
      69,    -1,    69,     8,    69,    -1,    69,     9,    69,    -1,
      69,    10,    69,    -1,    69,    11,    69,    -1,    69,    12,
      69,    -1,    69,    52,    69,    -1,    69,    53,    69,    -1,
      70,    31,    69,    -1,    71,    -1,    25,    -1,    25,    -1,
      24,    -1,    45,    69,    47,    -1,    73,    -1,    74,    -1,
      27,    -1,    74,    44,    54,    -1,    28,    -1,    29,    -1,
      30,    -1,    -1,    56,    75,     0,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned char
  Parser::yyprhs_[] =
  {
         0,     0,     3,     4,    12,    13,    15,    19,    21,    24,
      28,    29,    30,    35,    36,    40,    44,    46,    47,    51,
      54,    57,    60,    63,    66,    70,    74,    78,    82,    86,
      90,    94,    98,   102,   106,   110,   114,   118,   122,   126,
     130,   134,   136,   138,   140,   142,   146,   148,   150,   152,
     156,   158,   160,   162,   163
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   149,   149,   149,   155,   157,   161,   162,   166,   170,
     176,   178,   178,   179,   179,   181,   182,   186,   186,   191,
     199,   203,   204,   205,   208,   209,   210,   211,   212,   213,
     215,   216,   217,   218,   220,   221,   222,   223,   224,   225,
     227,   228,   232,   236,   237,   238,   246,   247,   248,   252,
     256,   257,   258,   262,   264
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
       2,     2,     2,    41,     2,     2,     2,    40,    33,     2,
      45,    47,    38,    37,    48,    36,    43,    39,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    51,
      34,    31,    35,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    54,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,    32,    50,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    42,    46,    52,    53
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 262;
  const int Parser::yynnts_ = 21;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 13;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 55;

  const unsigned int Parser::yyuser_token_number_max_ = 289;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


/* Line 1054 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

} } // kiwi::lang

/* Line 1054 of lalr1.cc  */
#line 1318 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"


/* Line 1056 of lalr1.cc  */
#line 269 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
 /*** Additional Code ***/

void kiwi::lang::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}

