#ifndef KIWI_CODEGEN_EMITTER_INTERNAL
#define KIWI_CODEGEN_EMITTER_INTERNAL

#include "kiwi/codegen/Emitter.hpp"
#include <llvm/Instruction.h>
#include <llvm/InstrTypes.h>

namespace kiwi {
    typedef boost::shared_ptr<class Type>    TypeRef;
    typedef boost::shared_ptr<class Context> ContextRef;
namespace codegen {

    /// LLVM unary operators emitter
    class LlvmUnaryOperator : public UnaryEmitter {
    public:
    }; // class LlvmUnaryOperator


    /// LLVM integer unary operators emitter
    class LlvmZeroUnaryOperator : public UnaryEmitter {
    public:
        /// constructor
        LlvmZeroUnaryOperator(llvm::Instruction::BinaryOps opcode, TypeRef type);

        /// emit llvm operator
        virtual ExpressionGen emit(const StatementGen& gen, const ExpressionGen& value);
    protected:
        llvm::Instruction::BinaryOps    m_opcode;
        TypeRef                         m_type;
    }; /// class LlvmZeroUnaryOperator

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
    }; /// class LlvmBinaryOperator


    /// LLVM binary operators emitter
    class LlvmICompareOperator : public BinaryEmitter {
    public:
        /// constructor
        LlvmICompareOperator(llvm::CmpInst::Predicate predicate, ContextRef context);

        /// emit llvm operator
        virtual ExpressionGen emit(const StatementGen& gen, const ExpressionGen& left, const ExpressionGen& right);
    protected:
        llvm::CmpInst::Predicate    m_predicate;
        ContextRef                  m_context;
    }; /// class LlvmICompareOperator

} // namesapce codegen
} // namesapce  kiwi

#endif