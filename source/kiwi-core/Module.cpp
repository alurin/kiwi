#include "ContextImpl.hpp"
#include "ModuleImpl.hpp"
#include "kiwi/Context.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Codegen/Startup.hpp"
#include "lang/Driver.hpp"
#include "lang/FunctionNode.hpp"
#include "llvm/Analysis/Passes.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/JIT.h"
#include "llvm/Function.h"
#include "llvm/Module.h"
#include "llvm/PassManager.h"
#include "llvm/Target/TargetData.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/IPO.h"
#include "llvm/Type.h"

using namespace kiwi;
using namespace kiwi::codegen;

typedef int32_t (*ReturnMainPoint)();

Module::Module(const Identifier& name, Context* context)
: m_name(name), m_context(context), m_module(0), m_engine(0), m_metadata(new ModuleImpl()) {
    m_context->getMetadata()->modules.push_back(this);
    m_module = new llvm::Module(name, context->getContext());
    m_engine = llvm::EngineBuilder(m_module).create();

    if (name != Identifier("system")) {
        m_module->addLibrary("system");
    }
}

Module::~Module() {
    for (std::vector<Type*>::iterator i = m_metadata->types.begin(); i != m_metadata->types.end(); ++i) {
        Type* type = *i;
        delete type;
    }
    delete m_metadata;
    delete m_module;
}

Module* Module::create(const Identifier& name, Context* ref) {
    Module* module = new Module(name, ref);
    return module;
}

Method* Module::getMainMethod() {
    return m_metadata->mainMethod;
}

void Module::includeFile(const Path& filename) {
    Context* context = getContext();
    ObjectType* type = ObjectType::create(this);
    lang::Driver driver(context, type);
    if (driver.parseFile(filename)) {
        for (std::vector<lang::FieldNode*>::const_iterator i = driver.field_begin(); i != driver.field_end(); ++i) {
            (*i)->generate(type);
        }

        /// Emit type structure
        type->emit();

        for (std::vector<lang::FunctionNode*>::const_iterator i = driver.func_begin(); i != driver.func_end(); ++i) {
            (*i)->generate(type);
            if ((*i)->getName() == "main") {
                m_metadata->mainMethod = (*i)->getMethod();
            }
        }

        /// @todo build examples
        for (std::vector<lang::FunctionNode*>::const_iterator i = driver.func_begin(); i != driver.func_end(); ++i) {
            (*i)->emit(type);
        }
    }
}

// Build module
/// @todo Constant propagation pass not worked
void Module::build() {
    llvm::FunctionPassManager funcManager(m_module);
    llvm::PassManager moduleManager;

    /// create startup function
    Method* mainMethod = getMainMethod();
    if (mainMethod) {
        StartupEmitter emitter(mainMethod);
        emitter.emitJIT();
    }


    // Set up the optimizer pipeline.  Start with registering info about how the
    // target lays out data structures.
    funcManager.add(new llvm::TargetData(*m_engine->getTargetData()));

    int8_t level = getContext()->getOptimizationLevel();

    // First level optimizations
    if (level > 0) {
        // Do simple "peephole" optimizations and bit-twiddling optzns.
        funcManager.add(llvm::createInstructionCombiningPass());
        // Provide basic AliasAnalysis support for GVN.
        funcManager.add(llvm::createBasicAliasAnalysisPass());
    }

    // Second level optimizations
    if (level > 1) {
        // Reassociate expressions.
        funcManager.add(llvm::createReassociatePass());
        // Eliminate Common SubExpressions.
        funcManager.add(llvm::createGVNPass());
        // Simplify the control flow graph (deleting unreachable blocks, etc).
        funcManager.add(llvm::createCFGSimplificationPass());
        funcManager.add(llvm::createConstantPropagationPass());
    }

    // Third level optimizations
    if (level > 2) {
        funcManager.add(llvm::createDeadCodeEliminationPass());
        funcManager.add(llvm::createDeadStoreEliminationPass());
        moduleManager.add(llvm::createGlobalOptimizerPass());
        moduleManager.add(llvm::createStripDeadPrototypesPass());
        moduleManager.add(llvm::createConstantMergePass());
    }

    /// run optimizations passes for all functions in module
    funcManager.doInitialization();
    for (llvm::Module::iterator func = m_module->begin(); func != m_module->end(); ++func) {
        funcManager.run(*func);
    }
    /// run module optimizations passes
    moduleManager.run(*m_module);
}

// Dump module
void Module::dump() {
    m_module->dump();
}

// Run module main function
int32_t Module::run() {
    // JIT the function, returning a function pointer.
    llvm::Function* mainFunc = m_module->getFunction("__start");
    if (mainFunc) {
        void *pointFunc          = m_engine->getPointerToFunction(mainFunc);
        ReturnMainPoint main     = reinterpret_cast<ReturnMainPoint>(reinterpret_cast<intptr_t>(pointFunc));
        return main();
    }

    throw "Not found main function";
}
