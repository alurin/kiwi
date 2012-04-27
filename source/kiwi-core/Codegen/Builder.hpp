/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_CODEGEN_BUILDER_INTERNAL
#define KIWI_CODEGEN_BUILDER_INTERNAL

#include "kiwi/types.hpp"
#include <vector>

namespace llvm {
    class LLVMContext;
    class Module;
    class Function;
    class FunctionType;
    class BasicBlock;
    class Value;
}

namespace kiwi {
    class BlockBuilder;
    class FunctionBuilder;
    class ValueBuilder;

    class Callable;
    class Context;
    class Field;
    class Module;
    class ObjectType;
    class Type;
    class Type;

    //==--------------------------------------------------------------------==//
    /// This class store information about module and context.
    class Builder {
    public:
        /// Constructor from function. Created first block for function
        Builder(Module* module);

        /// Copy constructor
        Builder(const Builder& builder);

        /// Assigment
        Builder& operator=(const Builder& builder);

        /// return native context
        Context* getNativeContext() const {
            return m_nativeContext;
        }

        /// return native context
        Module* getNativeModule() const {
            return m_nativeModule;
        }

        /// returns LLVM context
        llvm::LLVMContext& getContext() const {
            return *m_context;
        }

        /// returns LLVM module
        llvm::Module* getModule() const {
            return m_module;
        }
    protected:
        /// Native Kiwi context
        Context* m_nativeContext;

        /// Native Kiwi module
        Module* m_nativeModule;

        /// LLVM context
        llvm::LLVMContext*  m_context;

        /// LLVM module
        llvm::Module*       m_module;
    };

    //==--------------------------------------------------------------------==//
    /// This class stored information about function.
    class FunctionBuilder : public Builder {
    public:
        /// Constructor
        FunctionBuilder(Callable* analog);

        /// Constructor
        FunctionBuilder(Type* type, llvm::Function* func);

        /// Copy constructor
        FunctionBuilder(const FunctionBuilder& builder);

        /// Assigment
        FunctionBuilder& operator=(const FunctionBuilder& builder);

        /// emit method definition
        llvm::FunctionType* getFunctionType() const;

        /// return function
        llvm::Function* getFunction() const;

        /// Create sturtup point by current function
        llvm::Function* createJITStartupPoint();

        /// Create new basic block and return builder pointed to this block
        BlockBuilder createBlock(const Identifier& name);

                /// return native callable
        Callable* getNativeCallable() const {
            return m_nativeCallable;
        }

        /// return native type
        Type* getNativeOwner() const {
            return m_nativeOwner;
        }
    private:
        /// Current LLVM function
        mutable llvm::Function* m_func;

        /// Cullable analog
        Callable* m_nativeCallable;

        /// Cullable analog
        Type* m_nativeOwner;
    };

    //==--------------------------------------------------------------------==//
    /// This class stored information about block
    class BlockBuilder : public FunctionBuilder {
    public:
        /// constructor
        BlockBuilder(const FunctionBuilder& builder, llvm::BasicBlock* block);

        /// Copy constructor
        BlockBuilder(const BlockBuilder& builder);

        /// Assigment
        BlockBuilder& operator=(const BlockBuilder& builder);

        /// Create return, if basic block has not terminator instruction
        void createTrailReturn();

        /// Create void return
        void createReturn();

        /// Create return result of callable
        void createReturn(ValueBuilder value);

        /// Create conditional goto
        void createCond(ValueBuilder value, BlockBuilder blockTrue, BlockBuilder blockFalse);

        /// Create unconditional goto
        void createBr(BlockBuilder block);

        /// Allocate memory in stack for mutable variable
        ValueBuilder createVariable(const Identifier& name, Type* type, bool autoInit = true);

        /// Create store in mutable variable
        ValueBuilder createStore(ValueBuilder variable, ValueBuilder value);

        /// Create load from mutable variable
        ValueBuilder createLoad(ValueBuilder variable);

        /// Create new object
        ValueBuilder createNew(ObjectType* type, Callable* ctor = 0, std::vector<ValueBuilder> args = std::vector<ValueBuilder>());

        /// Create store in object field
        ValueBuilder createStore(ValueBuilder thisValue, Field* field, ValueBuilder value);

        /// Create load from object field
        ValueBuilder createLoad(ValueBuilder thisValue, Field* field);

        /// Create call for callable with arguments
        ValueBuilder createCall(Callable* call, std::vector<ValueBuilder> args);

        /// Create integer constant
        ValueBuilder createIntConst(int32_t value);

        /// Create boolean constant
        ValueBuilder createBoolConst(bool value);

        /// Create string constant
        ValueBuilder createStringConst(const String& value);

        /// Create char constant
        ValueBuilder createCharConst(UChar value);

        /// returns LLVM basic block
        llvm::BasicBlock* getBlock() const {
            return m_block;
        }
    protected:
        /// LLVM block
        llvm::BasicBlock* m_block;

        /// Find offset for field in object
        llvm::Value* offsetField(ValueBuilder thisValue, Field* field);
    };

    //==--------------------------------------------------------------------==//
    /// This class stored information about value
    class ValueBuilder : public BlockBuilder {
    public:
        /// constructor
        ValueBuilder(const BlockBuilder& builder, llvm::Value* value, Type* type);

        /// Copy constructor
        ValueBuilder(const ValueBuilder& builder);

        /// Assigment
        ValueBuilder& operator=(const ValueBuilder& builder);

        /// returns value
        llvm::Value* getValue() const {
            return m_value;
        }

        /// returns value type
        Type* getType() const {
            return m_type;
        }
    protected:
        /// Value
        llvm::Value* m_value;

        /// Value type
        Type* m_type;
    };
}

#endif
