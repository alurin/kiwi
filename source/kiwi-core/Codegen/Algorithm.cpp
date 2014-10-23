/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#include <llvm/IR/Instructions.h>

#include "kiwi/Exception.hpp"
#include "Algorithm.hpp"
#include "LlvmEmitter.hpp"
#include "llvm/IR/Type.h"
#include "llvm/IR/Module.h"
#include <llvm/IR/IRBuilder.h>

using namespace kiwi;
using namespace kiwi::codegen;

BlockBuilder kiwi::llvmDumpValue(BlockBuilder block, llvm::Value* value, String text) {
    // collect arguments
    std::vector<llvm::Value*> args;
    llvm::Function* dump_function = 0;

    llvm::LLVMContext& context = block.getContext();
    llvm::Module* module = block.getModule();

    llvm::Type* voidType   = llvm::Type::getVoidTy(context);
    llvm::Type* lengthType = llvm::IntegerType::get(context, 32);
    llvm::Type* bufferType = llvm::IntegerType::get(context, 16)->getPointerTo();

    if (value->getType()->isPointerTy()) {
        llvm::Type* pointerType = llvm::IntegerType::get(context, 8)->getPointerTo();
        dump_function = llvm::dyn_cast<llvm::Function>(module->getOrInsertFunction("kiwi_debug_pointer", voidType, pointerType, bufferType, lengthType, NULL));
        args.push_back(new llvm::BitCastInst(value, pointerType, "", block.getBlock()));
    } else if (value->getType()->isIntegerTy()) {
        llvm::Type* integerType = llvm::IntegerType::get(context, 64);
        dump_function = llvm::dyn_cast<llvm::Function>(module->getOrInsertFunction("kiwi_debug_integer", voidType, integerType, bufferType, lengthType, NULL));
        args.push_back(new llvm::ZExtInst(value, integerType, "", block.getBlock()));
    } else {
        value->dump();
        BOOST_THROW_EXCEPTION(Exception() << exception_message("Not implemented"));
    }

    LlvmStringEmitter string;
    block = string.emit(block, block.createStringConst(text));
    args.push_back(string.getBufferValue());
    args.push_back(string.getLengthValue());

    llvm::CallInst::Create(dump_function, makeArrayRef(args), "", block.getBlock());
    return block;
}
