#include "ContextMeta.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Context.hpp"
#include "kiwi/Members.hpp"
#include "codegen/LlvmEmitter.hpp"
#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/GlobalVariable.h>
#include <llvm/Instruction.h>
#include <llvm/Module.h>
#include <llvm/ADT/ArrayRef.h>

using namespace kiwi;
using namespace kiwi::codegen;

Type::Type(ModuleRef module)
: m_typeID((TypeID) 0), m_module(module), m_varType(0), m_addressMap(0), m_virtualTable(0) { }

Type::~Type() { }

// add binary operator
UnaryRef Type::add(
    Member::UnaryOpcode opcode,
    TypeRef resultType,
    codegen::UnaryEmitter* emitter
) {
    UnaryRef op = UnaryRef(new UnaryOperator(opcode, shared_from_this(), resultType, emitter));
    m_unary.push_back(op);
    return op;
}

// add binary operator
BinaryRef Type::add(
    Member::BinaryOpcode opcode,
    TypeRef resultType,
    TypeRef operandType,
    codegen::BinaryEmitter* emitter
) {
    BinaryRef op = BinaryRef(new BinaryOperator(opcode, shared_from_this(), resultType, operandType, emitter));
    m_binary.push_back(op);
    return op;
}

// add field
FieldRef Type::add(const Identifier& name, const TypeRef& fieldType)
{
    FieldRef field = FieldRef(new Field(name, shared_from_this(), fieldType));
    m_fields.push_back(field);
    return field;
}

// add method
MethodRef Type::add(const Identifier& name, const TypeRef& resultType, std::vector<ArgumentRef> arguments)
{
    MethodRef method = MethodRef(new Method(name, shared_from_this(), resultType, arguments));
    m_methods.push_back(method);
    return method;
}

// find unary operator
UnaryRef Type::find(Member::UnaryOpcode opcode)
{
    for (std::vector<UnaryRef>::iterator i = m_unary.begin(); i != m_unary.end(); ++i)
    {
        UnaryRef op = *i;
        if (op->getOpcode() == opcode) {
            return op;
        }
    }
    return UnaryRef();
}

// find binary operator
BinaryRef Type::find(Member::BinaryOpcode opcode, const TypeRef& operandType)
{
    for (std::vector<BinaryRef>::iterator i = m_binary.begin(); i != m_binary.end(); ++i)
    {
        BinaryRef op = *i;
        if (op->getOpcode() == opcode && operandType == op->getOperandType()) {
            return op;
        }
    }
    return BinaryRef();
}

// find field
FieldRef Type::find(const Identifier& name)
{
    for (std::vector<FieldRef>::iterator i = m_fields.begin(); i != m_fields.end(); ++i) {
        FieldRef field = *i;
        if (field->getName() == name) {
            return field;
        }
    }
    return FieldRef();
}

// find method
MethodRef Type::find(const Identifier& name, std::vector<TypeRef> arguments)
{
    for (std::vector<MethodRef>::iterator i = m_methods.begin(); i != m_methods.end(); ++i) {
        MethodRef method = *i;
        if (method->getName() == name) {
            bool isAccept = true;
            int j         = 0;
            for (Method::const_iterator i = method->begin(); i != method->end(); ++i, ++j) {
                ArgumentRef arg = *i;
                if (arg->getType() != arguments[j]) {
                    isAccept = false;
                    break;
                }
            }

            if (isAccept) return method;
        }
    }
    return MethodRef();
}

// Emit type structure
void Type::emit()
{
    if (m_varType != 0) {
        return;
    }

    // collect fields
    std::vector<llvm::Type*> types;
    int j = 0;
    for (std::vector<FieldRef>::iterator i = m_fields.begin(); i != m_fields.end(); ++i, ++j) {
        FieldRef field = *i;

        TypeRef type = field->getFieldType();
        types.push_back(type->getVarType());

        field->setPosition(j);
    }

    // emit llvm type analog
    llvm::LLVMContext& context = m_module.lock()->getContext()->getContext();
    llvm::Module* module       = m_module.lock()->getModule();
    if (types.size()) {
        m_varType = llvm::StructType::create(types);
    } else {
        m_varType = llvm::StructType::create(context);
    }

    // emit address map
    std::vector<llvm::Constant*> addresses;
    std::vector<llvm::Constant*> buffer;
    llvm::Constant* nullCst = llvm::Constant::getNullValue(m_varType->getPointerTo());
    llvm::ConstantInt* zero = llvm::ConstantInt::get(context, llvm::APInt(32, 0, false));
    j = 0;
    for (std::vector<FieldRef>::iterator i = m_fields.begin(); i != m_fields.end(); ++i, ++j) {
        // create variable for compare
        llvm::APInt idxV(32, j, false);
        llvm::ConstantInt* idx = llvm::ConstantInt::get(context, idxV);

        // buffer
        buffer.clear();
        buffer.push_back(zero);
        buffer.push_back(idx);

        llvm::Constant* cst = llvm::ConstantExpr::getGetElementPtr(nullCst, makeArrayRef(buffer));
        addresses.push_back(cst);
    }

    llvm::Type* sizeType            = llvm::IntegerType::get(context, 8)->getPointerTo();
    llvm::ArrayType* addressMapType = llvm::ArrayType::get(sizeType, m_fields.size());
    llvm::Constant* addressMapValue = llvm::ConstantArray::get(addressMapType, makeArrayRef(addresses));

    // generate string
    m_addressMap  = new llvm::GlobalVariable(
        *module,
        addressMapType,
        true,
        llvm::GlobalValue::PrivateLinkage,
        addressMapValue,
        "amap"
    );
}