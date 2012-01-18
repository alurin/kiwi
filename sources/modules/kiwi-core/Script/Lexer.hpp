/*
 *******************************************************************************
 *   Copyright (C) 2010 Kiwi Developers Group
 *   All Rights Reserved.
 *******************************************************************************
 */

/**
 * @file
 * @brief File containts extends base generation lexer by Flex
 */
#ifndef KIWI_SCRIPT_LEXER_HPP_INCLUDED
#define KIWI_SCRIPT_LEXER_HPP_INCLUDED

#include "kiwi/Config.hpp"

// Flex expects the signature of yylex to be defined in the macro YY_DECL, and
// the C++ parser expects it to be declared. We can factor both as follows.
#ifndef YY_DECL
#define YY_DECL                                        \
   kiwi::script::Parser::token_type                    \
      kiwi::script::Lexer::lex(                        \
        kiwi::script::Parser::semantic_type* yylval,   \
        kiwi::script::Parser::location_type* yylloc    \
    )
#endif

#ifndef __FLEX_LEXER_H
#define yyFlexLexer KiwiFlexLexer
#include "FlexLexer.h"
#undef yyFlexLexer
#endif

#include <istream>
#include "Driver.hpp"
#include "Parser.tab.hpp"

namespace kiwi {
    namespace script {
        /**
         * Класс лексического анализа Kiwi
         * @since 0.1
         */
        class KIWI_LOCAL Lexer : public KiwiFlexLexer {
        protected:
            /**
             * Драйвер анализатора
             * @since 0.1
             */
            DriverImpl& driver;

            /**
             * Поток для лексического анализа
             * @since 0.1
             */
            std::istream *stream;

        public:
            /**
             * @todo Добавить документацию
             * @since 0.1
             */
            Lexer(DriverImpl& driver, std::istream* stream);

            Parser::token_type lex(
                                   Parser::semantic_type* yylval,
                                   Parser::location_type* yylloc
                                   );
        };

    }
}

#endif	/* __KIWI_SOURCE_DRIVER_LEXER_HPP */
