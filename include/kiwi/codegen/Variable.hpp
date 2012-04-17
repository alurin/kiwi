#ifndef KIWI_CODEGEN_VARIABLE_INCLUDED
#define KIWI_CODEGEN_VARIABLE_INCLUDED

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
namespace codegen {
    /// Store information about variable
    class VariableGen
    {
    public:
        // empty constructor
        VariableGen();

        // constructor
        VariableGen(llvm::Value* value);

        // copy constructor
        VariableGen(const VariableGen& gen);

        // assigment operator
        VariableGen& operator=(const VariableGen& gen);

        /// return LLVM value
        llvm::Value* getValue() const {
            return m_value;
        }
    protected:
        llvm::Value* m_value;
    };

}}

#endif