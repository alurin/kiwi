#ifndef KIWI_TYPE_INCLUDED
#define KIWI_TYPE_INCLUDED

#include "kiwi/Member.hpp"
#include <vector>

namespace llvm
{
    class Type;
}

namespace kiwi
{
    typedef boost::shared_ptr<class Context>            ContextRef;
    typedef boost::shared_ptr<class Module>             ModuleRef;
    typedef boost::shared_ptr<class Type>               TypeRef;
    typedef boost::shared_ptr<class Argument>           ArgumentRef;
    typedef boost::weak_ptr<class Module>               ModuleWeak;
    typedef boost::weak_ptr<class Type>                 TypeWeak;
    typedef boost::shared_ptr<class VoidType>           VoidTy;
    typedef boost::shared_ptr<class IntType>            IntTy;
    typedef boost::shared_ptr<class BoolType>           BoolTy;
    typedef boost::shared_ptr<class CharType>           CharTy;
    typedef boost::shared_ptr<class StringType>         StringTy;
    typedef boost::shared_ptr<class InterfaceType>      InterfaceTy;
    typedef boost::shared_ptr<class ObjectType>         ObjectTy;

    namespace codegen
    {
        class UnaryEmitter;
        class BinaryEmitter;
    };

    /// Type metadata
    class Type : public boost::enable_shared_from_this<Type>
    {
        Type(const Type&);                   ///< NOT IMPLEMENT!!!
        Type& operator=(const Type& type);   ///< NOT IMPLEMENT!!!
    public:
        /// Type identifier
        enum TypeID {
            VoidID = 1,
            IntID,
            BoolID,
            CharID,
            StringID,
            ObjectID
        };

        /// destructor
        virtual ~Type();

        /// returns type identifier
        TypeID getTypeID() const {
            return m_typeID;
        }

        /// returns type owner module
        ModuleRef getModule() const {
            return m_module.lock();
        }

        /// return LLVM analog for variables
        llvm::Type* getVarType() const {
            return m_varType;
        }

        /// return LLVM analog for address map
        llvm::GlobalVariable* getVarAddressMap() const {
            return m_addressMap;
        }

        /// return LLVM analog for address map
        llvm::GlobalVariable* getVarVirtualTable() const {
            return m_virtualTable;
        }

        /// add unary operator
        UnaryRef add(
            Member::UnaryOpcode opcode,
            TypeRef resultType,
            codegen::UnaryEmitter* emitter
        );

        /// add binary operator
        BinaryRef add(
            Member::BinaryOpcode opcode,
            TypeRef resultType,
            TypeRef operandType,
            codegen::BinaryEmitter* emitter
        );

        /// add field
        FieldRef add(const Identifier& name, const TypeRef& type);

        /// add method
        MethodRef add(const Identifier& name, const TypeRef& resultType, std::vector<ArgumentRef> arguments);

        /// find unary operator
        UnaryRef find(Member::UnaryOpcode opcode);

        /// find binary operator
        BinaryRef find(Member::BinaryOpcode opcode, const TypeRef& operandType);

        /// find unary operator
        FieldRef find(const Identifier& name);

        /// find method
        MethodRef find(const Identifier& name, std::vector<TypeRef> arguments);

        /// emit type metadata and structure
        void emit();
    protected:
        /// Class uniqual identifier
        TypeID                  m_typeID;
        ModuleWeak              m_module;
        std::vector<UnaryRef>   m_unary;
        std::vector<BinaryRef>  m_binary;
        std::vector<MethodRef>  m_methods;
        std::vector<FieldRef>   m_fields;
        llvm::Type*             m_varType;
        llvm::GlobalVariable*   m_addressMap;
        llvm::GlobalVariable*   m_virtualTable;

        Type(ModuleRef module);
    };
}

#endif