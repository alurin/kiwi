#ifndef KIWI_CODEGEN_EXPRESSION_INCLUDED
#define KIWI_CODEGEN_EXPRESSION_INCLUDED

#include "kiwi/codegen/Statement.hpp"

namespace llvm {
    class Value;
}

namespace kiwi {
namespace codegen {

    /// Structure for store information about instructions emit process
    class ExpressionGen : public StatementGen
    {
    public:
        /// constructor
        ExpressionGen(llvm::BasicBlock* block, llvm::Value* value);

        /// copy constructor
        ExpressionGen(const ExpressionGen& gen);

        /// constructor
        ExpressionGen(const StatementGen& gen, llvm::Value* value);

        /// assigment operator
        ExpressionGen& operator=(const ExpressionGen& gen);

        /// returns LLVM value
        llvm::Value* getValue() const {
            return m_value;
        }
    protected:
        llvm::Value* m_value;
    };

}}

#endif