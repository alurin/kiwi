#ifndef KIWI_CODEGEN_TYPE_INCLUDED
#define KIWI_CODEGEN_TYPE_INCLUDED

#include "kiwi/config.hpp"

namespace llvm {
    class Type;
}

namespace kiwi {
    class Type;
namespace codegen {
    /// Structure for store information about instructions emit process
    class TypeGen
    {
    public:
        TypeGen(Type* type);

    protected:
        Type*         m_type;
        llvm::Type      m_llvmType;
    }; // class StatementGen

}} /// namespace kiwi::codegen
#endif
