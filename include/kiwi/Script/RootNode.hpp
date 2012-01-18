/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#ifndef KIWI_SCRIPT_ROOTNODE_HPP_INCLUDE
#define KIWI_SCRIPT_ROOTNODE_HPP_INCLUDE

#include "kiwi/Script/Node.hpp"

namespace kiwi {
    namespace script {
        class NamespaceNode;
        class ScriptNode;

        /// The RootNode class is root for abstract syntax tree
        class RootNode : public Node
        {
        public:
            /// Root node constructor
            RootNode(const UnicodeString& sourceName);

            /// Returns source name
            UnicodeString getSourceName() const {
                return m_sourceName;
            }

            /// Return root namespace
            NamespaceNode* getNamespace() const {
                return m_namespace;
            }

            /// Return root script statement
            ScriptNode* getScript() const {
                return m_script;
            }
        protected:
            /// Source name
            UnicodeString m_sourceName;

            /// Root namespace
            NamespaceNode* m_namespace;

            /// Root statement
            ScriptNode* m_script;
        };
    }
}

#endif
