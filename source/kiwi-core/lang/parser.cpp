
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
#line 133 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"


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
#line 127 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 255 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 25: /* "\"local variable\"" */

/* Line 480 of lalr1.cc  */
#line 127 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 264 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 26: /* "\"instance attribute\"" */

/* Line 480 of lalr1.cc  */
#line 127 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 273 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 70: /* "scope" */

/* Line 480 of lalr1.cc  */
#line 129 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 282 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 73: /* "return_statement" */

/* Line 480 of lalr1.cc  */
#line 129 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 291 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 78: /* "type" */

/* Line 480 of lalr1.cc  */
#line 128 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->typenode); };

/* Line 480 of lalr1.cc  */
#line 300 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 79: /* "type_complex" */

/* Line 480 of lalr1.cc  */
#line 128 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->typenode); };

/* Line 480 of lalr1.cc  */
#line 309 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
	break;
      case 80: /* "type_primary" */

/* Line 480 of lalr1.cc  */
#line 128 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
	{ delete (yyvaluep->typenode); };

/* Line 480 of lalr1.cc  */
#line 318 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
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
#line 404 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"

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
#line 154 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.func(*(yysemantic_stack_[(2) - (2)].stringVal), (yysemantic_stack_[(2) - (1)].typenode)); }
    break;

  case 3:

/* Line 678 of lalr1.cc  */
#line 157 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.funcEnd();     }
    break;

  case 8:

/* Line 678 of lalr1.cc  */
#line 171 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.func()->declare(*(yysemantic_stack_[(2) - (2)].stringVal), (yysemantic_stack_[(2) - (1)].typenode)); }
    break;

  case 11:

/* Line 678 of lalr1.cc  */
#line 183 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.scope()->append((yysemantic_stack_[(2) - (1)].rightnode)); }
    break;

  case 13:

/* Line 678 of lalr1.cc  */
#line 184 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.scope()->append((yysemantic_stack_[(1) - (1)].stmtnode)); }
    break;

  case 15:

/* Line 678 of lalr1.cc  */
#line 185 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.scope()->append((yysemantic_stack_[(1) - (1)].stmtnode)); }
    break;

  case 19:

/* Line 678 of lalr1.cc  */
#line 192 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.scopeBegin(); }
    break;

  case 21:

/* Line 678 of lalr1.cc  */
#line 197 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.scopeEnd(); }
    break;

  case 22:

/* Line 678 of lalr1.cc  */
#line 201 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.stmtnode) = driver.createReturn((yylocation_stack_[(2) - (1)]));     }
    break;

  case 23:

/* Line 678 of lalr1.cc  */
#line 202 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.stmtnode) = driver.createReturn((yysemantic_stack_[(3) - (2)].rightnode), (yylocation_stack_[(3) - (1)])); }
    break;

  case 24:

/* Line 678 of lalr1.cc  */
#line 214 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { driver.scope()->declare(*(yysemantic_stack_[(2) - (2)].stringVal), (yysemantic_stack_[(2) - (1)].typenode)); }
    break;

  case 25:

/* Line 678 of lalr1.cc  */
#line 218 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createNeg((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)])); }
    break;

  case 26:

/* Line 678 of lalr1.cc  */
#line 219 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createPos((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)])); }
    break;

  case 27:

/* Line 678 of lalr1.cc  */
#line 220 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createNot((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)])); }
    break;

  case 28:

/* Line 678 of lalr1.cc  */
#line 223 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createAdd((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 29:

/* Line 678 of lalr1.cc  */
#line 224 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createSub((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 30:

/* Line 678 of lalr1.cc  */
#line 225 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createMul((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 31:

/* Line 678 of lalr1.cc  */
#line 226 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createDiv((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 32:

/* Line 678 of lalr1.cc  */
#line 227 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createLsh((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 33:

/* Line 678 of lalr1.cc  */
#line 228 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createRsh((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 34:

/* Line 678 of lalr1.cc  */
#line 230 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createOr ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), false, (yylocation_stack_[(3) - (2)])); }
    break;

  case 35:

/* Line 678 of lalr1.cc  */
#line 231 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createOr ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), true,  (yylocation_stack_[(3) - (2)])); }
    break;

  case 36:

/* Line 678 of lalr1.cc  */
#line 232 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createAnd((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), false, (yylocation_stack_[(3) - (2)])); }
    break;

  case 37:

/* Line 678 of lalr1.cc  */
#line 233 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createAnd((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), true,  (yylocation_stack_[(3) - (2)])); }
    break;

  case 38:

/* Line 678 of lalr1.cc  */
#line 235 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createEq ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 39:

