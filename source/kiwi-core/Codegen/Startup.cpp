#include "kiwi/Module.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/DerivedTypes.hpp"
#include "kiwi/Codegen/Startup.hpp"
#include "kiwi/Codegen/Method.hpp"
#include "kiwi/Codegen/Object.hpp"
#include "kiwi/Support/Cast.hpp"
#include <llvm/InstrTypes.h>
#include <llvm/Instructions.h>
#include <llvm/Constants.h>
#include <llvm/Function.h>
#include <llvm/Module.h>
#include <llvm/ADT/ArrayRef.h>
#include <assert.h>

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
            llvm::ReturnInst::Create(context, block);
        }
    }
    return startFunc;
}

llvm::Function* StartupEmitter::emitNative() {
/*    Module* module   = m_method->getOwnerType()->getModule();
    ObjectType* self = dyn_cast<ObjectType>(m_method->getOwnerType());
    if (!self) {
        throw "Self type must be Object type";
    }
    llvm::Module* m_module = module->getModule();

    /// create startup function
    llvm::FunctionType* startType = llvm::FunctionType::get(llvm::IntegerType::get(m_module->getContext(), 32), false);
    llvm::FunctionType* dummpType = llvm::FunctionType::get(llvm::Type::getVoidTy(m_module->getContext()), false);
    llvm::Function* startFunc     = llvm::dyn_cast<llvm::Function>(m_module->getOrInsertFunction("__start", startType));
    llvm::Function* startupFunc   = llvm::dyn_cast<llvm::Function>(m_module->getOrInsertFunction("kiwi_startup", dummpType));
    llvm::Function* shutdownFunc  = llvm::dyn_cast<llvm::Function>(m_module->getOrInsertFunction("kiwi_shutdown", dummpType));
    if (startup->empty()) {
        llvm::Function* func     = MethodEmitter(m_method).emitDefinition();
        llvm::FunctionType* type = func->getType();
        llvm::BasicBlock* block  = new llvm::BasicBlock("entry", startFunc);
        llvm::Type* resultType   = type->getReturnType();

        std::vector<llvm::Value*> args;
        llvm::Value* thisValue = ObjectEmitter(self).emitNew();

        // call kiwi_startup
        llvm::CallInst::Create(startFunc, llvm::makeArrayRef(args), "", block);

        // call main
        args.push_back(thisValue);
        llvm::Value* call = llvm::CallInst::Create(mainFunc, llvm::makeArrayRef(args), "", block);

        // call kiwi_shutdown
        args.clean();
        llvm::CallInst::Create(shutdownFunc, llvm::makeArrayRef(args), "", block);

        if (resultType->isIntegerTy(32)) {
            new llvm::ReturnInst(call, block);
        } else {
            new llvm::ReturnInst(block);
        }
    }*/
}
