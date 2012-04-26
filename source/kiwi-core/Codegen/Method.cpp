/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "Method.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Type.hpp"
#include <llvm/Function.h>
#include <llvm/Instructions.h>
#include "kiwi/assert.hpp"

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
        Identifier fullName;

        fullName = m_method->getOwnerType()->getName() + "::" + m_method->getName();

        Module* module = m_method->getOwnerType()->getModule();
        llvm::FunctionType* funcType = emitType();
        llvm::Function* func = llvm::Function::Create(
            funcType,
            llvm::GlobalValue::ExternalLinkage,
            fullName,
            module->getModule()
        );
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