/* Line 678 of lalr1.cc  */
#line 236 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createNeq((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 40:

/* Line 678 of lalr1.cc  */
#line 237 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createGe ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 41:

/* Line 678 of lalr1.cc  */
#line 238 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createLe ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 42:

/* Line 678 of lalr1.cc  */
#line 239 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createGt ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 43:

/* Line 678 of lalr1.cc  */
#line 240 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createLt ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 44:

/* Line 678 of lalr1.cc  */
#line 242 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createAssign((yysemantic_stack_[(3) - (1)].leftnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 46:

/* Line 678 of lalr1.cc  */
#line 247 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.leftnode) = driver.left(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); }
    break;

  case 47:

/* Line 678 of lalr1.cc  */
#line 251 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.right(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); }
    break;

  case 48:

/* Line 678 of lalr1.cc  */
#line 252 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = driver.createInt((yysemantic_stack_[(1) - (1)].integerVal), (yylocation_stack_[(1) - (1)]));          }
    break;

  case 49:

/* Line 678 of lalr1.cc  */
#line 253 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.rightnode) = (yysemantic_stack_[(3) - (2)].rightnode); }
    break;

  case 52:

/* Line 678 of lalr1.cc  */
#line 263 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.typenode) = driver.createVoidTy((yylocation_stack_[(1) - (1)]));    }
    break;

  case 53:

/* Line 678 of lalr1.cc  */
#line 267 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.typenode) = driver.createArrayTy((yysemantic_stack_[(3) - (1)].typenode), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)])); }
    break;

  case 54:

/* Line 678 of lalr1.cc  */
#line 271 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.typenode) = driver.createIntTy((yylocation_stack_[(1) - (1)]));     }
    break;

  case 55:

/* Line 678 of lalr1.cc  */
#line 272 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.typenode) = driver.createBoolTy((yylocation_stack_[(1) - (1)]));    }
    break;

  case 56:

/* Line 678 of lalr1.cc  */
#line 273 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
    { (yyval.typenode) = driver.createStringTy((yylocation_stack_[(1) - (1)]));  }
    break;



