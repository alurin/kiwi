/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#include "ConsoleHost.hpp"

using namespace kiwi;
using namespace kiwi::io;
using namespace kiwi::console;

ConsoleHost::ConsoleHost() {
    m_inputStream  = InputStream::createFromFile(stdin);
    m_outputStream = OutputStream::createFromFile(stdout);
    m_errorStream  = OutputStream::createFromFile(stderr);
}

ConsoleHost::~ConsoleHost() {
    delete m_inputStream;
    delete m_outputStream;
    delete m_errorStream;
}