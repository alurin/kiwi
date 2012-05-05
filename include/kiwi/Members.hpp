/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_MEMBERS_INCLUDED
#define KIWI_MEMBERS_INCLUDED

#include "kiwi/Member.hpp"
#include "kiwi/Overridable.hpp"

/// @todo Remove public dependense
namespace llvm {
    class Function;
}

namespace kiwi
{
/// Method implementation strategy
    class MethodPolicy;

    //==--------------------------------------------------------------------==//
    /// Method member
    class Method : public Member, public Overridable<Method> {
        friend class Type;
        template<class Method> friend class MemberSet;
    public:
        typedef std::vector<TypePtr>                TypeVector;
        typedef std::vector<ArgumentPtr>            ArgumentVector;
        typedef ArgumentVector::const_iterator      const_iterator;

        /// virtual destructor
        virtual ~Method();


        /// Create method
        static MethodPtr create(TypePtr ownerType, TypePtr returnType, std::vector<TypePtr> arguments, const Identifier& name = "");

        /// Create operator
        static MethodPtr create(TypePtr ownerType, TypePtr returnType, std::vector<TypePtr> arguments, const MethodOpcode& opcode);

        /// Returns method name
        Identifier getName() const {
            return m_name;
        }

        /// method identifier
        MethodOpcode getOpcode() const{
            return m_opcode;
        }

        /// Method is operation?
        bool isOperator() const {
            return m_opcode != Member::Subroutine;
        }

        /// returns callable's return type
        TypePtr getReturnType() const {
            return m_returnType.lock();
        }

        /// Check signature
        bool hasSignature(const TypeVector& types, bool isCast = false) const;

        /// get callable implementation policy
        MethodPolicy* getPolicy() const {
            return m_policy;
        }

        /// set callable implementation policy
        void setPolicy(MethodPolicy* policy) {
            m_policy = policy;
        }

        /// get LLVM analog function
        void setFunction(llvm::Function* func);

        /// return LLVM analog function
        llvm::Function* getFunction() const {
            return m_func;
        }

        /// returns argument by index
        ArgumentPtr getArgument(int32_t indexAt) {
            if (indexAt < 0 || size() <= indexAt) {
                return ArgumentPtr();
            }
            return m_args[indexAt];
        }

        /// returns argument by name [not implemented]
        ArgumentPtr getArgument(const Identifier& name);

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

        /// classof check
        static bool classof(const MemberPtr type) {
            return type->getMemberID() == MethodID;
        }

        /// classof check
        static bool classof(const MethodPtr) {
            return true;
        }
    protected:
        /// method identifier
        Identifier m_name;

        /// method identifier
        MethodOpcode m_opcode;

        /// return type
        TypeWeak m_returnType;

        /// list of arguments
        ArgumentVector m_args;

        /// Emitter for generate IR code
        MethodPolicy* m_policy;

        /// Function
        llvm::Function* m_func;

        /// constructor
        Method(const Identifier& name, TypePtr ownerType, TypePtr returnType);

        /// constructor
        Method(MethodOpcode opcode, TypePtr ownerType, TypePtr returnType);

        /// constructor for inhertit method
        Method(TypePtr ownerType, MethodPtr method);

        /// inherit member from base type
        static MethodPtr inherit(TypePtr ownerType, MethodPtr method);

        /// create arguments from types
        void initializateArguments(TypeVector types);

        /// create arguments from parent callable
        void initializateArguments(TypePtr thisType, ArgumentVector args);
    };

    //==--------------------------------------------------------------------==//
    /// Field member
    class Field : public Member, public Overridable<Field> {
        friend class Type;
        friend class ObjectType;
        template<class Field> friend class MemberSet;
    public:
        /// create field
        static FieldPtr create(TypePtr ownerType, TypePtr fieldType, const Identifier& name = "");

        /// returns field name
        Identifier getName() const {
            return m_name;
        }

        /// returns field type
        TypePtr getFieldType() const {
            return m_fieldType.lock();
        }

        /// returns position in address map
        int32_t getPosition() const {
            return m_position;
        }

        /// classof check
        static bool classof(const MemberPtr type) {
            return type->getMemberID() == FieldID;
        }

        /// classof check
        static bool classof(const FieldPtr) {
            return true;
        }
    protected:
        /// field name
        Identifier m_name;

        /// field type
        TypeWeak m_fieldType;

        /// field position in address map for class
        int32_t m_position;

        /// constructor: inherit field field
        Field(TypePtr ownerType, FieldPtr field);

        /// constructor: declare field field
        Field(TypePtr ownerType, TypePtr fieldType);

        /// constructor: declare anonym field
        Field(const Identifier& name, TypePtr ownerType, TypePtr fieldType);

        /// Set position
        void setPosition(int32_t position) {
            m_position = position;
        }

        /// Set name
        void setName(const Identifier& name) {
            m_name = name;
        }
        /// inherit field from base type
        static FieldPtr inherit(TypePtr ownerType, FieldPtr field);
    };
}

#endif
