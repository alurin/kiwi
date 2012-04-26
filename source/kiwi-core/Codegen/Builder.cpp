/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "Builder.hpp"
#include "Emitter.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/DerivedTypes.hpp"
#include "kiwi/Support/Cast.hpp"
#include "llvm/Module.h"
#include "llvm/Function.h"
#include "llvm/BasicBlock.h"
#include "llvm/Instructions.h"
#include "llvm/Constants.h"
#include <llvm/Support/IRBuilder.h>
#include "kiwi/assert.hpp"

#define EMPTY_WHILE_WRAP(_stmt_) do { _stmt_ } while(0)

#define BUILDER_ASSERT() EMPTY_WHILE_WRAP( \
        kiwi_assert(m_nativeModule,  "Builder must have Kiwi module"); \
        kiwi_assert(m_nativeContext, "Builder must have Kiwi context"); \
        kiwi_assert(m_module,        "Builder must have LLVM module"); \
        kiwi_assert(m_context,       "Builder must have LLVM context"); \
    )

#define BUILDER_FUNCTION_ASSERT() EMPTY_WHILE_WRAP( \
        kiwi_assert(m_nativeCallable || m_func, "FunctionBuilder must have Kiwi callable or LLVM function"); \
        kiwi_assert(m_nativeOwner,    "FunctionBuilder must have Kiwi owner type"); \
    )

#define BUILDER_BLOCK_ASSERT() EMPTY_WHILE_WRAP( \
        kiwi_assert(getFunction(),  "BlockBuilder must have LLVM function");   \
        kiwi_assert(m_block, "BlockBuilder must have LLVM basic block"); \
        kiwi_assert(m_block->getParent() == getFunction(), "Builder must have block from the same function"); \
    )

#define BUILDER_VALUE_ASSERT() EMPTY_WHILE_WRAP( \
        kiwi_assert(m_value, "ValueBuilder must have LLVM value"); \
        kiwi_assert(m_type,  "ValueBuilder must have Kiwi type");   \
    )

using namespace kiwi;

//===--------------------------------------------------------------------------------------------------------------===//
//    Constructors and assignments
//===--------------------------------------------------------------------------------------------------------------===//
Builder::Builder(Module* module)
: m_nativeModule(module), m_nativeContext(0), m_module(0), m_context(0) {
    m_nativeContext = m_nativeModule->getContext();
    m_module        = m_nativeModule->getModule();
    m_context       = &m_module->getContext();
    BUILDER_ASSERT();
}

// Copy constructor
Builder::Builder(const Builder& builder)
: m_nativeModule(builder.m_nativeModule), m_nativeContext(0), m_module(0), m_context(0) {
    m_nativeContext = m_nativeModule->getContext();
    m_module        = m_nativeModule->getModule();
    m_context       = &m_module->getContext();
    BUILDER_ASSERT();
}

// Assigment
Builder& Builder::operator=(const Builder& builder) {
    if (this != &builder) {
        m_nativeModule  = builder.m_nativeModule;
        m_nativeContext = builder.m_nativeContext;
        m_module        = builder.m_module;
        m_context       = builder.m_context;
        BUILDER_ASSERT();
    }
    return *this;
}

// Constructor
FunctionBuilder::FunctionBuilder(Callable* analog)
: Builder(analog->getOwnerType()->getModule()), m_nativeCallable(analog)
, m_nativeOwner(analog->getOwnerType()) , m_func(0) {
    BUILDER_FUNCTION_ASSERT();
}

/// Constructor
FunctionBuilder::FunctionBuilder(Type* type, llvm::Function* func)
: Builder(type->getModule()), m_nativeCallable(0), m_nativeOwner(type), m_func(func) {
    BUILDER_FUNCTION_ASSERT();
}

// Copy constructor
FunctionBuilder::FunctionBuilder(const FunctionBuilder& builder)
: Builder(builder), m_func(builder.m_func), m_nativeCallable(builder.m_nativeCallable), m_nativeOwner(builder.m_nativeOwner) {
    BUILDER_FUNCTION_ASSERT();
}

