#ifndef KIWI_MODULE_INCLUDED
#define KIWI_MODULE_INCLUDED

#include "kiwi/Config.hpp"
#include <boost/shared_ptr.hpp>

namespace kiwi
{
    class Module;
    typedef boost::shared_ptr<Module> ModuleRef;

    #define FILE_SOURCE = 1; ///< File with source code
    #define FILE_VIEW   = 2; ///< File with view code

    class Module
    {
        Module(const Module&);            ///< NOT IMPLEMENT!!!
        Module& operator=(const Module&); ///< NOT IMPLEMENT!!!
    public:

    protected:
    };
}

#endif