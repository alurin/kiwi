/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_MODULE_INCLUDED
#define KIWI_MODULE_INCLUDED

#include "kiwi/types.hpp"
#include <vector>
#include <map>

namespace kiwi
{
    class Context;
    class Type;
    class Method;
    /// Storage for internal module metadata
    class ModuleImpl;

    /// Assembly of types
    class Module : public boost::enable_shared_from_this<Module>, public boost::noncopyable {
    public:
        /// destructor
        ~Module();

        /// create module
        static ModulePtr create(const Identifier& name, ContextPtr ref);

        /// returns internal context metadata
        ModuleImpl* getMetadata() const {
            return m_metadata;
        }

        /// return name of module
        Identifier getName() const {
            return m_name;
        }

        /// include and run file as script
        bool includeFile(const Path& filename);

        /// returns module owner
        ContextPtr getContext() const {
            return m_context.lock();
        }

        /// find type with name
        TypePtr find(const Identifier& name) const;

        /// returns main method in current module
        MethodPtr getMainMethod() const;

        /// build module
        void build();

        /// dump module
        void dump();
    protected:
        /// module name
        Identifier m_name;

        /// module context
        ContextWeak m_context;

        /// module internal metadata
        ModuleImpl* m_metadata;

        /// module constructor
        Module(const Identifier& name, ContextPtr ref);
    };
}

#endif