// Assigment
FunctionBuilder& FunctionBuilder::operator=(const FunctionBuilder& builder) {
    if (this != &builder) {
        Builder::operator=(builder);
        m_nativeCallable = builder.m_nativeCallable;
        m_nativeOwner    = builder.m_nativeOwner;
        m_func           = builder.m_func;

        BUILDER_FUNCTION_ASSERT();
    }
    return *this;
}

// constructor
BlockBuilder::BlockBuilder(const FunctionBuilder& builder, llvm::BasicBlock* block)
: FunctionBuilder(builder), m_block(block) {
    BUILDER_BLOCK_ASSERT();
}

// Copy constructor
BlockBuilder::BlockBuilder(const BlockBuilder& builder)
: FunctionBuilder(builder), m_block(builder.m_block) {
    BUILDER_BLOCK_ASSERT();
}

// Assigment
BlockBuilder& BlockBuilder::operator=(const BlockBuilder& builder) {
    if (this != &builder) {
        FunctionBuilder::operator=(builder);
        m_block = builder.m_block;
        BUILDER_BLOCK_ASSERT();
    }
    return *this;
}

// constructor
ValueBuilder::ValueBuilder(const BlockBuilder& builder, llvm::Value* value, Type* type)
: BlockBuilder(builder), m_value(value), m_type(type) {
    BUILDER_VALUE_ASSERT();
}

// Copy constructor
ValueBuilder::ValueBuilder(const ValueBuilder& builder)
: BlockBuilder(builder), m_value(builder.m_value), m_type(builder.m_type) {
    BUILDER_VALUE_ASSERT();
}

// Assigment
ValueBuilder& ValueBuilder::operator=(const ValueBuilder& builder) {
    if (this != &builder) {
        FunctionBuilder::operator=(builder);
        m_value = builder.m_value;
        m_type  = builder.m_type;

        BUILDER_VALUE_ASSERT();
    }
    return *this;
}

//===--------------------------------------------------------------------------------------------------------------===//
//    Function builder methods
//===--------------------------------------------------------------------------------------------------------------===//

// emit method type
llvm::FunctionType* FunctionBuilder::getFunctionType() const {
    if (m_func) {
        return m_func->getFunctionType();
    }

    // collect arguments types
    std::vector<llvm::Type*> args;
    llvm::Type* returnType = m_nativeCallable->getReturnType()->getVarType();

    // collect explicit arguments
    for (std::vector<Argument*>::const_iterator i = m_nativeCallable->begin(); i != m_nativeCallable->end(); ++i) {
        Argument* arg = *i;
        args.push_back(arg->getType()->getVarType());
    }

    // generate type and yeld
    return llvm::FunctionType::get(returnType, llvm::makeArrayRef(args), false);
}

// emit method definition
llvm::Function* FunctionBuilder::getFunction() const {
    // generate function, if this is required
    if (!m_func) {
        kiwi_assert(m_nativeCallable, "Function and callable member not found");
        // check function implementation in method
        if (!m_nativeCallable->getFunction()) {
            llvm::FunctionType* funcType = getFunctionType();
            m_func = llvm::Function::Create(
                funcType, llvm::GlobalValue::ExternalLinkage, "", m_module
            );
            m_nativeCallable->setFunction(m_func);

            // set argument name
            size_t j = 0;
            for (llvm::Function::arg_iterator i = m_func->arg_begin(); i != m_func->arg_end(); ++i, ++j) {
                Argument* arg = m_nativeCallable->getArgument(j);
                if (j) {
                    i->setName(arg->getName());
                } else {
                    i->setName("this");
                }
            }
        } else {
            m_func = m_nativeCallable->getFunction();
        }
    }
    if (m_func && m_nativeCallable)
        kiwi_assert(m_func->arg_size() == m_nativeCallable->size(), "Argument in function must be actual");
    return m_func;
}

