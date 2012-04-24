
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
#line 154 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"


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
#line 145 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 257 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 25: /* "\"string constant\"" */

/* Line 480 of lalr1.cc  */
#line 149 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->ustringVal); };

/* Line 480 of lalr1.cc  */
#line 266 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 29: /* "\"local variable\"" */

/* Line 480 of lalr1.cc  */
#line 145 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 275 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 30: /* "\"instance attribute\"" */

/* Line 480 of lalr1.cc  */
#line 145 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 284 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 70: /* "field" */

/* Line 480 of lalr1.cc  */
#line 150 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->membernode); };

/* Line 480 of lalr1.cc  */
#line 293 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 71: /* "function" */

/* Line 480 of lalr1.cc  */
#line 150 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->membernode); };

/* Line 480 of lalr1.cc  */
#line 302 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 79: /* "statement" */

/* Line 480 of lalr1.cc  */
#line 148 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 311 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 80: /* "scope" */

/* Line 480 of lalr1.cc  */
#line 148 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 320 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 82: /* "scope_end" */

/* Line 480 of lalr1.cc  */
#line 148 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 329 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 83: /* "return_statement" */

/* Line 480 of lalr1.cc  */
#line 148 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 338 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 84: /* "print_statement" */

/* Line 480 of lalr1.cc  */
#line 148 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 347 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 85: /* "conditional_statement" */

/* Line 480 of lalr1.cc  */
#line 148 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 356 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 92: /* "expression" */

/* Line 480 of lalr1.cc  */
#line 146 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->rightnode); };

/* Line 480 of lalr1.cc  */
#line 365 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 97: /* "right" */

/* Line 480 of lalr1.cc  */
#line 146 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->rightnode); };

/* Line 480 of lalr1.cc  */
#line 374 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 103: /* "class_element" */

/* Line 480 of lalr1.cc  */
#line 150 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->membernode); };

/* Line 480 of lalr1.cc  */
#line 383 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 104: /* "type" */

/* Line 480 of lalr1.cc  */
#line 147 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->typenode); };

/* Line 480 of lalr1.cc  */
#line 392 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 105: /* "type_complex" */

/* Line 480 of lalr1.cc  */
#line 147 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->typenode); };

/* Line 480 of lalr1.cc  */
#line 401 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 106: /* "type_primary" */

/* Line 480 of lalr1.cc  */
#line 147 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->typenode); };

/* Line 480 of lalr1.cc  */
#line 410 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 108: /* "qualified_identifier" */

/* Line 480 of lalr1.cc  */
#line 149 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 419 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
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
    driver.prepareScript(yylloc);
}

/* Line 553 of lalr1.cc  */
#line 506 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"

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
#line 178 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.membernode) = driver.field(*(yysemantic_stack_[(3) - (2)].stringVal), (yysemantic_stack_[(3) - (1)].typenode)); yyfree((yysemantic_stack_[(3) - (2)].stringVal)); }
    break;

  case 3:

/* Line 678 of lalr1.cc  */
#line 185 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.func(*(yysemantic_stack_[(2) - (2)].stringVal), (yysemantic_stack_[(2) - (1)].typenode)); yyfree((yysemantic_stack_[(2) - (2)].stringVal)); }
    break;

  case 4:

/* Line 678 of lalr1.cc  */
#line 187 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.membernode) = driver.funcEnd();            }
    break;

  case 9:

/* Line 678 of lalr1.cc  */
#line 201 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.func()->declare(*(yysemantic_stack_[(2) - (2)].stringVal), (yysemantic_stack_[(2) - (1)].typenode)); }
    break;

  case 12:

/* Line 678 of lalr1.cc  */
#line 213 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.scope()->append((yysemantic_stack_[(1) - (1)].stmtnode)); (yysemantic_stack_[(1) - (1)].stmtnode) = 0; }
    break;

  case 15:

/* Line 678 of lalr1.cc  */
#line 219 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createExpr((yysemantic_stack_[(2) - (1)].rightnode));       }
    break;

  case 20:

/* Line 678 of lalr1.cc  */
#line 224 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = 0; }
    break;

  case 21:

/* Line 678 of lalr1.cc  */
#line 228 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.scopeBegin();              }
    break;

  case 22:

/* Line 678 of lalr1.cc  */
#line 229 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = (yysemantic_stack_[(3) - (3)].stmtnode);                          }
    break;

  case 23:

/* Line 678 of lalr1.cc  */
#line 233 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.scopeEnd();           }
    break;

  case 24:

/* Line 678 of lalr1.cc  */
#line 237 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createReturn((yylocation_stack_[(1) - (1)]));     }
    break;

  case 25:

/* Line 678 of lalr1.cc  */
#line 238 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createReturn((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)])); }
    break;

  case 26:

/* Line 678 of lalr1.cc  */
#line 242 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createPrint((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)]));  }
    break;

  case 27:

/* Line 678 of lalr1.cc  */
#line 248 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createCond((yysemantic_stack_[(5) - (3)].rightnode), (yysemantic_stack_[(5) - (5)].stmtnode), 0,  (yylocation_stack_[(5) - (1)])); }
    break;

  case 28:

/* Line 678 of lalr1.cc  */
#line 249 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createCond((yysemantic_stack_[(7) - (3)].rightnode), (yysemantic_stack_[(7) - (5)].stmtnode), (yysemantic_stack_[(7) - (7)].stmtnode), (yylocation_stack_[(7) - (1)])); }
    break;

  case 33:

/* Line 678 of lalr1.cc  */
#line 266 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.call()->append(*(yysemantic_stack_[(3) - (1)].stringVal), (yysemantic_stack_[(3) - (3)].rightnode)); yyfree((yysemantic_stack_[(3) - (1)].stringVal)); (yysemantic_stack_[(3) - (3)].rightnode) = 0; }
    break;

  case 34:

/* Line 678 of lalr1.cc  */
#line 267 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.call()->append((yysemantic_stack_[(1) - (1)].rightnode)); (yysemantic_stack_[(1) - (1)].rightnode) = 0;          }
    break;

  case 35:

/* Line 678 of lalr1.cc  */
#line 271 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.sub()->append((yysemantic_stack_[(1) - (1)].rightnode)); (yysemantic_stack_[(1) - (1)].rightnode) = 0; }
    break;

  case 37:

/* Line 678 of lalr1.cc  */
#line 273 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.sub()->append((yysemantic_stack_[(1) - (1)].rightnode)); (yysemantic_stack_[(1) - (1)].rightnode) = 0; }
    break;

  case 38:

/* Line 678 of lalr1.cc  */
#line 281 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.scope()->declare(*(yysemantic_stack_[(2) - (2)].stringVal), (yysemantic_stack_[(2) - (1)].typenode));     yyfree((yysemantic_stack_[(2) - (2)].stringVal)); }
    break;

  case 39:

/* Line 678 of lalr1.cc  */
#line 282 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.scope()->declare(*(yysemantic_stack_[(4) - (2)].stringVal), (yysemantic_stack_[(4) - (1)].typenode), (yysemantic_stack_[(4) - (4)].rightnode)); yyfree((yysemantic_stack_[(4) - (2)].stringVal)); }
    break;

  case 40:

/* Line 678 of lalr1.cc  */
#line 283 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.scope()->declare(*(yysemantic_stack_[(4) - (2)].stringVal), (yysemantic_stack_[(4) - (4)].rightnode));     yyfree((yysemantic_stack_[(4) - (2)].stringVal)); }
    break;

  case 41:

/* Line 678 of lalr1.cc  */
#line 287 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createNeg((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)])); }
    break;

  case 42:

/* Line 678 of lalr1.cc  */
#line 288 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createPos((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)])); }
    break;

  case 43:

/* Line 678 of lalr1.cc  */
#line 289 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createNot((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)])); }
    break;

  case 44:

/* Line 678 of lalr1.cc  */
#line 292 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createAdd((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 45:

/* Line 678 of lalr1.cc  */
#line 293 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createSub((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 46:

/* Line 678 of lalr1.cc  */
#line 294 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createMul((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 47:

/* Line 678 of lalr1.cc  */
#line 295 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createDiv((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 48:

/* Line 678 of lalr1.cc  */
#line 296 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createLsh((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 49:

/* Line 678 of lalr1.cc  */
#line 297 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createRsh((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 50:

/* Line 678 of lalr1.cc  */
#line 299 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createOr ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), false, (yylocation_stack_[(3) - (2)])); }
    break;

  case 51:

/* Line 678 of lalr1.cc  */
#line 300 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createOr ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), true,  (yylocation_stack_[(3) - (2)])); }
    break;

  case 52:

/* Line 678 of lalr1.cc  */
#line 301 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createAnd((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), false, (yylocation_stack_[(3) - (2)])); }
    break;

  case 53:

/* Line 678 of lalr1.cc  */
#line 302 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createAnd((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), true,  (yylocation_stack_[(3) - (2)])); }
    break;

  case 54:

/* Line 678 of lalr1.cc  */
#line 304 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createEq ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 55:

/* Line 678 of lalr1.cc  */
#line 305 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createNeq((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 56:

/* Line 678 of lalr1.cc  */
#line 306 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createGe ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 57:

/* Line 678 of lalr1.cc  */
#line 307 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createLe ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 58:

/* Line 678 of lalr1.cc  */
#line 308 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createGt ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 59:

/* Line 678 of lalr1.cc  */
#line 309 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createLt ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 60:

/* Line 678 of lalr1.cc  */
#line 311 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.subBegin((yysemantic_stack_[(1) - (1)].rightnode));               }
    break;

  case 61:

/* Line 678 of lalr1.cc  */
#line 312 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.subEnd((yylocation_stack_[(5) - (3)]) + (yylocation_stack_[(5) - (5)]));       }
    break;

  case 62:

/* Line 678 of lalr1.cc  */
#line 314 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.call(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal));  }
    break;

  case 63:

/* Line 678 of lalr1.cc  */
#line 315 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.callEnd();             }
    break;

  case 64:

/* Line 678 of lalr1.cc  */
#line 317 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.call((yysemantic_stack_[(3) - (1)].rightnode), *(yysemantic_stack_[(3) - (3)].stringVal), (yylocation_stack_[(3) - (1)]) + (yylocation_stack_[(3) - (3)])); yyfree((yysemantic_stack_[(3) - (3)].stringVal)); }
    break;

  case 65:

/* Line 678 of lalr1.cc  */
#line 318 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.callEnd();                     }
    break;

  case 66:

/* Line 678 of lalr1.cc  */
#line 320 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createAssign((yysemantic_stack_[(3) - (1)].leftnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 68:

/* Line 678 of lalr1.cc  */
#line 325 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.leftnode) = driver.left(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal));          }
    break;

  case 69:

/* Line 678 of lalr1.cc  */
#line 326 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.leftnode) = driver.instanceLeft(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal));  }
    break;

  case 70:

/* Line 678 of lalr1.cc  */
#line 330 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.right(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal));         }
    break;

  case 71:

/* Line 678 of lalr1.cc  */
#line 331 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.instanceRight(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal)); }
    break;

  case 72:

/* Line 678 of lalr1.cc  */
#line 332 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createInt((yysemantic_stack_[(1) - (1)].integerVal), (yylocation_stack_[(1) - (1)]));                  }
    break;

  case 73:

/* Line 678 of lalr1.cc  */
#line 333 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createString(*(yysemantic_stack_[(1) - (1)].ustringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].ustringVal));  }
    break;

  case 74:

/* Line 678 of lalr1.cc  */
#line 334 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createBool(true, (yylocation_stack_[(1) - (1)]));               }
    break;

  case 75:

/* Line 678 of lalr1.cc  */
#line 335 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createBool(false, (yylocation_stack_[(1) - (1)]));              }
    break;

  case 76:

/* Line 678 of lalr1.cc  */
#line 336 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createChar((yysemantic_stack_[(1) - (1)].charVal), (yylocation_stack_[(1) - (1)]));                 }
    break;

  case 77:

/* Line 678 of lalr1.cc  */
#line 337 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createThis((yylocation_stack_[(1) - (1)]));                     }
    break;

  case 78:

/* Line 678 of lalr1.cc  */
#line 338 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = (yysemantic_stack_[(3) - (2)].rightnode);                                        }
    break;

  case 79:

/* Line 678 of lalr1.cc  */
#line 345 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.classBegin(*(yysemantic_stack_[(2) - (2)].stringVal), (yylocation_stack_[(2) - (2)])); yyfree((yysemantic_stack_[(2) - (2)].stringVal));   }
    break;

  case 80:

/* Line 678 of lalr1.cc  */
#line 346 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.classEnd();                        }
    break;

  case 82:

/* Line 678 of lalr1.cc  */
#line 351 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.classTop()->append((yysemantic_stack_[(1) - (1)].membernode)); (yysemantic_stack_[(1) - (1)].membernode) = 0;    }
    break;

  case 85:

/* Line 678 of lalr1.cc  */
#line 358 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.classTop()->inherit(*(yysemantic_stack_[(3) - (2)].stringVal));   yyfree((yysemantic_stack_[(3) - (2)].stringVal)); }
    break;

  case 86:

/* Line 678 of lalr1.cc  */
#line 359 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.classTop()->implement(*(yysemantic_stack_[(3) - (2)].stringVal)); yyfree((yysemantic_stack_[(3) - (2)].stringVal)); }
    break;

  case 91:

/* Line 678 of lalr1.cc  */
#line 373 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createVoidTy((yylocation_stack_[(1) - (1)]));    }
    break;

  case 92:

/* Line 678 of lalr1.cc  */
#line 377 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createArrayTy((yysemantic_stack_[(3) - (1)].typenode), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)])); }
    break;

  case 93:

/* Line 678 of lalr1.cc  */
#line 381 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createIntTy((yylocation_stack_[(1) - (1)]));    }
    break;

  case 94:

/* Line 678 of lalr1.cc  */
#line 382 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createBoolTy((yylocation_stack_[(1) - (1)]));   }
    break;

  case 95:

/* Line 678 of lalr1.cc  */
#line 383 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createStringTy((yylocation_stack_[(1) - (1)])); }
    break;

  case 96:

/* Line 678 of lalr1.cc  */
#line 384 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createCharTy((yylocation_stack_[(1) - (1)]));   }
    break;

  case 97:

/* Line 678 of lalr1.cc  */
#line 385 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createQualifiedTy(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal)); }
    break;

  case 99:

/* Line 678 of lalr1.cc  */
#line 390 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.classTop()->append((yysemantic_stack_[(1) - (1)].membernode)); (yysemantic_stack_[(1) - (1)].membernode) = 0; }
    break;