/* Line 678 of lalr1.cc  */
#line 803 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"
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
  const signed char Parser::yypact_ninf_ = -41;
  const short int
  Parser::yypact_[] =
  {
       121,   -41,   -41,   -41,   -41,   121,    -3,   -41,   -27,    27,
      41,   -41,   -16,   -41,   -41,     0,   -41,   121,     6,    20,
     -41,    57,    28,   121,   -41,   213,   -41,   -41,   -41,    50,
     224,   164,   164,   164,   164,   -41,   -41,    37,   -41,   -41,
      39,    -5,    71,   -41,    70,   -41,     3,   -40,   -40,   -40,
      56,   213,   -41,   213,   213,   213,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     -41,   164,   164,   164,   -41,   -41,   -41,    76,   -41,   -41,
     -41,   -41,    60,    60,    78,   117,    13,    13,   160,   160,
     127,   135,    -9,    -9,   -40,   -40,   213,    68,    68,    68,
     -41,   -41
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
        57,    52,    54,    55,    56,    57,     0,    50,    51,     0,
       0,     2,     0,     1,    58,     0,    53,     4,     0,     5,
       7,     0,     0,     0,     8,    10,     3,     6,    48,    47,
       0,     0,     0,     0,     0,    19,    18,     0,    13,    15,
       0,     0,     0,    45,     0,    22,     0,    25,    26,    27,
       0,    10,     9,    10,    10,    10,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      11,     0,     0,     0,    24,    23,    49,     0,    20,    14,
      16,    17,    32,    33,    35,    37,    38,    39,    40,    41,
      34,    36,    29,    28,    30,    31,    10,    42,    43,    44,
      21,    12
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
       -41,   -41,   -41,   -41,   -41,   108,   -41,   -25,   -41,   -41,
     -41,   -41,   -41,   -41,   -41,   -41,   163,   -41,   -41,   255,
     -41,   -41,   137
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  Parser::yydefgoto_[] =
  {
        -1,     5,    15,    18,    19,    20,    26,    37,    96,    53,
      54,    38,    51,    78,    39,    40,    41,    42,    43,    44,
       7,     8,     9
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -47;
  const signed char
  Parser::yytable_[] =
  {
        56,    57,    58,    59,    60,    61,    62,    63,    56,    57,
      58,    59,    60,    61,    62,    63,    71,    72,    56,    57,
      11,    12,   -47,   -47,    62,    63,    77,    13,    79,    80,
      81,    64,    65,    68,    69,    66,    67,    68,    69,    64,
      65,    14,    16,    66,    67,    68,    69,    71,    72,    17,
      70,    71,    72,    66,    67,    68,    69,    22,    75,    71,
      72,    56,    57,    58,    59,    60,    61,    62,    63,    71,
      72,   101,    23,    56,    57,    58,    59,    60,    61,    62,
      63,    25,    24,    56,    57,   -46,    59,    60,    61,    62,
      63,    52,    64,    65,    55,    74,    66,    67,    68,    69,
      66,    67,    68,    69,    64,    65,    73,    76,    66,    67,
      68,    69,    71,    72,    64,    65,    71,    72,    66,    67,
      68,    69,    56,    57,    71,    72,    60,    61,    62,    63,
     100,    27,    56,    57,    71,    72,    60,    61,    62,    63,
      56,    57,    10,     0,    60,    61,    62,    63,     1,     2,
       3,     4,     0,    64,    65,     0,     0,    66,    67,    68,
      69,     0,     0,     0,    65,    56,    57,    66,    67,    68,
      69,   -47,   -47,    71,    72,    66,    67,    68,    69,     0,
       0,     0,     0,    71,    72,     0,     0,     0,    28,    29,
       0,    71,    72,    46,    47,    48,    49,    50,     0,     0,
      66,    67,    68,    69,    31,    32,     0,     0,     0,    33,
       0,     0,     0,    34,     0,     0,    71,    72,     0,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,     0,    97,    98,    99,    28,    29,     0,
       1,     2,     3,     4,    30,     0,     0,     0,    28,    29,
       0,     0,     0,    31,    32,     6,     0,     0,    33,     0,
       6,     0,    34,     0,    31,    32,    35,     0,    36,    33,
       0,     0,    21,    34,     0,     0,     0,     0,    21,    45
  };

  /* YYCHECK.  */
  const signed char
  Parser::yycheck_[] =
  {
         5,     6,     7,     8,     9,    10,    11,    12,     5,     6,
       7,     8,     9,    10,    11,    12,    56,    57,     5,     6,
      23,    48,     9,    10,    11,    12,    51,     0,    53,    54,
      55,    36,    37,    42,    43,    40,    41,    42,    43,    36,
      37,     0,    58,    40,    41,    42,    43,    56,    57,    49,
      55,    56,    57,    40,    41,    42,    43,    51,    55,    56,
      57,     5,     6,     7,     8,     9,    10,    11,    12,    56,
      57,    96,    52,     5,     6,     7,     8,     9,    10,    11,
      12,    53,    25,     5,     6,    35,     8,     9,    10,    11,
      12,    54,    36,    37,    55,    25,    40,    41,    42,    43,
      40,    41,    42,    43,    36,    37,    35,    51,    40,    41,
      42,    43,    56,    57,    36,    37,    56,    57,    40,    41,
      42,    43,     5,     6,    56,    57,     9,    10,    11,    12,
      54,    23,     5,     6,    56,    57,     9,    10,    11,    12,
       5,     6,     5,    -1,     9,    10,    11,    12,    27,    28,
      29,    30,    -1,    36,    37,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    -1,    37,     5,     6,    40,    41,    42,
      43,    11,    12,    56,    57,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    56,    57,    -1,    -1,    -1,    24,    25,
      -1,    56,    57,    30,    31,    32,    33,    34,    -1,    -1,
      40,    41,    42,    43,    40,    41,    -1,    -1,    -1,    45,
      -1,    -1,    -1,    49,    -1,    -1,    56,    57,    -1,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    -1,    71,    72,    73,    24,    25,    -1,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    24,    25,
      -1,    -1,    -1,    40,    41,     0,    -1,    -1,    45,    -1,
       5,    -1,    49,    -1,    40,    41,    53,    -1,    55,    45,
      -1,    -1,    17,    49,    -1,    -1,    -1,    -1,    23,    55
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    27,    28,    29,    30,    60,    78,    79,    80,    81,
      81,    23,    48,     0,     0,    61,    58,    49,    62,    63,
      64,    78,    51,    52,    25,    53,    65,    64,    24,    25,
      31,    40,    41,    45,    49,    53,    55,    66,    70,    73,
      74,    75,    76,    77,    78,    55,    75,    75,    75,    75,
      75,    71,    54,    68,    69,    55,     5,     6,     7,     8,
       9,    10,    11,    12,    36,    37,    40,    41,    42,    43,
      55,    56,    57,    35,    25,    55,    51,    66,    72,    66,
      66,    66,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    67,    75,    75,    75,
      54,    66
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
     285,   286,   287,   288,   289,    61,   124,    38,    60,    62,
      45,    43,    42,    47,    37,    33,   290,    46,    91,    40,
     291,    41,    44,   123,   125,    59,   292,   293,    93
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    59,    61,    60,    62,    62,    63,    63,    64,    65,
      66,    67,    66,    68,    66,    69,    66,    66,    66,    71,
      70,    72,    73,    73,    74,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    76,    77,    77,    77,
      78,    78,    78,    79,    80,    80,    80,    81,    81
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     0,     7,     0,     1,     3,     1,     2,     3,
       0,     0,     4,     0,     3,     0,     3,     3,     1,     0,
       3,     2,     2,     3,     2,     2,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     0,     3
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
  "\"string\"", "\"return\"", "\"if\"", "\"else\"", "\"ifelse\"", "'='",
  "'|'", "'&'", "'<'", "'>'", "'-'", "'+'", "'*'", "'/'", "'%'", "'!'",
  "UNARY", "'.'", "'['", "'('", "PRE", "')'", "','", "'{'", "'}'", "';'",
  "\">\"", "\"<\"", "']'", "$accept", "function", "$@1",
  "function_arguments", "function_arguments_required", "function_argument",
  "function_statement", "statements", "$@2", "$@3", "$@4", "scope", "$@5",
  "scope_end", "return_statement", "variable_declare", "expression",
  "left", "right", "type", "type_complex", "type_primary", "start", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        81,     0,    -1,    -1,    78,    23,    61,    49,    62,    51,
      65,    -1,    -1,    63,    -1,    63,    52,    64,    -1,    64,
      -1,    78,    25,    -1,    53,    66,    54,    -1,    -1,    -1,
      75,    55,    67,    66,    -1,    -1,    70,    68,    66,    -1,
      -1,    73,    69,    66,    -1,    74,    55,    66,    -1,    55,
      -1,    -1,    53,    71,    72,    -1,    66,    54,    -1,    31,
      55,    -1,    31,    75,    55,    -1,    78,    25,    -1,    40,
      75,    -1,    41,    75,    -1,    45,    75,    -1,    75,    41,
      75,    -1,    75,    40,    75,    -1,    75,    42,    75,    -1,
      75,    43,    75,    -1,    75,     5,    75,    -1,    75,     6,
      75,    -1,    75,    36,    75,    -1,    75,     7,    75,    -1,
      75,    37,    75,    -1,    75,     8,    75,    -1,    75,     9,
      75,    -1,    75,    10,    75,    -1,    75,    11,    75,    -1,
      75,    12,    75,    -1,    75,    56,    75,    -1,    75,    57,
      75,    -1,    76,    35,    75,    -1,    77,    -1,    25,    -1,
      25,    -1,    24,    -1,    49,    75,    51,    -1,    79,    -1,
      80,    -1,    27,    -1,    80,    48,    58,    -1,    28,    -1,
      29,    -1,    30,    -1,    -1,    60,    81,     0,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned char
  Parser::yyprhs_[] =
  {
         0,     0,     3,     4,    12,    13,    15,    19,    21,    24,
      28,    29,    30,    35,    36,    40,    41,    45,    49,    51,
      52,    56,    59,    62,    66,    69,    72,    75,    78,    82,
      86,    90,    94,    98,   102,   106,   110,   114,   118,   122,
     126,   130,   134,   138,   142,   146,   148,   150,   152,   154,
     158,   160,   162,   164,   168,   170,   172,   174,   175
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   154,   154,   154,   160,   162,   166,   167,   171,   175,
     181,   183,   183,   184,   184,   185,   185,   187,   188,   192,
     192,   197,   201,   202,   214,   218,   219,   220,   223,   224,
     225,   226,   227,   228,   230,   231,   232,   233,   235,   236,
     237,   238,   239,   240,   242,   243,   247,   251,   252,   253,
     261,   262,   263,   267,   271,   272,   273,   277,   279
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
       2,     2,     2,    45,     2,     2,     2,    44,    37,     2,
      49,    51,    42,    41,    52,    40,    47,    43,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    55,
      38,    35,    39,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    48,     2,    58,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    53,    36,    54,     2,     2,     2,     2,
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
      46,    50,    56,    57
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 279;
  const int Parser::yynnts_ = 23;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 13;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 59;

  const unsigned int Parser::yyuser_token_number_max_ = 293;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


/* Line 1054 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

} } // kiwi::lang

/* Line 1054 of lalr1.cc  */
#line 1356 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.cpp"


/* Line 1056 of lalr1.cc  */
#line 284 "/home/alurin/workplace/project/kiwi/source/kiwi-core/lang/parser.yy"
 /*** Additional Code ***/

void kiwi::lang::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}

