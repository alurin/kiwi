/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_SUPPORT_ANCESTORMAP_INTERNAL
#define	KIWI_SUPPORT_ANCESTORMAP_INTERNAL

#include "kiwi/Type.hpp"
#include "kiwi/Ancestor.hpp"
#include <boost/signals2.hpp>
#include <map>

//Ancestor
namespace kiwi {
    /// Map for ancestor
    class AncestorMap {
    public:
        typedef std::map<TypePtr, AncestorPtr> Map;

        typedef Map::const_iterator const_iterator;

        /// Signal for insert new field
        boost::signals2::signal<void (AncestorPtr)> onInsert;

        /// constructor
        AncestorMap(Type* owner);

        /// insert reference
        bool insert(AncestorPtr ancestor);

        /// find ancestor
        AncestorPtr find(TypePtr type);

        /// return size
        size_t size() const {
            return m_ancestors.size();
        }

        /// is empty?
        bool empty() const {
            return m_ancestors.empty();
        }

        /// return iterator pointed to begin
        const_iterator begin() const {
            return m_ancestors.begin();
        }

        /// return iterator pointed to end
        const_iterator end() const {
            return m_ancestors.end();
        }
    protected:
        /// Owner for this implementation
        Type* m_owner;

        /// set of members
        Map m_ancestors;
    };

    // constructor
    inline
    AncestorMap::AncestorMap(Type* owner)
    : m_owner(owner) {
    }


    // insert reference
    inline
    bool AncestorMap::insert(AncestorPtr ancestor) {
        if (m_ancestors.insert(std::make_pair(ancestor->getAncestorType(), ancestor)).second) {
            onInsert(ancestor);
            return true;
        }
        return false;
    }

    // find ancestor
    inline
    AncestorPtr AncestorMap::find(TypePtr type) {
        Map::const_iterator result = m_ancestors.find(type);
        if (result != m_ancestors.end())
            return result->second;
        return AncestorPtr();
    }
}

#endif	/* ANCESTORMAP_HPP */
