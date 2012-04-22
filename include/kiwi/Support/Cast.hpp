#ifndef KIWI_SUPPORT_CAST_INCLUDED
#define KIWI_SUPPORT_CAST_INCLUDED

#include "kiwi/Config.hpp"

namespace kiwi {
    /// simple check if object is instance of class B
    template<typename D, typename S>
    bool classof(S* obj)
    {
        return D::classof(obj);
    }

    /// simple dynamic cast to instance B
    template<typename D, typename S>
    D* dyn_cast(S* obj)
    {
        if (classof<D>(obj))
            return reinterpret_cast<D*>(obj);
        return 0;
    }
}

#endif
