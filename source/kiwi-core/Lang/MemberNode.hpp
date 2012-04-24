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
        virtual void generate(Driver& driver, Type* owner) =0;

        /// Emit function code and instruction
        virtual void emit(Driver& driver, Type* owner) =0;

    protected:
        /// Internal constructor
        MemberNode();
    };
}} // namespace kiwi::lang

#endif
