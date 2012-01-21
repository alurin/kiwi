/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#include "Lexer.hpp"

using namespace kiwi;
using namespace kiwi::script;

Lexer::Lexer(DriverImpl& driver, std::istream* stream)
: KiwiFlexLexer(stream), driver(driver)
{
	
}