/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "ContextImpl.hpp"
#include "kiwi/Context.hpp"
#include "kiwi/Module.hpp"
#include "RuntimeModule.hpp"
#include <llvm/LLVMContext.h>

using namespace kiwi;

ContextImpl::ContextImpl()
: runtime(0), boolTy(0), int32Ty(0), voidTy(0), charTy(0), stringTy(0) {
}

Context::Context()
: m_context(0), m_metadata(new ContextImpl()), m_optimizationLevel(1), m_debug(false) {
}

Context::~Context() {
    for (std::vector<Module*>::iterator i = m_metadata->modules.begin(); i != m_metadata->modules.end(); ++i) {
        Module* module = *i;
        delete module;
    }
    delete m_metadata;
    delete m_context;
}

Context* Context::create() {
    Context* context = new Context();
    context->initializate();
    return context;
}

void Context::initializate() {
    m_context            = new llvm::LLVMContext();
    m_metadata->runtime  = Module::create("system", this);
    m_metadata->boolTy   = BoolType::create(m_metadata->runtime);
    m_metadata->int32Ty  = IntType::create(m_metadata->runtime, 32, false);
    m_metadata->voidTy   = VoidType::create(m_metadata->runtime);
    m_metadata->charTy   = CharType::create(m_metadata->runtime);
    m_metadata->stringTy = StringType::create(m_metadata->runtime);

    initRuntimeModule(m_metadata->runtime);
}
