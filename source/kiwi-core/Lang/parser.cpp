// A Bison parser, made by GNU Bison 3.0.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2013 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Take the name prefix into account.
#define yylex   kiwi::langlex

// First part of user declarations.
#line 7 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:399
 /*** C/C++ Declarations ***/

#include "kiwi/config.hpp"
#include <stdio.h>
#include <string>
#include <vector>
#include "ExpressionNode.hpp"
#include "TypeNode.hpp"
#include "FunctionNode.hpp"


#line 50 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:399

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.hpp"

// User implementation prologue.
#line 162 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:407


#include "Driver.hpp"
#include "scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

#define yyfree(__px1) delete __px1; __px1 = 0;


#line 78 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:407


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyempty = true)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace kiwi { namespace lang {
#line 164 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:474

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
              // Fall through.
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
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  Parser::by_type::by_type ()
     : type (empty)
  {}

  inline
  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.type = empty;
  }

  inline
  int
  Parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.state = empty;
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    return state == empty ? 0 : yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.type_get ())
    {
            case 23: // "identifier"

#line 152 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:599
        { delete (yysym.value.stringVal); }
#line 383 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:599
        break;

      case 25: // "string constant"

#line 157 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:599
        { delete (yysym.value.ustringVal); }
#line 390 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:599
        break;

      case 29: // "local variable"

#line 152 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:599
        { delete (yysym.value.stringVal); }
#line 397 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:599
        break;

      case 30: // "instance attribute"

#line 152 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:599
        { delete (yysym.value.stringVal); }
#line 404 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:599
        break;

      case 72: // field

#line 158 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:599
        { delete (yysym.value.membernode); }
#line 411 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:599
        break;

      case 73: // function

#line 158 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:599
        { delete (yysym.value.membernode); }
#line 418 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:599
        break;

      case 81: // statement

#line 155 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:599
        { delete (yysym.value.stmtnode); }
#line 425 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:599
        break;

      case 82: // scope

#line 155 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:599
        { delete (yysym.value.stmtnode); }
#line 432 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:599
        break;

      case 84: // scope_end

#line 155 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:599
        { delete (yysym.value.stmtnode); }
#line 439 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:599
        break;

      case 85: // return_statement

#line 155 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:599
        { delete (yysym.value.stmtnode); }
#line 446 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:599
        break;

      case 86: // print_statement

#line 155 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:599
        { delete (yysym.value.stmtnode); }
#line 453 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:599
        break;

      case 87: // conditional_statement

#line 155 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:599
        { delete (yysym.value.stmtnode); }
#line 460 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:599
        break;

      case 91: // variable_declare

#line 156 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:599
        { delete (yysym.value.stmtnode); }
#line 467 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:599
        break;

      case 93: // call_inline

#line 153 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:599
        { delete (yysym.value.rightnode); }
#line 474 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:599
        break;

      case 94: // expression

#line 153 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:599
        { delete (yysym.value.rightnode); }
#line 481 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:599
        break;

      case 98: // right

#line 153 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:599
        { delete (yysym.value.rightnode); }
#line 488 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:599
        break;

      case 104: // class_element

#line 158 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:599
        { delete (yysym.value.membernode); }
#line 495 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:599
        break;

      case 105: // type

#line 154 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:599
        { delete (yysym.value.typenode); }
#line 502 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:599
        break;

      case 106: // type_complex

#line 154 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:599
        { delete (yysym.value.typenode); }
#line 509 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:599
        break;

      case 107: // type_primary

#line 154 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:599
        { delete (yysym.value.typenode); }
#line 516 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:599
        break;

      case 109: // qualified_identifier

#line 157 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:599
        { delete (yysym.value.stringVal); }
#line 523 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:599
        break;


      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
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
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

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
    /// Whether yyla contains a lookahead.
    bool yyempty = true;

    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 46 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:725
{
    // initialize the initial location object
    yyla.location.begin.filename = yyla.location.end.filename = &driver.streamname;
    driver.prepareScript(yyla.location);
}

#line 661 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:725

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyempty)
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
        yyempty = false;
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Discard the token being shifted.
    yyempty = true;

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 186 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.membernode) = driver.field(*(yystack_[1].value.stringVal), (yystack_[2].value.typenode)); yyfree((yystack_[1].value.stringVal)); }
#line 775 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 3:
#line 193 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { driver.func(*(yystack_[0].value.stringVal), (yystack_[1].value.typenode)); yyfree((yystack_[0].value.stringVal)); }
#line 781 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 4:
#line 195 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.membernode) = driver.funcEnd();            }
#line 787 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 9:
#line 209 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { driver.func()->declare(*(yystack_[0].value.stringVal), (yystack_[1].value.typenode), yystack_[0].location); }
#line 793 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 12:
#line 221 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { driver.scope()->append((yystack_[0].value.stmtnode)); (yystack_[0].value.stmtnode) = 0; }
#line 799 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 15:
#line 227 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.stmtnode) = driver.createExpr((yystack_[1].value.rightnode));       }
#line 805 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 16:
#line 228 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.stmtnode) = driver.createExpr((yystack_[1].value.rightnode));       }
#line 811 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 22:
#line 237 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { driver.scopeBegin(yystack_[0].location);            }
#line 817 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 23:
#line 238 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.stmtnode) = (yystack_[0].value.stmtnode);                          }
#line 823 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 24:
#line 242 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.stmtnode) = driver.scopeEnd();         }
#line 829 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 25:
#line 246 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.stmtnode) = driver.createReturn(yystack_[0].location);     }
#line 835 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 26:
#line 247 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.stmtnode) = driver.createReturn((yystack_[0].value.rightnode), yystack_[1].location); }
#line 841 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 27:
#line 251 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.stmtnode) = driver.createPrint((yystack_[0].value.rightnode), yystack_[1].location);  }
#line 847 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 28:
#line 257 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.stmtnode) = driver.createCond((yystack_[2].value.rightnode), (yystack_[0].value.stmtnode), 0,  yystack_[4].location); }
#line 853 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 29:
#line 258 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.stmtnode) = driver.createCond((yystack_[4].value.rightnode), (yystack_[2].value.stmtnode), (yystack_[0].value.stmtnode), yystack_[6].location); }
#line 859 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 34:
#line 275 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { driver.call()->append(*(yystack_[2].value.stringVal), (yystack_[0].value.rightnode)); yyfree((yystack_[2].value.stringVal)); (yystack_[0].value.rightnode) = 0; }
#line 865 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 35:
#line 276 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { driver.call()->append((yystack_[0].value.rightnode)); (yystack_[0].value.rightnode) = 0; }
#line 871 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 36:
#line 284 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    {
                                                driver.scope()->declare(*(yystack_[0].value.stringVal), (yystack_[1].value.typenode), yystack_[0].location);
                                                (yylhs.value.stmtnode) = 0;
                                                yyfree((yystack_[0].value.stringVal));
                                            }
