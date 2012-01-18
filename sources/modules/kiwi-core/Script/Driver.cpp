/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#include "Driver.hpp"
#include "Lexer.hpp"
#include "kiwi/Engine.hpp"
#include "kiwi/Script/Driver.hpp"

#include <fstream>
#include <sstream>

using namespace kiwi;
using namespace kiwi::script;

bool Driver::s_debug = false;

DriverImpl::DriverImpl(Engine* engine) : m_lexer(0) {
}

DriverImpl::~DriverImpl() {
}

Path DriverImpl::getStreamNameUTF8() const {
    if (m_streamNameUTF8.size() == 0) {
        m_streamNameUTF8 = m_streamName.toUTF8String(m_streamNameUTF8);
    }
    return m_streamNameUTF8;
}

/// @todo exception if error in parser or lexer
RootNode* DriverImpl::parseStream(std::istream& in, const String& sname) {
    m_streamName = sname;

    Lexer scanner(*this, &in);
    scanner.set_debug(Driver::isDebugMode());
    this->m_lexer = &scanner;

    Parser parser(*this, scanner);
    parser.set_debug_level(Driver::isDebugMode());
    (parser.parse() == 0);
    return 0;
}

RootNode* Driver::parseStream(Engine* engine, std::istream& in, const String& sname) {
    DriverImpl impl(engine);
    return impl.parseStream(in, sname);
}

/// @todo exception if file not found
RootNode* Driver::parseFile(Engine* engine, const Path& filename) {
    const char* sname = filename.c_str();
    std::ifstream in(sname);
    if (!in.good()) return 0;
    return parseStream(engine, in, sname);
}

RootNode* Driver::parseString(Engine* engine, const std::string &input, const String& sname) {
    std::istringstream iss(input);
    return parseStream(engine, iss, sname);
}