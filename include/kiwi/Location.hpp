#ifndef KIWI_LOCATION_HPP_INCLUDED
#define KIWI_LOCATION_HPP_INCLUDED

#include "kiwi/Types.hpp"

namespace kiwi {
    namespace script {
        /// Internal location class
        class location;
    }

    /**
     * The Location class represents node's location in source stream
     */
    class KIWI_API Location {
    public:
        /// Default constructor
        Location(const String& streamName);

        /// Internal constructor
        KIWI_LOCAL Location(const script::location& loc);

        String getStreamName() const {
            return m_streamName;
        }
    protected:
        String m_streamName;
    };
}

#endif