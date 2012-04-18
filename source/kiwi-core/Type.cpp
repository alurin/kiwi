#include "ContextMeta.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Context.hpp"
#include "codegen/LlvmEmitter.hpp"
#include <llvm/DerivedTypes.h>
#include <llvm/Instruction.h>


using namespace kiwi;
using namespace kiwi::codegen;

typedef boost::shared_ptr<IntType>  IntTypeRef;
typedef boost::shared_ptr<BoolType> BoolTypeRef;

Type::Type(ModuleRef module)
: m_module(module), m_varType(0) { }

Type::~Type() { }

IntType::IntType(ModuleRef module, int32_t size, bool unsign)
: Type(module) {
    llvm::LLVMContext& context = module->getContext()->getContext();
    m_varType = llvm::IntegerType::get(context, size);
}

BoolType::BoolType(ModuleRef module)
: Type(module) {
    llvm::LLVMContext& context = module->getContext()->getContext();
    m_varType = llvm::IntegerType::get(context, 1);
}

TypeRef IntType::create(ModuleRef module, int32_t size, bool unsign)
{
    IntTypeRef type = IntTypeRef(new IntType(module, size, unsign));
    type->initializate();
    return type;
}

TypeRef BoolType::create(ModuleRef module)
{
    BoolTypeRef type = BoolTypeRef(new BoolType(module));
    type->initializate();
    return type;
}

void IntType::initializate()
{
    TypeRef self = shared_from_this();

    add(BinaryOperator::ADD, self, self, new LlvmBinaryOperator(llvm::Instruction::Add, self));
    add(BinaryOperator::SUB, self, self, new LlvmBinaryOperator(llvm::Instruction::Sub, self));
    add(BinaryOperator::MUL, self, self, new LlvmBinaryOperator(llvm::Instruction::Mul, self));
}

void BoolType::initializate()
{

}

BinaryOperator::BinaryOperator(
    BinaryOperator::Opcode opcode,
    TypeRef resultType,
    TypeRef operatorType,
    codegen::BinaryEmitter* emitter
) : m_opcode(opcode), m_resultType(resultType), m_operatorType(operatorType), m_emitter(emitter)
{ }

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

TypeRef IntType::get32(ContextRef context)
{
    ContextMeta* meta = context->getMetadata();
    return meta->int32Ty;
}