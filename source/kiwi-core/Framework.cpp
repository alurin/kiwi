#include "kiwi/Framework.hpp"

#include <log4cxx/logger.h>
#include <log4cxx/level.h>
#include <log4cxx/consoleappender.h>
#include <log4cxx/patternlayout.h>

#include <llvm/LLVMContext.h>

using namespace kiwi;

Framework::Framework()
: m_context(new llvm::LLVMContext())
{
    // Configure the logging mechanism
    log4cxx::LoggerPtr rootlogger = log4cxx::Logger::getRootLogger();
    rootlogger->addAppender(new log4cxx::ConsoleAppender(new log4cxx::PatternLayout("[%-5p] %m%n")));

    m_logger = rootlogger;
}

Framework::~Framework() {
    delete m_context;
}

FrameworkRef Framework::create()
{
    FrameworkRef ref = FrameworkRef(new Framework());
    return ref;
}
