#ifndef KIWI_CODEGEN_EXPRESSION_INCLUDED
#define KIWI_CODEGEN_EXPRESSION_INCLUDED

#include "kiwi/codegen/Statement.hpp"

namespace llvm {
    class Value;
}

namespace kiwi {

    typedef boost::shared_ptr<class Type> TypeRef;

namespace codegen {

    /// Structure for store information about instructions emit process
    class ExpressionGen : public StatementGen
    {
    public:
        /// constructor
        ExpressionGen(llvm::BasicBlock* block, TypeRef type, llvm::Value* value);

        /// copy constructor
        ExpressionGen(const ExpressionGen& gen);

        /// constructor
        ExpressionGen(const StatementGen& gen, TypeRef type, llvm::Value* value);

        /// assigment operator
        ExpressionGen& operator=(const ExpressionGen& gen);

        /// returns type
        TypeRef getType() const {
            return m_type;
        }

        /// returns LLVM value
        llvm::Value* getValue() const {
            return m_value;
        }
    protected:
        TypeRef         m_type;
        llvm::Value*    m_value;
    };

}}

#endif