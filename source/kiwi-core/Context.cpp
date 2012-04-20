#include "kiwi/Context.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/DerivedTypes.hpp"
#include <log4cxx/logger.h>
#include <log4cxx/level.h>
#include <log4cxx/consoleappender.h>
#include "ContextMeta.hpp"
#include "llvm/Support/TargetSelect.h"
#include "RuntimeModule.hpp"
#include <llvm/LLVMContext.h>
#include <log4cxx/patternlayout.h>

using namespace kiwi;

Context::Context()
: m_context(0), m_meta(new ContextMeta()), m_optimizationLevel(1), m_debug(false)
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
    llvm::InitializeNativeTarget();
    m_context = new llvm::LLVMContext();

    ModuleRef module = Module::create("system", shared_from_this());
    m_meta->boolTy   = BoolType::create(module);
    m_meta->int32Ty  = IntType::create(module, 32, false);
    m_meta->voidTy   = VoidType::create(module);
    m_meta->charTy   = CharType::create(module);
    m_meta->stringTy = StringType::create(module);

    initRuntimeModule(module);
}