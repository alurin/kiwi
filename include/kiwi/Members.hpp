#ifndef KIWI_MEMBERS_INCLUDED
#define KIWI_MEMBERS_INCLUDED

#include "kiwi/Member.hpp"
#include <vector>

namespace kiwi
{
    class Callable;

    namespace codegen {
        class CallableEmitter;
        class UnaryEmitter;
        class BinaryEmitter;
    };

    //==--------------------------------------------------------------------==//
    /// Method argument
    class Argument {
        friend class Callable;
    public:
        /// return argument owner
        Callable* getOwner() const {
            return m_owner;
        }

        /// returns argument name
        Identifier getName() const {
            return m_name;
        }

        /// set argument name
        void setName(const Identifier& name) {
            m_name = name;
        }

        /// returns argument type
        Type* getType () const {
            return m_type;
        }

        /// returns argument position
        int32_t getPosition() const {
            return m_position;
        }
    protected:
        /// argument owner method
        Callable* m_owner;

        /// argument name
        Identifier m_name;

        /// argument type
        Type* m_type;

        /// argument position
        int32_t m_position;

        Argument(Callable* owner, Type* type, int32_t position);
    };

    //==--------------------------------------------------------------------==//
    /// Callable member, common base for all operators and methods
    class Callable : public Member {
    public:
        typedef std::vector<Type*>      TypeVector;
        typedef std::vector<Argument*>  ArgumentVector;
        typedef ArgumentVector::const_iterator const_iterator;

        /// virtual destructo
        virtual ~Callable();

        /// returns callable's return type
        Type* getReturnType() const {
            return m_returnType;
        }

        /// returns size of arguments
        size_t size() const {
            return m_args.size();
        }

        /// empty arguments?
        bool empty() const {
            return m_args.empty();
        }

        /// Check signature
        bool hasSignature(const TypeVector& types, bool isCast = false);

        /// Return emitter for callable
        codegen::CallableEmitter* getEmitter() const {
            return m_emitter;
        }

        /// returns llvm analog
        llvm::Function* getFunction() const {
            return m_func;
        }

        /// set llvm analog
        void setFunction(llvm::Function* func);

        /// returns pointer to first argument from callable (iterator)
        const_iterator begin() const {
            return m_args.begin();
        }

        /// return pointer after last argument from callable (iterator)
        const_iterator end() const {
            return m_args.end();
        }
    protected:
        /// return type
        Type* m_returnType;

        /// list of arguments
        ArgumentVector m_args;

        /// Emitter for generate IR code
        codegen::CallableEmitter* m_emitter;

        /// External or internal IR function
        llvm::Function* m_func;

        /// constructor with standart emitter
        Callable(Type* ownerType, Type* returnType);

        /// constructor
        Callable(Type* ownerType, Type* returnType, codegen::CallableEmitter* emitter);

        /// constructor with standart emitter
        Callable(Type* ownerType, Type* returnType, TypeVector types);

        /// constructor
        Callable(Type* ownerType, Type* returnType, TypeVector types, codegen::CallableEmitter* emitter);
    private:
        /// create arguments from types
        void makeArgumentsFromTypes(TypeVector types);
    };

    //==--------------------------------------------------------------------==//
    /// Unary operator
    class UnaryOperator : public Callable {
        friend class Type;
    public:
        /// virtual destructor
        virtual ~UnaryOperator();

        /// returns binary operator opcode
        UnaryOpcode getOpcode() const {
            return m_opcode;
        }

        /// returns result type
        Type* getReturnType() const {
            return m_returnType;
        }

        /// classof check
        static bool classof(class Member* type) {
            return type->getMemberID() == UnaryOperatorID;
        }

        /// classof check
        static bool classof(const UnaryOperator*) {
            return true;
        }
    protected:
        UnaryOpcode             m_opcode;

        /// constructor
        UnaryOperator(
            UnaryOpcode opcode,
            Type* ownerType,
            Type* resultType,
            codegen::UnaryEmitter* emitter
        );
    };

    //==--------------------------------------------------------------------==//
    /// Binary operator
    class BinaryOperator : public Callable {
        friend class Type;
    public:
        /// virtual destructor
        virtual ~BinaryOperator();

        /// returns binary opcode
        BinaryOpcode getOpcode() const {
            return m_opcode;
        }

        /// classof check
        static bool classof(class Member* type) {
            return type->getMemberID() == BinaryOperatorID;
        }

        /// classof check
        static bool classof(const BinaryOperator&) {
            return true;
        }
    protected:
        BinaryOpcode             m_opcode;

        /// constructor
        BinaryOperator(
            BinaryOpcode opcode,
            Type* ownerType,
            Type* resultType,
            Type* operandType,
            codegen::BinaryEmitter* emitter
        );
    };

    //==--------------------------------------------------------------------==//
    /// Method argument
    class MultiaryOperator : public Callable {
        friend class Type;
    public:
        /// destructor
        ~MultiaryOperator();

        /// returns multiary opcode
        MultiaryOpcode getOpcode() const {
            return m_opcode;
        }
    protected:
        MultiaryOpcode            m_opcode;

        // constructor
        MultiaryOperator(
            MultiaryOpcode opcode,
            Type* ownerType,
            Type* resultType,
            TypeVector types,
            codegen::CallableEmitter* emitter
        );
    };

    //==--------------------------------------------------------------------==//
    /// Method member
    class Method : public Callable {
        friend class Type;
    public:
        /// Returns method name
        Identifier getName() const {
            return m_name;
        }

        /// returns this is static method?
        bool isStatic() const {
            return false;
        }

        /// returns this is abstract method?
        bool isAbstract() const {
            return false;
        }

        /// classof check
        static bool classof(class Member* type) {
            return type->getMemberID() == MethodID;
        }

        /// classof check
        static bool classof(const Method*) {
            return true;
        }
    protected:
        Identifier          m_name;

        Method(const Identifier& name, Type* ownerType, Type* resultType, std::vector<Type*> arguments);
    };

    //==--------------------------------------------------------------------==//
    /// Field member
    class Field : public Member {
        friend class Type;
        friend class ObjectType;
    public:
        /// virtual destructor
        virtual ~Field();

        /// returns field name
        Identifier getName() const {
            return m_name;
        }

        /// returns field type
        Type* getFieldType() const {
            return m_fieldType;
        }

        /// returns position in address map
        int32_t getPosition() const {
            return m_position;
        }

        /// classof check
        static bool classof(class Member* type) {
            return type->getMemberID() == FieldID;
        }

        /// classof check
        static bool classof(const Field*) {
            return true;
        }
    protected:
        Identifier m_name;
        Type* m_fieldType;
        int32_t m_position;

        /// constructor
        Field(const Identifier& name, Type* ownerType, Type* fieldType);

        /// Set position
        void setPosition(int32_t position) {
            m_position = position;
        }
    };
}

#endif
