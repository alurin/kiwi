/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "kiwi/assert.hpp"
#include "Driver.hpp"
#include "ExpressionNode.hpp"
#include "FunctionNode.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/DerivedTypes.hpp"
#include "kiwi/Support/Cast.hpp"
#include "../Codegen/Builder.hpp"

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

MultiaryNode::MultiaryNode(Member::MultiaryOpcode opcode)
: m_opcode(opcode) {
}

AssignNode::AssignNode(MutableNode* left, ExpressionNode* right)
: m_left(left), m_right(right) {
}

AssignNode::~AssignNode() {
    delete m_left;
    delete m_right;
}

NamedMutableNode::NamedMutableNode(NamedNode* var)
: o_var(var) { }

NamedExpressionNode::NamedExpressionNode(NamedNode* var)
: o_var(var) { }


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
    for (ArgumentList::iterator i = m_arguments.begin(); i != m_arguments.end(); ++i) {
        CallableArgument* node = *i;
        delete node;
    }
}

CallNode::CallNode(ExpressionNode* calle, const Identifier& method)
: m_method(method) {
    append(calle);
}

// constructor
NewNode::NewNode(TypeNode* type)
: MultiaryNode(Member::Constructor), m_type(type) {
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

void CallableNode::prepend(ExpressionNode* value) {
    if (value)
        m_arguments.push_front(new CallableArgument(value, m_arguments.size()));
}

ValueBuilder CallableArgument::emit(Driver& driver, BlockBuilder block) const {
    return m_value->emit(driver, block);
}

ValueBuilder CallableNode::emit(Driver& driver, BlockBuilder block) const {
    std::vector<ValueBuilder> args;
    return emitCall(driver, block, args);
}

// Find arguments for append before other
ValueBuilder CallableNode::emitCall(Driver& driver, BlockBuilder block, std::vector<ValueBuilder> args) const {
    std::vector<Type*> types;
    int j = 0;
    for (std::vector<ValueBuilder>::const_iterator i = args.begin(); i != args.end(); ++i, ++j) {
        types.push_back(i->getType());
    }

    /// collect arguments
    for (ArgumentList::const_iterator i = m_arguments.begin(); i != m_arguments.end(); ++i) {
        CallableArgument* arg = *i;
        ValueBuilder expr = arg->emit(driver, block);
        args.push_back(expr);
        types.push_back(expr.getType());
        block = expr;
    }

    /// find call
    Callable* call = call = findCallable(driver, types);

    if (!call)
        KIWI_ERROR_AND_EXIT("Method or operator for call not found", getLocation());
    return block.createCall(call, args);
}

Callable* BinaryNode::findCallable(Driver& driver, std::vector<Type*> types) const {
    Callable* call = types[0]->findBinary(m_opcode, types[1]);
    if (!call) {
        KIWI_ERROR_AND_EXIT("Not found binary operator", getLocation());
    }
    return call;
}

Callable* UnaryNode::findCallable(Driver& driver, std::vector<Type*> types) const {
    Callable* call = types[0]->findUnary(m_opcode);
    if (!call) {
        KIWI_ERROR_AND_EXIT("not found unary operator", getLocation());
    }
    return call;
}

Callable* MultiaryNode::findCallable(Driver& driver, std::vector<Type*> types) const {
    kiwi_assert(types.size() > 0, "MultiaryNode::findCallable must recive at last one argument");
    std::vector<Type*> args(types.begin() + 1, types.end());
    Callable* call = types[0]->findMultiary(m_opcode, args);
    if (!call) {
        KIWI_ERROR_AND_EXIT("not found multiary operator", getLocation());
    }
    return call;
}

Callable* CallNode::findCallable(Driver& driver, std::vector<Type*> types) const {
    std::vector<Type*> args(types.begin() + 1, types.end());
    Callable* call = types[0]->findMethod(m_method, args);
    if (!call) {
        KIWI_ERROR_AND_EXIT("Method not found", getLocation());
    }
    return call;
}

// Emit instructions
ValueBuilder NewNode::emit(Driver& driver, BlockBuilder block) const {
    KIWI_NOT_IMPLEMENTED();
    // std::vector<ValueBuilder> args;
    // Type* type = m_type->get(driver);
    // if (ObjectType* objType = dyn_cast<ObjectType>(type)) {
    //     ValueBuilder expr   = ObjectEmitter(objType).emitNew(gen);
    //     args.push_back(expr);
    //     ValueBuilder result = emitCall(driver, expr, args);
    //     return ValueBuilder(result, expr.getType(), expr.getValue());
    // }
    // KIWI_ERROR_AND_EXIT("Type has not constructed", m_type->getLocation());
}

ValueBuilder AssignNode::emit(Driver& driver, BlockBuilder block) const {
    ValueBuilder value = m_right->emit(driver, block);
    return m_left->emit(driver, value);
}

ValueBuilder NamedMutableNode::emit(Driver& driver, ValueBuilder value) const {
    ValueBuilder* builder = o_var->findBuilder(value.getFunction());
    if (!builder)
        KIWI_ERROR_AND_EXIT("Not found value builder for store value in varaible", getLocation());
    return value.createStore(*builder, value);
}

ValueBuilder NamedExpressionNode::emit(Driver& driver, BlockBuilder block) const {
    ValueBuilder* builder = o_var->findBuilder(block.getFunction());
    if (!builder)
        KIWI_ERROR_AND_EXIT("Not found value builder for store value in varaible", getLocation());
    return block.createLoad(*builder);
}

ValueBuilder IntegerConstNode::emit(Driver& driver, BlockBuilder block) const {
    return block.createIntConst(m_value);
}

ValueBuilder BoolConstNode::emit(Driver& driver, BlockBuilder block) const {
    return block.createBoolConst(m_value);
}

ValueBuilder StringConstNode::emit(Driver& driver, BlockBuilder block) const {
    return block.createStringConst(m_value);
}

ValueBuilder CharConstNode::emit(Driver& driver, BlockBuilder block) const {
    return block.createCharConst(m_value);
}

ValueBuilder InstanceMutableNode::emit(Driver& driver, ValueBuilder value) const {
    KIWI_NOT_IMPLEMENTED();
    // Type* owner = block.getOwner();
    // ObjectType* type = dyn_cast<ObjectType>(owner);
    // if (type) {
    //     ValueBuilder thisValue = ThisNode(dyn_cast<ObjectType>(owner)).emit(driver, gen);
    //     return ObjectEmitter(type).emitStore(block, thisValue, m_name, gen);
    // } else {
    //     KIWI_ERROR_AND_EXIT("Fields not exists in type", getLocation());
    // }
}

ValueBuilder InstanceExpressionNode::emit(Driver& driver, BlockBuilder block) const {
    KIWI_NOT_IMPLEMENTED();
    // Type* owner = block.getOwner();
    // ObjectType* type = dyn_cast<ObjectType>(owner);
    // if (type) {
    //     ValueBuilder thisValue = ThisNode(dyn_cast<ObjectType>(owner)).emit(driver, gen);
    //     return ObjectEmitter(type).emitLoad(block, thisValue, m_name);
    // } else {
    //     KIWI_ERROR_AND_EXIT("Fields not exists in type", getLocation());
    // }
}

#include <llvm/Function.h>
ValueBuilder ThisNode::emit(Driver& driver, BlockBuilder block) const {
    llvm::Function* func = block.getFunction();
    if (func->arg_empty()) {
        KIWI_ERROR_AND_EXIT("Not found this", getLocation());
    }
    llvm::Argument* arg  = func->arg_begin();
    return ValueBuilder(block, arg, m_thisType);
}
