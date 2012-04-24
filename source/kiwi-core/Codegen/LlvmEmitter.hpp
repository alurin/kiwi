#ifndef KIWI_CODEGEN_EMITTER_INTERNAL
#define KIWI_CODEGEN_EMITTER_INTERNAL

#include "kiwi/Codegen/Emitter.hpp"
#include <llvm/Instruction.h>
#include <llvm/InstrTypes.h>

namespace kiwi {
    class Type;
    class Context;
namespace codegen {

    //==--------------------------------------------------------------------==//
    /// LLVM emitter for function from source code
    class LlvmCallEmitter : public CallableEmitter {
    public:
        LlvmCallEmitter(llvm::Function* func, Type* returnType);

        /// emit IR instruction for binary operation
        virtual ExpressionGen emit(
            const StatementGen& gen,
            const ExpressionVector& values
        );
    protected:
        llvm::Function* m_func;
        Type* m_returnType;
    }; // class LlvmCallEmitter

    //==--------------------------------------------------------------------==//
    /// LLVM integer unary operators emitter
    class LlvmZeroUnaryOperator : public UnaryEmitter {
    public:
        /// constructor
        LlvmZeroUnaryOperator(llvm::Instruction::BinaryOps opcode, Type* type);

        /// emit llvm operator
        virtual ExpressionGen emit(
            const StatementGen& gen,
            const ExpressionGen& value
        );
    protected:
        llvm::Instruction::BinaryOps m_opcode;
        Type*  m_type;
    }; /// class LlvmZeroUnaryOperator

    //==--------------------------------------------------------------------==//
    /// LLVM binary operators emitter
    class LlvmBinaryOperator : public BinaryEmitter {
    public:
        /// constructor
        LlvmBinaryOperator(llvm::Instruction::BinaryOps opcode, Type* type);

        /// emit llvm operator
        virtual ExpressionGen emit(
            const StatementGen& gen,
            const ExpressionGen& left,
            const ExpressionGen& right
     );
    protected:
        llvm::Instruction::BinaryOps m_opcode;
        Type* m_type;
    }; /// class LlvmBinaryOperator

    //==--------------------------------------------------------------------==//
    /// LLVM binary operators emitter for compare integers
    class LlvmIntegerCompareOperator : public BinaryEmitter {
    public:
        /// constructor
        LlvmIntegerCompareOperator(
            llvm::CmpInst::Predicate predicate,
            Context* context
        );

        /// emit llvm operator
        virtual ExpressionGen emit(
            const StatementGen& gen,
            const ExpressionGen& left,
            const ExpressionGen& right
        );
    protected:
        llvm::CmpInst::Predicate m_predicate;
        Context* m_context;
    }; /// class LlvmIntegerCompareOperator

    //==--------------------------------------------------------------------==//
    /// LLVM binary operators emitter for compare strings
    class LlvmStringCompareOperator : public BinaryEmitter {
    public:
        /// constructor
        LlvmStringCompareOperator(
            llvm::CmpInst::Predicate predicate,
            Context* context
        );

        /// emit llvm operator
        virtual ExpressionGen emit(
            const StatementGen& gen,
            const ExpressionGen& left,
            const ExpressionGen& right
        );
    protected:
        llvm::CmpInst::Predicate m_predicate;
        Context* m_context;
    }; /// class LlvmStringCompareOperator

    //==--------------------------------------------------------------------==//
    class LlvmIntegerPrintOperator : public UnaryEmitter {
    public:
        /// emit llvm operator
        virtual ExpressionGen emit(
            const StatementGen& gen,
            const ExpressionGen& value
        );
    }; // class LlvmIntegerPrintOperator

    //==--------------------------------------------------------------------==//
    class LlvmBoolPrintOperator : public UnaryEmitter {
    public:
        /// emit llvm operator
        virtual ExpressionGen emit(
            const StatementGen& gen,
            const ExpressionGen& value
        );
    }; // class LlvmBoolPrintOperator

    //==--------------------------------------------------------------------==//
    class LlvmCharPrintOperator : public UnaryEmitter {
    public:
        /// emit llvm operator
        virtual ExpressionGen emit(
            const StatementGen& gen,
            const ExpressionGen& value
        );
    }; // class LlvmCharPrintOperator

    //==--------------------------------------------------------------------==//
    class LlvmStringPrintOperator : public UnaryEmitter {
    public:
        /// emit llvm operator
        virtual ExpressionGen emit(
            const StatementGen& gen,
            const ExpressionGen& value
        );
    }; // class LlvmStringPrintOperator

    //==--------------------------------------------------------------------==//
    class LlvmStringEmitter {
    public:
        /// emit llvm operator
        StatementGen emit(const StatementGen& gen, const ExpressionGen& value);

        llvm::Value* getLengthValue() const {
            return m_lengthValue;
        }

        llvm::Value* getBufferValue() const {
            return m_bufferValue;
        }
    protected:
        llvm::Value* m_lengthValue;
        llvm::Value* m_bufferValue;
    }; /// class LlvmStringEmitter

    //==--------------------------------------------------------------------==//
    class LlvmStringConcatenate : public BinaryEmitter {
    public:
        /// emit llvm operator
        virtual ExpressionGen emit(
            const StatementGen& gen,
            const ExpressionGen& left,
            const ExpressionGen& right
        );
    }; /// class LlvmStringConcatenate

    //==--------------------------------------------------------------------==//
    class LlvmStringSubtraction : public CallableEmitter {
    public:
        /// emit IR instruction for binary operation
        virtual ExpressionGen emit(
            const StatementGen& gen,
            const ExpressionVector& values
        );
    }; /// class LlvmStringSubtraction
} // namesapce codegen
} // namesapce  kiwi

#endif
