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
: m_opcode(opcode), m_logic(logic) {
    append(left);
    append(right);
}

UnaryNode::UnaryNode(Member::UnaryOpcode opcode, ExpressionNode* value, bool post)
: m_opcode(opcode), m_post(post) {
    append(value);
}

MultiaryNode::MultiaryNode(Member::MultiaryOpcode opcode, ExpressionNode* value)
: m_opcode(opcode) {
    append(value);
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

CallableArgument::CallableArgument(const Identifier& name, ExpressionNode* value, int32_t position)
: m_name(name), m_value(value), m_position(position) {
}

CallableArgument::CallableArgument(ExpressionNode* value, int32_t position)
: m_value(value), m_position(position) {
}

CallableArgument::~CallableArgument() {
    delete m_value;
}

CallableNode::CallableNode() {
}

CallableNode::~CallableNode() {
    for (std::vector<CallableArgument*>::iterator i = m_arguments.begin(); i != m_arguments.end(); ++i) {
        CallableArgument* node = *i;
        delete node;
    }
}

CallNode::CallNode(ExpressionNode* calle, const Identifier& method)
: m_calle(calle), m_method(method) {
}

CallNode::CallNode(ExpressionNode* calle)
: m_calle(calle) {
}

// constructor
NewNode::NewNode(TypeNode* type)
: m_type(type) {
}

InstanceMutableNode::InstanceMutableNode(const Identifier& name)
: m_name(name) { }

InstanceExpressionNode::InstanceExpressionNode(const Identifier& name)
: m_name(name) { }

ThisNode::ThisNode(ObjectType* thisType)
: m_thisType(thisType) { }

void CallableNode::append(const Identifier& name, ExpressionNode* value) {
    if (value) {
        m_arguments.push_back(new CallableArgument(name, value, m_arguments.size()));
        //m_hasNamed = true;
    }
}

void CallableNode::append(ExpressionNode* value) {
    if (value)
        m_arguments.push_back(new CallableArgument(value, m_arguments.size()));
}

ExpressionGen CallableArgument::emit(Driver& driver, const StatementGen& gen) {
    return m_value->emit(driver, gen);
}

ExpressionGen CallableNode::emit(Driver& driver, const StatementGen& gen) {
    std::vector<Type*> types;
    std::vector<ExpressionGen> args;

    StatementGen current = gen;
    for (std::vector<CallableArgument*>::iterator i = m_arguments.begin(); i != m_arguments.end(); ++i) {
        CallableArgument* arg = *i;
        ExpressionGen expr = arg->emit(driver, current);
        types.push_back(expr.getType());
        args.push_back(expr);
        current = expr;
    }

    Callable* call = findCallable(driver, types);
    if (call) {
        CallableEmitter* emitter = call->getEmitter();
        return emitter->emit(gen, args);
    }
    KIWI_ERROR_AND_EXIT("Method or operator for call not found", getLocation());
}

Callable* BinaryNode::findCallable(Driver& driver, std::vector<Type*> types) {
    Callable* call = types[0]->find(m_opcode, types[1]);
    if (!call) {
        KIWI_ERROR_AND_EXIT("Not found binary operator", getLocation());
    }
    return call;
}

Callable* UnaryNode::findCallable(Driver& driver, std::vector<Type*> types) {
    Callable* call = types[0]->find(m_opcode);
    if (!call) {
        KIWI_ERROR_AND_EXIT("not found unary operator", getLocation());
    }
    return call;
}

Callable* MultiaryNode::findCallable(Driver& driver, std::vector<Type*> types) {
    std::vector<Type*> args(types.end() + 1, types.end());
    Callable* call = types[0]->find(m_opcode, args);
    if (!call) {
        KIWI_ERROR_AND_EXIT("not found multiary operator", getLocation());
    }
    return call;
}


Callable* CallNode::findCallable(Driver& driver, std::vector<Type*> types) {
    std::vector<Type*> args(types.end() + 1, types.end());
    Callable* call = types[0]->find(m_method, args);
    if (!call) {
        KIWI_ERROR_AND_EXIT("Method not found", getLocation());
    }
    return call;
}

// Emit instructions
ExpressionGen NewNode::emit(Driver& driver, const StatementGen& gen) {
    KIWI_ERROR_AND_EXIT("Constructors not implemented", getLocation());
    CallableNode::emit(driver, gen);
}

Callable* NewNode::findCallable(Driver& driver, std::vector<Type*> types) {
    KIWI_ERROR_AND_EXIT("Constructors not implemented", getLocation());
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
