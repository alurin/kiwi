#include "Driver.hpp"
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
: m_opcode(opcode), m_left(left), m_right(right), m_logic(logic) {
}

BinaryNode::~BinaryNode() {
    delete m_left;
    delete m_right;
}

UnaryNode::UnaryNode(Member::UnaryOpcode opcode, ExpressionNode* value, bool post)
: m_opcode(opcode), m_value(value), m_post(post) {
}

UnaryNode::~UnaryNode() {
    delete m_value;
}

AssignNode::AssignNode(MutableNode* left, ExpressionNode* right)
: m_left(left), m_right(right) {

}

AssignNode::~AssignNode() {
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

CallNode::CallNode(ExpressionNode* calle, const Identifier& method)
: m_calle(calle), m_method(method), m_hasNamed(false) {
}

CallNode::CallNode(ExpressionNode* calle)
: m_calle(calle), m_hasNamed(false) {
}

InstanceMutableNode::InstanceMutableNode(const Identifier& name)
: m_name(name) { }

InstanceExpressionNode::InstanceExpressionNode(const Identifier& name)
: m_name(name) { }

ThisNode::ThisNode(ObjectType* thisType)
: m_thisType(thisType) { }

SubtractionNode::SubtractionNode(ExpressionNode* expr)
: m_expr(expr) {
}

SubtractionNode::~SubtractionNode() {
    for (std::vector<ExpressionNode*>::iterator i = m_indexes.begin(); i != m_indexes.end(); ++i) {
        ExpressionNode* node;
        delete node;
    }
}

void CallNode::append(const Identifier& name, ExpressionNode* value) {
    CallArgument arg;
    arg.Name     = name;
    arg.Position = m_arguments.size();
    arg.Value    = value;
    m_arguments.push_back(arg);
    m_hasNamed = true;
}

void CallNode::append(ExpressionNode* value) {
    CallArgument arg;
    arg.Name     = "";
    arg.Position = m_arguments.size();
    arg.Value    = value;
    m_arguments.push_back(arg);
}

ExpressionGen BinaryNode::emit(Driver& driver, const StatementGen& gen) {
    // emit operands
    ExpressionGen left  = m_left->emit(driver, gen);
    ExpressionGen right = m_right->emit(driver, gen);

    // find emitter
    Type* type = left.getType();
    BinaryOperator* op = type->find(m_opcode, right.getType());

    // emit instruction
    if (op) {
        return op->getEmitter()->emit(right, left, right);
    }
    KIWI_ERROR_AND_EXIT("not found binary operator", getLocation());
}

ExpressionGen UnaryNode::emit(Driver& driver, const StatementGen& gen) {
    // emit operand
    ExpressionGen value  = m_value->emit(driver, gen);

    // find emitter
    Type* type = value.getType();
    UnaryOperator* op  = type->find(m_opcode);

    // emit instruction
    if (op) {
        return op->getEmitter()->emit(value, value);
    }
    KIWI_ERROR_AND_EXIT("not found unary operator", getLocation());
}

ExpressionGen AssignNode::emit(Driver& driver, const StatementGen& gen) {
    ExpressionGen value = m_right->emit(driver, gen);
    return m_left->emit(driver, value);
}

ExpressionGen ArgumentMutableNode::emit(Driver& driver, const ExpressionGen& gen) {
    VariableGen var = o_arg->getGenerator();
    if (var.getType() == gen.getType()) {
        llvm::StoreInst* inst = new llvm::StoreInst(gen.getValue(), var.getValue(), gen.getBlock());
        return gen;
    }

    KIWI_ERROR_AND_EXIT("unknown cast", getLocation());
}

ExpressionGen ArgumentExpressionNode::emit(Driver& driver, const StatementGen& gen) {
    VariableGen var      = o_arg->getGenerator();
    llvm::LoadInst* inst = new llvm::LoadInst(var.getValue(), "", gen.getBlock());
    return ExpressionGen(gen, var.getType(), inst);
}

ExpressionGen VariableMutableNode::emit(Driver& driver, const ExpressionGen& gen) {
    VariableGen var = o_var->getGenerator();
    if (var.getType() == gen.getType()) {
        llvm::StoreInst* inst = new llvm::StoreInst(gen.getValue(), var.getValue(), gen.getBlock());
        return gen;
    }

    KIWI_ERROR_AND_EXIT("unknown cast", getLocation());
}

ExpressionGen VariableExpressionNode::emit(Driver& driver, const StatementGen& gen) {
    VariableGen var      = o_var->getGenerator();
    llvm::LoadInst* inst = new llvm::LoadInst(var.getValue(), "", gen.getBlock());
    return ExpressionGen(gen, var.getType(), inst);
}

ExpressionGen IntegerConstNode::emit(Driver& driver, const StatementGen& gen) {
    llvm::APInt cst(32, m_value, false);
    llvm::ConstantInt* value = llvm::ConstantInt::get(gen.getContext(), cst);
    return ExpressionGen(gen, IntType::get32(m_context), value);
}

ExpressionGen BoolConstNode::emit(Driver& driver, const StatementGen& gen) {
    llvm::APInt cst(1, m_value, false);
    llvm::ConstantInt* value = llvm::ConstantInt::get(gen.getContext(), cst);
    return ExpressionGen(gen, BoolType::get(m_context), value);
}

ExpressionGen StringConstNode::emit(Driver& driver, const StatementGen& gen) {
    return StringEmitter(StringType::get(m_context)).emit(gen, m_value);
}

ExpressionGen CharConstNode::emit(Driver& driver, const StatementGen& gen) {
    llvm::APInt cst(16, m_value, true);
    llvm::ConstantInt* value = llvm::ConstantInt::get(gen.getContext(), cst);
    return ExpressionGen(gen, CharType::get(m_context), value);
}

ExpressionGen CallNode::emit(Driver& driver, const StatementGen& gen) {
    std::vector<Type*>          types;
    std::vector<llvm::Value*>   args;

    if (m_hasNamed) {
        KIWI_ERROR_AND_EXIT("Not implement call by named arguments", getLocation());
    } else if (m_method.empty()) {
        KIWI_ERROR_AND_EXIT("Not implement call expression", getLocation());
    }

    ExpressionGen calle = m_calle->emit(driver, gen);
    StatementGen current = calle;
    args.push_back(calle.getValue());

    for (std::vector<CallArgument>::iterator i = m_arguments.begin(); i != m_arguments.end(); ++i) {
        // emit code for argument
        ExpressionGen expr = i->Value->emit(driver, current);
        current            = expr;

        // store info
        types.push_back(expr.getType());
        args.push_back(expr.getValue());
    }

    Type* owner    = calle.getType();
    Method* method = owner->find(m_method, types);
    if (method) {
        llvm::Function* func = method->getFunction();
        if (!func) {
            KIWI_ERROR_AND_EXIT("Function implementation not found", getLocation());
        }

        // return result of call
        llvm::Value* result = llvm::CallInst::Create(func, makeArrayRef(args), "", current.getBlock());
        return ExpressionGen(current, method->getReturnType(), result);
    } else {
        KIWI_ERROR_AND_EXIT("Method not found", getLocation());
    }
}

ExpressionGen InstanceMutableNode::emit(Driver& driver, const ExpressionGen& gen) {
    Type* owner = gen.getOwner();
    ObjectType* type = dyn_cast<ObjectType>(owner);
    if (type) {
        ExpressionGen thisValue = ThisNode(dyn_cast<ObjectType>(owner)).emit(driver, gen);
        return ObjectEmitter(type).emitStore(gen, thisValue, m_name, gen);
    } else {
        KIWI_ERROR_AND_EXIT("Fields not exists in type", getLocation());
    }
}

ExpressionGen InstanceExpressionNode::emit(Driver& driver, const StatementGen& gen) {
    Type* owner = gen.getOwner();
    ObjectType* type = dyn_cast<ObjectType>(owner);
    if (type) {
        ExpressionGen thisValue = ThisNode(dyn_cast<ObjectType>(owner)).emit(driver, gen);
        return ObjectEmitter(type).emitLoad(gen, thisValue, m_name);
    } else {
        KIWI_ERROR_AND_EXIT("Fields not exists in type", getLocation());
    }
}

ExpressionGen ThisNode::emit(Driver& driver, const StatementGen& gen) {
    llvm::Function* func = gen.getFunction();
    if (func->arg_empty()) {
        KIWI_ERROR_AND_EXIT("Not found this", getLocation());
    }
    llvm::Argument* arg  = func->arg_begin();
    return ExpressionGen(gen, m_thisType, arg);
}

ExpressionGen SubtractionNode::emit(Driver& driver, const StatementGen& gen) {
    // emit operand
    ExpressionGen value  = m_expr->emit(driver, gen);
    StatementGen current = value;
    std::vector<ExpressionGen>  values;
    std::vector<Type*>          types;

    for (std::vector<ExpressionNode*>::iterator i = m_indexes.begin(); i != m_indexes.end(); ++i) {
        ExpressionNode* node = *i;
        ExpressionGen nodeGen = node->emit(driver, current);
        current = nodeGen;

        values.push_back(nodeGen);
        types.push_back(nodeGen.getType());
    }

    // find emitter
    Type* type = value.getType();
    MultiaryOperator* op = type->find(Member::Subtraction, types);
    if (op)
        return op->getEmitter()->emit(current, values);
    KIWI_ERROR_AND_EXIT("not found multiary operator", getLocation());
}