/* Line 678 of lalr1.cc  */
#line 1129 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
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
  const short int Parser::yypact_ninf_ = -147;
  const short int
  Parser::yypact_[] =
  {
       158,  -147,  -147,  -147,  -147,  -147,  -147,    -4,  -147,  -147,
    -147,  -147,    30,  -147,   -37,   158,  -147,    35,  -147,  -147,
      -8,    -7,    62,  -147,    -2,     5,  -147,  -147,  -147,   -21,
     225,    44,    59,    17,   -21,  -147,    22,  -147,    31,    57,
      34,    36,  -147,  -147,   -21,    37,   225,  -147,  -147,  -147,
    -147,   306,  -147,  -147,    40,  -147,  -147,  -147,  -147,  -147,
      55,    58,    76,  -147,   392,    46,   392,   392,   392,   392,
     392,  -147,  -147,    60,  -147,  -147,    63,    65,  -147,    66,
     135,    91,    80,   119,    89,   121,  -147,   193,   392,   193,
    -147,  -147,  -147,   103,   306,  -147,   306,  -147,  -147,  -147,
     392,   392,   392,   392,   392,   392,   392,   392,   392,   392,
     392,   392,   392,   392,   392,   392,  -147,   109,   392,   146,
     124,   410,   392,   111,  -147,   107,  -147,  -147,    25,    25,
      82,   166,   224,   224,   274,   274,   216,   244,   274,   274,
       3,     3,  -147,  -147,   392,   193,  -147,   392,   112,   117,
    -147,   132,   193,   193,   349,  -147,   138,    21,   147,   193,
     392,  -147,   410,   165,  -147,   145,   410,   193,  -147,   349,
     392,   148,  -147,  -147,  -147
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
       101,   100,    91,    93,    94,    96,    95,     0,    88,    87,
      98,    99,     0,    89,    90,   101,    97,     0,    79,     3,
       0,     0,     0,     1,     0,     0,     2,    92,   102,    81,
       5,     0,     0,     0,    81,    82,     0,     6,     8,     0,
       0,     0,    80,    84,    81,     0,     0,     9,    85,    86,
      83,    11,     4,     7,   100,    72,    73,    76,    74,    75,
      70,    71,     0,    77,    24,     0,     0,     0,     0,     0,
       0,    14,    21,     0,    12,    16,     0,     0,    17,     0,
      60,     0,    67,     0,     0,     0,    62,    25,     0,    26,
      41,    42,    43,    60,    11,    10,    11,    18,    19,    20,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    15,     0,     0,     0,
      38,    29,     0,    60,    78,     0,    22,    13,    48,    49,
      51,    53,    54,    55,    56,    57,    50,    52,    59,    58,
      45,    44,    46,    47,     0,    66,    64,     0,    62,     0,
      30,    32,    34,    40,     0,    23,     0,    35,     0,    39,
       0,    63,     0,    27,    61,     0,    29,    33,    31,     0,
       0,     0,    28,    36,    65
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -147,  -147,  -147,  -147,  -147,   164,  -147,  -147,   -60,  -147,
    -146,  -147,  -147,  -147,  -147,  -147,  -147,    71,    50,  -147,
      53,  -147,  -147,   -63,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,   -24,  -147,  -147,     9,   -30,  -147,  -147,  -147,  -147,
     209
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     8,     9,    25,    36,    37,    38,    52,    73,    96,
      74,    75,    94,   126,    76,    77,    78,   149,   150,   151,
     156,   165,    79,    80,   117,    84,   158,    81,    82,    10,
      24,    33,    44,    34,    35,    12,    13,    14,    15,    16,
      17
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -70;
  const short int
  Parser::yytable_[] =
  {
        39,    87,     1,    89,    90,    91,    92,    93,   163,    11,
      43,     2,     3,     4,     5,     6,    39,    31,    32,    18,
      50,    83,    21,   172,    11,   123,   100,   101,   102,   103,
     104,   105,   106,   107,   125,    23,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,    19,    26,   145,   114,   115,   152,   153,
      20,    27,    28,    29,    83,    30,    83,    40,   108,   109,
     110,   111,   112,   113,   114,   115,   112,   113,   114,   115,
     -60,   157,    41,    42,   159,    45,    47,   100,   101,   -37,
     103,   104,   105,   106,   107,    46,    48,   167,    49,   152,
     -62,   -68,    51,   152,   -69,    85,    88,   157,   100,   101,
     102,   103,   104,   105,   106,   107,   100,   101,   102,   103,
     104,   105,   106,   107,    83,    97,    95,    98,    99,   108,
     109,   110,   111,   112,   113,   114,   115,   118,   119,    83,
     100,   101,   102,   103,   104,   105,   106,   107,   120,   121,
     108,   109,   110,   111,   112,   113,   114,   115,   108,   109,
     110,   111,   112,   113,   114,   115,   124,   122,   144,   146,
     147,   100,   101,   155,   154,   104,   105,   106,   107,   160,
     161,     1,   108,   109,   110,   111,   112,   113,   114,   115,
       2,     3,     4,     5,     6,     7,   162,   116,   100,   101,
     102,   103,   104,   105,   106,   107,   164,   166,   169,   170,
      53,   174,   168,   108,   109,   110,   111,   112,   113,   114,
     115,   100,   101,   173,    22,   104,   105,   106,   107,   100,
     101,     0,     0,   -70,   -70,   106,   107,   171,     0,     0,
     108,   109,   110,   111,   112,   113,   114,   115,     1,   100,
     101,     0,   -60,   104,   105,   106,   107,     2,     3,     4,
       5,     6,     0,     0,   109,   110,   111,   112,   113,   114,
     115,     0,     0,   110,   111,   112,   113,   114,   115,   100,
     101,     0,     0,     0,     0,   -70,   -70,     0,     0,     0,
       0,     0,     0,   110,   111,   112,   113,   114,   115,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -70,   -70,   112,   113,   114,   115,    54,
      55,    56,    57,    58,    59,    60,    61,    62,     2,     3,
       4,     5,     6,     0,     0,     0,    63,    64,    65,     0,
       0,    66,     0,     0,     0,     0,     0,    67,    68,     0,
       0,     0,    69,     0,     0,     0,    70,     0,    71,     0,
       0,    72,    54,    55,    56,    57,    58,    59,    60,    61,
      62,     2,     3,     4,     5,     6,     0,     0,     0,    63,
      64,    65,     0,     0,    66,     0,     0,     0,     0,     0,
      67,    68,     0,     0,     0,    69,     0,     0,     0,    70,
       0,     0,     0,     0,    72,    86,    55,    56,    57,    58,
      59,    60,    61,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    63,   148,    55,    56,    57,    58,    59,    60,
      61,     0,     0,    67,    68,     0,     0,     0,    69,     0,
      63,     0,    70,     0,     0,     0,     0,     0,     0,     0,
       0,    67,    68,     0,     0,     0,    69,     0,     0,     0,
      70
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
        30,    64,    23,    66,    67,    68,    69,    70,   154,     0,
      34,    32,    33,    34,    35,    36,    46,    38,    39,    23,
      44,    51,    59,   169,    15,    88,     5,     6,     7,     8,
       9,    10,    11,    12,    94,     0,    96,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,    23,    62,   118,    53,    54,   121,   122,
      30,    68,     0,    65,    94,    60,    96,    23,    47,    48,
      49,    50,    51,    52,    53,    54,    51,    52,    53,    54,
      59,   144,    23,    66,   147,    63,    29,     5,     6,    68,
       8,     9,    10,    11,    12,    64,    62,   160,    62,   162,
      60,    46,    65,   166,    46,    29,    60,   170,     5,     6,
       7,     8,     9,    10,    11,    12,     5,     6,     7,     8,
       9,    10,    11,    12,   154,    62,    66,    62,    62,    47,
      48,    49,    50,    51,    52,    53,    54,    46,    58,   169,
       5,     6,     7,     8,     9,    10,    11,    12,    29,    60,
      47,    48,    49,    50,    51,    52,    53,    54,    47,    48,
      49,    50,    51,    52,    53,    54,    63,    46,    59,    23,
      46,     5,     6,    66,    63,     9,    10,    11,    12,    67,
      63,    23,    47,    48,    49,    50,    51,    52,    53,    54,
      32,    33,    34,    35,    36,    37,    64,    62,     5,     6,
       7,     8,     9,    10,    11,    12,    68,    60,    43,    64,
      46,    63,   162,    47,    48,    49,    50,    51,    52,    53,
      54,     5,     6,   170,    15,     9,    10,    11,    12,     5,
       6,    -1,    -1,     9,    10,    11,    12,   166,    -1,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    23,     5,
       6,    -1,    59,     9,    10,    11,    12,    32,    33,    34,
      35,    36,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    -1,    -1,    49,    50,    51,    52,    53,    54,     5,
       6,    -1,    -1,    -1,    -1,    11,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    50,    51,    52,    53,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    50,    51,    52,    53,    54,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    40,    41,    42,    -1,
      -1,    45,    -1,    -1,    -1,    -1,    -1,    51,    52,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    60,    -1,    62,    -1,
      -1,    65,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    -1,    40,
      41,    42,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,
      51,    52,    -1,    -1,    -1,    56,    -1,    -1,    -1,    60,
      -1,    -1,    -1,    -1,    65,    23,    24,    25,    26,    27,
      28,    29,    30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    23,    24,    25,    26,    27,    28,    29,
      30,    -1,    -1,    51,    52,    -1,    -1,    -1,    56,    -1,
      40,    -1,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    52,    -1,    -1,    -1,    56,    -1,    -1,    -1,
      60
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    23,    32,    33,    34,    35,    36,    37,    70,    71,
      98,   103,   104,   105,   106,   107,   108,   109,    23,    23,
      30,    59,   109,     0,    99,    72,    62,    68,     0,    65,
      60,    38,    39,   100,   102,   103,    73,    74,    75,   104,
      23,    23,    66,   100,   101,    63,    64,    29,    62,    62,
     100,    65,    76,    74,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    40,    41,    42,    45,    51,    52,    56,
      60,    62,    65,    77,    79,    80,    83,    84,    85,    91,
      92,    96,    97,   104,    94,    29,    23,    92,    60,    92,
      92,    92,    92,    92,    81,    66,    78,    62,    62,    62,
       5,     6,     7,     8,     9,    10,    11,    12,    47,    48,
      49,    50,    51,    52,    53,    54,    62,    93,    46,    58,
      29,    60,    46,    92,    63,    77,    82,    77,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    59,    92,    23,    46,    23,    86,
      87,    88,    92,    92,    63,    66,    89,    92,    95,    92,
      67,    63,    64,    79,    68,    90,    60,    92,    87,    43,
      64,    86,    79,    89,    63
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
     295,   296,   297,   298,   299,   300,    61,   124,    38,    60,
      62,    45,    43,    42,    47,    37,    33,   301,    46,    91,
      40,   302,    59,    41,    44,   123,   125,    58,    93
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    69,    70,    72,    71,    73,    73,    74,    74,    75,
      76,    77,    78,    77,    77,    79,    79,    79,    79,    79,
      79,    81,    80,    82,    83,    83,    84,    85,    85,    86,
      86,    87,    87,    88,    88,    90,    89,    89,    91,    91,
      91,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      93,    92,    94,    92,    95,    92,    92,    92,    96,    96,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    99,
      98,   100,   101,   100,   100,   102,   102,   103,   103,   104,
     104,   104,   105,   106,   106,   106,   106,   106,   107,   107,
     108,   109,   109
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     3,     0,     7,     0,     1,     3,     1,     2,
       3,     0,     0,     3,     1,     2,     1,     1,     2,     2,
       2,     0,     3,     2,     1,     2,     2,     5,     7,     0,
       1,     3,     1,     3,     1,     0,     4,     1,     2,     4,
       4,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       0,     5,     0,     5,     0,     7,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       6,     0,     0,     3,     2,     3,     3,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     3
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
  "\"class\"", "\"inherit\"", "\"implement\"", "\"this\"", "\"return\"",
  "\"if\"", "\"else\"", "\"ifelse\"", "\"print\"", "'='", "'|'", "'&'",
  "'<'", "'>'", "'-'", "'+'", "'*'", "'/'", "'%'", "'!'", "UNARY", "'.'",
  "'['", "'('", "PRE", "';'", "')'", "','", "'{'", "'}'", "':'", "']'",
  "$accept", "field", "function", "$@1", "function_arguments",
  "function_arguments_required", "function_argument", "function_statement",
  "statements", "$@2", "statement", "scope", "$@3", "scope_end",
  "return_statement", "print_statement", "conditional_statement",
  "call_arguments", "call_arguments_required", "call_argument",
  "subtraction_args", "$@4", "variable_declare", "expression", "$@5",
  "$@6", "$@7", "left", "right", "class_definition", "$@8", "class_body",
  "$@9", "class_modificator", "class_element", "type", "type_complex",
  "type_primary", "script_elements", "qualified_identifier", "start", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
       109,     0,    -1,   104,    30,    62,    -1,    -1,   104,    23,
      72,    60,    73,    63,    76,    -1,    -1,    74,    -1,    75,
      64,    74,    -1,    75,    -1,   104,    29,    -1,    65,    77,
      66,    -1,    -1,    -1,    79,    78,    77,    -1,    62,    -1,
      92,    62,    -1,    80,    -1,    85,    -1,    83,    62,    -1,
      84,    62,    -1,    91,    62,    -1,    -1,    65,    81,    82,
      -1,    77,    66,    -1,    41,    -1,    41,    92,    -1,    45,
      92,    -1,    42,    60,    92,    63,    79,    -1,    42,    60,
      92,    63,    79,    43,    79,    -1,    -1,    87,    -1,    88,
      64,    87,    -1,    88,    -1,    23,    67,    92,    -1,    92,
      -1,    -1,    92,    90,    64,    89,    -1,    92,    -1,   104,
      29,    -1,   104,    29,    46,    92,    -1,    31,    29,    46,
      92,    -1,    51,    92,    -1,    52,    92,    -1,    56,    92,
      -1,    92,    52,    92,    -1,    92,    51,    92,    -1,    92,
      53,    92,    -1,    92,    54,    92,    -1,    92,     5,    92,
      -1,    92,     6,    92,    -1,    92,    47,    92,    -1,    92,
       7,    92,    -1,    92,    48,    92,    -1,    92,     8,    92,
      -1,    92,     9,    92,    -1,    92,    10,    92,    -1,    92,
      11,    92,    -1,    92,    12,    92,    -1,    92,    50,    92,
      -1,    92,    49,    92,    -1,    -1,    92,    93,    59,    89,
      68,    -1,    -1,    23,    94,    60,    86,    63,    -1,    -1,
      97,    58,    23,    95,    60,    86,    63,    -1,    96,    46,
      92,    -1,    97,    -1,    29,    -1,    30,    -1,    29,    -1,
      30,    -1,    24,    -1,    25,    -1,    27,    -1,    28,    -1,
      26,    -1,    40,    -1,    60,    92,    63,    -1,    -1,    37,
      23,    99,    65,   100,    66,    -1,    -1,    -1,   103,   101,
     100,    -1,   102,   100,    -1,    38,    23,    62,    -1,    39,
      23,    62,    -1,    71,    -1,    70,    -1,   105,    -1,   106,
      -1,    32,    -1,   106,    59,    68,    -1,    33,    -1,    34,
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
      87,    89,    93,    95,    99,   101,   102,   107,   109,   112,
     117,   122,   125,   128,   131,   135,   139,   143,   147,   151,
     155,   159,   163,   167,   171,   175,   179,   183,   187,   191,
     195,   196,   202,   203,   209,   210,   218,   222,   224,   226,
     228,   230,   232,   234,   236,   238,   240,   242,   244,   248,
     249,   256,   257,   258,   262,   265,   269,   273,   275,   277,
     279,   281,   283,   287,   289,   291,   293,   295,   297,   299,
     301,   303,   304
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   178,   178,   185,   185,   190,   192,   196,   197,   201,
     205,   211,   213,   213,   215,   219,   220,   221,   222,   223,
     224,   228,   228,   233,   237,   238,   242,   248,   249,   255,
     257,   261,   262,   266,   267,   271,   271,   273,   281,   282,
     283,   287,   288,   289,   292,   293,   294,   295,   296,   297,
     299,   300,   301,   302,   304,   305,   306,   307,   308,   309,
     311,   311,   314,   314,   317,   317,   320,   321,   325,   326,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   345,
     345,   349,   351,   351,   353,   358,   359,   363,   364,   371,
     372,   373,   377,   381,   382,   383,   384,   385,   389,   390,
     394,   398,   400
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
       2,     2,     2,    56,     2,     2,     2,    55,    48,     2,
      60,    63,    53,    52,    64,    51,    58,    54,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    67,    62,
      49,    46,    50,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    59,     2,    68,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    65,    47,    66,     2,     2,     2,     2,
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
      45,    57,    61
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 470;
  const int Parser::yynnts_ = 41;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 23;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 69;

  const unsigned int Parser::yyuser_token_number_max_ = 302;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


/* Line 1054 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

} } // kiwi::lang

/* Line 1054 of lalr1.cc  */
#line 1789 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"


/* Line 1056 of lalr1.cc  */
#line 405 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
 /*** Additional Code ***/

void kiwi::lang::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}

