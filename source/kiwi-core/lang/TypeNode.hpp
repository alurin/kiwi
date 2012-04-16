#ifndef KIWI_LANG_TYPENODE_INTERNAL
#define KIWI_LANG_TYPENODE_INTERNAL

#include "kiwi/Config.hpp"
#include "Node.hpp"

namespace kiwi { namespace lang {

    class TypeNode : public Node
    {

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