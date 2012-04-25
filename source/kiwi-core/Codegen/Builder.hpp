#ifndef KIWI_CODEGEN_BUILDER_INTERNAL
#define KIWI_CODEGEN_BUILDER_INTERNAL

namespace llvm {
    class LLVMContext;
    class Module;
    class Function;
    class BasicBlock;
    class Value;
}

namespace kiwi {
    class Module;
    class Type;

    class FunctionBuilder;
    class BlockBuilder;
    class ValueBuilder;

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

        /// returns LLVM context
        llvm::LLVMContext& getContext() const {
            return *m_context;
        }

        /// returns LLVM module
        llvm::Module* getModule() const {
            return m_module;
        }

        /// emit method type
        FunctionBuilder emitType(Method* method);

        /// emit method definition
        FunctionBuilder emitDefinition(Method* method);
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

        /// Append instructions for create new structure
        void createNew();

        /// Append instructions for call method from object
        void createCall();

        /// Append instructions for store value in structure field
        void createFieldStore();

        /// Append instructions for load value from structure field
        void createFieldLoad();

        /// Create constant string
        void createConstantString();

        /// return function
        llvm::Function* getFunction() const {
            return m_function;
        }

        /// return callable
        Callable* getCallable() const {
            return m_analog;
        }
    protected:
        /// Current LLVM function
        llvm::Function* m_function;

        /// Cullable analog
        Callable* m_analog;
    };

    //==--------------------------------------------------------------------==//
    /// This class stored information about block
    class BlockBuilder : public FunctionBuilder {
    public:
        /// constructor
        BlockBuilder(llvm::BasicBlock* block);

        /// Copy constructor
        BlockBuilder(const BlockBuilder& builder);

        /// Assigment
        BlockBuilder& operator=(const BlockBuilder& builder);

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
        ValueBuilder(llvm::BasicBlock& block, llvm::Value* value, Type* type);

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
