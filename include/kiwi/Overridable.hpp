/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_OVERRIDABLE_INCLUDED
#define KIWI_OVERRIDABLE_INCLUDED

#include "kiwi/config.hpp"
#include <set>
#include <algorithm>

namespace kiwi {
    //==--------------------------------------------------------------------==//
    /// The class Overridable is mixin class for inhrited and overridable members,
    /// e.g. fieldss and methods
    template<typename T>
    class Overridable {
        friend class Type;
    public:
        typedef boost::weak_ptr<T> reference;

        /// set of overrides
        typedef std::set<reference> override_set;

        /// iterator for set of overrides
        typedef typename override_set::iterator iterator;

        /// const iterator for set of overrides
        typedef typename override_set::const_iterator const_iterator;

        /// Is override member from parent class?
        bool isDeclared() const {
            return m_isDeclared;
        }

        /// member is overrided member from base type?
        bool isOverride() const {
            return !m_overrides.empty();
        }

        /// Is override member from parent class?
        bool isOverride(reference member) const;

        /// returns iterator pointed to begin of members set
        iterator override_begin() {
            return m_overrides.begin();
        }

        /// returns iterator pointed to begin of members set
        const_iterator override_begin() const {
            return m_overrides.begin();
        }

        /// returns iterator pointed to end of members set
        iterator override_end() {
            return m_overrides.end();
        }

        /// returns iterator pointed to end of members set
        const_iterator override_end() const {
            return m_overrides.end();
        }
    protected:
        /// list of merged parent members
        override_set m_overrides;

        /// Field is declared in owner type?
        bool m_isDeclared;

        /// constructor
        Overridable(bool isDeclared);

        /// Override member in parent class with this fiels
        void override(reference member);

        /// Override member in parent class with this fiels
        void unoverride(reference member);

        /// Change isDeclared flag
        void declare(bool value = true);
    };

    //==--------------------------------------------------------------------==//
    // constructor
    template<typename T>
    Overridable<T>::Overridable(bool isDeclared) : m_isDeclared(isDeclared) {
    }

    // Override member in parent class with this fiels
    template<typename T>
    void Overridable<T>::override(reference member) {
        m_overrides.insert(member);
    }

    // Remove override member in parent class with this fiels
    template<typename T>
    void Overridable<T>::unoverride(reference member) {
        m_overrides.erase(member);
    }

    // Override member in parent class with this fiels
    template<typename T>
    bool Overridable<T>::isOverride(reference member) const{
        return m_overrides.find(member) != m_overrides.end();
    }
    // Change isDeclared flag
    template<typename T>
    void Overridable<T>::declare(bool value) {
        m_isDeclared = value;
    }
}

#endif
