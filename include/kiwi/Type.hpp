#ifndef KIWI_TYPE_INCLUDED
#define KIWI_TYPE_INCLUDED

#include "kiwi/Member.hpp"
#include <vector>

namespace llvm {
    class Type;
}

namespace kiwi {
    namespace codegen {
        class UnaryEmitter;
        class BinaryEmitter;
        class MultiaryEmitter;
    };
    class Context;
    class Module;
    class Member;
    class Type;
    class BinaryOperator;
    class UnaryOperator;
    class MultiaryOperator;
    class Method;
    class Field;

    /// Type metadata
    class Type {
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
        Module* getModule() const {
            return m_module;
        }

        /// return LLVM analog for variables
        llvm::Type* getVarType() const {
            return m_varType;
        }

        /// add unary operator
        UnaryOperator* add(
            Member::UnaryOpcode opcode,
            Type* resultType,
            codegen::UnaryEmitter* emitter
        );

        /// add binary operator
        BinaryOperator* add(
            Member::BinaryOpcode opcode,
            Type* resultType,
            Type* operandType,
            codegen::BinaryEmitter* emitter
        );

        /// add binary operator
        MultiaryOperator* add(
            Member::MultiaryOpcode opcode,
            Type* resultType,
            std::vector<Type*> arguments,
            codegen::MultiaryEmitter* emitter
        );

        /// add field
        Field* add(const Identifier& name, Type* type);

        /// add method
        Method* add(const Identifier& name, Type* resultType, std::vector<Type*> arguments);

        /// find unary operator
        UnaryOperator* find(Member::UnaryOpcode opcode);

        /// find binary operator
        BinaryOperator* find(Member::BinaryOpcode opcode, Type* operandType);

        /// find binary operator
        MultiaryOperator* find(Member::MultiaryOpcode opcode, std::vector<Type*> arguments);

        /// find field operator
        Field* find(const Identifier& name);

        /// find method
        Method* find(const Identifier& name, std::vector<Type*> arguments);

        /// emit type metadata and structure
        virtual void emit();

        /// returns name of type
        Identifier getName() const {
            return m_name;
        }
    protected:
        /// Class uniqual identifier
        TypeID m_typeID;

        /// Type module
        Module* m_module;

        /// Name of type
        Identifier m_name;

        /// List of unary operators
        std::vector<UnaryOperator*> m_unary;

        /// List of binary operators
        std::vector<BinaryOperator*> m_binary;

        /// List of multiary operators
        std::vector<MultiaryOperator*> m_multiary;

        /// List of methods
        std::vector<Method*> m_methods;

        /// List of fields
        std::vector<Field*> m_fields;

        /// LLVM analog
        llvm::Type* m_varType;

        /// constructor
        Type(Module* module);
    };
}

#endif
