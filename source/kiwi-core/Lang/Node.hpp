#ifndef KIWI_LANG_NODE_INTERNAL
#define KIWI_LANG_NODE_INTERNAL

#include "kiwi/config.hpp"
#include "kiwi/types.hpp"
#include "location.hh"

#define KIWI_ERROR_AND_EXIT(message, location) \
    do {                                 \
        driver.error(location, message); \
        throw message;                   \
    } while (0)

#define KIWI_NOT_IMPLEMENTED() \
    do {                                 \
        driver.error(getLocation(), "Yet not implemented"); \
        throw "Yet not implemented";                   \
    } while (0)

namespace kiwi { namespace lang {

    /// Root for all statements nodes
    class Node
    {
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

} }

#endif
