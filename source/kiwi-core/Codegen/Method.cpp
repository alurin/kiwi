#include "kiwi/Codegen/Method.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Type.hpp"
#include <llvm/Type.h>
#include <llvm/Function.h>
#include <llvm/Instructions.h>
#include <llvm/ADT/ArrayRef.h>
#include <vector>

using namespace kiwi;
using namespace kiwi::codegen;

MethodEmitter::MethodEmitter(Method* method)
: m_method(method) { }


// emit method type
llvm::FunctionType* MethodEmitter::emitType() {
    Module* module = m_method->getOwnerType()->getModule();

    // collect arguments types
    std::vector<llvm::Type*> args;
    llvm::Type* resultType = m_method->getReturnType()->getVarType();

    // collect implicit arguments
    if (m_method->isStatic()) {
        throw "Static methods not implemented";
    } else {
        /// @todo remove pointer to
        llvm::Type* argType = m_method->getOwnerType()->getVarType();
        args.push_back(argType->getPointerTo());
    }

    // collect explicit arguments
    for (std::vector<Argument*>::const_iterator i = m_method->begin(); i != m_method->end(); ++i) {
        Argument* arg = *i;
        args.push_back(arg->getType()->getVarType());
    }

    // generate type and yeld
    return llvm::FunctionType::get(resultType, llvm::makeArrayRef(args), false);
}

// emit method definition
llvm::Function* MethodEmitter::emitDefinition() {
    if (!m_method->getFunction()) {
        Module* module             = m_method->getOwnerType()->getModule();
        llvm::FunctionType* funcType = emitType();
        llvm::Function* func         = llvm::Function::Create(funcType, llvm::GlobalValue::ExternalLinkage, m_method->getName(), module->getModule());
        m_method->setFunction(func);

        std::vector<Identifier> argNames;
        // collect explicit arguments
        for (std::vector<Argument*>::const_iterator i = m_method->begin(); i != m_method->end(); ++i) {
            Argument* arg = *i;
            argNames.push_back(arg->getName());
        }

        // set argument name
        size_t j = 0;
        for (llvm::Function::arg_iterator i = func->arg_begin(); i != func->arg_end(); ++i, ++j) {
            if (j) {
                i->setName(argNames[j - 1]);
            } else {
                i->setName("this");
            }
        }
    }
    return m_method->getFunction();
}

// emit method call
ExpressionGen MethodEmitter::emitCall(const StatementGen& gen, const ExpressionGen& thisObject, const ArgumentList& args) {
    llvm::Function* func = emitDefinition();
    if (!func) {
        throw "Function implementation not found";
    }

    std::vector<llvm::Value*> largs;
    largs.push_back(thisObject.getValue());
    for (ArgumentList::const_iterator i = args.begin(); i != args.end(); ++i) {
        largs.push_back(i->getValue());
    }

     // return result of call
     llvm::Value* result = llvm::CallInst::Create(func, llvm::makeArrayRef(largs), "", gen.getBlock());
     return ExpressionGen(gen, m_method->getReturnType(), result);
}
