#ifndef KIWI_DERIVEDTYPES_INCLUDED
#define KIWI_DERIVEDTYPES_INCLUDED

#include "kiwi/Type.hpp"

namespace kiwi {
    //==--------------------------------------------------------------------==//
    /// Void types metadata
    class VoidType : public Type {
        friend class Context;
    public:
        /// returns void type from context
        static VoidType* get(Context* context);

        /// classof check
        static bool classof(const Type* type) {
            return type->getTypeID() == VoidID;
        }

        /// classof check
        static bool classof(const VoidType*) {
            return true;
        }
    private:
        /// constructor
        VoidType(Module* module);

        /// create integer type
        static VoidType* create(Module* module);
    };

    //==--------------------------------------------------------------------==//
    /// Integers types metadata
    class IntType : public Type
    {
        friend class Context;
    public:
        /// returns 32-bit signed integer type for context
        static IntType* get32(Context* context);

        /// classof check
        static bool classof(const Type* type) {
            return type->getTypeID() == IntID;
        }

        /// classof check
        static bool classof(const IntType*) {
            return true;
        }
    private:
        /// constructor
        IntType(Module* module, int32_t size, bool unsign);

        /// create integer type
        static IntType* create(Module* module, int32_t size, bool unsign);

        /// initializator
        void initializate();
    };

    //==--------------------------------------------------------------------==//
    /// Boolean type metadata
    class BoolType : public Type
    {
        friend class Context;
    public:
        /// returns boolean type from context
        static BoolType* get(Context* context);

        /// classof check
        static bool classof(const Type* type) {
            return type->getTypeID() == BoolID;
        }

        /// classof check
        static bool classof(const BoolType*) {
            return true;
        }
    protected:
        /// constructor
        BoolType(Module* module);

        /// create module type
        static BoolType* create(Module* module);

        /// initializator
        void initializate();
    };

    //==--------------------------------------------------------------------==//
    /// Character type metadata
    class CharType : public Type {
        friend class Context;
    public:
        /// return unicode character type from context
        static CharType* get(Context* context);

        /// classof check
        static bool classof(const Type* type) {
            return type->getTypeID() == CharID;
        }

        /// classof check
        static bool classof(const CharType*) {
            return true;
        }
    protected:
        /// constructor
        CharType(Module* module);

        /// create module type
        static CharType* create(Module* module);

        /// initializator
        void initializate();
    };

    //==--------------------------------------------------------------------==//
    /// String type metdata
    class StringType : public Type {
        friend class Context;
    public:
        /// returns unicode string type from context
        static StringType* get(Context* context);

        /// classof check
        static bool classof(const Type* type) {
            return type->getTypeID() == StringID;
        }

        /// classof check
        static bool classof(const StringType*) {
            return true;
        }
    protected:
        /// constructor
        StringType(Module* module);

        /// create module type
        static StringType* create(Module* module);

        /// initializator
        void initializate();
    };

    //==--------------------------------------------------------------------==//
    /// Interfaces metadata
    class InterfaceType : public Type {
    public:
        /// Inherti other interface
        void inherit(InterfaceType* type);

        /// classof check
        static bool classof(const Type* type) {
            return type->getTypeID() == InterfaceID;
        }

        /// classof check
        static bool classof(const InterfaceType*) {
            return true;
        }
    protected:
        // anonym object constructor
        InterfaceType(Module* module);

        // constructor
        InterfaceType(Module* module, const Identifier& name);
    };
    class InterfaceType;

    //==--------------------------------------------------------------------==//
    /// Object type
    class ObjectType : public Type {
    public:
        typedef std::vector<InterfaceType*>     InterfaceVector;
        typedef std::vector<ObjectType*>        ParentVector;
        typedef InterfaceVector::const_iterator interface_iterator;
        typedef ParentVector::const_iterator    parent_iterator;

        /// Create anonym object type in module
        static ObjectType* create(Module* module);

        /// Create object type in module
        static ObjectType* create(Module* module, const Identifier& name);

        /// Implement interface
        // void implement(InterfaceType* type);

        /// Inherit class
        bool inherit(ObjectType* type);

        /// This class implement interface?
        bool isImplement(const InterfaceType* type, bool duckCast = true) const;

        /// This class inherits from class?
        bool isInherit(const ObjectType* type) const;

        /// Type is castable to other type (up-cast(from child to parent) or implict cast)
        virtual bool isCastableTo(const Type* type, bool duckCast = true) const;

        /// classof check
        static bool classof(const Type* type) {
            return type->getTypeID() == ObjectID;
        }

        /// classof check
        static bool classof(const ObjectType*) {
            return true;
        }

        /// return LLVM analog for address map
        llvm::GlobalVariable* getVarAddressMap() const {
            return m_addressMap;
        }

        /// return LLVM analog for address map
        llvm::GlobalVariable* getVarVirtualTable() const {
            return m_virtualTable;
        }

        /// returns iterator pointed to first parent in class
        parent_iterator parent_begin() const {
            return m_parents.begin();
        }

        /// returns iterator pointed after last parent in class
        parent_iterator parent_end() const {
            return m_parents.end();
        }

        /// returns iterator pointed to first interface in class
        interface_iterator interface_begin() const {
            return m_interfaces.begin();
        }

        /// returns iterator pointed after last interface in class
        interface_iterator interface_end() const {
            return m_interfaces.end();
        }

        /// emit LLVM analog for type
        virtual void emit();
    protected:
        /// List of implemented interfaces
        InterfaceVector m_interfaces;

        /// List of inherit classes
        ParentVector m_parents;

        /// LLVM global variable with address map for class
        llvm::GlobalVariable* m_addressMap;

        /// LLVM global variable with virtual table for class
        llvm::GlobalVariable* m_virtualTable;

        // anonym object constructor
        ObjectType(Module* module);

        // constructor
        ObjectType(Module* module, const Identifier& name);
    };
}

#endif
