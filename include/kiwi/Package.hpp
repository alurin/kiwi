#ifndef KIWI_PACKAGE_HPP_INCLUDED
#define KIWI_PACKAGE_HPP_INCLUDED

#include "kiwi/String.hpp"

namespace kiwi {
    class Engine;

    /// The Package class represents assembly of code, resources and virtual file system
    class Package {
    public:
        /// Consturct package for module, with unique name
        Package(Engine* engine);

        /// Returns module's owner engine
        Engine* getEngine() const {
            return m_engine;
        }

        /// Returns module name
        String getName() const {
            return m_name;
        }
    protected:
        /// Package's owner engine
        Engine* m_engine;

        /// Package name
        String m_name;
    };
}

#endif