#include "kiwi/Codegen/Object.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/DerivedTypes.hpp"
#include <llvm/Constants.h>
#include <llvm/GlobalVariable.h>
#include <llvm/Instructions.h>

using namespace kiwi;
using namespace kiwi::codegen;

ObjectEmitter::ObjectEmitter(ObjectType* type)
: m_type(type) { }

// emit instructions for load value from object field
ExpressionGen ObjectEmitter::emitLoad(const StatementGen& gen, const ExpressionGen& thisValue, const Identifier& name) {
    const ExpressionGen offset = findField(gen, thisValue, name);
    // load value and yeld
    llvm::Value* loadInst   = new llvm::LoadInst(offset.getValue(), "", gen.getBlock());
    return ExpressionGen(gen, offset.getType(), loadInst);
}

// emit instructions for store value in object field
ExpressionGen ObjectEmitter::emitStore(const StatementGen& gen, const ExpressionGen& thisValue, const Identifier& name, const ExpressionGen& value) {
    const ExpressionGen offset = findField(gen, thisValue, name);
    // store value and yeld
    new llvm::StoreInst(value.getValue(), offset.getValue(), "", gen.getBlock());
    return ExpressionGen(gen, value.getType(), value.getValue());
}

// emit instruction for create new instance of class
ExpressionGen ObjectEmitter::emitNew(const StatementGen& gen) {
    llvm::Value* value = new llvm::AllocaInst(m_type->getVarType(), "this", gen.getBlock());
    return ExpressionGen(gen, m_type, value);
}

// Returns pointer to value of field obkect
ExpressionGen ObjectEmitter::findField(const StatementGen& gen, const ExpressionGen& thisValue, const Identifier& name) {
    // Find field
    Field* field = m_type->find(name);
    if (!field) {
        throw "Field not found";
    }

    // Prepare
    llvm::Type* type           = m_type->getVarType()->getPointerTo();
    llvm::Type* fieldType      = field->getFieldType()->getVarType()->getPointerTo();
    llvm::LLVMContext& context = type->getContext();
    llvm::Value* addressMap    = m_type->getVarAddressMap();

    // create variable for compare
    llvm::APInt cst(32, 0, false);
    llvm::ConstantInt* zero = llvm::ConstantInt::get(gen.getContext(), cst);

    cst = llvm::APInt(32, field->getPosition(), false);
    llvm::ConstantInt* one = llvm::ConstantInt::get(gen.getContext(), cst);

    // prepare GetElementPtrInst indexes
    std::vector<llvm::Value*> lengthIdx; // length
    lengthIdx.push_back(zero);
    lengthIdx.push_back(one);

    llvm::Value* value = thisValue.getValue();
    assert(value && "value is null");

    llvm::Value* position    = llvm::GetElementPtrInst::Create(addressMap, makeArrayRef(lengthIdx), "", gen.getBlock());
    llvm::Value* fieldOffset = new llvm::LoadInst(position, "", gen.getBlock());

    llvm::Value* castNull   = new llvm::PtrToIntInst(value, llvm::IntegerType::get(context, 64), "", gen.getBlock());
    llvm::Value* castOffset = new llvm::PtrToIntInst(fieldOffset, llvm::IntegerType::get(context, 64), "", gen.getBlock());
    llvm::Value* summInst   = llvm::BinaryOperator::Create(llvm::Instruction::Add, castNull, castOffset, "", gen.getBlock());
    llvm::Value* offset     = new llvm::IntToPtrInst(summInst, fieldType, "", gen.getBlock());

    return ExpressionGen(gen, field->getFieldType(), offset);
}
