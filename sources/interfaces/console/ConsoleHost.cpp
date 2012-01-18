#include "ConsoleHost.hpp"

using namespace kiwi;
using namespace kiwi::io;
using namespace kiwi::console;

ConsoleHost::ConsoleHost() {
    m_inputStream  = InputStream::createFromFile(stdin);
    m_outputStream = OutputStream::createFromFile(stdout);
    m_errorStream  = OutputStream::createFromFile(stderr);
}