llvm::Function* FunctionBuilder::createJITStartupPoint() {
    ObjectType* self = dyn_cast<ObjectType>(m_nativeCallable->getOwnerType());
    if (!self) {
        throw "Self type must be Object type";
    }

    /// create startup function
    llvm::FunctionType* startType = llvm::FunctionType::get(llvm::IntegerType::get(*m_context, 32), false);
    llvm::Function* startFunc     = llvm::dyn_cast<llvm::Function>(m_module->getOrInsertFunction("__start", startType));
    if (startFunc->empty()) {
        FunctionBuilder builder(self, startFunc);

        llvm::Function* func     = getFunction();
        llvm::FunctionType* type = func->getFunctionType();
        llvm::Type* returnType   = type->getReturnType();

        BlockBuilder block = builder.createBlock("start");

        // generate this
        ValueBuilder thisValue = block.createNew(self);

        // call main
        std::vector<ValueBuilder> args;
        args.push_back(thisValue);
        ValueBuilder result = thisValue.createCall(getNativeCallable(), args);
        if (returnType->isIntegerTy(32)) {
            llvm::ReturnInst::Create(*m_context, result.getValue(), block.getBlock());
        } else {
            llvm::APInt cst(32, 0, false);
            llvm::ConstantInt* zero = llvm::ConstantInt::get(*m_context, cst);
            llvm::ReturnInst::Create(*m_context, zero, block.getBlock());
        }
    }
    return startFunc;
}

BlockBuilder FunctionBuilder::createBlock(const Identifier& name) {
    kiwi_assert(getFunction(), "Function is not defined");
    llvm::BasicBlock* block = llvm::BasicBlock::Create(*m_context, name, getFunction());
    return BlockBuilder(*this, block);
}

//===--------------------------------------------------------------------------------------------------------------===//
//    Block builder methods
//===--------------------------------------------------------------------------------------------------------------===//
void BlockBuilder::createTrailReturn() {
    if (!m_block->getTerminator()) {
        llvm::Type* returnType = getFunctionType()->getReturnType();
        if (returnType->isVoidTy()) {
            llvm::ReturnInst::Create(*m_context, m_block);
        } else {
            llvm::Value* result = llvm::Constant::getNullValue(returnType);
            llvm::ReturnInst::Create(*m_context, result, m_block);
        }
    }
}

/// Create void return
void BlockBuilder::createReturn() {
    /// @todo check equals of return type
    llvm::ReturnInst::Create(*m_context, m_block);
}

/// Create return result of callable
void BlockBuilder::createReturn(ValueBuilder value) {
    llvm::ReturnInst::Create(*m_context, value.getValue(), m_block);
}

// Allocate memory in stack for mutable varaible
ValueBuilder BlockBuilder::createVariable(const Identifier& name, Type* type, bool autoInit) {
    llvm::Type* analog = type->getVarType();
    llvm::AllocaInst* variable = new llvm::AllocaInst(analog, name, m_block);
    if (autoInit) {
        llvm::Value* null = llvm::Constant::getNullValue(type->getVarType());
        new llvm::StoreInst(null, variable, m_block);
    }
    return ValueBuilder(*this, variable, type);
}

/// Create store in mutable variable
ValueBuilder BlockBuilder::createStore(ValueBuilder variable, ValueBuilder value) {
    if (variable.getType() == value.getType()) {
        llvm::StoreInst* inst = new llvm::StoreInst(value.getValue(), variable.getValue(), m_block);
        return ValueBuilder(*this, value.getValue(), value.getType());
    }
    throw "Unknown cast";
}

/// Create load from mutable variable
ValueBuilder BlockBuilder::createLoad(ValueBuilder variable) {
    llvm::LoadInst* inst = new llvm::LoadInst(variable.getValue(), "", m_block);
    return ValueBuilder(*this, inst, variable.getType());
}

