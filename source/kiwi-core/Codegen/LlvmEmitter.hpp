/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_CODEGEN_LLVMEMITTER_INTERNAL
#define KIWI_CODEGEN_LLVMEMITTER_INTERNAL

#include "Emitter.hpp"
#include <llvm/Instruction.h>
#include <llvm/InstrTypes.h>

namespace kiwi {
    class Type;
    class Context;
namespace codegen {

    //==--------------------------------------------------------------------==//
    /// LLVM emitter for function from source code
    class LlvmCallEmitter : public MethodPolicy {
    public:
        LlvmCallEmitter(llvm::Function* func, TypePtr returnType);

        /// emit IR instruction for binary operation
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    protected:
        llvm::Function* m_func;
        TypeWeak m_returnType;
    }; // class LlvmCallEmitter

    //==--------------------------------------------------------------------==//
    /// LLVM integer unary operators emitter
    class LlvmZeroUnaryOperator : public MethodPolicy {
    public:
        /// constructor
        LlvmZeroUnaryOperator(llvm::Instruction::BinaryOps opcode, TypePtr type);

        /// emit llvm operator
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    protected:
        llvm::Instruction::BinaryOps m_opcode;
        TypeWeak m_type;
    }; /// class LlvmZeroUnaryOperator

    //==--------------------------------------------------------------------==//
    /// LLVM binary operators emitter
    class LlvmBinaryOperator : public MethodPolicy {
    public:
        /// constructor
        LlvmBinaryOperator(llvm::Instruction::BinaryOps opcode, TypePtr type);

        /// emit llvm operator
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    protected:
        llvm::Instruction::BinaryOps m_opcode;
        TypeWeak m_type;
    }; /// class LlvmBinaryOperator

    //==--------------------------------------------------------------------==//
    /// LLVM binary operators emitter for compare integers
    class LlvmIntegerCompareOperator : public MethodPolicy {
    public:
        /// constructor
        LlvmIntegerCompareOperator(
            llvm::CmpInst::Predicate predicate,
            ContextPtr context
        );

        /// emit llvm operator
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    protected:
        llvm::CmpInst::Predicate m_predicate;
        ContextWeak m_context;
    }; /// class LlvmIntegerCompareOperator

    //==--------------------------------------------------------------------==//
    /// LLVM binary operators emitter for compare strings
    class LlvmStringCompareOperator : public MethodPolicy {
    public:
        /// constructor
        LlvmStringCompareOperator(
            llvm::CmpInst::Predicate predicate,
            ContextPtr context
        );

        /// emit llvm operator
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    protected:
        llvm::CmpInst::Predicate m_predicate;
        ContextWeak m_context;
    }; /// class LlvmStringCompareOperator

    //==--------------------------------------------------------------------==//
    class LlvmIntegerPrintOperator : public MethodPolicy {
    public:
        /// emit llvm operator
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    }; // class LlvmIntegerPrintOperator

    //==--------------------------------------------------------------------==//
    class LlvmBoolPrintOperator : public MethodPolicy {
    public:
        /// emit llvm operator
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    }; // class LlvmBoolPrintOperator

    //==--------------------------------------------------------------------==//
    class LlvmCharPrintOperator : public MethodPolicy {
    public:
        /// emit llvm operator
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    }; // class LlvmCharPrintOperator

    //==--------------------------------------------------------------------==//
    class LlvmStringPrintOperator : public MethodPolicy {
    public:
        /// emit llvm operator
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    }; // class LlvmStringPrintOperator

    //==--------------------------------------------------------------------==//
    class LlvmStringEmitter {
    public:
        /// emit llvm operator
        BlockBuilder emit(BlockBuilder block, ValueBuilder value);

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
    class LlvmStringConcatenate : public MethodPolicy {
    public:
        /// emit llvm operator
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    }; /// class LlvmStringConcatenate

    //==--------------------------------------------------------------------==//
    class LlvmStringSubtraction : public MethodPolicy {
    public:
        /// emit IR instruction for binary operation
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    }; /// class LlvmStringSubtraction

    //==--------------------------------------------------------------------==//
    /// LLVM emitter for empty constructors
    class LlvmCtorEmitter : public MethodPolicy {
    public:
        /// emit IR instruction for binary operation
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    protected:
    }; // class LlvmCallEmitter

    /// Llvm emitter for up cast
    class LlvmUpcast : public MethodPolicy {
    public:
        /// emit IR instruction for binary operation
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    };

    /// Converter from this type to object type and vice versa
    class ObjectThisConverter : public ThisConverter {
    public:
        /// Convert from variable to this
        virtual ValueBuilder emitToThis(BlockBuilder block, ValueBuilder variableValue);

        /// Convert from this to variable
        virtual ValueBuilder emitFromThis(BlockBuilder block, ValueBuilder thisValue);
    };
} // namesapce codegen
} // namesapce  kiwi

#endif
