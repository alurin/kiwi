/* A Bison parser, made by GNU Bison 2.5.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002-2011 Free Software Foundation, Inc.
   
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

/* Line 293 of lalr1.cc  */
#line 7 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
 /*** C/C++ Declarations ***/

#include "kiwi/config.hpp"
#include <stdio.h>
#include <string>
#include <vector>
#include "ExpressionNode.hpp"
#include "TypeNode.hpp"
#include "FunctionNode.hpp"



/* Line 293 of lalr1.cc  */
#line 54 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"


#include "parser.hpp"

/* User implementation prologue.  */

/* Line 299 of lalr1.cc  */
#line 162 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"


#include "Driver.hpp"
#include "scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

#define yyfree(__px1) delete __px1; __px1 = 0;



/* Line 299 of lalr1.cc  */
#line 79 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                               \
 do                                                                    \
   if (N)                                                              \
     {                                                                 \
       (Current).begin = YYRHSLOC (Rhs, 1).begin;                      \
       (Current).end   = YYRHSLOC (Rhs, N).end;                        \
     }                                                                 \
   else                                                                \
     {                                                                 \
       (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;        \
     }                                                                 \
 while (false)
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


namespace kiwi { namespace lang {

/* Line 382 of lalr1.cc  */
#line 165 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"

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
#line 152 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 270 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 25: /* "\"string constant\"" */

/* Line 480 of lalr1.cc  */
#line 157 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->ustringVal); };

/* Line 480 of lalr1.cc  */
#line 279 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 29: /* "\"local variable\"" */

/* Line 480 of lalr1.cc  */
#line 152 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 288 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 30: /* "\"instance attribute\"" */

/* Line 480 of lalr1.cc  */
#line 152 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 297 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 72: /* "field" */

/* Line 480 of lalr1.cc  */
#line 158 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->membernode); };

/* Line 480 of lalr1.cc  */
#line 306 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 73: /* "function" */

/* Line 480 of lalr1.cc  */
#line 158 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->membernode); };

/* Line 480 of lalr1.cc  */
#line 315 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 81: /* "statement" */

/* Line 480 of lalr1.cc  */
#line 155 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 324 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 82: /* "scope" */

/* Line 480 of lalr1.cc  */
#line 155 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 333 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 84: /* "scope_end" */

/* Line 480 of lalr1.cc  */
#line 155 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 342 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 85: /* "return_statement" */

/* Line 480 of lalr1.cc  */
#line 155 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 351 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 86: /* "print_statement" */

/* Line 480 of lalr1.cc  */
#line 155 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 360 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 87: /* "conditional_statement" */

/* Line 480 of lalr1.cc  */
#line 155 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 369 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 91: /* "variable_declare" */

/* Line 480 of lalr1.cc  */
#line 156 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stmtnode); };

/* Line 480 of lalr1.cc  */
#line 378 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 93: /* "call_inline" */

/* Line 480 of lalr1.cc  */
#line 153 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->rightnode); };

/* Line 480 of lalr1.cc  */
#line 387 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 94: /* "expression" */

/* Line 480 of lalr1.cc  */
#line 153 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->rightnode); };

/* Line 480 of lalr1.cc  */
#line 396 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 98: /* "right" */

/* Line 480 of lalr1.cc  */
#line 153 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->rightnode); };

/* Line 480 of lalr1.cc  */
#line 405 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 104: /* "class_element" */

/* Line 480 of lalr1.cc  */
#line 158 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->membernode); };

/* Line 480 of lalr1.cc  */
#line 414 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 105: /* "type" */

/* Line 480 of lalr1.cc  */
#line 154 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->typenode); };

/* Line 480 of lalr1.cc  */
#line 423 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 106: /* "type_complex" */

/* Line 480 of lalr1.cc  */
#line 154 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->typenode); };

/* Line 480 of lalr1.cc  */
#line 432 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 107: /* "type_primary" */

/* Line 480 of lalr1.cc  */
#line 154 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->typenode); };

/* Line 480 of lalr1.cc  */
#line 441 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	break;
      case 109: /* "qualified_identifier" */

/* Line 480 of lalr1.cc  */
#line 157 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
	{ delete (yyvaluep->stringVal); };

/* Line 480 of lalr1.cc  */
#line 450 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
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

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

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
    location_type yyerror_range[3];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* User initialization code.  */
    
/* Line 565 of lalr1.cc  */
#line 46 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
{
    // initialize the initial location object
    yylloc.begin.filename = yylloc.end.filename = &driver.streamname;
    driver.prepareScript(yylloc);
}

/* Line 565 of lalr1.cc  */
#line 549 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"

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
    if (yy_pact_value_is_default_ (yyn))
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
	if (yy_table_value_is_error_ (yyn))
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

/* Line 690 of lalr1.cc  */
#line 186 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.membernode) = driver.field(*(yysemantic_stack_[(3) - (2)].stringVal), (yysemantic_stack_[(3) - (1)].typenode)); yyfree((yysemantic_stack_[(3) - (2)].stringVal)); }
    break;

  case 3:

/* Line 690 of lalr1.cc  */
#line 193 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.func(*(yysemantic_stack_[(2) - (2)].stringVal), (yysemantic_stack_[(2) - (1)].typenode)); yyfree((yysemantic_stack_[(2) - (2)].stringVal)); }
    break;

  case 4:

/* Line 690 of lalr1.cc  */
#line 195 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.membernode) = driver.funcEnd();            }
    break;

  case 9:

/* Line 690 of lalr1.cc  */
#line 209 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.func()->declare(*(yysemantic_stack_[(2) - (2)].stringVal), (yysemantic_stack_[(2) - (1)].typenode), (yylocation_stack_[(2) - (2)])); }
    break;

  case 12:

/* Line 690 of lalr1.cc  */
#line 221 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.scope()->append((yysemantic_stack_[(1) - (1)].stmtnode)); (yysemantic_stack_[(1) - (1)].stmtnode) = 0; }
    break;

  case 15:

/* Line 690 of lalr1.cc  */
#line 227 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createExpr((yysemantic_stack_[(2) - (1)].rightnode));       }
    break;

  case 16:

/* Line 690 of lalr1.cc  */
#line 228 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createExpr((yysemantic_stack_[(2) - (1)].rightnode));       }
    break;

  case 22:

/* Line 690 of lalr1.cc  */
#line 237 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.scopeBegin((yylocation_stack_[(1) - (1)]));            }
    break;

  case 23:

/* Line 690 of lalr1.cc  */
#line 238 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = (yysemantic_stack_[(3) - (3)].stmtnode);                          }
    break;

  case 24:

/* Line 690 of lalr1.cc  */
#line 242 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.scopeEnd();         }
    break;

  case 25:

/* Line 690 of lalr1.cc  */
#line 246 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createReturn((yylocation_stack_[(1) - (1)]));     }
    break;

  case 26:

/* Line 690 of lalr1.cc  */
#line 247 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createReturn((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)])); }
    break;

  case 27:

/* Line 690 of lalr1.cc  */
#line 251 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createPrint((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)]));  }
    break;

  case 28:

/* Line 690 of lalr1.cc  */
#line 257 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createCond((yysemantic_stack_[(5) - (3)].rightnode), (yysemantic_stack_[(5) - (5)].stmtnode), 0,  (yylocation_stack_[(5) - (1)])); }
    break;

  case 29:

/* Line 690 of lalr1.cc  */
#line 258 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.stmtnode) = driver.createCond((yysemantic_stack_[(7) - (3)].rightnode), (yysemantic_stack_[(7) - (5)].stmtnode), (yysemantic_stack_[(7) - (7)].stmtnode), (yylocation_stack_[(7) - (1)])); }
    break;

  case 34:

/* Line 690 of lalr1.cc  */
#line 275 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.call()->append(*(yysemantic_stack_[(3) - (1)].stringVal), (yysemantic_stack_[(3) - (3)].rightnode)); yyfree((yysemantic_stack_[(3) - (1)].stringVal)); (yysemantic_stack_[(3) - (3)].rightnode) = 0; }
    break;

  case 35:

/* Line 690 of lalr1.cc  */
#line 276 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.call()->append((yysemantic_stack_[(1) - (1)].rightnode)); (yysemantic_stack_[(1) - (1)].rightnode) = 0; }
    break;

  case 36:

/* Line 690 of lalr1.cc  */
#line 284 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    {
                                                driver.scope()->declare(*(yysemantic_stack_[(2) - (2)].stringVal), (yysemantic_stack_[(2) - (1)].typenode), (yylocation_stack_[(2) - (2)]));
                                                (yyval.stmtnode) = 0;
                                                yyfree((yysemantic_stack_[(2) - (2)].stringVal));
                                            }
    break;

  case 37:

/* Line 690 of lalr1.cc  */
#line 289 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    {
                                                VariableNode* node = driver.scope()->declare(*(yysemantic_stack_[(4) - (2)].stringVal), (yysemantic_stack_[(4) - (1)].typenode), (yysemantic_stack_[(4) - (4)].rightnode), (yylocation_stack_[(4) - (2)]));
                                                (yyval.stmtnode) = driver.createInit(node, (yylocation_stack_[(4) - (3)]));
                                                yyfree((yysemantic_stack_[(4) - (2)].stringVal));
                                            }
    break;

  case 38:

/* Line 690 of lalr1.cc  */
#line 294 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    {
                                                VariableNode* node = driver.scope()->declare(*(yysemantic_stack_[(4) - (2)].stringVal), (yysemantic_stack_[(4) - (4)].rightnode), (yylocation_stack_[(4) - (2)]));
                                                (yyval.stmtnode) = driver.createInit(node, (yylocation_stack_[(4) - (3)]));
                                                yyfree((yysemantic_stack_[(4) - (2)].stringVal));
                                            }
    break;

  case 39:

