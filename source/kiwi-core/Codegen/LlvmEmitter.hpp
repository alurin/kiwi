#ifndef KIWI_CODEGEN_EMITTER_INTERNAL
#define KIWI_CODEGEN_EMITTER_INTERNAL

#include "kiwi/Codegen/Emitter.hpp"
#include <llvm/Instruction.h>
#include <llvm/InstrTypes.h>

namespace kiwi {
    typedef boost::shared_ptr<class Type>    TypeRef;
    typedef boost::weak_ptr<class Type>      TypeWeak;
    typedef boost::shared_ptr<class Context> ContextRef;
    typedef boost::weak_ptr<class Context>   ContextWeak;
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
        TypeWeak                        m_type;
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
        TypeWeak                        m_type;
    }; /// class LlvmBinaryOperator

    /// LLVM binary operators emitter for compare integers
    class LlvmIntegerCompareOperator : public BinaryEmitter {
    public:
        /// constructor
        LlvmIntegerCompareOperator(llvm::CmpInst::Predicate predicate, ContextRef context);

        /// emit llvm operator
        virtual ExpressionGen emit(const StatementGen& gen, const ExpressionGen& left, const ExpressionGen& right);
    protected:
        llvm::CmpInst::Predicate    m_predicate;
        ContextWeak                 m_context;
    }; /// class LlvmIntegerCompareOperator

    /// LLVM binary operators emitter for compare strings
    class LlvmStringCompareOperator : public BinaryEmitter {
    public:
        /// constructor
        LlvmStringCompareOperator(llvm::CmpInst::Predicate predicate, ContextRef context);

        /// emit llvm operator
        virtual ExpressionGen emit(const StatementGen& gen, const ExpressionGen& left, const ExpressionGen& right);
    protected:
        llvm::CmpInst::Predicate    m_predicate;
        ContextWeak                 m_context;
    }; /// class LlvmStringCompareOperator

    class LlvmIntegerPrintOperator : public UnaryEmitter {
    public:
        /// emit llvm operator
        virtual ExpressionGen emit(const StatementGen& gen, const ExpressionGen& value);

    protected:
    }; // class LlvmIntegerPrintOperator

    class LlvmBoolPrintOperator : public UnaryEmitter {
    public:
        /// emit llvm operator
        virtual ExpressionGen emit(const StatementGen& gen, const ExpressionGen& value);

    protected:
    }; // class LlvmBoolPrintOperator

    class LlvmCharPrintOperator : public UnaryEmitter {
    public:
        /// emit llvm operator
        virtual ExpressionGen emit(const StatementGen& gen, const ExpressionGen& value);

    protected:
    }; // class LlvmCharPrintOperator

    class LlvmStringPrintOperator : public UnaryEmitter {
    public:
        /// emit llvm operator
        virtual ExpressionGen emit(const StatementGen& gen, const ExpressionGen& value);

    protected:
    }; // class LlvmStringPrintOperator

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
} // namesapce codegen
} // namesapce  kiwi

#endif
