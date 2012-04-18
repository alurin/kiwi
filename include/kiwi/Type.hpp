#ifndef KIWI_TYPE_INCLUDED
#define KIWI_TYPE_INCLUDED

#include "kiwi/Config.hpp"
#include <vector>

namespace llvm
{
    class Type;
}

namespace kiwi
{
    typedef boost::shared_ptr<class Module>             ModuleRef;
    typedef boost::weak_ptr<class Module>               ModuleWeak;
    typedef boost::shared_ptr<class Type>               TypeRef;
    typedef boost::shared_ptr<class BinaryOperator>     BinaryRef;
    typedef boost::shared_ptr<class UnaryOperator>      UnaryRef;

    namespace codegen
    {
        class UnaryEmitter;
        class BinaryEmitter;
    };

    /// Binary operator
    class BinaryOperator {
    public:
        enum Opcode {
            ADD = 1,
            SUB,
            MUL,
            DIV
        };

    protected:
        BinaryOperator();

        /// create binary operator with binary emitter
        static BinaryRef create(TypeRef firstType, TypeRef secondType, class BinaryEmmiter* emitter);

        /// create binary operator with callable emitter
        BinaryRef create(TypeRef firstType, TypeRef secondType);
    };

    /// Unary operator
    class UnaryOperator
    {
    public:
        enum Opcode {
            POS = 1,
            NEG,
            NOT
        };
    };

    /// Type metadata
    class Type : public boost::enable_shared_from_this<Type>
    {
        Type(const Type&);                  ///< NOT IMPLEMENT!!!
        Type& operator=(const Type& type);   ///< NOT IMPLEMENT!!!
    public:
        /// destructor
        virtual ~Type();

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

        /// find binary operator
        BinaryRef find(BinaryOperator::Opcode opcode, TypeRef operatorType);
    protected:
        ModuleWeak              m_module;
        std::vector<UnaryRef>   m_unary;
        std::vector<BinaryRef>  m_binary;

        llvm::Type*             m_varType;

        Type(ModuleRef module);
    };

    /// Integers types metadata
    class IntType : public Type
    {
        friend class Context;
    public:
        static TypeRef get32(ContextRef context);
    private:
        /// constructor
        IntType(ModuleRef module, int32_t size, bool unsign);

        /// create integer type
        static TypeRef create(ModuleRef module, int32_t size, bool unsign);

        /// initializator
        void initializate();
    };

    /// Boolean type metadata
    class BoolType : public Type
    {
    public:
        static TypeRef get(ContextRef context);
    protected:
        /// constructor
        BoolType(ModuleRef module);

        /// create module type
        static TypeRef create(ModuleRef module);

        /// initializator
        void initializate();
    };
}

#endif