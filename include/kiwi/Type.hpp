#ifndef KIWI_TYPE_INCLUDED
#define KIWI_TYPE_INCLUDED

#include "kiwi/Config.hpp"

namespace kiwi
{
    typedef boost::shared_ptr<class Module>     ModuleRef;
    typedef boost::shared_ptr<class Module>     ModuleWeak;

    class Type : public boost::enable_shared_from_this<Type>
    {
        Type(const Type&);                  ///< NOT IMPLEMENT!!!
        Type& operator(const Type& type);   ///< NOT IMPLEMENT!!!
    public:
        ModuleRef getModule() const {

        }
    protected:
        ModuleWeak module;

        Type(ModuleRef module);
    };
}

#endif