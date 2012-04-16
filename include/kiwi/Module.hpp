#ifndef KIWI_MODULE_INCLUDED
#define KIWI_MODULE_INCLUDED

#include "kiwi/Config.hpp"
#include "kiwi/Version.hpp"
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
        /// Create module
        ModuleRef create(const UnicodeString& name, const Version& version);

        /// Load module from cache
        ModuleRef load(const UnicodeString& name, const Version& version);

        /// Load module from path
        ModuleRef load(const Path& path);

        /// Returns module name
        UnicodeString getName() const
        {
            return m_name;
        }

        /// Returns module version
        Version getVersion() const
        {
            return m_version;
        }

    protected:
        UnicodeString m_name;
        UnicodeString m_version;

        Module(UnicodeString name, UnicodeString version);
    };
}

#endif