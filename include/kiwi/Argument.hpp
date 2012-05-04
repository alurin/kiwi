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
    class Callable;

    //==--------------------------------------------------------------------==//
    /// Method argument
    class Argument {
        friend class Callable;
    public:
        /// return argument owner
        Callable* getOwner() const {
            return m_owner;
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
        Callable* m_owner;

        /// argument name
        Identifier m_name;

        /// argument type
        TypeWeak m_type;

        /// argument position
        int32_t m_position;

        Argument(Callable* owner, TypePtr type, int32_t position);
    };
}

#endif