/* Line 690 of lalr1.cc  */
#line 302 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.call(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal));  }
    break;

  case 40:

/* Line 690 of lalr1.cc  */
#line 303 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.call((yysemantic_stack_[(3) - (1)].rightnode), *(yysemantic_stack_[(3) - (3)].stringVal), (yylocation_stack_[(3) - (1)]) + (yylocation_stack_[(3) - (3)])); yyfree((yysemantic_stack_[(3) - (3)].stringVal)); }
    break;

  case 41:

/* Line 690 of lalr1.cc  */
#line 308 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.callEnd((yylocation_stack_[(2) - (1)])); }
    break;

  case 42:

/* Line 690 of lalr1.cc  */
#line 312 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createNeg((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)])); }
    break;

  case 43:

/* Line 690 of lalr1.cc  */
#line 313 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createPos((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)])); }
    break;

  case 44:

/* Line 690 of lalr1.cc  */
#line 314 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createNot((yysemantic_stack_[(2) - (2)].rightnode), (yylocation_stack_[(2) - (1)])); }
    break;

  case 45:

/* Line 690 of lalr1.cc  */
#line 316 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createAdd((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 46:

/* Line 690 of lalr1.cc  */
#line 317 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createSub((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 47:

/* Line 690 of lalr1.cc  */
#line 318 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createMul((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 48:

