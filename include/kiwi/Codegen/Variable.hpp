#ifndef KIWI_CODEGEN_VARIABLE_INCLUDED
#define KIWI_CODEGEN_VARIABLE_INCLUDED

#include "kiwi/Config.hpp"

namespace llvm {
    class Value;
    class Function;
    class Module;
    class BasicBlock;
    class Argument;
    class AllocaInst;
    class LLVMContext;
}

namespace kiwi {
    typedef boost::shared_ptr<class Type> TypeRef;

namespace codegen {
    /// Store information about variable
    class VariableGen
    {
    public:
        /// empty constructor
        VariableGen();

        /// constructor
        VariableGen(TypeRef type, llvm::Value* value);

        /// copy constructor
        VariableGen(const VariableGen& gen);

        /// assigment operator
        VariableGen& operator=(const VariableGen& gen);

        /// returns variable type
        TypeRef getType() const {
            return m_type;
        }

        /// return LLVM value
        llvm::Value* getValue() const {
            return m_value;
        }
    protected:
        TypeRef         m_type;
        llvm::Value*    m_value;
    };

}}

#endif