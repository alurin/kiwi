#ifndef KIWI_SCRIPT_NAMESPACE_HPP_INCLUDE
#define KIWI_SCRIPT_NAMESPACE_HPP_INCLUDE

#include "kiwi/Script/Node.hpp"

namespace kiwi {
    namespace script {
        class NamespaceNode : public Node {
        public:
            /// Create root namespace node
            NamespaceNode(const UnicodeString& name);

            /// Create child for namespace
            NamespaceNode(const UnicodeString& name, NamespaceNode* parentNode);

            /// Clean up all children nodes
            virtual ~NamespaceNode();

            /// Get namespace name
            UnicodeString getName() const {
                return m_name;
            }

            /// Get namespace fully qualified name
            UnicodeString getFullName() const;

            NamespaceNode* getParent() const {
                return m_parent;
            }
        private:
            /// Namespace name
            UnicodeString m_name;

            /// Cached namespace fully qualified name
            UnicodeString m_fullName;

            /// Namespace parent
            NamespaceNode* m_parent;
        };
    }
}

#endif
