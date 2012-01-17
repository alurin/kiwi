#ifndef KIWI_SCRIPT_NODE_HPP_INCLUDED
#define KIWI_SCRIPT_NODE_HPP_INCLUDED

#include "kiwi/Config.hpp"

namespace kiwi {
    namespace script {
        /// The Node class is abstract root for all syntaxis nodes
        class Node {
        public:
            /// Virtual node destructor
            virtual ~Node();

        protected:
            /// Protected constructor for children
            Node();
        };
    }
}

#endif