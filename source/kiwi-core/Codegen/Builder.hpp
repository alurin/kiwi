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
    class Argument;
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
        Builder(ModulePtr module);

        /// Copy constructor
        Builder(const Builder& builder);

        /// Assigment
        Builder& operator=(const Builder& builder);

        /// return native context
        ContextPtr getNativeContext() const {
            return m_nativeContext;
        }

        /// return native context
        ModulePtr getNativeModule() const {
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
        ContextPtr m_nativeContext;

        /// Native Kiwi module
        ModulePtr m_nativeModule;

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
        FunctionBuilder(MethodPtr analog);

        /// Constructor
        FunctionBuilder(TypePtr type, llvm::Function* func);

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
        MethodPtr getNativeCallable() const {
            return m_nativeCallable;
        }

        /// return native type
        TypePtr getNativeOwner() const {
            return m_nativeOwner;
        }
    private:
        /// Current LLVM function
        mutable llvm::Function* m_func;

        /// Cullable analog
        MethodPtr m_nativeCallable;

        /// Cullable analog
        TypePtr m_nativeOwner;
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
        ValueBuilder createVariable(const Identifier& name, TypePtr type, bool autoInit = true);

        /// Allocate memory in stack for mutable variable
        ValueBuilder createThis();

        /// Create store in mutable variable
        ValueBuilder createStore(ValueBuilder variable, ValueBuilder value);

        /// Create load from mutable variable
        ValueBuilder createLoad(ValueBuilder variable);

        /// Create new object
        ValueBuilder createNew(ObjectPtr type, MethodPtr ctor = MethodPtr(), std::vector<ValueBuilder> args = std::vector<ValueBuilder>());

        /// Create store in object field
        ValueBuilder createStore(ValueBuilder thisValue, FieldPtr field, ValueBuilder value);

        /// Create load from object field
        ValueBuilder createLoad(ValueBuilder thisValue, FieldPtr field);

        /// Create call for callable with arguments
        ValueBuilder createCall(MethodPtr call, std::vector<ValueBuilder> args);

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
        llvm::Value* offsetField(ValueBuilder thisValue, FieldPtr field);
    };

    //==--------------------------------------------------------------------==//
    /// This class stored information about value
    class ValueBuilder : public BlockBuilder {
    public:
        /// constructor
        ValueBuilder(const BlockBuilder& builder, llvm::Value* value, TypePtr type);

        /// Copy constructor
        ValueBuilder(const ValueBuilder& builder);

        /// Assigment
        ValueBuilder& operator=(const ValueBuilder& builder);

        /// returns value
        llvm::Value* getValue() const {
            return m_value;
        }

        /// returns value type
        TypePtr getType() const {
            return m_type;
        }
    protected:
        /// Value
        llvm::Value* m_value;

        /// Value type
        TypePtr m_type;
    };
}

#endif
