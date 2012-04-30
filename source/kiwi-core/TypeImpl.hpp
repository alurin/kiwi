#ifndef KIWI_TYPEIMPL_INTERNAL
#define KIWI_TYPEIMPL_INTERNAL

#include <boost/signals2.hpp>
#include "kiwi/Support/MemberSet.hpp"
#include <vector>

namespace kiwi {
    class TypeImpl {
    public:
        /// Signal for insert new field
        boost::signals2::signal<void (Field* field)> onInsertField;

        /// Singal for insert new method
        boost::signals2::signal<void (Method* method)> onInsertMethod;

        /// List of base types
        std::vector<Type*> m_bases;

        /// List of unary operators
        std::vector<UnaryOperator*> m_unary;

        /// List of binary operators
        std::vector<BinaryOperator*> m_binary;

        /// List of multiary operators
        std::vector<MultiaryOperator*> m_multiary;

        /// List of methods
        std::vector<Method*> m_methods;

        /// List of fields
        MemberSet<Field> m_fields;

        /// LLVM analog
        llvm::Type* m_varType;

        void connectType(Type* type);
    };
}

#endif
