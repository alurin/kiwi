#ifndef KIWI_CODEGEN_EMITTER_INCLUDED
#define KIWI_CODEGEN_EMITTER_INCLUDED

#include "kiwi/Codegen/Expression.hpp"
#include "kiwi/Codegen/Statement.hpp"
#include <vector>

namespace kiwi {
namespace codegen {
    /// Abstract emmiter for unary operators
    class UnaryEmitter
    {
    public:
        /// virtual destructor
        virtual ~UnaryEmitter();

        /// emit IR instruction for unary operation
        virtual ExpressionGen emit(const StatementGen& gen, const ExpressionGen& value) =0;
    }; // class UnaryEmitter

    /// Abstract emitter for binary operators
    class BinaryEmitter {
    public:
        /// virtual destructor
        virtual ~BinaryEmitter();

        /// emit IR instruction for binary operation
        virtual ExpressionGen emit(const StatementGen& gen, const ExpressionGen& left, const ExpressionGen& right) =0;
    }; // class BinaryEmitter

    class MultiaryEmitter {
    public:
        typedef std::vector<ExpressionGen> expressions;

        /// virtual destructor
        virtual ~MultiaryEmitter();

        /// emit IR instruction for binary operation
        virtual ExpressionGen emit(const StatementGen& gen, const expressions& values) =0;
    };
} // namespace codegen
} // namespace kiwi

#endif
