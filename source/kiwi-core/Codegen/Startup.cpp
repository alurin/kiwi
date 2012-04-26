/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "kiwi/Module.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/DerivedTypes.hpp"
#include "kiwi/Codegen/Startup.hpp"
#include "kiwi/Codegen/Method.hpp"
#include "kiwi/Codegen/Object.hpp"
#include "kiwi/Support/Cast.hpp"
#include <llvm/Instructions.h>
#include <llvm/Constants.h>
#include <llvm/Module.h>

using namespace kiwi;
using namespace kiwi::codegen;

StartupEmitter::StartupEmitter(Method* method)
: m_method(method) {
}

llvm::Function* StartupEmitter::emitJIT() {
    Module* module   = m_method->getOwnerType()->getModule();
    ObjectType* self = dyn_cast<ObjectType>(m_method->getOwnerType());
    if (!self) {
        throw "Self type must be Object type";
    }
    llvm::Module* m_module = module->getModule();
    llvm::LLVMContext& context = m_module->getContext();

    /// create startup function
    llvm::FunctionType* startType = llvm::FunctionType::get(llvm::IntegerType::get(context, 32), false);
    llvm::Function* startFunc     = llvm::dyn_cast<llvm::Function>(m_module->getOrInsertFunction("__start", startType));
    if (startFunc->empty()) {
        llvm::Function* func     = MethodEmitter(m_method).emitDefinition();
        llvm::FunctionType* type = llvm::dyn_cast<llvm::FunctionType>(func->getFunctionType());
        llvm::BasicBlock* block  = llvm::BasicBlock::Create(context, "entry", startFunc);
        llvm::Type* resultType   = type->getReturnType();

        std::vector<llvm::Value*> args;

        // generate this
        StatementGen gen(self, block);
        ExpressionGen thisValue = ObjectEmitter(self).emitNew(gen);

        // call main
        args.push_back(thisValue.getValue());
        llvm::Value* call = llvm::CallInst::Create(func, llvm::makeArrayRef(args), "", thisValue.getBlock());

        if (resultType->isIntegerTy(32)) {
            llvm::ReturnInst::Create(context, call, block);
        } else {
            llvm::APInt cst(32, 0, false);
            llvm::ConstantInt* zero = llvm::ConstantInt::get(gen.getContext(), cst);
            llvm::ReturnInst::Create(context, zero, block);
        }
    }
    return startFunc;
}

llvm::Function* StartupEmitter::emitNative() {
}
