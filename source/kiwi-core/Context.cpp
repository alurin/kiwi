#include "kiwi/Context.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/DerivedTypes.hpp"
#include <log4cxx/logger.h>
#include <log4cxx/level.h>
#include <log4cxx/consoleappender.h>
#include <log4cxx/patternlayout.h>
#include <llvm/LLVMContext.h>
#include "ContextMeta.hpp"

using namespace kiwi;

Context::Context()
: m_context(new llvm::LLVMContext()), m_meta(new ContextMeta())
{
    // Configure the logging mechanism
    log4cxx::LoggerPtr rootlogger = log4cxx::Logger::getRootLogger();
    rootlogger->addAppender(new log4cxx::ConsoleAppender(new log4cxx::PatternLayout("[%-5p] %m%n")));

    m_logger = rootlogger;
}

Context::~Context() {
    delete m_context;
    delete m_meta;
}

ContextRef Context::create()
{
    ContextRef ref = ContextRef(new Context());
    ref->initializate();
    return ref;
}

void Context::initializate()
{
    ModuleRef module = Module::create("system", shared_from_this());
    m_meta->boolTy   = BoolType::create(module);
    m_meta->int32Ty  = IntType::create(module, 32, false);
    m_meta->voidTy   = VoidType::create(module);
    m_meta->charTy   = CharType::create(module);
    m_meta->stringTy = StringType::create(module);
}