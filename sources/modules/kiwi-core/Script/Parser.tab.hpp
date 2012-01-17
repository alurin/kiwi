
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison LALR(1) parsers in C++
   
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

/* C++ LALR(1) parser skeleton written by Akim Demaille.  */

#ifndef PARSER_HEADER_H
# define PARSER_HEADER_H

/* "%code requires" blocks.  */

/* Line 35 of lalr1.cc  */
#line 16 "/home/alurin/projects/kiwi/sources/modules/kiwi-core/Script/Parser.ypp"

    #include "Driver.hpp"
    #include "CompoundList.hpp"

    namespace kiwi {
        namespace script {
            class Driver;
            class Lexer;
        }
    }



/* Line 35 of lalr1.cc  */
#line 59 "Parser.tab.hpp"


#include <string>
#include <iostream>
#include "stack.hh"


/* Line 35 of lalr1.cc  */
#line 4 "/home/alurin/projects/kiwi/sources/modules/kiwi-core/Script/Parser.ypp"
namespace kiwi { namespace script {

/* Line 35 of lalr1.cc  */
#line 72 "Parser.tab.hpp"
  class position;
  class location;

/* Line 35 of lalr1.cc  */
#line 4 "/home/alurin/projects/kiwi/sources/modules/kiwi-core/Script/Parser.ypp"
} } // kiwi::script

/* Line 35 of lalr1.cc  */
#line 81 "Parser.tab.hpp"

#include "location.hh"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
do {							\
  if (N)						\
    {							\
      (Current).begin = (Rhs)[1].begin;			\
      (Current).end   = (Rhs)[N].end;			\
    }							\
  else							\
    {							\
      (Current).begin = (Current).end = (Rhs)[0].end;	\
    }							\
} while (false)
#endif


/* Line 35 of lalr1.cc  */
#line 4 "/home/alurin/projects/kiwi/sources/modules/kiwi-core/Script/Parser.ypp"
namespace kiwi { namespace script {

/* Line 35 of lalr1.cc  */
#line 128 "Parser.tab.hpp"

  /// A Bison parser.
  class Parser
  {
  public:
    /// Symbol semantic values.
#ifndef YYSTYPE
    union semantic_type
    {

/* Line 35 of lalr1.cc  */
#line 154 "/home/alurin/projects/kiwi/sources/modules/kiwi-core/Script/Parser.ypp"

    //===- Lexer values----------------------------------------------------===//
    int64_t                                 ival;           ///< Integer constant
    UChar                                   cval;           ///< Text constant
    String*                                 sval;           ///< String constant or identifier



/* Line 35 of lalr1.cc  */
#line 150 "Parser.tab.hpp"
    };
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;
    /// Tokens.
    struct token
    {
      /* Tokens.  */
   enum yytokentype {
     T_EOF = 0,
     T_SCRIPT_BEGIN = 258,
     T_SCRIPT_PRINT = 259,
     T_SCRIPT_END = 260,
     T_SCRIPT_STRING = 261,
     T_SCRIPT_NEWLINE = 262,
     T_PRINT = 263,
     T_PRINT_NL = 264,
     T_IN = 265,
     T_REF = 266,
     T_OUT = 267,
     T_DOTS = 268,
     T_INSERT = 269,
     T_SHL = 270,
     T_SHR = 271,
     T_OR = 272,
     T_AND = 273,
     T_EQ = 274,
     T_NE = 275,
     T_GE = 276,
     T_LE = 277,
     T_INC = 278,
     T_DEC = 279,
     T_AADD = 280,
     T_ASUB = 281,
     T_ADIV = 282,
     T_AMUL = 283,
     T_ASHL = 284,
     T_ASHR = 285,
     T_AAND = 286,
     T_AOR = 287,
     T_IDENTIFIER = 288,
     T_SYMBOL = 289,
     T_VARIABLE = 290,
     T_INSTANCE_FIELD = 291,
     T_STATIC_FIELD = 292,
     T_AUTO = 293,
     T_DECL = 294,
     T_VOID = 295,
     T_BOOL = 296,
     T_INT = 297,
     T_CHAR = 298,
     T_STRING = 299,
     T_DOUBLE = 300,
     T_AS = 301,
     T_IS = 302,
     T_NEW = 303,
     T_IF = 304,
     T_ELSE = 305,
     T_ELSEIF = 306,
     T_FOR = 307,
     T_FOREACH = 308,
     T_WHILE = 309,
     T_REPEAT = 310,
     T_BREAK = 311,
     T_CONTINUE = 312,
     T_RETURN = 313,
     T_TRY = 314,
     T_CATCH = 315,
     T_FINALLY = 316,
     T_THROW = 317,
     T_NULL = 318,
     T_TRUE = 319,
     T_FALSE = 320,
     T_CONST_INTEGER = 321,
     T_CONST_CHAR = 322,
     T_CONST_STRING = 323,
     T_NAMESPACE = 324,
     T_CLASS = 325,
     T_INTERFACE = 326,
     T_ASPECT = 327,
     T_ENUM = 328,
     T_DELEGATE = 329,
     T_MIXIN = 330,
     T_FUNCTION = 331,
     T_STATIC = 332,
     T_ABSTRACT = 333,
     T_FINAL = 334,
     T_PRIVATE = 335,
     T_PROTECTED = 336,
     T_PUBLIC = 337,
     T_VAR = 338,
     T_NS_SEPARATOR = 339,
     T_BOGUS = 340,
     MEMBER = 341,
     UMINUS = 342,
     PRE = 343
   };

    };
    /// Token type.
    typedef token::yytokentype token_type;

