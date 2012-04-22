#ifndef KIWI_CODEGEN_STATEMENT_INCLUDED
#define KIWI_CODEGEN_STATEMENT_INCLUDED

#include "kiwi/Config.hpp"

namespace llvm {
    class Value;
    class Function;
    class Module;
    class BasicBlock;
    class Argument;
    class LLVMContext;
}

namespace kiwi {
    class Type;
namespace codegen {
    /// Structure for store information about instructions emit process
    class StatementGen {
    public:
        /// constructor
        StatementGen(Type* owner, llvm::BasicBlock* block, llvm::Value* thisValue);

        /// copy constructor
        StatementGen(const StatementGen& gen);

        /// assigment operator
        StatementGen& operator=(const StatementGen& gen);

        /// returns owner
        Type* getOwner() const {
            return m_owner;
        }

        /// returns LLVM context
        llvm::LLVMContext& getContext() const
        {
            return *m_context;
        }

        /// returns LLVM module
        llvm::Module* getModule() const
        {
            return m_module;
        }

        /// returns LLVM function
        llvm::Function* getFunction() const
        {
            return m_function;
        }

        /// returns LLVM basic block
        llvm::BasicBlock* getBlock() const
        {
            return m_block;
        }

        /// returns this value
        llvm::Value* getThisValue() const {
            return m_thisValue;
        }

    protected:
        /// Owner type
        Type*m_owner;

        /// LLVM context
        llvm::LLVMContext* m_context;

        /// LLVM module
        llvm::Module* m_module;

        /// LLVM function
        llvm::Function* m_function;

        /// LLVM block
        llvm::BasicBlock* m_block;

        /// LLVM this value
        llvm::Value* m_thisValue;
    }; // class StatementGen

}} /// namespace kiwi::codegen
#endif
