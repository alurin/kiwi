#ifndef KIWI_CODEGEN_FUNCTION_INCLUDED
#define KIWI_CODEGEN_FUNCTION_INCLUDED

#include "kiwi/Codegen/Expression.hpp"
#include <vector>

namespace llvm {
    class Function;
    class FunctionType;
}

namespace kiwi {
    typedef boost::shared_ptr<class Method> MethodRef;
namespace codegen {

    /// Emitter for method calls and definitions
    class MethodEmitter
    {
    public:
        /// Type for list of method arguments
        typedef std::vector<ExpressionGen> ArgumentList;

        /// constructor
        MethodEmitter(MethodRef method);

        /// emit method type
        llvm::FunctionType* emitType();

        /// emit method definition
        llvm::Function* emitDefinition();

        /// emit method call with ordered arguments
        ExpressionGen emitCall(const StatementGen& gen, const ExpressionGen& thisObject, const ArgumentList& args);
    protected:
        MethodRef m_method;
    };

}}

#endif