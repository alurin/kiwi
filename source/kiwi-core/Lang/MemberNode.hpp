#ifndef KIWI_LANG_MEMBERNODE_INTERNAL
#define KIWI_LANG_MEMBERNODE_INTERNAL

#include "Node.hpp"

namespace kiwi {
    class Type;
namespace lang {
    class Driver;
    //==--------------------------------------------------------------------==//
    /// Base for member nodes
    class MemberNode : public Node {
    public:
        /// Generate metadata (LLVM analog is no aviable)
        virtual void generateMember(Driver& driver, Type* owner);

        /// Emit function code and instruction
        virtual void generateCode(Driver& driver, Type* owner);

    protected:
        /// Internal constructor
        MemberNode();
    };
}} // namespace kiwi::lang

#endif