/* Line 690 of lalr1.cc  */
#line 319 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createDiv((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 49:

/* Line 690 of lalr1.cc  */
#line 320 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createLsh((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 50:

/* Line 690 of lalr1.cc  */
#line 321 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createRsh((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 51:

/* Line 690 of lalr1.cc  */
#line 323 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createOr ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), false, (yylocation_stack_[(3) - (2)])); }
    break;

  case 52:

/* Line 690 of lalr1.cc  */
#line 324 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createOr ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), true,  (yylocation_stack_[(3) - (2)])); }
    break;

  case 53:

/* Line 690 of lalr1.cc  */
#line 325 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createAnd((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), false, (yylocation_stack_[(3) - (2)])); }
    break;

  case 54:

/* Line 690 of lalr1.cc  */
#line 326 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createAnd((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), true,  (yylocation_stack_[(3) - (2)])); }
    break;

  case 55:

/* Line 690 of lalr1.cc  */
#line 328 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createEq ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 56:

/* Line 690 of lalr1.cc  */
#line 329 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createNeq((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 57:

/* Line 690 of lalr1.cc  */
#line 330 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createGe ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 58:

/* Line 690 of lalr1.cc  */
#line 331 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createLe ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 59:

/* Line 690 of lalr1.cc  */
#line 332 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createGt ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 60:

/* Line 690 of lalr1.cc  */
#line 333 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createLt ((yysemantic_stack_[(3) - (1)].rightnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 61:

/* Line 690 of lalr1.cc  */
#line 336 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.subBegin((yysemantic_stack_[(1) - (1)].rightnode), (yylocation_stack_[(1) - (1)]));           }
    break;

  case 62:

/* Line 690 of lalr1.cc  */
#line 337 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.callEnd((yylocation_stack_[(5) - (3)]) + (yylocation_stack_[(5) - (5)]));      }
    break;

  case 63:

/* Line 690 of lalr1.cc  */
#line 340 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.callEnd((yylocation_stack_[(4) - (1)]));           }
    break;

  case 64:

/* Line 690 of lalr1.cc  */
#line 342 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.newBegin((yysemantic_stack_[(2) - (2)].typenode), (yylocation_stack_[(2) - (1)]));              }
    break;

  case 65:

/* Line 690 of lalr1.cc  */
#line 343 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.callEnd((yylocation_stack_[(6) - (1)]) + (yylocation_stack_[(6) - (2)]));         }
    break;

  case 66:

/* Line 690 of lalr1.cc  */
#line 345 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createAssign((yysemantic_stack_[(3) - (1)].leftnode), (yysemantic_stack_[(3) - (3)].rightnode), (yylocation_stack_[(3) - (2)])); }
    break;

  case 68:

/* Line 690 of lalr1.cc  */
#line 350 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.leftnode) = driver.left(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal));          }
    break;

  case 69:

/* Line 690 of lalr1.cc  */
#line 351 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.leftnode) = driver.instanceLeft(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal));  }
    break;

  case 70:

/* Line 690 of lalr1.cc  */
#line 355 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.right(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal));         }
    break;

  case 71:

/* Line 690 of lalr1.cc  */
#line 356 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.instanceRight(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal)); }
    break;

  case 72:

/* Line 690 of lalr1.cc  */
#line 357 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createInt((yysemantic_stack_[(1) - (1)].integerVal), (yylocation_stack_[(1) - (1)]));                  }
    break;

  case 73:

/* Line 690 of lalr1.cc  */
#line 358 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createString(*(yysemantic_stack_[(1) - (1)].ustringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].ustringVal));  }
    break;

  case 74:

/* Line 690 of lalr1.cc  */
#line 359 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createBool(true, (yylocation_stack_[(1) - (1)]));               }
    break;

  case 75:

/* Line 690 of lalr1.cc  */
#line 360 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createBool(false, (yylocation_stack_[(1) - (1)]));              }
    break;

  case 76:

/* Line 690 of lalr1.cc  */
#line 361 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createChar((yysemantic_stack_[(1) - (1)].charVal), (yylocation_stack_[(1) - (1)]));                 }
    break;

  case 77:

/* Line 690 of lalr1.cc  */
#line 362 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = driver.createThis((yylocation_stack_[(1) - (1)]));                     }
    break;

  case 78:

/* Line 690 of lalr1.cc  */
#line 363 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.rightnode) = (yysemantic_stack_[(3) - (2)].rightnode);                                        }
    break;

  case 79:

/* Line 690 of lalr1.cc  */
#line 370 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.classBegin(*(yysemantic_stack_[(2) - (2)].stringVal), (yylocation_stack_[(2) - (2)])); yyfree((yysemantic_stack_[(2) - (2)].stringVal));   }
    break;

  case 80:

/* Line 690 of lalr1.cc  */
#line 371 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.classEnd();                        }
    break;

  case 82:

/* Line 690 of lalr1.cc  */
#line 376 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.classTop()->append((yysemantic_stack_[(1) - (1)].membernode)); (yysemantic_stack_[(1) - (1)].membernode) = 0;    }
    break;

  case 85:

/* Line 690 of lalr1.cc  */
#line 383 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.classTop()->inherit(*(yysemantic_stack_[(3) - (2)].stringVal));   yyfree((yysemantic_stack_[(3) - (2)].stringVal)); }
    break;

  case 86:

/* Line 690 of lalr1.cc  */
#line 384 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.classTop()->implement(*(yysemantic_stack_[(3) - (2)].stringVal)); yyfree((yysemantic_stack_[(3) - (2)].stringVal)); }
    break;

  case 91:

/* Line 690 of lalr1.cc  */
#line 398 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createVoidTy((yylocation_stack_[(1) - (1)]));    }
    break;

  case 92:

/* Line 690 of lalr1.cc  */
#line 402 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createArrayTy((yysemantic_stack_[(3) - (1)].typenode), (yylocation_stack_[(3) - (2)]) + (yylocation_stack_[(3) - (3)])); }
    break;

  case 93:

/* Line 690 of lalr1.cc  */
#line 406 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createIntTy((yylocation_stack_[(1) - (1)]));    }
    break;

  case 94:

/* Line 690 of lalr1.cc  */
#line 407 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createBoolTy((yylocation_stack_[(1) - (1)]));   }
    break;

  case 95:

/* Line 690 of lalr1.cc  */
#line 408 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createStringTy((yylocation_stack_[(1) - (1)])); }
    break;

  case 96:

/* Line 690 of lalr1.cc  */
#line 409 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createCharTy((yylocation_stack_[(1) - (1)]));   }
    break;

  case 97:

/* Line 690 of lalr1.cc  */
#line 410 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { (yyval.typenode) = driver.createQualifiedTy(*(yysemantic_stack_[(1) - (1)].stringVal), (yylocation_stack_[(1) - (1)])); yyfree((yysemantic_stack_[(1) - (1)].stringVal)); }
    break;

  case 99:

/* Line 690 of lalr1.cc  */
#line 415 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
    { driver.classTop()->append((yysemantic_stack_[(1) - (1)].membernode)); (yysemantic_stack_[(1) - (1)].membernode) = 0; }
    break;



