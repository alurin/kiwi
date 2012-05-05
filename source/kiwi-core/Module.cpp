/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "ContextImpl.hpp"
#include "ModuleImpl.hpp"
#include "Codegen/Builder.hpp"
#include "Lang/Driver.hpp"
#include "kiwi/Context.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Exception.hpp"
#include "kiwi/Support/Cast.hpp"
#include "llvm/Module.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/PassManager.h"

using namespace kiwi;

ModuleImpl::ModuleImpl() : m_backendModule(0) {
}

Module::Module(const Identifier& name, ContextPtr context)
: m_name(name), m_context(context), m_metadata(new ModuleImpl()) {
    ContextImpl* meta = context->getMetadata();
    m_metadata->m_backendModule = new llvm::Module(name, meta->getBackendContext());
    if (llvm::ExecutionEngine* engine = meta->getBackendEngine()) {
        engine->addModule(m_metadata->m_backendModule);
    }
}

Module::~Module() {
    delete m_metadata;
}

ModulePtr Module::create(const Identifier& name, ContextPtr context) {
    ModulePtr module = ModulePtr(new Module(name, context));
    context->getMetadata()->registerModule(module);
    return module;
}

bool Module::includeFile(const Path& filename) {
    ContextPtr context = getContext();
    ObjectPtr type = dyn_cast<ObjectType>(this->find("Script"));
    if (!type) {
        type = ObjectType::create(shared_from_this(), "Script");
    }
    lang::DriverRef driver(context, type);
    if (driver.parseFile(filename)) {
        if (!m_metadata->mainMethod && driver.getMainMethod()) {
            m_metadata->mainMethod = driver.getMainMethod();
        }
        return true;
    }
    return false;
}

// Build module
/// @todo Constant propagation pass not worked
void Module::build() {
    /// create startup function
    MethodPtr mainMethod = getMainMethod();
    if (mainMethod) {
        FunctionBuilder builder(mainMethod);
        builder.createJITStartupPoint();
    }

    // run function optimizations passes
    ContextImpl* meta    = getContext()->getMetadata();
    llvm::Module& module = *m_metadata->getBackendModule();
    for (llvm::Module::iterator func = module.begin(); func != module.end(); ++func) {
        meta->getBackendFunctionPassManager()->run(*func);
    }

    /// run module optimizations passes
    meta->getBackendModulePassManager()->run(module);
}

// Dump module
void Module::dump() {
    getMetadata()->getBackendModule()->dump();
}

// return main method from module
MethodPtr Module::getMainMethod() const {
    return m_metadata->mainMethod;
}

// register type with alias
void ModuleImpl::registerType(TypePtr type, const Identifier& name) {
    m_types.insert(type);
    m_names.insert(std::make_pair(name, type));
}

/// create alias for type
void ModuleImpl::registerType(TypePtr type) {
    m_types.insert(type);
}

TypePtr Module::find(const Identifier& name) const {
    std::map<Identifier, TypePtr>::const_iterator result = m_metadata->m_names.find(name);
    if (result == m_metadata->m_names.end()) {
        return TypePtr();
    }
    return result->second;
}
