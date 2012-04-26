#include "Builder.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/DerivedTypes.hpp"
#include "llvm/Module.h"
#include "llvm/Function.h"
#include "llvm/BasicBlock.h"
#include "llvm/Instructions.h"
#include "llvm/Constants.h"
#include "kiwi/assert.hpp"

#define EMPTY_WHILE_WRAP(_stmt_) do { _stmt_ } while(0)

#define BUILDER_ASSERT() EMPTY_WHILE_WRAP( \
        kiwi_assert(m_module, "Builder must have LLVM module"); \
    )

#define BUILDER_FUNCTION_ASSERT() EMPTY_WHILE_WRAP( \
        kiwi_assert(m_func, "Builder must have LLVM function");   \
        kiwi_assert(m_analog, "Builder must have Kiwi callable"); \
        kiwi_assert(m_func->arg_size() == m_analog->size(), "Argument in function must be actual"); \
    )

#define BUILDER_BLOCK_ASSERT() EMPTY_WHILE_WRAP( \
        kiwi_assert(m_block, "Builder must have LLVM basic block"); \
        kiwi_assert(m_block->getParent() == m_func, "Builder must have block from the same function"); \
    )

#define BUILDER_VALUE_ASSERT() EMPTY_WHILE_WRAP( \
        kiwi_assert(m_value, "Builder must have LLVM value"); \
        kiwi_assert(m_type, "Builder must have Kiwi type");   \
    )

using namespace kiwi;

//===--------------------------------------------------------------------------------------------------------------===//
//    Constructors and assignments
//===--------------------------------------------------------------------------------------------------------------===//
Builder::Builder(llvm::Module* module)
: m_module(module), m_context(&(module->getContext())) {
    BUILDER_ASSERT();
}

// Copy constructor
Builder::Builder(const Builder& builder)
: m_module(builder.m_module), m_context(builder.m_context) {
    BUILDER_ASSERT();
}

// Assigment
Builder& Builder::operator=(const Builder& builder) {
    if (this != &builder) {
        m_module  = builder.m_module;
        m_context = builder.m_context;

        BUILDER_ASSERT();
    }
    return *this;
}

// Call
FunctionBuilder::FunctionBuilder(llvm::Function* function, Callable* analog)
: Builder(function->getParent()), m_func(function), m_analog(analog) {
    BUILDER_FUNCTION_ASSERT();
}

// Copy constructor
FunctionBuilder::FunctionBuilder(const FunctionBuilder& builder)
: Builder(builder), m_func(builder.m_func), m_analog(builder.m_analog) {
    BUILDER_FUNCTION_ASSERT();
}

// Assigment
FunctionBuilder& FunctionBuilder::operator=(const FunctionBuilder& builder) {
    if (this != &builder) {
        Builder::operator=(builder);
        m_func   = builder.m_func;
        m_analog = builder.m_analog;

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
Context* FunctionBuilder::getNativeContext() const {
    return m_analog->getOwnerType()->getContext();
}

BlockBuilder FunctionBuilder::createBlock(const Identifier& name) {
    llvm::BasicBlock* block = llvm::BasicBlock::Create(*m_context, name, m_func);
    return BlockBuilder(*this, block);
}

//===--------------------------------------------------------------------------------------------------------------===//
//    Block builder methods
//===--------------------------------------------------------------------------------------------------------------===//
void BlockBuilder::createTrailReturn() {
    if (!m_block->getTerminator()) {
        llvm::Type* resultType = m_func->getFunctionType()->getReturnType();
        if (resultType->isVoidTy()) {
            llvm::ReturnInst::Create(*m_context, m_block);
        } else {
            llvm::Value* result = llvm::Constant::getNullValue(resultType);
            llvm::ReturnInst::Create(*m_context, result, m_block);
        }
    }
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

    // generate string type
    std::vector<llvm::Type*> elements;
    elements.push_back(sizeType);
    elements.push_back(bufferType);

    llvm::Type* elementType = llvm::dyn_cast<llvm::PointerType>(type->getVarType())->getElementType();
    llvm::StructType* stringType = llvm::dyn_cast<llvm::StructType>(elementType);

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

    // generate string
    llvm::Constant* string = llvm::ConstantStruct::get(stringType, size, buffer, NULL);
    llvm::GlobalVariable* result = new llvm::GlobalVariable(
        *m_module,
        stringType,
        true,
        llvm::GlobalValue::PrivateLinkage,
        string,
        "string"
     );
    result->setUnnamedAddr(true); // Binary equal strings must be merged
    return ValueBuilder(*this, result, type);
}