/* Line 690 of lalr1.cc  */
#line 1184 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"
	default:
          break;
      }
    /* User semantic actions sometimes alter yychar, and that requires
       that yytoken be updated with the new translation.  We take the
       approach of translating immediately before every use of yytoken.
       One alternative is translating here after every semantic action,
       but that translation would be missed if the semantic action
       invokes YYABORT, YYACCEPT, or YYERROR immediately after altering
       yychar.  In the case of YYABORT or YYACCEPT, an incorrect
       destructor might then be invoked immediately.  In the case of
       YYERROR, subsequent parser actions might lead to an incorrect
       destructor call or verbose syntax error message before the
       lookahead is translated.  */
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
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = yytranslate_ (yychar);

    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	if (yychar == yyempty_)
	  yytoken = yyempty_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[1] = yylloc;
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

    yyerror_range[1] = yylocation_stack_[yylen - 1];
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
	if (!yy_pact_value_is_default_ (yyn))
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

	yyerror_range[1] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[2] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
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
      {
        /* Make sure we have latest lookahead translation.  See comments
           at user semantic actions for why this is necessary.  */
        yytoken = yytranslate_ (yychar);
        yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval,
                     &yylloc);
      }

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
  Parser::yysyntax_error_ (int yystate, int yytoken)
  {
    std::string yyres;
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yytoken) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yychar.
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (yytoken != yyempty_)
      {
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            /* Stay within bounds of both yycheck and yytname.  */
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = 0;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const short int Parser::yypact_ninf_ = -141;
  const short int
  Parser::yypact_[] =
  {
       448,  -141,  -141,  -141,  -141,  -141,  -141,     1,  -141,  -141,
    -141,  -141,    15,  -141,   -20,   448,  -141,    42,  -141,  -141,
     -15,   -17,    55,  -141,    -3,     5,  -141,  -141,  -141,   289,
     134,    44,    46,    20,   289,  -141,    25,  -141,    27,    62,
      35,    37,  -141,  -141,   289,    47,   134,  -141,  -141,  -141,
    -141,   327,  -141,  -141,    53,  -141,  -141,  -141,  -141,  -141,
      57,    68,    73,   134,  -141,   -18,    56,   -18,   -18,   -18,
     -18,   -18,  -141,  -141,    50,  -141,  -141,    58,    60,  -141,
      81,   417,    82,   184,    72,    67,    92,   109,  -141,  -141,
      97,   201,   -18,   201,  -141,  -141,  -141,   123,   327,  -141,
     327,  -141,  -141,  -141,    90,   436,  -141,  -141,    95,   201,
    -141,   -18,   -18,   -18,   -18,   -18,   -18,   -18,   -18,   -18,
     -18,   -18,   -18,   -18,   -18,   -18,   -18,  -141,   102,   -18,
     140,   117,   -18,   118,   436,   132,  -141,   130,  -141,  -141,
     -18,   135,   100,   436,    43,    43,   214,     8,   265,   265,
     294,   294,   235,   286,   294,   294,    -8,    -8,  -141,  -141,
     436,   201,  -141,   -18,   201,   436,   372,  -141,   201,  -141,
    -141,   129,   201,   136,   158,  -141,  -141,   372,  -141
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
       101,   100,    91,    93,    94,    96,    95,     0,    88,    87,
      98,    99,     0,    89,    90,   101,    97,     0,    79,     3,
       0,     0,     0,     1,     0,     0,     2,    92,   102,    81,
       5,     0,     0,     0,    81,    82,     0,     6,     8,     0,
       0,     0,    80,    84,    81,     0,     0,     9,    85,    86,
      83,    11,     4,     7,    39,    72,    73,    76,    74,    75,
      70,    71,     0,     0,    77,    25,     0,     0,     0,     0,
       0,     0,    14,    22,     0,    12,    17,     0,     0,    18,
       0,    30,     0,    61,     0,    67,     0,     0,    64,    39,
       0,    26,     0,    27,    42,    43,    44,    61,    11,    10,
      11,    19,    20,    21,    39,    30,    41,    31,    33,    35,
      15,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    16,     0,     0,
       0,    36,     0,     0,    30,    61,    78,     0,    23,    13,
       0,     0,    35,     0,    49,    50,    52,    54,    55,    56,
      57,    58,    51,    53,    60,    59,    46,    45,    47,    48,
       0,    66,    40,     0,    38,    30,     0,    24,    34,    63,
      32,     0,    37,     0,    28,    62,    65,     0,    29
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  Parser::yypgoto_[] =
  {
      -141,  -141,  -141,  -141,  -141,   157,  -141,  -141,   -96,  -141,
    -140,  -141,  -141,  -141,  -141,  -141,  -141,   -78,  -128,  -141,
    -141,   -50,  -141,   -40,  -141,  -141,  -141,  -141,  -141,  -141,
      10,  -141,  -141,    36,   -30,  -141,  -141,  -141,  -141,   189
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  Parser::yydefgoto_[] =
  {
        -1,     8,     9,    25,    36,    37,    38,    52,    74,   100,
      75,    76,    98,   138,    77,    78,    79,   141,   107,   108,
      80,    90,    82,    83,   128,   133,    84,    85,    10,    24,
      33,    44,    34,    35,    12,    13,    14,    15,    16,    17
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const signed char Parser::yytable_ninf_ = -101;
  const short int
  Parser::yytable_[] =
  {
        39,    81,   137,   106,   139,    89,    55,    56,    57,    58,
      59,    60,    61,   111,   112,   170,    39,   115,   116,   117,
     118,    86,    63,    64,    18,    91,   174,    93,    94,    95,
      96,    97,   171,    88,    68,    69,    11,   178,    19,    70,
      21,   109,    23,    71,    43,    20,   125,   126,    81,    26,
      81,    11,   135,    27,    50,    28,   119,   120,   121,   122,
     123,   124,   125,   126,    29,   142,    30,    40,    86,    41,
      86,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   173,    42,   161,
      45,    47,   164,    46,   109,   123,   124,   125,   126,    48,
     168,    49,    87,   109,   -68,   111,   112,   113,   114,   115,
     116,   117,   118,  -100,    51,   -69,    81,    92,    99,   129,
     109,   131,   101,   172,   102,   109,   130,    81,   111,   112,
     113,   114,   115,   116,   117,   118,    86,   111,   112,   113,
     114,   115,   116,   117,   118,   103,   110,    86,   119,   120,
     121,   122,   123,   124,   125,   126,   132,     1,   134,   140,
     -61,   143,   160,   162,   163,   136,     2,     3,     4,     5,
       6,   119,   120,   121,   122,   123,   124,   125,   126,   165,
     119,   120,   121,   122,   123,   124,   125,   126,   136,   111,
     112,   113,   114,   115,   116,   117,   118,   166,   167,   175,
     169,   176,   177,    53,    22,     0,   111,   112,   113,   114,
     115,   116,   117,   118,     0,     0,     0,     0,     0,   111,
     112,     0,   114,   115,   116,   117,   118,     0,     0,     0,
       0,     0,   119,   120,   121,   122,   123,   124,   125,   126,
     111,   112,     0,     0,   115,   116,   117,   118,   127,   119,
     120,   121,   122,   123,   124,   125,   126,     0,     0,     0,
       0,   -61,   119,   120,   121,   122,   123,   124,   125,   126,
     111,   112,     0,     0,  -101,  -101,   117,   118,     0,     0,
       0,     0,     0,     0,   120,   121,   122,   123,   124,   125,
     126,   111,   112,     0,     0,   115,   116,   117,   118,   111,
     112,     0,     0,     0,     0,  -101,  -101,     0,     0,     0,
       0,     0,     1,     0,     0,   121,   122,   123,   124,   125,
     126,     2,     3,     4,     5,     6,     0,    31,    32,     0,
       0,     0,     0,     0,     0,     0,   121,   122,   123,   124,
     125,   126,     0,     0,  -101,  -101,   123,   124,   125,   126,
      54,    55,    56,    57,    58,    59,    60,    61,    62,     2,
       3,     4,     5,     6,     0,     0,     0,    63,    64,    65,
      66,     0,     0,    67,     0,     0,     0,     0,     0,    68,
      69,     0,     0,     0,    70,     0,     0,     0,    71,     0,
       0,    72,     0,     0,    73,    54,    55,    56,    57,    58,
      59,    60,    61,    62,     2,     3,     4,     5,     6,     0,
       0,     0,    63,    64,    65,    66,     0,     0,    67,     0,
       0,     0,     0,     0,    68,    69,     0,     0,     0,    70,
       0,     0,     0,    71,     0,     0,     0,     0,     0,    73,
     104,    55,    56,    57,    58,    59,    60,    61,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    63,    64,   104,
      55,    56,    57,    58,    59,    60,    61,     0,     0,    68,
      69,     1,     0,     0,    70,     0,    63,    64,   105,     0,
       2,     3,     4,     5,     6,     7,     0,     0,    68,    69,
       0,     0,     0,    70,     0,     0,     0,    71
  };

  /* YYCHECK.  */
  const short int
  Parser::yycheck_[] =
  {
        30,    51,    98,    81,   100,    23,    24,    25,    26,    27,
      28,    29,    30,     5,     6,   143,    46,     9,    10,    11,
      12,    51,    40,    41,    23,    65,   166,    67,    68,    69,
      70,    71,   160,    63,    52,    53,     0,   177,    23,    57,
      60,    81,     0,    61,    34,    30,    54,    55,    98,    64,
     100,    15,    92,    70,    44,     0,    48,    49,    50,    51,
      52,    53,    54,    55,    67,   105,    61,    23,    98,    23,
     100,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   165,    68,   129,
      65,    29,   132,    66,   134,    52,    53,    54,    55,    64,
     140,    64,    29,   143,    47,     5,     6,     7,     8,     9,
      10,    11,    12,    60,    67,    47,   166,    61,    68,    47,
     160,    29,    64,   163,    64,   165,    59,   177,     5,     6,
       7,     8,     9,    10,    11,    12,   166,     5,     6,     7,
       8,     9,    10,    11,    12,    64,    64,   177,    48,    49,
      50,    51,    52,    53,    54,    55,    47,    23,    61,    69,
      60,    66,    60,    23,    47,    65,    32,    33,    34,    35,
      36,    48,    49,    50,    51,    52,    53,    54,    55,    61,
      48,    49,    50,    51,    52,    53,    54,    55,    65,     5,
       6,     7,     8,     9,    10,    11,    12,    65,    68,    70,
      65,    65,    44,    46,    15,    -1,     5,     6,     7,     8,
       9,    10,    11,    12,    -1,    -1,    -1,    -1,    -1,     5,
       6,    -1,     8,     9,    10,    11,    12,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
       5,     6,    -1,    -1,     9,    10,    11,    12,    64,    48,
      49,    50,    51,    52,    53,    54,    55,    -1,    -1,    -1,
      -1,    60,    48,    49,    50,    51,    52,    53,    54,    55,
       5,     6,    -1,    -1,     9,    10,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,     5,     6,    -1,    -1,     9,    10,    11,    12,     5,
       6,    -1,    -1,    -1,    -1,    11,    12,    -1,    -1,    -1,
      -1,    -1,    23,    -1,    -1,    50,    51,    52,    53,    54,
      55,    32,    33,    34,    35,    36,    -1,    38,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    -1,    -1,    50,    51,    52,    53,    54,    55,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,    52,
      53,    -1,    -1,    -1,    57,    -1,    -1,    -1,    61,    -1,
      -1,    64,    -1,    -1,    67,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    40,    41,    42,    43,    -1,    -1,    46,    -1,
      -1,    -1,    -1,    -1,    52,    53,    -1,    -1,    -1,    57,
      -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    67,
      23,    24,    25,    26,    27,    28,    29,    30,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    23,
      24,    25,    26,    27,    28,    29,    30,    -1,    -1,    52,
      53,    23,    -1,    -1,    57,    -1,    40,    41,    61,    -1,
      32,    33,    34,    35,    36,    37,    -1,    -1,    52,    53,
      -1,    -1,    -1,    57,    -1,    -1,    -1,    61
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    23,    32,    33,    34,    35,    36,    37,    72,    73,
      99,   104,   105,   106,   107,   108,   109,   110,    23,    23,
      30,    60,   110,     0,   100,    74,    64,    70,     0,    67,
      61,    38,    39,   101,   103,   104,    75,    76,    77,   105,
      23,    23,    68,   101,   102,    65,    66,    29,    64,    64,
     101,    67,    78,    76,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    40,    41,    42,    43,    46,    52,    53,
      57,    61,    64,    67,    79,    81,    82,    85,    86,    87,
      91,    92,    93,    94,    97,    98,   105,    29,   105,    23,
      92,    94,    61,    94,    94,    94,    94,    94,    83,    68,
      80,    64,    64,    64,    23,    61,    88,    89,    90,    94,
      64,     5,     6,     7,     8,     9,    10,    11,    12,    48,
      49,    50,    51,    52,    53,    54,    55,    64,    95,    47,
      59,    29,    47,    96,    61,    94,    65,    79,    84,    79,
      69,    88,    94,    66,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      60,    94,    23,    47,    94,    61,    65,    68,    94,    65,
      89,    89,    94,    88,    81,    70,    65,    44,    81
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
      91,    40,   303,   304,    59,    41,    44,   123,   125,    58,
      93
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    71,    72,    74,    73,    75,    75,    76,    76,    77,
      78,    79,    80,    79,    79,    81,    81,    81,    81,    81,
      81,    81,    83,    82,    84,    85,    85,    86,    87,    87,
      88,    88,    89,    89,    90,    90,    91,    91,    91,    92,
      92,    93,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    95,    94,    94,    96,    94,    94,    94,    97,    97,
      98,    98,    98,    98,    98,    98,    98,    98,    98,   100,
      99,   101,   102,   101,   101,   103,   103,   104,   104,   105,
     105,   105,   106,   107,   107,   107,   107,   107,   108,   108,
     109,   110,   110
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     3,     0,     7,     0,     1,     3,     1,     2,
       3,     0,     0,     3,     1,     2,     2,     1,     1,     2,
       2,     2,     0,     3,     2,     1,     2,     2,     5,     7,
       0,     1,     3,     1,     3,     1,     2,     4,     4,     1,
       3,     2,     2,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     0,     5,     4,     0,     6,     3,     1,     1,     1,
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
  "\"class\"", "\"inherit\"", "\"implement\"", "\"new\"", "\"this\"",
  "\"return\"", "\"if\"", "\"else\"", "\"ifelse\"", "\"print\"", "'='",
  "'|'", "'&'", "'<'", "'>'", "'-'", "'+'", "'*'", "'/'", "'%'", "'!'",
  "UNARY", "'.'", "'['", "'('", "PRE", "MINIM", "';'", "')'", "','", "'{'",
  "'}'", "':'", "']'", "$accept", "field", "function", "$@1",
  "function_arguments", "function_arguments_required", "function_argument",
  "function_statement", "statements", "$@2", "statement", "scope", "$@3",
  "scope_end", "return_statement", "print_statement",
  "conditional_statement", "call_arguments", "call_arguments_required",
  "call_argument", "variable_declare", "call_start", "call_inline",
  "expression", "$@4", "$@5", "left", "right", "class_definition", "$@6",
  "class_body", "$@7", "class_modificator", "class_element", "type",
  "type_complex", "type_primary", "script_elements",
  "qualified_identifier", "start", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
       110,     0,    -1,   105,    30,    64,    -1,    -1,   105,    23,
      74,    61,    75,    65,    78,    -1,    -1,    76,    -1,    77,
      66,    76,    -1,    77,    -1,   105,    29,    -1,    67,    79,
      68,    -1,    -1,    -1,    81,    80,    79,    -1,    64,    -1,
      93,    64,    -1,    94,    64,    -1,    82,    -1,    87,    -1,
      85,    64,    -1,    86,    64,    -1,    91,    64,    -1,    -1,
      67,    83,    84,    -1,    79,    68,    -1,    42,    -1,    42,
      94,    -1,    46,    94,    -1,    43,    61,    94,    65,    81,
      -1,    43,    61,    94,    65,    81,    44,    81,    -1,    -1,
      89,    -1,    90,    66,    89,    -1,    90,    -1,    23,    69,
      94,    -1,    94,    -1,   105,    29,    -1,   105,    29,    47,
      94,    -1,    31,    29,    47,    94,    -1,    23,    -1,    98,
      59,    23,    -1,    92,    88,    -1,    52,    94,    -1,    53,
      94,    -1,    57,    94,    -1,    94,    53,    94,    -1,    94,
      52,    94,    -1,    94,    54,    94,    -1,    94,    55,    94,
      -1,    94,     5,    94,    -1,    94,     6,    94,    -1,    94,
      48,    94,    -1,    94,     7,    94,    -1,    94,    49,    94,
      -1,    94,     8,    94,    -1,    94,     9,    94,    -1,    94,
      10,    94,    -1,    94,    11,    94,    -1,    94,    12,    94,
      -1,    94,    51,    94,    -1,    94,    50,    94,    -1,    -1,
      94,    95,    60,    89,    70,    -1,    92,    61,    88,    65,
      -1,    -1,    40,   105,    96,    61,    88,    65,    -1,    97,
      47,    94,    -1,    98,    -1,    29,    -1,    30,    -1,    29,
      -1,    30,    -1,    24,    -1,    25,    -1,    27,    -1,    28,
      -1,    26,    -1,    41,    -1,    61,    94,    65,    -1,    -1,
      37,    23,   100,    67,   101,    68,    -1,    -1,    -1,   104,
     102,   101,    -1,   103,   101,    -1,    38,    23,    64,    -1,
      39,    23,    64,    -1,    73,    -1,    72,    -1,   106,    -1,
     107,    -1,    32,    -1,   107,    60,    70,    -1,    33,    -1,
      34,    -1,    36,    -1,    35,    -1,   109,    -1,    99,    -1,
     104,    -1,    23,    -1,    -1,   108,   110,     0,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  Parser::yyprhs_[] =
  {
         0,     0,     3,     7,     8,    16,    17,    19,    23,    25,
      28,    32,    33,    34,    38,    40,    43,    46,    48,    50,
      53,    56,    59,    60,    64,    67,    69,    72,    75,    81,
      89,    90,    92,    96,    98,   102,   104,   107,   112,   117,
     119,   123,   126,   129,   132,   135,   139,   143,   147,   151,
     155,   159,   163,   167,   171,   175,   179,   183,   187,   191,
     195,   199,   200,   206,   211,   212,   219,   223,   225,   227,
     229,   231,   233,   235,   237,   239,   241,   243,   245,   249,
     250,   257,   258,   259,   263,   266,   270,   274,   276,   278,
     280,   282,   284,   288,   290,   292,   294,   296,   298,   300,
     302,   304,   305
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,   186,   186,   193,   193,   198,   200,   204,   205,   209,
     213,   219,   221,   221,   223,   227,   228,   229,   230,   231,
     232,   233,   237,   237,   242,   246,   247,   251,   257,   258,
     264,   266,   270,   271,   275,   276,   284,   289,   294,   302,
     303,   307,   312,   313,   314,   316,   317,   318,   319,   320,
     321,   323,   324,   325,   326,   328,   329,   330,   331,   332,
     333,   336,   336,   339,   342,   342,   345,   346,   350,   351,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   370,
     370,   374,   376,   376,   378,   383,   384,   388,   389,   396,
     397,   398,   402,   406,   407,   408,   409,   410,   414,   415,
     419,   423,   425
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
      61,    65,    54,    53,    66,    52,    59,    55,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    69,    64,
      50,    47,    51,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    60,     2,    70,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    67,    48,    68,     2,     2,     2,     2,
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
      45,    46,    58,    62,    63
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 497;
  const int Parser::yynnts_ = 40;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 23;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 71;

  const unsigned int Parser::yyuser_token_number_max_ = 304;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


} } // kiwi::lang

/* Line 1136 of lalr1.cc  */
#line 1914 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.cpp"


/* Line 1138 of lalr1.cc  */
#line 430 "/home/alurin/workplace/project/kiwi/source/kiwi-core/Lang/parser.yy"
 /*** Additional Code ***/

void kiwi::lang::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}

