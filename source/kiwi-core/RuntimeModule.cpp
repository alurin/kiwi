#include "kiwi/DerivedTypes.hpp"
#include "RuntimeModule.hpp"
#include <llvm/ADT/ArrayRef.h>
#include <llvm/Constants.h>
#include <llvm/Function.h>
#include <llvm/InstrTypes.h>
#include <llvm/Instructions.h>
#include <llvm/Module.h>

using namespace kiwi;

void kiwi::initRuntimeModule(Module* mod) {
    llvm::Module*       module = mod->getModule();
    llvm::LLVMContext& context = module->getContext();
    llvm::Type*       voidType = llvm::Type::getVoidTy(context);
    llvm::Type*        intType = llvm::IntegerType::get(context, 32);
    llvm::Type*       charType = llvm::IntegerType::get(context, 16);
    llvm::Type*       boolType = llvm::IntegerType::get(context, 1);
    llvm::Type*     bufferType = charType->getPointerTo();

    // llvm::Function* printInt    = llvm::dyn_cast<llvm::Function>(module->getOrInsertFunction("kiwi_print_integer", voidType, intType, NULL));
    // llvm::Function* printBool   = llvm::dyn_cast<llvm::Function>(module->getOrInsertFunction("kiwi_print_bool",    voidType, boolType, NULL));
    // llvm::Function* printChar   = llvm::dyn_cast<llvm::Function>(module->getOrInsertFunction("kiwi_print_char",    voidType, charType, NULL));
    // llvm::Function* printString = llvm::dyn_cast<llvm::Function>(module->getOrInsertFunction("kiwi_print_string",  voidType, bufferType, intType, NULL));
}
