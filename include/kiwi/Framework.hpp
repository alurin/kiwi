#ifndef KIWI_FRAMEWORK_INCLUDED
#define KIWI_FRAMEWORK_INCLUDED

#include "kiwi/Config.hpp"
#include <boost/shared_ptr.hpp>

namespace kiwi
{
    class Framework;
    typedef boost::shared_ptr<Framework> FrameworkRef;

    /**
     * General enter point for Kiwi compiler infrastructure
     *
     * @author Vasiliy Sheredeko
     * @since 2012-04-15
     */
    class Framework
    {
        Framework(const Framework&);    ///< NOT IMPLEMENT!!!
        Framework& operator=(const Framework&);    ///< NOT IMPLEMENT!!!

    public:
        /// Create new isntance and return smart reference for this instance
        static FrameworkRef create();

        /// Include and run file as script
        void includeFile(const Path& filename);
    private:
        Framework();
    };
}

#endif