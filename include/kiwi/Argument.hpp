/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_ARGUMENT_INCLUDED
#define KIWI_ARGUMENT_INCLUDED

#include "kiwi/types.hpp"

namespace kiwi {
    class Type;
    class Method;

    //==--------------------------------------------------------------------==//
    /// Method argument
    class Argument {
        friend class Method;
    public:
        /// return argument owner
        MethodPtr getOwner() const {
            return m_owner.lock();
        }

        /// returns argument name
        Identifier getName() const {
            return m_name;
        }

        /// set argument name
        void setName(const Identifier& name) {
            m_name = name;
        }

        /// returns argument type
        TypePtr getType () const {
            return m_type.lock();
        }

        /// returns argument position
        int32_t getPosition() const {
            return m_position;
        }
    protected:
        /// argument owner method
        MethodWeak m_owner;

        /// argument name
        Identifier m_name;

        /// argument type
        TypeWeak m_type;

        /// argument position
        int32_t m_position;

        Argument(MethodPtr owner, TypePtr type, int32_t position);
    };
}

#endif
