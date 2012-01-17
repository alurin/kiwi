/*
 *******************************************************************************
 *   Copyright (C) 2010 Kiwi Developers Group
 *   All Rights Reserved.
 *******************************************************************************
 */
/**
 * @file
 * @brief
 */
#ifndef KIWI_SCRIPT_COMPOUNDLIST_HPP_INCLUDED
#define KIWI_SCRIPT_COMPOUNDLIST_HPP_INCLUDED

#include "kiwi/Config.hpp"
#include <vector>
#include <list>

namespace kiwi {
    namespace script {
        template<typename T>
        class CompoundList {
        public:
            typedef std::vector<T*> Values;
            typedef std::list<T*> elements;

            typedef CompoundList<T> this_type;
            typedef T* element_type;
            static this_type* create()
            {
                return new this_type();
            }
            static this_type* combine(T* lvalue, T* rvalue)
            {
                CompoundList<T>* list = create();
                if (lvalue != 0) list->push_back(lvalue);
                if (rvalue != 0) list->push_back(rvalue);
                return list;
            }
            static this_type* combine(this_type* list, T* value)
            {
                if (list == 0) list = create();
                if (value != 0) list->push_back(value);
                return list;
            }
            static this_type* combine(T* value, this_type* list)
            {
                if (list == 0) list = create();
                if (value != 0) list->push_front(value);
                return list;
            }
            void push_front(T* value)
            {
                _values.push_front(value);
            }
            void push_back(T* value)
            {
                _values.push_back(value);
            }
            operator Values()
            {
                return Values(_values.begin(), _values.end());
            }
            size_t size() const
            {
                return _values.size();
            }

        protected:
            elements _values;
        };
    }
}

#endif	/* COMPOUNDLIST_HPP */
