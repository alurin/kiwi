/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_ITERATOR_SUPPORT_INCLUDED
#define	KIWI_ITERATOR_SUPPORT_INCLUDED

#include "kiwi/types.hpp"

namespace kiwi {
    /// Iterator over type method
    class MethodIterator {
    public:
        virtual void visit(MethodPtr method) =0;
    };

    /// Iterator over type fields
    class FieldIterator {
    public:
        virtual void visit(FieldPtr field) =0;
    };

    /// Iteratir over type members
    class MemberIterator : public MethodIterator, public FieldIterator {
    };

    /// Iterator over type ancestors
    class AncestorIterator {
    public:
        virtual void visit(AncestorPtr ancestor) =0;
    };
}

#endif	/* ITERATOR_HPP */
