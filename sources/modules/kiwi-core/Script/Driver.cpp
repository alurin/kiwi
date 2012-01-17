/*
 *******************************************************************************
 *   Copyright (C) 2010-2011 Kiwi Developers Group
 *   All Rights Reserved.
 *******************************************************************************
 */
/**
 * @file
 * @brief File containts extends base generation lexer by Flex
 */
#include "Driver.hpp"
#include "Lexer.hpp"
#include "kiwi/Engine.hpp"

#include <fstream>
#include <sstream>

using namespace kiwi;
using namespace kiwi::script;

Driver::Driver(Engine* engine) : m_lexer(0) {
}

Driver::~Driver() {
}

Path Driver::getStreamNameUTF8() const {
    if (m_streamNameUTF8.size() == 0) {
        m_streamNameUTF8 = m_streamName.toUTF8String(m_streamNameUTF8);
    }
    return m_streamNameUTF8;
}

bool Driver::parseStream(std::istream& in, const String& sname) {
    m_streamName = sname;

    Lexer scanner(*this, &in);
    scanner.set_debug(isDebug());
    this->m_lexer = &scanner;

    Parser parser(*this, scanner);
    parser.set_debug_level(isDebug());
    return (parser.parse() == 0);
}

bool Driver::parseFile(const Path& filename) {
    const char* sname = filename.c_str();
    std::ifstream in(sname);
    if (!in.good()) return false;
    return parseStream(in, sname);
}

bool Driver::parseString(const std::string &input, const String& sname) {
    std::istringstream iss(input);
    return parseStream(iss, sname);
}