// Emit constants
ValueBuilder BlockBuilder::createIntConst(int32_t value) {
    llvm::ConstantInt* result = llvm::ConstantInt::get(*m_context, llvm::APInt(32, value, false));
    return ValueBuilder(*this, result, IntType::get32(getNativeContext()));
}

// Emit constants
ValueBuilder BlockBuilder::createBoolConst(bool value) {
    llvm::ConstantInt* result = llvm::ConstantInt::get(*m_context, llvm::APInt(1, value, false));
    return ValueBuilder(*this, result, BoolType::get(getNativeContext()));
}

// Emit constants
ValueBuilder BlockBuilder::createCharConst(UChar value) {
    llvm::ConstantInt* result = llvm::ConstantInt::get(*m_context, llvm::APInt(16, value, true));
    return ValueBuilder(*this, result, CharType::get(getNativeContext()));
}

// Emit constants
ValueBuilder BlockBuilder::createStringConst(const String& value) {
    StringType* type = StringType::get(getNativeContext());
    // get partial types for string
    llvm::Type* charType = llvm::IntegerType::get(*m_context, 16);
    llvm::Type* sizeType = llvm::IntegerType::get(*m_context, 32);
    llvm::ArrayType* bufferType = llvm::ArrayType::get(charType, value.length());

        // generate size
    llvm::Constant* size = llvm::ConstantInt::get(*m_context, llvm::APInt(32, value.length(), false));

    // generate buffer
    llvm::Constant* buffer = 0; {
        std::vector<llvm::Constant*> bufferConst;
        for (int i = 0; i < value.length(); ++i) {
            UChar c = value[i];
            llvm::Constant* value = llvm::ConstantInt::get(*m_context, llvm::APInt(16, c, false));
            bufferConst.push_back(value);
        }
        buffer = llvm::ConstantArray::get(bufferType, bufferConst);
    }

    // generate string type
    std::vector<llvm::Type*> elements;
    elements.push_back(sizeType);
    elements.push_back(bufferType);

    llvm::StructType* stringCstType = llvm::StructType::get(*m_context, elements);

    // generate string
    llvm::Constant* string = llvm::ConstantStruct::get(stringCstType, size, buffer, NULL);
    llvm::GlobalVariable* stringCst = new llvm::GlobalVariable(
        *m_module,
        stringCstType,
        true,
        llvm::GlobalValue::PrivateLinkage,
        string,
        "string.cst"
     );
    stringCst->setUnnamedAddr(true); // Binary equal strings must be merged
    llvm::Type* stringType = type->getVarType();
    llvm::Value* result = new llvm::BitCastInst(stringCst, stringType, "string.val", m_block);
    return ValueBuilder(*this, result, type);
}

/// Create call for callable with arguments
ValueBuilder BlockBuilder::createCall(Callable* call, std::vector<ValueBuilder> args) {
    codegen::CallableEmitter* emitter = call->getEmitter();
    if (emitter) {
        return emitter->emit(*this, args);
    }
    throw "emitter not founded";
}

/// Create conditional goto
void BlockBuilder::createCond(ValueBuilder value, BlockBuilder blockTrue, BlockBuilder blockFalse) {
    llvm::Value* cond = value.getValue();
    if (!cond->getType()->isIntegerTy(1)) {
        throw "Condition must be boolean";
    }
    llvm::IRBuilder<>(m_block).CreateCondBr(cond, blockTrue.getBlock(), blockFalse.getBlock());
}

/// Create unconditional goto
void BlockBuilder::createBr(BlockBuilder block) {
    llvm::IRBuilder<>(m_block).CreateBr(block.getBlock());
}

/// Create new object
ValueBuilder BlockBuilder::createNew(ObjectType* type, Callable* ctor, std::vector<ValueBuilder> args) {
    llvm::Type* elementType = llvm::dyn_cast<llvm::PointerType>(type->getVarType())->getElementType();
    llvm::AllocaInst* variable = new llvm::AllocaInst(elementType, "new.obj", m_block);
    return ValueBuilder(*this, variable, type);
}
