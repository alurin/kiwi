/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_LANG_NODE_INTERNAL
#define KIWI_LANG_NODE_INTERNAL

#include "config.hpp"
#include "location.hh"

namespace kiwi { namespace lang {

    /// Root for all statements nodes
    class Node {
        Node(const Node&);              ///< NOT IMPLEMENT!!!
        Node& operator=(const Node&);   ///< NOT IMPLEMENT!!!
    public:
        /// @todo move
        virtual ~Node() {};

        /// set node location
        void setLocation(const location& loc) {
            m_location = loc;
        }

        /// returns node location
        location getLocation() const {
            return m_location;
        }
    protected:
        location m_location;

        /// @todo move
        Node() {};
    };


    inline
    Location to_location(const Node* node) {
        return to_location(node->getLocation());
    }
} }

#endif
