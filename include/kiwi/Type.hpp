#ifndef KIWI_TYPE_INCLUDED
#define KIWI_TYPE_INCLUDED

#include "kiwi/Config.hpp"
#include <vector>

namespace llvm
{
    class Type;
    class Function;
}

namespace kiwi
{
    typedef boost::shared_ptr<class Context>            ContextRef;
    typedef boost::shared_ptr<class Module>             ModuleRef;
    typedef boost::shared_ptr<class Type>               TypeRef;
    typedef boost::shared_ptr<class BinaryOperator>     BinaryRef;
    typedef boost::shared_ptr<class UnaryOperator>      UnaryRef;
    typedef boost::shared_ptr<class Method>             MethodRef;
    typedef boost::shared_ptr<class Field>              FieldRef;
    typedef boost::shared_ptr<class Argument>           ArgumentRef;

    typedef boost::weak_ptr<class Module>               ModuleWeak;

    namespace codegen
    {
        class UnaryEmitter;
        class BinaryEmitter;
    };

    /// Unary operator
    class UnaryOperator
    {
        friend class Type;
    public:
        enum Opcode {
            POS = 1,
            NEG,
            NOT,
            DEC,
            INC,
            PRINT
        };

        Opcode getOpcode() const {
            return m_opcode;
        }

        TypeRef getResultType() const {
            return m_resultType;
        }

        codegen::UnaryEmitter* getEmitter() const {
            return m_emitter;
        }
    protected:
        Opcode                  m_opcode;
        TypeRef                 m_resultType;
        codegen::UnaryEmitter*  m_emitter;

        /// constructor
        UnaryOperator(
            Opcode opcode,
            TypeRef resultType,
            codegen::UnaryEmitter* emitter
        );
    };

    /// Binary operator
    class BinaryOperator {
        friend class Type;
    public:
        enum Opcode {
            ADD = 1,
            SUB,
            MUL,
            DIV,
            LSH,
            RSH,
            OR,
            AND,
            EQ,
            NEQ,
            GE,
            LE,
            GT,
            LT
        };

        Opcode getOpcode() const {
            return m_opcode;
        }

        TypeRef getResultType() const {
            return m_resultType;
        }

        TypeRef getOperatorType() const {
            return m_operatorType;
        }

        codegen::BinaryEmitter* getEmitter() const {
            return m_emitter;
        }
    protected:
        Opcode                  m_opcode;
        TypeRef                 m_resultType;
        TypeRef                 m_operatorType;
        codegen::BinaryEmitter* m_emitter;

        /// constructor
        BinaryOperator(
            Opcode opcode,
            TypeRef resultType,
            TypeRef operatorType,
            codegen::BinaryEmitter* emitter
        );
    };

    class Argument {
    public:
        static ArgumentRef create(const Identifier& name, const TypeRef& type);

        Identifier getName() const {
            return m_name;
        }

        TypeRef getType () const {
            return m_type;
        }
    protected:
        Identifier  m_name;
        TypeRef     m_type;

        Argument(const Identifier& name, const TypeRef& type);
    };

    /// Methods
    class Method {
        friend class Type;
    public:
        typedef std::vector<ArgumentRef>::const_iterator const_iterator;

        Identifier getName() const {
            return m_name;
        }

        TypeRef getOwnerType() const {
            return m_ownerType;
        }

        TypeRef getResultType() const {
            return m_resultType;
        }

        llvm::Function* getFunction() const {
            return m_func;
        }

        void setFunction(llvm::Function* func) {
            m_func = func;
        }

        const_iterator begin() const { return m_arguments.begin(); }
        const_iterator end()   const { return m_arguments.end();   }
    protected:
        Identifier                  m_name;
        TypeRef                     m_ownerType;
        TypeRef                     m_resultType;
        std::vector<ArgumentRef>    m_arguments;
        llvm::Function*             m_func;

        Method(const Identifier& name, const TypeRef& ownerType, const TypeRef& resultType, std::vector<ArgumentRef> arguments);
    };

    /// Fields. Not implemented
    class Field {
        friend class Type;
    protected:
        Identifier  m_name;
        TypeRef     m_fieldType;

        Field(const Identifier& name, const TypeRef& fieldType);
    };

    /// Type metadata
    class Type : public boost::enable_shared_from_this<Type>
    {
        Type(const Type&);                   ///< NOT IMPLEMENT!!!
        Type& operator=(const Type& type);   ///< NOT IMPLEMENT!!!
    public:
        /// destructor
        virtual ~Type();

        static TypeRef create(ModuleRef module);

        /// returns type owner module
        ModuleRef getModule() const {
            return m_module.lock();
        }

        /// return LLVM analog for variables
        llvm::Type* getVarType() const {
            return m_varType;
        }

        /// add unary operator
        UnaryRef add(
            UnaryOperator::Opcode opcode,
            TypeRef resultType,
            codegen::UnaryEmitter* emitter
        );

        /// add binary operator
        BinaryRef add(
            BinaryOperator::Opcode opcode,
            TypeRef resultType,
            TypeRef operatorType,
            codegen::BinaryEmitter* emitter
        );

        /// add field
        FieldRef add(const Identifier& name, const TypeRef& type);

        /// add method
        MethodRef add(const Identifier& name, const TypeRef& resultType, std::vector<ArgumentRef> arguments);

        /// find unary operator
        UnaryRef find(UnaryOperator::Opcode opcode);

        /// find binary operator
        BinaryRef find(BinaryOperator::Opcode opcode, const TypeRef& operatorType);

        /// find method
        MethodRef find(const Identifier& name, std::vector<TypeRef> arguments);

        /// emit type metadata and structure
        void emit();
    protected:
        ModuleWeak              m_module;
        std::vector<UnaryRef>   m_unary;
        std::vector<BinaryRef>  m_binary;
        std::vector<MethodRef>  m_methods;
        std::vector<FieldRef>   m_fields;
        llvm::Type*             m_varType;

        Type(ModuleRef module);
    };
}

#endif