/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#ifndef KIWI_SCRIPT_COMPOUNDNODE_HPP_INCLUDED
#define KIWI_SCRIPT_COMPOUNDNODE_HPP_INCLUDED

#include "kiwi/Script/Node.hpp"

namespace kiwi {
    namespace script {
        /// The CompoundNode class represents compound node, e.g. class nodes, namespaces nodes
        class CompoundNode : public Node {
        public:
            /// Get owner namespace
            NamespaceNode* getNamespace() const;

        protected:
            /// Compound owner namespace
            NamespaceNode* m_namespace;

            /// Protected constructor for anonym compund node in namespace
            CompoundNode(NamespaceNode* namespace);
        };
    }
}

#endif
