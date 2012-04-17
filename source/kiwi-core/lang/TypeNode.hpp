#ifndef KIWI_LANG_TYPENODE_INTERNAL
#define KIWI_LANG_TYPENODE_INTERNAL

#include "kiwi/Config.hpp"
#include "Node.hpp"

namespace llvm
{
    class Type;
}

namespace kiwi
{
    typedef boost::shared_ptr<class Module> ModuleRef;

namespace lang
{

    class TypeNode : public Node
    {
    public:
        llvm::Type* generate(ModuleRef module);
    };

    class TypeFactory
    {
    public:
        TypeNode* getVoid() {
            return 0;
        }

        TypeNode* getInt() {
            return 0;
        }

        TypeNode* getString() {
            return 0;
        }

        TypeNode* getArray(TypeNode* type) {
            return 0;
        }
    };

}}

#endif