#ifndef KIWI_CODEGEN_EMITTER_INCLUDED
#define KIWI_CODEGEN_EMITTER_INCLUDED

#include "kiwi/Codegen/Expression.hpp"
#include "kiwi/Codegen/Statement.hpp"
#include <vector>

namespace kiwi {
namespace codegen {
    /// Abstract emmiter for unary operators
    class CallableEmitter {
    public:
        /// type for vector of expressions
        typedef std::vector<ExpressionGen> ExpressionVector;

        /// virtual destructor
        virtual ~CallableEmitter();

        /// emit IR instruction
        virtual ExpressionGen emit(const StatementGen& gen, const ExpressionVector& values) =0;
    }; // class Emitter

    /// Abstract emmiter for unary operators
    class UnaryEmitter : public CallableEmitter {
    public:
        /// emit IR instruction for unary operation
        /// @todo Remove and move to multiary emit
        virtual ExpressionGen emit(const StatementGen& gen, const ExpressionGen& value) =0;
    private:
        /// emit IR instruction [proxy]
        virtual ExpressionGen emit(const StatementGen& gen, const ExpressionVector& values);
    }; // class UnaryEmitter

    /// Abstract emitter for binary operators
    class BinaryEmitter : public CallableEmitter {
    public:
        /// emit IR instruction for binary operation
        /// @todo Remove and move to multiary emit
        virtual ExpressionGen emit(const StatementGen& gen, const ExpressionGen& left, const ExpressionGen& right) =0;
    private:
        /// emit IR instruction [proxy]
        virtual ExpressionGen emit(const StatementGen& gen, const ExpressionVector& values);
    }; // class BinaryEmitter
} // namespace codegen
} // namespace kiwi

#endif
