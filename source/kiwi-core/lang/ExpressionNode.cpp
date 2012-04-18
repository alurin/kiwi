#include "kiwi/Type.hpp"
#include "kiwi/codegen/Emitter.hpp"
#include "ExpressionNode.hpp"
#include "FunctionNode.hpp"
#include <llvm/Instructions.h>
#include <llvm/Constants.h>

using namespace kiwi;
using namespace kiwi::lang;

BinaryNode::BinaryNode(Opcode opcode, RightNode* left, RightNode* right, bool logic)
: m_opcode(opcode), m_left(left), m_right(right), m_logic(logic)
{}

BinaryNode::~BinaryNode()
{
    delete m_left;
    delete m_right;
}

UnaryNode::UnaryNode(Opcode opcode, RightNode* value, bool post)
: m_opcode(opcode), m_value(value), m_post(post)
{}

UnaryNode::~UnaryNode()
{
    delete m_value;
}

AssignNode::AssignNode(LeftNode* left, RightNode* right)
: m_left(left), m_right(right)
{

}

AssignNode::~AssignNode()
{
    delete m_left;
    delete m_right;
}

VariableLeftNode::VariableLeftNode(VariableNode* var)
: o_var(var) { }

VariableRightNode::VariableRightNode(VariableNode* var)
: o_var(var) { }

ArgumentLeftNode::ArgumentLeftNode(ArgumentNode* arg)
: o_arg(arg) { }

ArgumentRightNode::ArgumentRightNode(ArgumentNode* arg)
: o_arg(arg) { }

IntegerConstNode::IntegerConstNode(ContextRef context, int32_t value)
: m_context(context), m_value(value) { }

ExpressionGen BinaryNode::emit(const StatementGen& gen)
{
    // emit operands
    ExpressionGen left  = m_left->emit(gen);
    ExpressionGen right = m_right->emit(gen);

    // find emitter
    TypeRef type = left.getType();
    BinaryRef op = type->find(m_opcode, right.getType());

    // emit instruction
    if (op) {
        return op->getEmitter()->emit(right, left, right);
    }
    throw "not found binary operator";
}

ExpressionGen UnaryNode::emit(const StatementGen& gen)
{
    // emit operand
    ExpressionGen value  = m_value->emit(gen);

    // find emitter
    TypeRef type = value.getType();
    UnaryRef op  = type->find(m_opcode);

    // emit instruction
    if (op) {
        return op->getEmitter()->emit(value, value);
    }
    throw "not found unary operator";
}

ExpressionGen AssignNode::emit(const StatementGen& gen)
{
    ExpressionGen value = m_right->emit(gen);
    return m_left->emit(value);
}

ExpressionGen ArgumentLeftNode::emit(const ExpressionGen& gen)
{
    VariableGen var = o_arg->getGenerator();
    if (var.getType() == gen.getType()) {
        llvm::StoreInst* inst = new llvm::StoreInst(var.getValue(), gen.getValue(), gen.getBlock());
        return gen;
    }

    throw "unknown cast";
}

ExpressionGen ArgumentRightNode::emit(const StatementGen& gen)
{
    VariableGen var      = o_arg->getGenerator();
    llvm::LoadInst* inst = new llvm::LoadInst(var.getValue(), "", gen.getBlock());
    return ExpressionGen(gen, var.getType(), inst);
}

ExpressionGen VariableLeftNode::emit(const ExpressionGen& gen)
{
    VariableGen var = o_var->getGenerator();
    if (var.getType() == gen.getType()) {
        llvm::StoreInst* inst = new llvm::StoreInst(var.getValue(), gen.getValue(), gen.getBlock());
        return gen;
    }

    throw "unknown cast";
}

ExpressionGen VariableRightNode::emit(const StatementGen& gen)
{
    VariableGen var      = o_var->getGenerator();
    llvm::LoadInst* inst = new llvm::LoadInst(var.getValue(), "", gen.getBlock());
    return ExpressionGen(gen, var.getType(), inst);
}

ExpressionGen IntegerConstNode::emit(const StatementGen& gen)
{
    llvm::APInt cst(32, m_value, false);
    llvm::ConstantInt* value = llvm::ConstantInt::get(gen.getContext(), cst);
    return ExpressionGen(gen, IntType::get32(m_context), value);
}
