#include "kiwi/Type.hpp"
#include "codegen/Emitter.hpp"
#include "llvm/DerivedTypes.h"

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
    m_varType = llvm::IntegerType::get(context);
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

    // add(UnaryOperator::NEG, self, new LlvmUnaryOperator(Instruction::NEG));
    // add(UnaryOperator::POS, self, new NullEmitter());

    add(BinaryOperator::ADD, self, self, new LlvmBinaryOperator(Instruction::ADD));
    add(BinaryOperator::SUB, self, self, new LlvmBinaryOperator(Instruction::SUB));
    add(BinaryOperator::MUL, self, self, new LlvmBinaryOperator(Instruction::MUL));

    // add(BINARY_DIV, shared_from_this(), shared_from_this(), new BinaryEmitter(Instruction::ADD));
}

void BoolType::initializate()
{
    // add(BINARY_EQ, shared_from_this(), shared_from_this)
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

BinaryRef Type::find(BinaryOperator::Opcode opcode, TypeRef operatorType)
{

}