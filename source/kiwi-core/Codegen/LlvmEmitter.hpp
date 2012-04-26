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
    class LlvmCallEmitter : public CallableEmitter {
    public:
        LlvmCallEmitter(llvm::Function* func, Type* returnType);

        /// emit IR instruction for binary operation
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    protected:
        llvm::Function* m_func;
        Type* m_returnType;
    }; // class LlvmCallEmitter

    //==--------------------------------------------------------------------==//
    /// LLVM integer unary operators emitter
    class LlvmZeroUnaryOperator : public CallableEmitter {
    public:
        /// constructor
        LlvmZeroUnaryOperator(llvm::Instruction::BinaryOps opcode, Type* type);

        /// emit llvm operator
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    protected:
        llvm::Instruction::BinaryOps m_opcode;
        Type*  m_type;
    }; /// class LlvmZeroUnaryOperator

    //==--------------------------------------------------------------------==//
    /// LLVM binary operators emitter
    class LlvmBinaryOperator : public CallableEmitter {
    public:
        /// constructor
        LlvmBinaryOperator(llvm::Instruction::BinaryOps opcode, Type* type);

        /// emit llvm operator
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    protected:
        llvm::Instruction::BinaryOps m_opcode;
        Type* m_type;
    }; /// class LlvmBinaryOperator

    //==--------------------------------------------------------------------==//
    /// LLVM binary operators emitter for compare integers
    class LlvmIntegerCompareOperator : public CallableEmitter {
    public:
        /// constructor
        LlvmIntegerCompareOperator(
            llvm::CmpInst::Predicate predicate,
            Context* context
        );

        /// emit llvm operator
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    protected:
        llvm::CmpInst::Predicate m_predicate;
        Context* m_context;
    }; /// class LlvmIntegerCompareOperator

    //==--------------------------------------------------------------------==//
    /// LLVM binary operators emitter for compare strings
    class LlvmStringCompareOperator : public CallableEmitter {
    public:
        /// constructor
        LlvmStringCompareOperator(
            llvm::CmpInst::Predicate predicate,
            Context* context
        );

        /// emit llvm operator
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    protected:
        llvm::CmpInst::Predicate m_predicate;
        Context* m_context;
    }; /// class LlvmStringCompareOperator

    //==--------------------------------------------------------------------==//
    class LlvmIntegerPrintOperator : public CallableEmitter {
    public:
        /// emit llvm operator
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    }; // class LlvmIntegerPrintOperator

    //==--------------------------------------------------------------------==//
    class LlvmBoolPrintOperator : public CallableEmitter {
    public:
        /// emit llvm operator
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    }; // class LlvmBoolPrintOperator

    //==--------------------------------------------------------------------==//
    class LlvmCharPrintOperator : public CallableEmitter {
    public:
        /// emit llvm operator
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    }; // class LlvmCharPrintOperator

    //==--------------------------------------------------------------------==//
    class LlvmStringPrintOperator : public CallableEmitter {
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
    class LlvmStringConcatenate : public CallableEmitter {
    public:
        /// emit llvm operator
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    }; /// class LlvmStringConcatenate

    //==--------------------------------------------------------------------==//
    class LlvmStringSubtraction : public CallableEmitter {
    public:
        /// emit IR instruction for binary operation
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    }; /// class LlvmStringSubtraction

    //==--------------------------------------------------------------------==//
    /// LLVM emitter for empty constructors
    class LlvmCtorEmitter : public CallableEmitter {
    public:
        /// emit IR instruction for binary operation
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    protected:
    }; // class LlvmCallEmitter

    /// Llvm emitter for up cast
    class LlvmUpcast : public CallableEmitter {
    public:
        /// emit IR instruction for binary operation
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    };
} // namesapce codegen
} // namesapce  kiwi

#endif