#line 881 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 37:
#line 289 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    {
                                                VariableNode* node = driver.scope()->declare(*(yystack_[2].value.stringVal), (yystack_[3].value.typenode), (yystack_[0].value.rightnode), yystack_[2].location);
                                                (yylhs.value.stmtnode) = driver.createInit(node, yystack_[1].location);
                                                yyfree((yystack_[2].value.stringVal));
                                            }
#line 891 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 38:
#line 294 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    {
                                                VariableNode* node = driver.scope()->declare(*(yystack_[2].value.stringVal), (yystack_[0].value.rightnode), yystack_[2].location);
                                                (yylhs.value.stmtnode) = driver.createInit(node, yystack_[1].location);
                                                yyfree((yystack_[2].value.stringVal));
                                            }
#line 901 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 39:
#line 302 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { driver.call(*(yystack_[0].value.stringVal), yystack_[0].location); yyfree((yystack_[0].value.stringVal));  }
#line 907 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 40:
#line 303 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { driver.call((yystack_[2].value.rightnode), *(yystack_[0].value.stringVal), yystack_[2].location + yystack_[0].location); yyfree((yystack_[0].value.stringVal)); }
#line 913 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 41:
#line 308 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.callEnd(yystack_[1].location); }
#line 919 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 42:
#line 312 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createNeg((yystack_[0].value.rightnode), yystack_[1].location); }
#line 925 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 43:
#line 313 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createPos((yystack_[0].value.rightnode), yystack_[1].location); }
#line 931 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 44:
#line 314 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createNot((yystack_[0].value.rightnode), yystack_[1].location); }
#line 937 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 45:
#line 316 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createAdd((yystack_[2].value.rightnode), (yystack_[0].value.rightnode), yystack_[1].location); }
#line 943 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 46:
#line 317 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createSub((yystack_[2].value.rightnode), (yystack_[0].value.rightnode), yystack_[1].location); }
#line 949 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 47:
#line 318 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createMul((yystack_[2].value.rightnode), (yystack_[0].value.rightnode), yystack_[1].location); }
#line 955 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 48:
#line 319 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createDiv((yystack_[2].value.rightnode), (yystack_[0].value.rightnode), yystack_[1].location); }
#line 961 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 49:
#line 320 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createLsh((yystack_[2].value.rightnode), (yystack_[0].value.rightnode), yystack_[1].location); }
#line 967 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 50:
#line 321 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createRsh((yystack_[2].value.rightnode), (yystack_[0].value.rightnode), yystack_[1].location); }
#line 973 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 51:
#line 323 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createOr ((yystack_[2].value.rightnode), (yystack_[0].value.rightnode), false, yystack_[1].location); }
#line 979 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 52:
#line 324 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createOr ((yystack_[2].value.rightnode), (yystack_[0].value.rightnode), true,  yystack_[1].location); }
#line 985 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 53:
#line 325 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createAnd((yystack_[2].value.rightnode), (yystack_[0].value.rightnode), false, yystack_[1].location); }
#line 991 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 54:
#line 326 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createAnd((yystack_[2].value.rightnode), (yystack_[0].value.rightnode), true,  yystack_[1].location); }
#line 997 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 55:
#line 328 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createEq ((yystack_[2].value.rightnode), (yystack_[0].value.rightnode), yystack_[1].location); }
#line 1003 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 56:
#line 329 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createNeq((yystack_[2].value.rightnode), (yystack_[0].value.rightnode), yystack_[1].location); }
#line 1009 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 57:
#line 330 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createGe ((yystack_[2].value.rightnode), (yystack_[0].value.rightnode), yystack_[1].location); }
#line 1015 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 58:
#line 331 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createLe ((yystack_[2].value.rightnode), (yystack_[0].value.rightnode), yystack_[1].location); }
#line 1021 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 59:
#line 332 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createGt ((yystack_[2].value.rightnode), (yystack_[0].value.rightnode), yystack_[1].location); }
#line 1027 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 60:
#line 333 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createLt ((yystack_[2].value.rightnode), (yystack_[0].value.rightnode), yystack_[1].location); }
#line 1033 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 61:
#line 336 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { driver.subBegin((yystack_[0].value.rightnode), yystack_[0].location);           }
#line 1039 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 62:
#line 337 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.callEnd(yystack_[2].location + yystack_[0].location);      }
#line 1045 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 63:
#line 340 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.callEnd(yystack_[3].location);           }
#line 1051 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 64:
#line 342 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { driver.newBegin((yystack_[0].value.typenode), yystack_[1].location);              }
#line 1057 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 65:
#line 343 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.callEnd(yystack_[5].location + yystack_[4].location);         }
#line 1063 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 66:
#line 345 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createAssign((yystack_[2].value.leftnode), (yystack_[0].value.rightnode), yystack_[1].location); }
#line 1069 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 68:
#line 350 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.leftnode) = driver.left(*(yystack_[0].value.stringVal), yystack_[0].location); yyfree((yystack_[0].value.stringVal));          }
#line 1075 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 69:
#line 351 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.leftnode) = driver.instanceLeft(*(yystack_[0].value.stringVal), yystack_[0].location); yyfree((yystack_[0].value.stringVal));  }
#line 1081 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 70:
#line 355 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.right(*(yystack_[0].value.stringVal), yystack_[0].location); yyfree((yystack_[0].value.stringVal));         }
#line 1087 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 71:
#line 356 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.instanceRight(*(yystack_[0].value.stringVal), yystack_[0].location); yyfree((yystack_[0].value.stringVal)); }
#line 1093 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 72:
#line 357 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createInt((yystack_[0].value.integerVal), yystack_[0].location);                  }
#line 1099 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 73:
#line 358 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createString(*(yystack_[0].value.ustringVal), yystack_[0].location); yyfree((yystack_[0].value.ustringVal));  }
#line 1105 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 74:
#line 359 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createBool(true, yystack_[0].location);               }
#line 1111 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 75:
#line 360 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createBool(false, yystack_[0].location);              }
#line 1117 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 76:
#line 361 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createChar((yystack_[0].value.charVal), yystack_[0].location);                 }
#line 1123 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 77:
#line 362 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = driver.createThis(yystack_[0].location);                     }
#line 1129 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 78:
#line 363 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.rightnode) = (yystack_[1].value.rightnode);                                        }
#line 1135 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 79:
#line 370 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { driver.classBegin(*(yystack_[0].value.stringVal), yystack_[0].location); yyfree((yystack_[0].value.stringVal));   }
#line 1141 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 80:
#line 371 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { driver.classEnd();                        }
#line 1147 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 82:
#line 376 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { driver.classTop()->append((yystack_[0].value.membernode)); (yystack_[0].value.membernode) = 0;    }
#line 1153 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 85:
#line 383 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { driver.classTop()->inherit(*(yystack_[1].value.stringVal));   yyfree((yystack_[1].value.stringVal)); }
#line 1159 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 86:
#line 384 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { driver.classTop()->implement(*(yystack_[1].value.stringVal)); yyfree((yystack_[1].value.stringVal)); }
#line 1165 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 91:
#line 398 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.typenode) = driver.createVoidTy(yystack_[0].location);    }
#line 1171 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 92:
#line 402 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.typenode) = driver.createArrayTy((yystack_[2].value.typenode), yystack_[1].location + yystack_[0].location); }
#line 1177 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 93:
#line 406 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.typenode) = driver.createIntTy(yystack_[0].location);    }
#line 1183 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 94:
#line 407 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.typenode) = driver.createBoolTy(yystack_[0].location);   }
#line 1189 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 95:
#line 408 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.typenode) = driver.createStringTy(yystack_[0].location); }
#line 1195 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 96:
#line 409 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.typenode) = driver.createCharTy(yystack_[0].location);   }
#line 1201 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 97:
#line 410 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { (yylhs.value.typenode) = driver.createQualifiedTy(*(yystack_[0].value.stringVal), yystack_[0].location); yyfree((yystack_[0].value.stringVal)); }
#line 1207 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;

  case 99:
#line 415 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:847
    { driver.classTop()->append((yystack_[0].value.membernode)); (yystack_[0].value.membernode) = 0; }
#line 1213 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
    break;


#line 1217 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:847
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state,
                                           yyempty ? yyempty_ : yyla.type_get ()));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyempty)
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyempty = true;
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
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
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
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

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyempty)
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyempty)
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, symbol_number_type yytoken) const
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
         yyla.  (However, yyla is currently not documented for users.)
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
            // Stay within bounds of both yycheck and yytname.
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

    char const* yyformat = YY_NULLPTR;
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


  const short int Parser::yypact_ninf_ = -141;

  const signed char Parser::yytable_ninf_ = -101;

  const short int
  Parser::yypact_[] =
  {
     182,  -141,  -141,  -141,  -141,  -141,  -141,    26,  -141,  -141,
    -141,  -141,    15,  -141,   -14,   182,  -141,    51,  -141,  -141,
     -11,   -16,    55,  -141,    -3,     4,  -141,  -141,  -141,   290,
     134,    44,    46,    20,   290,  -141,    25,  -141,    27,    62,
      35,    37,  -141,  -141,   290,    47,   134,  -141,  -141,  -141,
    -141,   327,  -141,  -141,    41,  -141,  -141,  -141,  -141,  -141,
      57,    66,    86,   134,  -141,   -18,    56,   -18,   -18,   -18,
     -18,   -18,  -141,  -141,    49,  -141,  -141,    58,    60,  -141,
      81,   417,    82,   184,    72,    61,    97,   109,  -141,  -141,
      96,   201,   -18,   201,  -141,  -141,  -141,   123,   327,  -141,
     327,  -141,  -141,  -141,    90,   425,  -141,  -141,    94,   201,
    -141,   -18,   -18,   -18,   -18,   -18,   -18,   -18,   -18,   -18,
     -18,   -18,   -18,   -18,   -18,   -18,   -18,  -141,   101,   -18,
     140,   117,   -18,   136,   425,   132,  -141,   111,  -141,  -141,
     -18,   135,   100,   425,    43,    43,   215,     8,   266,   266,
     294,   294,   235,   286,   294,   294,   -12,   -12,  -141,  -141,
     425,   201,  -141,   -18,   201,   425,   372,  -141,   201,  -141,
    -141,   129,   201,   137,   157,  -141,  -141,   372,  -141
  };

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

  const short int
  Parser::yypgoto_[] =
  {
    -141,  -141,  -141,  -141,  -141,   158,  -141,  -141,   -96,  -141,
    -140,  -141,  -141,  -141,  -141,  -141,  -141,   -78,  -128,  -141,
    -141,   -50,  -141,   -40,  -141,  -141,  -141,  -141,  -141,  -141,
       2,  -141,  -141,    24,   -30,  -141,  -141,  -141,  -141,   188
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     8,     9,    25,    36,    37,    38,    52,    74,   100,
      75,    76,    98,   138,    77,    78,    79,   141,   107,   108,
      80,    90,    82,    83,   128,   133,    84,    85,    10,    24,
      33,    44,    34,    35,    12,    13,    14,    15,    16,    17
  };

  const short int
  Parser::yytable_[] =
  {
      39,    81,   137,   106,   139,    89,    55,    56,    57,    58,
      59,    60,    61,   111,   112,   170,    39,   115,   116,   117,
     118,    86,    63,    64,    11,    91,   174,    93,    94,    95,
      96,    97,   171,    88,    68,    69,    43,   178,    19,    11,
      70,   109,   125,   126,    71,    20,    50,    21,    81,    18,
      81,    23,   135,    26,    27,    28,   119,   120,   121,   122,
     123,   124,   125,   126,    29,   142,    30,    40,    86,    41,
      86,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   173,    42,   161,
      45,    47,   164,    46,   109,   123,   124,   125,   126,    48,
     168,    49,  -100,   109,   -68,   111,   112,   113,   114,   115,
     116,   117,   118,   -69,    51,    87,    81,    99,    92,   129,
     109,   130,   101,   172,   102,   109,   131,    81,   111,   112,
     113,   114,   115,   116,   117,   118,    86,   111,   112,   113,
     114,   115,   116,   117,   118,   103,   110,    86,   119,   120,
     121,   122,   123,   124,   125,   126,   132,     1,   134,   140,
     143,   -61,   160,   162,   163,   136,     2,     3,     4,     5,
       6,   119,   120,   121,   122,   123,   124,   125,   126,   167,
     119,   120,   121,   122,   123,   124,   125,   126,   136,   111,
     112,   113,   114,   115,   116,   117,   118,   166,   165,   175,
     169,   177,   176,    22,    53,     1,   111,   112,   113,   114,
     115,   116,   117,   118,     2,     3,     4,     5,     6,     7,
     111,   112,     0,   114,   115,   116,   117,   118,     0,     0,
       0,     0,   119,   120,   121,   122,   123,   124,   125,   126,
     111,   112,     0,     0,   115,   116,   117,   118,   127,   119,
     120,   121,   122,   123,   124,   125,   126,     0,     0,     0,
       0,     0,   -61,   119,   120,   121,   122,   123,   124,   125,
     126,   111,   112,     0,     0,  -101,  -101,   117,   118,     0,
       0,     0,     0,     0,   120,   121,   122,   123,   124,   125,
     126,   111,   112,     0,     0,   115,   116,   117,   118,   111,
     112,     0,     0,     0,     0,  -101,  -101,     0,     0,     0,
       0,     0,     0,     1,     0,     0,   121,   122,   123,   124,
     125,   126,     2,     3,     4,     5,     6,     0,    31,    32,
       0,     0,     0,     0,     0,     0,   121,   122,   123,   124,
     125,   126,     0,     0,  -101,  -101,   123,   124,   125,   126,
      54,    55,    56,    57,    58,    59,    60,    61,    62,     2,
       3,     4,     5,     6,     0,     0,     0,    63,    64,    65,
      66,     0,     0,    67,     0,     0,     0,     0,     0,    68,
      69,     0,     0,     0,     0,    70,     0,     0,     0,    71,
       0,    72,     0,     0,    73,    54,    55,    56,    57,    58,
      59,    60,    61,    62,     2,     3,     4,     5,     6,     0,
       0,     0,    63,    64,    65,    66,     0,     0,    67,     0,
       0,     0,     0,     0,    68,    69,     0,     0,     0,     0,
      70,     0,     0,     0,    71,     0,     0,     0,     0,    73,
     104,    55,    56,    57,    58,    59,    60,    61,   104,    55,
      56,    57,    58,    59,    60,    61,     0,    63,    64,     0,
       0,     0,     0,     0,     0,    63,    64,     0,     0,    68,
      69,     0,     0,     0,     0,    70,     0,    68,    69,   105,
       0,     0,     0,    70,     0,     0,     0,    71
  };

  const short int
  Parser::yycheck_[] =
  {
      30,    51,    98,    81,   100,    23,    24,    25,    26,    27,
      28,    29,    30,     5,     6,   143,    46,     9,    10,    11,
      12,    51,    40,    41,     0,    65,   166,    67,    68,    69,
      70,    71,   160,    63,    52,    53,    34,   177,    23,    15,
      58,    81,    54,    55,    62,    30,    44,    61,    98,    23,
     100,     0,    92,    64,    70,     0,    48,    49,    50,    51,
      52,    53,    54,    55,    67,   105,    62,    23,    98,    23,
     100,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   165,    68,   129,
      65,    29,   132,    66,   134,    52,    53,    54,    55,    64,
     140,    64,    61,   143,    47,     5,     6,     7,     8,     9,
      10,    11,    12,    47,    67,    29,   166,    68,    62,    47,
     160,    60,    64,   163,    64,   165,    29,   177,     5,     6,
       7,     8,     9,    10,    11,    12,   166,     5,     6,     7,
       8,     9,    10,    11,    12,    64,    64,   177,    48,    49,
      50,    51,    52,    53,    54,    55,    47,    23,    62,    69,
      66,    61,    61,    23,    47,    65,    32,    33,    34,    35,
      36,    48,    49,    50,    51,    52,    53,    54,    55,    68,
      48,    49,    50,    51,    52,    53,    54,    55,    65,     5,
       6,     7,     8,     9,    10,    11,    12,    65,    62,    70,
      65,    44,    65,    15,    46,    23,     5,     6,     7,     8,
       9,    10,    11,    12,    32,    33,    34,    35,    36,    37,
       5,     6,    -1,     8,     9,    10,    11,    12,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
       5,     6,    -1,    -1,     9,    10,    11,    12,    64,    48,
      49,    50,    51,    52,    53,    54,    55,    -1,    -1,    -1,
      -1,    -1,    61,    48,    49,    50,    51,    52,    53,    54,
      55,     5,     6,    -1,    -1,     9,    10,    11,    12,    -1,
      -1,    -1,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,     5,     6,    -1,    -1,     9,    10,    11,    12,     5,
       6,    -1,    -1,    -1,    -1,    11,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    -1,    -1,    50,    51,    52,    53,
      54,    55,    32,    33,    34,    35,    36,    -1,    38,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    -1,    -1,    50,    51,    52,    53,    54,    55,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,    52,
      53,    -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,    62,
      -1,    64,    -1,    -1,    67,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    40,    41,    42,    43,    -1,    -1,    46,    -1,
      -1,    -1,    -1,    -1,    52,    53,    -1,    -1,    -1,    -1,
      58,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    67,
      23,    24,    25,    26,    27,    28,    29,    30,    23,    24,
      25,    26,    27,    28,    29,    30,    -1,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    40,    41,    -1,    -1,    52,
      53,    -1,    -1,    -1,    -1,    58,    -1,    52,    53,    62,
      -1,    -1,    -1,    58,    -1,    -1,    -1,    62
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,    23,    32,    33,    34,    35,    36,    37,    72,    73,
      99,   104,   105,   106,   107,   108,   109,   110,    23,    23,
      30,    61,   110,     0,   100,    74,    64,    70,     0,    67,
      62,    38,    39,   101,   103,   104,    75,    76,    77,   105,
      23,    23,    68,   101,   102,    65,    66,    29,    64,    64,
     101,    67,    78,    76,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    40,    41,    42,    43,    46,    52,    53,
      58,    62,    64,    67,    79,    81,    82,    85,    86,    87,
      91,    92,    93,    94,    97,    98,   105,    29,   105,    23,
      92,    94,    62,    94,    94,    94,    94,    94,    83,    68,
      80,    64,    64,    64,    23,    62,    88,    89,    90,    94,
      64,     5,     6,     7,     8,     9,    10,    11,    12,    48,
      49,    50,    51,    52,    53,    54,    55,    64,    95,    47,
      60,    29,    47,    96,    62,    94,    65,    79,    84,    79,
      69,    88,    94,    66,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      61,    94,    23,    47,    94,    62,    65,    68,    94,    65,
      89,    89,    94,    88,    81,    70,    65,    44,    81
  };

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



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
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
  "'|'", "'&'", "'<'", "'>'", "'-'", "'+'", "'*'", "'/'", "'%'", "UNARY",
  "'!'", "PRE", "'.'", "'['", "'('", "MINIM", "';'", "')'", "','", "'{'",
  "'}'", "':'", "']'", "$accept", "field", "function", "$@1",
  "function_arguments", "function_arguments_required", "function_argument",
  "function_statement", "statements", "$@2", "statement", "scope", "$@3",
  "scope_end", "return_statement", "print_statement",
  "conditional_statement", "call_arguments", "call_arguments_required",
  "call_argument", "variable_declare", "call_start", "call_inline",
  "expression", "$@4", "$@5", "left", "right", "class_definition", "$@6",
  "class_body", "$@7", "class_modificator", "class_element", "type",
  "type_complex", "type_primary", "script_elements",
  "qualified_identifier", "start", YY_NULLPTR
  };

#if YYDEBUG
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
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
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
       2,     2,     2,    58,     2,     2,     2,    56,    49,     2,
      62,    65,    54,    53,    66,    52,    60,    55,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    69,    64,
      50,    47,    51,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    61,     2,    70,     2,     2,     2,     2,     2,     2,
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
      45,    46,    57,    59,    63
    };
    const unsigned int user_token_number_max_ = 304;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} } // kiwi::lang
#line 1834 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.cpp" // lalr1.cc:1155
#line 430 "/home/alurin/projects/archive/languages/kiwi/source/kiwi-core/Lang/parser.yy" // lalr1.cc:1156
 /*** Additional Code ***/

void kiwi::lang::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}
