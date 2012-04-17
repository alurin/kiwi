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
namespace codegen {
    /// Structure for store information about instructions emit process
    class StatementGen
    {
    public:
        /// constructor
        StatementGen(llvm::BasicBlock* block);

        /// copy constructor
        StatementGen(const StatementGen& gen);

        /// assigment operator
        StatementGen& operator=(const StatementGen& gen);

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
    protected:
        llvm::LLVMContext*  m_context;
        llvm::Module*       m_module;
        llvm::Function*     m_function;
        llvm::BasicBlock*   m_block;
    }; // class StatementGen

}} /// namespace kiwi::codegen
#endif
