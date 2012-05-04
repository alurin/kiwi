/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_TYPES_HPP_INCLUDED
#define KIWI_TYPES_HPP_INCLUDED

#include "kiwi/config.hpp"

// Include std string and intefers headers
#include "string.h"
#include "stdint.h"

// Include unicode headers
#include <unicode/unistr.h>

// Smart pointers
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/smart_ptr/enable_shared_from_this.hpp>

namespace kiwi {
    /// String contains characters in Unicode 16 encoding
    typedef UnicodeString   String;

    /// ASCII string contains paths
    typedef std::string     Path;

    /// ASCII string for identificators
    typedef std::string     Identifier;

    //== Smart pointers: General elements
    typedef boost::shared_ptr<class Context>            ContextPtr;
    typedef boost::weak_ptr<class Context>              ContextWeak;
    typedef boost::shared_ptr<class Module>             ModulePtr;
    typedef boost::weak_ptr<class Module>               ModuleWeak;

    //== Smart pointers: Types
    typedef boost::shared_ptr<class Type>               TypePtr;
    typedef boost::weak_ptr<class Type>                 TypeWeak;
    typedef boost::shared_ptr<class VoidType>           VoidPtr;
    typedef boost::shared_ptr<class IntegerType>        IntegerPtr;
    typedef boost::shared_ptr<class BooleanType>        BooleanPtr;
    typedef boost::shared_ptr<class CharType>           CharPtr;
    typedef boost::shared_ptr<class StringType>         StringPtr;
    typedef boost::shared_ptr<class InterfaceType>      InterfacePtr;
    typedef boost::shared_ptr<class ObjectType>         ObjectPtr;

    //== Smart pointers: Members
    typedef boost::shared_ptr<class Member>             MemberPtr;
    typedef boost::shared_ptr<class Callable>           CallablePtr;
    typedef boost::shared_ptr<class Method>             MethodPtr;
    typedef boost::shared_ptr<class Field>              FieldPtr;
    typedef boost::shared_ptr<class UnaryOperator>      UnaryPtr;
    typedef boost::shared_ptr<class BinaryOperator>     BinaryPtr;
    typedef boost::shared_ptr<class MultiaryOperator>   MultiaryPtr;
}

#endif
