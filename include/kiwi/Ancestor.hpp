/*
 * File:   Ancestor.hpp
 * Author: alurin
 *
 * Created on 21 Май 2012 г., 6:44
 */

#ifndef KIWI_ANCESTOR_INCLUDED
#define	KIWI_ANCESTOR_INCLUDED

#include "kiwi/types.hpp"

namespace kiwi {
    class AncestorMetadata;
    
    /// Information about ancestor types
    class Ancestor {
        friend class Type;
    public:
        /// destructor
        virtual ~Ancestor();

        /// return ancestor type
        TypePtr getAncestorType() const {
            return m_ancestorType.lock();
        }

        /// return derived type
        TypePtr getDerivedType() const {
            return m_derivedType.lock();
        }

        /// return ancestor metadata
        AncestorMetadata* getMetadata() const {
            return m_meta;
        }
    protected:
        /// ancestor type
        TypeWeak m_ancestorType;

        /// derived type
        TypeWeak m_derivedType;

        /// internal metadata
        AncestorMetadata* m_meta;

        /// constructor
        Ancestor(TypePtr derivedType, TypePtr ancestorType);
    };
}

#endif	/* ANCESTOR_HPP */

