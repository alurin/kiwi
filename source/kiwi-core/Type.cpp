#include "ContextMeta.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Context.hpp"
#include "codegen/LlvmEmitter.hpp"
#include <llvm/DerivedTypes.h>
#include <llvm/Instruction.h>

using namespace kiwi;
using namespace kiwi::codegen;

Type::Type(ModuleRef module)
: m_module(module), m_varType(0) { }

Type::~Type() { }

// constructor
UnaryOperator::UnaryOperator(
    UnaryOperator::Opcode opcode,
    TypeRef resultType,
    codegen::UnaryEmitter* emitter
) : m_opcode(opcode), m_resultType(resultType), m_emitter(emitter)
{ }

// constructor
BinaryOperator::BinaryOperator(
    BinaryOperator::Opcode opcode,
    TypeRef resultType,
    TypeRef operatorType,
    codegen::BinaryEmitter* emitter
) : m_opcode(opcode), m_resultType(resultType), m_operatorType(operatorType), m_emitter(emitter)
{ }

// constructor
Method::Method(const Identifier& name, TypeRef ownerType, TypeRef resultType, std::vector<ArgumentRef> arguments)
: m_name(name), m_ownerType(ownerType), m_resultType(resultType), m_arguments(arguments), m_func(0)
{}

// constructor
Argument::Argument(const Identifier& name, const TypeRef& type)
: m_name(name), m_type(type) { }

// crate type
TypeRef Type::create(ModuleRef module)
{
    TypeRef type               = TypeRef(new Type(module));
    llvm::LLVMContext& context = module->getContext()->getContext();
    type->m_varType            = llvm::StructType::create(context);
    return type;
}

// create method
MethodRef Method::create(const Identifier& name, TypeRef ownerType, TypeRef resultType, std::vector<ArgumentRef> arguments)
{
    MethodRef method = MethodRef(new Method(name, ownerType, resultType, arguments));
    return method;
}

ArgumentRef Argument::create(const Identifier& name, const TypeRef& type)
{
    ArgumentRef arg = ArgumentRef(new Argument(name, type));
    return arg;
}

// add binary operator
UnaryRef Type::add(
    UnaryOperator::Opcode opcode,
    TypeRef resultType,
    codegen::UnaryEmitter* emitter
) {
    UnaryRef op = UnaryRef(new UnaryOperator(opcode, resultType, emitter));
    m_unary.push_back(op);
    return op;
}

// add binary operator
BinaryRef Type::add(
    BinaryOperator::Opcode opcode,
    TypeRef resultType,
    TypeRef operatorType,
    codegen::BinaryEmitter* emitter
) {
    BinaryRef op = BinaryRef(new BinaryOperator(opcode, resultType, operatorType, emitter));
    m_binary.push_back(op);
    return op;
}

// add method
MethodRef Type::add(const Identifier& name, TypeRef resultType, std::vector<ArgumentRef> arguments)
{
    MethodRef method = Method::create(name, shared_from_this(), resultType, arguments);
    m_methods.push_back(method);
    return method;
}

// find unary operator
UnaryRef Type::find(UnaryOperator::Opcode opcode)
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
BinaryRef Type::find(BinaryOperator::Opcode opcode, TypeRef operatorType)
{
    for (std::vector<BinaryRef>::iterator i = m_binary.begin(); i != m_binary.end(); ++i)
    {
        BinaryRef op = *i;
        if (op->getOpcode() == opcode && operatorType == op->getOperatorType()) {
            return op;
        }
    }
    return BinaryRef();
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