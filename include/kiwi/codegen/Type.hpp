#ifndef KIWI_CODEGEN_TYPE_INCLUDED
#define KIWI_CODEGEN_TYPE_INCLUDED

#include "kiwi/Config.hpp"

namespace llvm {
    class Type;
}

namespace kiwi {
    typedef boost::shared_ptr<class Type> TypeRef;

namespace codegen {
    /// Structure for store information about instructions emit process
    class TypeGen
    {
    public:
        TypeGen(TypeRef type);

    protected:
        TypeRef         m_type;
        llvm::Type      m_llvmType;
    }; // class StatementGen

}} /// namespace kiwi::codegen
#endif
