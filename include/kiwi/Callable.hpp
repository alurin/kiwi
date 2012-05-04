/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_CALLABLE_INCLUDED
#define KIWI_CALLABLE_INCLUDED

#include "kiwi/Member.hpp"
#include <vector>

namespace llvm {
    class Function;
}

namespace kiwi {
    class Argument;

    /// Callable implementation strategy
    class CallablePolicy;

    //==--------------------------------------------------------------------==//
    /// Callable member, common base for all operators and methods
    class Callable : public Member {
    public:
        typedef std::vector<TypePtr>              TypeVector;
        typedef std::vector<Argument*>          ArgumentVector;
        typedef ArgumentVector::const_iterator  const_iterator;

        /// virtual destructo
        virtual ~Callable();

        /// returns callable's return type
        TypePtr getReturnType() const {
            return m_returnType.lock();
        }

        /// Check signature
        bool hasSignature(const TypeVector& types, bool isCast = false) const;

        /// get callable implementation policy
        CallablePolicy* getPolicy() const {
            return m_policy;
        }

        /// set callable implementation policy
        void setPolicy(CallablePolicy* policy) {
            m_policy = policy;
        }

        /// get LLVM analog function
        void setFunction(llvm::Function* func);

        /// return LLVM analog function
        llvm::Function* getFunction() const {
            return m_func;
        }

        /// returns argument by index
        Argument* getArgument(int32_t indexAt) {
            if (indexAt < 0 || size() <= indexAt) {
                return 0;
            }
            return m_args[indexAt];
        }

        /// returns argument by name [not implemented]
        Argument* getArgument(const Identifier& name);

        /// returns size of arguments
        size_t size() const {
            return m_args.size();
        }

        /// empty arguments?
        bool empty() const {
            return m_args.empty();
        }

        /// returns pointer to first argument from callable (iterator)
        const_iterator arg_begin() const {
            return m_args.begin();
        }

        /// return pointer after last argument from callable (iterator)
        const_iterator arg_end() const {
            return m_args.end();
        }
    protected:
        /// return type
        TypeWeak m_returnType;

        /// list of arguments
        ArgumentVector m_args;

        /// Emitter for generate IR code
        CallablePolicy* m_policy;

        /// Function
        llvm::Function* m_func;

        /// constructor
        Callable(TypePtr ownerType, TypePtr returnType, TypeVector types);

        /// constructor for inherited callable
        Callable(TypePtr ownerType, Callable* callable);
    private:
        /// create arguments from types
        /// @todo move in anonym namespace
        void makeArgumentsFromTypes(TypeVector types);

        /// create arguments from parent callable
        /// @todo move in anonym namespace
        void cloneArguments(TypePtr thisType, ArgumentVector args);
    };
}

#endif
