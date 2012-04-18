#ifndef KIWI_CODEGEN_EMITTER_INTERNAL
#define KIWI_CODEGEN_EMITTER_INTERNAL

#include "kiwi/codegen/Emitter.hpp"
#include <llvm/Instruction.h>

namespace kiwi {
namespace codegen {

    /// LLVM unary operators emitter
    class LlvmUnaryOperator : public UnaryEmmiter {
    public:
    }; // class LlvmUnaryOperator

    /// LLVM binary operators emitter
    class LlvmBinaryOperator : public BinaryEmitter {
    public:
        /// constructor
        LlvmBinaryOperator(llvm::Instruction::BinaryOps opcode);

        /// emit llvm operator
        virtual ExpressionGen emit(const StatementGen& gen, const ExpressionGen& left, const ExpressionGen& right) =0;
    protected:
        llvm::Instruction::BinaryOps m_opcode;
    }; /// classLlvmBinaryOperator

} // namesapce codegen
} // namesapce  kiwi

#endif