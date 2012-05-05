/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_SUPPORT_ARRAY_INCLUDED
#define KIWI_SUPPORT_ARRAY_INCLUDED

#include "kiwi/types.hpp"

namespace kiwi {
    ////////////////////////////////////////////////////////
    //// REMOVE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! //
    ////////////////////////////////////////////////////////
    template<typename T>
    inline std::vector< boost::shared_ptr<T> > makeVector(const boost::shared_ptr<T>& first, const std::vector< boost::shared_ptr<T> >& last) {
        std::vector< boost::shared_ptr<T> > result;
        result.push_back(first);
        result.insert(result.end(), last.begin(), last.end());
        return result;
    }

    ////////////////////////////////////////////////////////
    //// REMOVE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! //
    ////////////////////////////////////////////////////////
    template<typename T>
    inline typename std::vector< boost::shared_ptr<T> > makeVector(const boost::shared_ptr<T>& first) {
        std::vector< boost::shared_ptr<T> > result;
        result.push_back(first);
        return result;
    }

    template<typename T>
    inline std::vector< boost::shared_ptr<T> > makeVector(const boost::shared_ptr<T> first, const boost::shared_ptr<T> second) {
        std::vector< boost::shared_ptr<T> > array;
        array.push_back(first);
        array.push_back(second);
        return array;
    }
}

#endif
