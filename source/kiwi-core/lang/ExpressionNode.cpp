#include "ExpressionNode.hpp"
#include "FunctionNode.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/DerivedTypes.hpp"
#include "kiwi/Codegen/Emitter.hpp"
#include "kiwi/Codegen/Object.hpp"
#include "kiwi/Codegen/String.hpp"
#include "kiwi/Support/Cast.hpp"
#include <llvm/Constants.h>
#include <llvm/Function.h>
#include <llvm/GlobalVariable.h>
#include <llvm/Instructions.h>

using namespace kiwi;
using namespace kiwi::lang;
using namespace kiwi::codegen;

BinaryNode::BinaryNode(Member::BinaryOpcode opcode, ExpressionNode* left, ExpressionNode* right, bool logic)
: m_opcode(opcode), m_left(left), m_right(right), m_logic(logic)
{}

BinaryNode::~BinaryNode()
{
    delete m_left;
    delete m_right;
}

UnaryNode::UnaryNode(Member::UnaryOpcode opcode, ExpressionNode* value, bool post)
: m_opcode(opcode), m_value(value), m_post(post)
{}

UnaryNode::~UnaryNode()
{
    delete m_value;
}

AssignNode::AssignNode(MutableNode* left, ExpressionNode* right)
: m_left(left), m_right(right)
{

}

AssignNode::~AssignNode()
{
    delete m_left;
    delete m_right;
}

VariableMutableNode::VariableMutableNode(VariableNode* var)
: o_var(var) { }

VariableExpressionNode::VariableExpressionNode(VariableNode* var)
: o_var(var) { }

ArgumentMutableNode::ArgumentMutableNode(ArgumentNode* arg)
: o_arg(arg) { }

ArgumentExpressionNode::ArgumentExpressionNode(ArgumentNode* arg)
: o_arg(arg) { }

IntegerConstNode::IntegerConstNode(Context* context, int32_t value)
: m_context(context), m_value(value) { }

BoolConstNode::BoolConstNode(Context* context, bool value)
: m_context(context), m_value(value) { }

StringConstNode::StringConstNode(Context* context, const String& value)
: m_context(context), m_value(value) { }

CharConstNode::CharConstNode(Context* context, const UChar& value)
: m_context(context), m_value(value) { }

CallNode::CallNode(const Identifier& method)
: m_method(method), m_hasNamed(false) {}

InstanceMutableNode::InstanceMutableNode(const Identifier& name)
: m_name(name) { }

InstanceExpressionNode::InstanceExpressionNode(const Identifier& name)
: m_name(name) { }

void CallNode::append(const Identifier& name, ExpressionNode* value)
{
    CallArgument arg;
    arg.Name     = name;
    arg.Position = m_arguments.size();
    arg.Value    = value;
    m_arguments.push_back(arg);
    m_hasNamed = true;
}

void CallNode::append(ExpressionNode* value)
{
    CallArgument arg;
    arg.Name     = "";
    arg.Position = m_arguments.size();
    arg.Value    = value;
    m_arguments.push_back(arg);
}

ExpressionGen BinaryNode::emit(const StatementGen& gen)
{
    // emit operands
    ExpressionGen left  = m_left->emit(gen);
    ExpressionGen right = m_right->emit(gen);

    // find emitter
    Type* type = left.getType();
    BinaryOperator* op = type->find(m_opcode, right.getType());

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
    Type* type = value.getType();
    UnaryOperator* op  = type->find(m_opcode);

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

ExpressionGen ArgumentMutableNode::emit(const ExpressionGen& gen)
{
    VariableGen var = o_arg->getGenerator();
    if (var.getType() == gen.getType()) {
        llvm::StoreInst* inst = new llvm::StoreInst(gen.getValue(), var.getValue(), gen.getBlock());
        return gen;
    }

    throw "unknown cast";
}

ExpressionGen ArgumentExpressionNode::emit(const StatementGen& gen)
{
    VariableGen var      = o_arg->getGenerator();
    llvm::LoadInst* inst = new llvm::LoadInst(var.getValue(), "", gen.getBlock());
    return ExpressionGen(gen, var.getType(), inst);
}

ExpressionGen VariableMutableNode::emit(const ExpressionGen& gen)
{
    VariableGen var = o_var->getGenerator();
    if (var.getType() == gen.getType()) {
        llvm::StoreInst* inst = new llvm::StoreInst(gen.getValue(), var.getValue(), gen.getBlock());
        return gen;
    }

    throw "unknown cast";
}

ExpressionGen VariableExpressionNode::emit(const StatementGen& gen)
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

ExpressionGen BoolConstNode::emit(const StatementGen& gen)
{
    llvm::APInt cst(1, m_value, false);
    llvm::ConstantInt* value = llvm::ConstantInt::get(gen.getContext(), cst);
    return ExpressionGen(gen, BoolType::get(m_context), value);
}

ExpressionGen StringConstNode::emit(const StatementGen& gen)
{
    return StringEmitter(StringType::get(m_context)).emit(gen, m_value);
}

ExpressionGen CharConstNode::emit(const StatementGen& gen)
{
    llvm::APInt cst(16, m_value, true);
    llvm::ConstantInt* value = llvm::ConstantInt::get(gen.getContext(), cst);
    return ExpressionGen(gen, CharType::get(m_context), value);
}

ExpressionGen CallNode::emit(const StatementGen& gen)
{
    std::vector<Type*>        types;
    std::vector<llvm::Value*>   args;

    if (m_hasNamed) {
        throw "Not implement call by named arguments";
    }

    StatementGen current = gen;
    for (std::vector<CallArgument>::iterator i = m_arguments.begin(); i != m_arguments.end(); ++i) {
        // emit code for argument
        ExpressionGen expr = i->Value->emit(current);
        current            = expr;

        // store info
        types.push_back(expr.getType());
        args.push_back(expr.getValue());
    }

    Type* owner    = gen.getOwner();
    Method* method = owner->find(m_method, types);
    if (method) {
        llvm::Function* func = method->getFunction();
        if (!func) {
            throw "Function implementation not found";
        }

        // return result of call
        llvm::Value* result = llvm::CallInst::Create(func, makeArrayRef(args), "", current.getBlock());
        return ExpressionGen(current, method->getResultType(), result);
    } else {
        throw "Method not found";
    }
}

ExpressionGen InstanceMutableNode::emit(const ExpressionGen& gen)
{
    Type* owner = gen.getOwner();
    ObjectType* type = dyn_cast<ObjectType>(owner);
    if (type) {
        return ObjectEmitter(type).emitStore(gen, m_name, gen);
    } else {
        throw "Fields not exists in type";
    }
}

ExpressionGen InstanceExpressionNode::emit(const StatementGen& gen)
{
    Type* owner = gen.getOwner();
    ObjectType* type = dyn_cast<ObjectType>(owner);
    if (type) {
        return ObjectEmitter(type).emitLoad(gen, m_name);
    } else {
        throw "Fields not exists in type";
    }
}