    /// Build a parser object.
    Parser (Driver& driver_yyarg, Lexer& lexer_yyarg);
    virtual ~Parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

  private:
    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Generate an error message.
    /// \param state   the state where the error occurred.
    /// \param tok     the lookahead token.
    virtual std::string yysyntax_error_ (int yystate, int tok);

#if YYDEBUG
    /// \brief Report a symbol value on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    virtual void yy_symbol_value_print_ (int yytype,
					 const semantic_type* yyvaluep,
					 const location_type* yylocationp);
    /// \brief Report a symbol on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    virtual void yy_symbol_print_ (int yytype,
				   const semantic_type* yyvaluep,
				   const location_type* yylocationp);
#endif


    /// State numbers.
    typedef int state_type;
    /// State stack type.
    typedef stack<state_type>    state_stack_type;
    /// Semantic value stack type.
    typedef stack<semantic_type> semantic_stack_type;
    /// location stack type.
    typedef stack<location_type> location_stack_type;

    /// The state stack.
    state_stack_type yystate_stack_;
    /// The semantic value stack.
    semantic_stack_type yysemantic_stack_;
    /// The location stack.
    location_stack_type yylocation_stack_;

    /// Internal symbol numbers.
    typedef unsigned char token_number_type;
    /* Tables.  */
    /// For a state, the index in \a yytable_ of its portion.
    static const signed char yypact_[];
    static const signed char yypact_ninf_;

    /// For a state, default rule to reduce.
    /// Unless\a  yytable_ specifies something else to do.
    /// Zero means the default is an error.
    static const unsigned char yydefact_[];

    static const signed char yypgoto_[];
    static const signed char yydefgoto_[];

    /// What to do in a state.
    /// \a yytable_[yypact_[s]]: what to do in state \a s.
    /// - if positive, shift that token.
    /// - if negative, reduce the rule which number is the opposite.
    /// - if zero, do what YYDEFACT says.
    static const unsigned char yytable_[];
    static const signed char yytable_ninf_;

    static const signed char yycheck_[];

    /// For a state, its accessing symbol.
    static const unsigned char yystos_[];

    /// For a rule, its LHS.
    static const unsigned char yyr1_[];
    /// For a rule, its RHS length.
    static const unsigned char yyr2_[];

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#endif

#if YYERROR_VERBOSE
    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    virtual std::string yytnamerr_ (const char *n);
#endif

#if YYDEBUG
    /// A type to store symbol numbers and -1.
    typedef signed char rhs_number_type;
    /// A `-1'-separated list of the rules' RHS.
    static const rhs_number_type yyrhs_[];
    /// For each rule, the index of the first RHS symbol in \a yyrhs_.
    static const unsigned char yyprhs_[];
    /// For each rule, its source line number.
    static const unsigned char yyrline_[];
    /// For each scanner token number, its symbol number.
    static const unsigned short int yytoken_number_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    /* Debugging.  */
    int yydebug_;
    std::ostream* yycdebug_;
#endif

    /// Convert a scanner token number \a t to a symbol number.
    token_number_type yytranslate_ (int t);

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg        Why this token is reclaimed.
    /// \param yytype       The symbol type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    inline void yydestruct_ (const char* yymsg,
			     int yytype,
			     semantic_type* yyvaluep,
			     location_type* yylocationp);

    /// Pop \a n symbols the three stacks.
    inline void yypop_ (unsigned int n = 1);

    /* Constants.  */
    static const int yyeof_;
    /* LAST_ -- Last index in TABLE_.  */
    static const int yylast_;
    static const int yynnts_;
    static const int yyempty_;
    static const int yyfinal_;
    static const int yyterror_;
    static const int yyerrcode_;
    static const int yyntokens_;
    static const unsigned int yyuser_token_number_max_;
    static const token_number_type yyundef_token_;

    /* User arguments.  */
    Driver& driver;
    Lexer& lexer;
  };

/* Line 35 of lalr1.cc  */
#line 4 "/home/alurin/projects/kiwi/sources/modules/kiwi-core/Script/Parser.ypp"
} } // kiwi::script

/* Line 35 of lalr1.cc  */
#line 425 "Parser.tab.hpp"



#endif /* ! defined PARSER_HEADER_H */
