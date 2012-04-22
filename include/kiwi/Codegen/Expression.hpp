#ifndef KIWI_CODEGEN_EXPRESSION_INCLUDED
#define KIWI_CODEGEN_EXPRESSION_INCLUDED

#include "kiwi/Codegen/Statement.hpp"

namespace llvm {
    class Value;
}

namespace kiwi {
namespace codegen {

    /// Structure for store information about instructions emit process
    class ExpressionGen : public StatementGen {
    public:
        /// copy constructor
        ExpressionGen(const ExpressionGen& gen);

        /// constructor
        ExpressionGen(const StatementGen& gen, Type* type, llvm::Value* value);

        /// assigment operator
        ExpressionGen& operator=(const ExpressionGen& gen);

        /// returns type
        Type* getType() const {
            return m_type;
        }

        /// returns LLVM value
        llvm::Value* getValue() const {
            return m_value;
        }
    protected:
        /// Expression type
        Type* m_type;

        /// Expression value
        llvm::Value* m_value;
    };

}}

#endif
