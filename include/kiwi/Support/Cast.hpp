/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_SUPPORT_CAST_INCLUDED
#define KIWI_SUPPORT_CAST_INCLUDED

#include "kiwi/config.hpp"

namespace kiwi {

    /// simple check if object is instance of class B
    template<typename D, typename S>
    bool classof(const boost::shared_ptr<S> obj) {
        return D::classof(obj);
    }

    /// simple dynamic cast to instance B
    template<typename D, typename S>
    boost::shared_ptr<D> dyn_cast(boost::shared_ptr<S> obj) {
        if (obj && classof<D>(obj))
            return boost::shared_ptr<D>(obj, reinterpret_cast<D*>(obj.get()));
        return boost::shared_ptr<D>();
    }
}

#endif
