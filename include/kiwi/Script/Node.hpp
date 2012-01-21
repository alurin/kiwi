/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#ifndef KIWI_SCRIPT_NODE_HPP_INCLUDED
#define KIWI_SCRIPT_NODE_HPP_INCLUDED

#include "kiwi/Location.hpp"

namespace kiwi {
    namespace io {
        class OutputStream;
    }

    namespace script {
        class NodeVisitor;

        /// The Node class is abstract root for all syntax nodes
        /// Node must have references counter
        ///
        class Node {
        public:
            /// Virtual node destructor
            virtual ~Node();

            /// Returns node location
            Location getLocation() const {
                return m_location;
            }

            /// Accept visitor
            virtual void accept(NodeVisitor& visitor) =0;

            /// Dump tree for node
            static void dump(Node* node, io::OutputStream* stream);
        protected:
            /// Node location
            Location m_location;

            /// Protected constructor for children
            Node(const Location& location);
        };
    }
}

#endif