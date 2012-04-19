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

Module::Module(const Identifier& name, const ContextRef& context)
: m_name(name), m_context(context), m_module(0)
{
    m_module = new llvm::Module(name, context->getContext());

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
    lang::Driver driver(m_context.lock());
    if (driver.parseFile(filename)) {
        /// @todo build examples
        for (std::vector<lang::FunctionNode*>::const_iterator i = driver.func_begin(); i != driver.func_end(); ++i)
        {
            (*i)->generate(shared_from_this());
        }
    }
}

typedef void    (*VoidMainPoint)();
typedef int32_t (*ReturnMainPoint)();

#include <iostream>

int32_t Module::run()
{
    llvm::ExecutionEngine* engine = llvm::EngineBuilder(m_module).create();
    llvm::Function*      mainFunc = m_module->getFunction("main");

    m_module->dump();

    if (mainFunc) {
        /// @todo replace to optim level check
        if (false) {
            llvm::FunctionPassManager funcManager(m_module);

            // Set up the optimizer pipeline.  Start with registering info about how the
            // target lays out data structures.
            funcManager.add(new llvm::TargetData(*engine->getTargetData()));
            // Provide basic AliasAnalysis support for GVN.
            funcManager.add(llvm::createBasicAliasAnalysisPass());
            // Do simple "peephole" optimizations and bit-twiddling optzns.
            funcManager.add(llvm::createInstructionCombiningPass());
            // Reassociate expressions.
            funcManager.add(llvm::createReassociatePass());
            // Eliminate Common SubExpressions.
            funcManager.add(llvm::createGVNPass());
            // Simplify the control flow graph (deleting unreachable blocks, etc).
            funcManager.add(llvm::createCFGSimplificationPass());

            funcManager.add(llvm::createConstantPropagationPass());
            funcManager.add(llvm::createDeadCodeEliminationPass());
            funcManager.add(llvm::createDeadStoreEliminationPass());

            funcManager.doInitialization();

            // Set the global so the code gen can use this.
            for (llvm::Module::iterator func = m_module->begin(); func != m_module->end(); ++func) {
                funcManager.run(*func);
            }

            llvm::PassManager moduleManager;

            moduleManager.add(llvm::createConstantMergePass());

            moduleManager.add(llvm::createGlobalOptimizerPass());

            moduleManager.add(llvm::createStripDeadPrototypesPass());

            moduleManager.add(llvm::createMergeFunctionsPass());
            moduleManager.run(*m_module);

            // dump module
            m_module->dump();


            // Set the global so the code gen can use this.
            //for (llvm::Module::iterator func = m_module->begin(); func != m_module->end(); ++func) {
            //  engine->getPointerToFunction(func);
            //}
        }

        // JIT the function, returning a function pointer.
        void *pointFunc = engine->getPointerToFunction(mainFunc);

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