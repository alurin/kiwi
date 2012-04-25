#ifndef KIWI_CODEGEN_BUILDER_INTERNAL
#define KIWI_CODEGEN_BUILDER_INTERNAL

#include "kiwi/types.hpp"

namespace llvm {
    class LLVMContext;
    class Module;
    class Function;
    class BasicBlock;
    class Value;
}

namespace kiwi {
    class Context;
    class Module;
    class Type;
    class Callable;

    class FunctionBuilder;
    class BlockBuilder;
    class ValueBuilder;

    //==--------------------------------------------------------------------==//
    /// This class store information about module and context.
    class Builder {
    public:
        /// Constructor from function. Created first block for function
        Builder(llvm::Module* module);

        /// Copy constructor
        Builder(const Builder& builder);

        /// Assigment
        Builder& operator=(const Builder& builder);

        /// returns LLVM context
        llvm::LLVMContext& getContext() const {
            return *m_context;
        }

        /// returns LLVM module
        llvm::Module* getModule() const {
            return m_module;
        }
    protected:
        /// Current LLVM context
        llvm::LLVMContext* m_context;

        /// Current LLVM module
        llvm::Module* m_module;

        /// Current Kiwi module
    };

    //==--------------------------------------------------------------------==//
    /// This class stored information about function.
    class FunctionBuilder : public Builder {
    public:
        /// Call
        FunctionBuilder(llvm::Function* function, Callable* analog);

        /// Copy constructor
        FunctionBuilder(const FunctionBuilder& builder);

        /// Assigment
        FunctionBuilder& operator=(const FunctionBuilder& builder);

        /// Create new basic block and return builder pointed to this block
        BlockBuilder createBlock(const Identifier& name);

        /// return function
        llvm::Function* getFunction() const {
            return m_func;
        }

        /// return native context
        Context* getNativeContext() const;

        /// return callable
        Callable* getCallable() const {
            return m_analog;
        }
    protected:
        /// Current LLVM function
        llvm::Function* m_func;

        /// Cullable analog
        Callable* m_analog;
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

        /// Allocate memory in stack for mutable varaible
        ValueBuilder createVariable(const Identifier& name, Type* type, bool autoInit = true);

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
