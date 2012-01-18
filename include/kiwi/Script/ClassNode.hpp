/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#ifndef KIWI_SCRIPT_CLASSNODE_HPP_INCLUDED
#define KIWI_SCRIPT_CLASSNODE_HPP_INCLUDED

#include "kiwi/Script/CompoundNode.hpp"

namespace kiwi {
    namespace script {
        /// The
        class ClassNode : public CompoundNode {
        public:
            /// Constructor named class node
            ClassNode(const UnicodeString& name, NamespaceNode* parentNamespace);

            /// Constructor for anonym class node
            ClassNode(NamespaceNode* parentNamespace);
        };
    }
}

#endif