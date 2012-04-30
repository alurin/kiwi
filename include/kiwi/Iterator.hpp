#ifndef KIWI_ITERATOR_INCLUDED
#define KIWI_ITERATOR_INCLUDED

namespace kiwi {
    class Field;
    class Callable;

    /// Iterator for fields
    class FieldIterator {
    public:
        /// Filter for fields
        virtual bool isValid(Field* field);

        /// Accept field and run
        virtual void accept(Field* field);
    }; // class FieldIterator

    /// Iterator for callables
    class CallableIterator {
    public:
        /// Filter for callables
        virtual bool isValid(Callable* callable);

        /// Accept callable and run
        virtual void accept(Callable* callable);
    }; // class CallableIterator
}

#endif
