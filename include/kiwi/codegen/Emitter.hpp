#ifndef KIWI_CODEGEN_EXPRESSION_INCLUDED
#define KIWI_CODEGEN_EXPRESSION_INCLUDED

#include "kiwi/codegen/Expression.hpp"
#include "kiwi/codegen/Statement.hpp"

namespace kiwi {
namespace codegen {
    /// Abstract emmiter for unary operators
    class UnaryEmitter
    {
    public:
        virtual ExpressionGen emit(const StatementGen& gen, const ExpressionGen& value) =0;
    }; // class UnaryEmitter

    /// Abstract emitter for binary operators
    class BinaryEmitter {
    public:
        virtual ExpressionGen emit(const StatementGen& gen, const ExpressionGen& left, const ExpressionGen& right) =0;
    }; // class BinaryEmitter

} // namespace codegen
} // namespace kiwi

#endif
