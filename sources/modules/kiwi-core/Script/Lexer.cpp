/*
 *******************************************************************************
 *   Copyright (C) 2010 Kiwi Developers Group
 *   All Rights Reserved.
 *******************************************************************************
 */
/**
 * @file
 * @brief
 */
#include "Lexer.hpp"

using namespace kiwi;
using namespace kiwi::script;

Lexer::Lexer(Driver& driver, std::istream* stream)
: KiwiFlexLexer(stream), driver(driver)
{
	
}