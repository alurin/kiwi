#ifndef KIWI_CODEGEN_EMITTER_INTERNAL
#define KIWI_CODEGEN_EMITTER_INTERNAL

#include "kiwi/codegen/Emitter.hpp"
#include <llvm/Instruction.h>

namespace kiwi {
    typedef boost::shared_ptr<class Type>               TypeRef;
namespace codegen {

    /// LLVM unary operators emitter
    class LlvmUnaryOperator : public UnaryEmitter {
    public:
    }; // class LlvmUnaryOperator

    /// LLVM binary operators emitter
    class LlvmBinaryOperator : public BinaryEmitter {
    public:
        /// constructor
        LlvmBinaryOperator(llvm::Instruction::BinaryOps opcode, TypeRef type);

        /// emit llvm operator
        virtual ExpressionGen emit(const StatementGen& gen, const ExpressionGen& left, const ExpressionGen& right);
    protected:
        llvm::Instruction::BinaryOps    m_opcode;
        TypeRef                         m_type;
    }; /// classLlvmBinaryOperator

} // namesapce codegen
} // namesapce  kiwi

#endif