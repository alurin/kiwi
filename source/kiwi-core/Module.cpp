#include "kiwi/Context.hpp"
#include "kiwi/Module.hpp"
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

typedef void    (*VoidMainPoint)();
typedef int32_t (*ReturnMainPoint)();

Module::Module(const Identifier& name, const ContextRef& context)
: m_name(name), m_context(context), m_module(0), m_engine(0)
{
    m_module = new llvm::Module(name, context->getContext());
    m_engine = llvm::EngineBuilder(m_module).create();

    if (name != Identifier("system")) {
        m_module->addLibrary("system");
    }
}

ModuleRef Module::create(const Identifier& name, const ContextRef& ref)
{
    ModuleRef module = ModuleRef(new Module(name, ref));
    return module;
}

void Module::includeFile(const Path& filename)
{
    ContextRef context = getContext();
    lang::Driver driver(context);
    if (driver.parseFile(filename)) {

        TypeRef type = Type::create(shared_from_this());

        /// @todo build examples
        for (std::vector<lang::FunctionNode*>::const_iterator i = driver.func_begin(); i != driver.func_end(); ++i)
        {
            (*i)->generate(type);
        }

        /// @todo build examples
        for (std::vector<lang::FunctionNode*>::const_iterator i = driver.func_begin(); i != driver.func_end(); ++i)
        {
            (*i)->emit(type);
        }
    }
}

// Build module
/// @todo Constant propagation pass not worked
void Module::build()
{
    llvm::FunctionPassManager   funcManager(m_module);
    llvm::PassManager           moduleManager;

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
void Module::dump()
{
    m_module->dump();
}

// Run module main function
int32_t Module::run()
{
    llvm::Function* mainFunc = m_module->getFunction("main");

    if (mainFunc) {
        // JIT the function, returning a function pointer.
        void *pointFunc = m_engine->getPointerToFunction(mainFunc);

        if (mainFunc->empty()) {
            throw "Main function is empty";
        } else if (!mainFunc->arg_empty()) {
            throw "Main function has arguments";
        } else if (mainFunc->getReturnType()->isVoidTy()) {
            VoidMainPoint main = reinterpret_cast<VoidMainPoint>(reinterpret_cast<intptr_t>(pointFunc));
            main();
            return 0;
        } else if (mainFunc->getReturnType()->isIntegerTy(32)) {
            ReturnMainPoint main = reinterpret_cast<ReturnMainPoint>(reinterpret_cast<intptr_t>(pointFunc));
            return main();
        }

        throw "Main function has unsupported return type";
    }

    throw "Main function is not found";
}