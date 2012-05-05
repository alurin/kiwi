/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "Driver.hpp"
#include "ExpressionNode.hpp"
#include "FunctionNode.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/DerivedTypes.hpp"
#include "kiwi/Support/Cast.hpp"
#include "../Codegen/Builder.hpp"
#include <sstream>

using namespace kiwi;
using namespace kiwi::lang;


namespace {
    inline
    std::string format_call(const std::vector<TypePtr>& args) {
        std::stringstream ss;
        bool notFirst = false;
        for (std::vector<TypePtr>::const_iterator i = args.begin(); i != args.end(); ++i) {
            if (notFirst) ss << ", "; else notFirst = true;
            ss << (*i)->getName();
        }
        return ss.str();
    }
}

BinaryNode::BinaryNode(Member::MethodOpcode opcode, ExpressionNode* left, ExpressionNode* right, bool logic)
: m_opcode(opcode), m_logic(logic) {
    append(left);
    append(right);
}

UnaryNode::UnaryNode(Member::MethodOpcode opcode, ExpressionNode* value, bool post)
: m_opcode(opcode), m_post(post) {
    append(value);
}

MultiaryNode::MultiaryNode(Member::MethodOpcode opcode, ExpressionNode* value)
: m_opcode(opcode) {
    append(value);
}

MultiaryNode::MultiaryNode(Member::MethodOpcode opcode)
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


IntegerConstNode::IntegerConstNode(ContextPtr context, int32_t value)
: m_context(context), m_value(value) { }

BoolConstNode::BoolConstNode(ContextPtr context, bool value)
: m_context(context), m_value(value) { }

StringConstNode::StringConstNode(ContextPtr context, const String& value)
: m_context(context), m_value(value) { }

CharConstNode::CharConstNode(ContextPtr context, const UChar& value)
: m_context(context), m_value(value) { }

CallableArgument::CallableArgument(const Identifier& name, ExpressionNode* value, int32_t position)
: m_name(name), m_value(value), m_position(position) {
    setLocation(value->getLocation());
}

CallableArgument::CallableArgument(ExpressionNode* value, int32_t position)
: m_value(value), m_position(position) {
    setLocation(value->getLocation());
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

InstanceMutableNode::InstanceMutableNode(ThisNode* thisNode, const Identifier& name)
: m_thisNode(thisNode), m_name(name) { }

InstanceExpressionNode::InstanceExpressionNode(ThisNode* thisNode, const Identifier& name)
: m_thisNode(thisNode), m_name(name) { }

ThisNode::ThisNode(CompoundNode* thisType)
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

// void CallableNode::prepend(ExpressionNode* value) {
//     if (value)
//         m_arguments.push_front(new CallableArgument(value, m_arguments.size()));
// }

ValueBuilder MutableNode::emit(Driver& driver, ValueBuilder value) const {
    KIWI_EXCEPTION_ADD_LOCATION({
        return emitImpl(driver, value);
    }, getLocation());
}

ValueBuilder ExpressionNode::emit(Driver& driver, BlockBuilder block) const {
    KIWI_EXCEPTION_ADD_LOCATION({
        return emitImpl(driver, block);
    }, getLocation());
}

ValueBuilder CallableArgument::emit(Driver& driver, BlockBuilder block) const {
    return m_value->emit(driver, block);
}

ValueBuilder CallableNode::emitImpl(Driver& driver, BlockBuilder block) const {
    std::vector<ValueBuilder> args;
    return emitCall(driver, block, args);
}

// Find arguments for append before other
ValueBuilder CallableNode::emitCall(Driver& driver, BlockBuilder block, std::vector<ValueBuilder> args) const {
    std::vector<TypePtr> types;
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
    MethodPtr call = call = findCallable(driver, types);

    if (!call) {
        throw LangException()
            << exception_message("Not found rules for call")
            << exception_location(to_location(this));
    }
    return block.createCall(call, args);
}

MethodPtr BinaryNode::findCallable(Driver& driver, std::vector<TypePtr> types) const {
    MethodPtr call = types[0]->findBinary(m_opcode, types[1]);
    if (!call) {
        throw LangException()
            << exception_format("Not found binary operator %1%(%2%)", Member::getOperatorName(m_opcode) % format_call(types))
            << exception_location(to_location(this));
    }
    return call;
}

MethodPtr UnaryNode::findCallable(Driver& driver, std::vector<TypePtr> types) const {
    MethodPtr call = types[0]->findUnary(m_opcode);
    if (!call) {
        throw LangException()
            << exception_format("Not found unary operator %1%(%2%)", Member::getOperatorName(m_opcode) % format_call(types))
            << exception_location(to_location(this));
    }
    return call;
}

MethodPtr MultiaryNode::findCallable(Driver& driver, std::vector<TypePtr> types) const {
    kiwi_assert(types.size() > 0, "MultiaryNode::findCallable must recive at last one argument");
    std::vector<TypePtr> args(types.begin() + 1, types.end());
    MethodPtr call = types[0]->findMultiary(m_opcode, args);
    if (!call) {
        throw LangException()
            << exception_format("Not found multiary operator %1%(%2%)", Member::getOperatorName(m_opcode) % format_call(types))
            << exception_location(to_location(this));
    }
    return call;
}

MethodPtr CallNode::findCallable(Driver& driver, std::vector<TypePtr> types) const {
    std::vector<TypePtr> args(types.begin() + 1, types.end());
    MethodPtr call = types[0]->findMethod(m_method, args);
    if (!call) {
        throw LangException()
            << exception_format("Not found method %1%(%2%)", m_method % format_call(types))
            << exception_location(to_location(this));
    }
    return call;
}

// Emit instructions
ValueBuilder NewNode::emitImpl(Driver& driver, BlockBuilder block) const {
    TypePtr type = m_type->get(driver);
    if (ObjectPtr objType = dyn_cast<ObjectType>(type)) {
        return block.createNew(objType);
    } else {
        throw LangException()
            << exception_format("Type '%1%' is not constructable", type->getName())
            << exception_location(to_location(this));
    }
}

ValueBuilder AssignNode::emitImpl(Driver& driver, BlockBuilder block) const {
    ValueBuilder value = m_right->emit(driver, block);
    return m_left->emit(driver, value);
}

ValueBuilder NamedMutableNode::emitImpl(Driver& driver, ValueBuilder value) const {
    ValueBuilder* builder = o_var->findBuilder(value.getFunction());
    if (!builder) {
        throw LangException()
            << exception_message("Not found value builder for store value in varaible")
            << exception_location(to_location(this));
    }
    return value.createStore(*builder, value);
}

ValueBuilder NamedExpressionNode::emitImpl(Driver& driver, BlockBuilder block) const {
    ValueBuilder* builder = o_var->findBuilder(block.getFunction());
    if (!builder)
        throw LangException()
            << exception_message("Not found value builder for store value in varaible")
            << exception_location(to_location(this));
    return block.createLoad(*builder);
}

ValueBuilder IntegerConstNode::emitImpl(Driver& driver, BlockBuilder block) const {
    return block.createIntConst(m_value);
}

ValueBuilder BoolConstNode::emitImpl(Driver& driver, BlockBuilder block) const {
    return block.createBoolConst(m_value);
}

ValueBuilder StringConstNode::emitImpl(Driver& driver, BlockBuilder block) const {
    return block.createStringConst(m_value);
}

ValueBuilder CharConstNode::emitImpl(Driver& driver, BlockBuilder block) const {
    return block.createCharConst(m_value);
}

/// @todo Remove copy past
ValueBuilder InstanceMutableNode::emitImpl(Driver& driver, ValueBuilder value) const {
    TypePtr owner      = value.getNativeOwner();
    ObjectPtr type = dyn_cast<ObjectType>(owner);
    if (type) {
        FieldPtr field = type->findField(m_name);
        if (field) {
            ValueBuilder thisValue = m_thisNode->emit(driver, value);
            return thisValue.createStore(thisValue, field, value);
        }
    }
    throw LangException()
        << exception_format("Field '%1%' not found in type '%2%'", m_name % type->getName())
        << exception_location(to_location(this));
}

/// @todo Remove copy past
ValueBuilder InstanceExpressionNode::emitImpl(Driver& driver, BlockBuilder block) const {
    TypePtr owner      = block.getNativeOwner();
    ObjectPtr type = dyn_cast<ObjectType>(owner);
    if (type) {
        FieldPtr field     = type->findField(m_name);
        if (field) {
            ValueBuilder thisValue = m_thisNode->emit(driver, block);
            return thisValue.createLoad(thisValue, field);
        }
    }
    throw LangException()
        << exception_format("Field '%1%' not found in type '%2%'", m_name % type->getName())
        << exception_location(to_location(this));
}

#include <llvm/Function.h>
ValueBuilder ThisNode::emitImpl(Driver& driver, BlockBuilder block) const {
    llvm::Function* func = block.getFunction();
    if (func->arg_empty()) {
        throw LangException()
            << exception_message("This or self argument not found")
            << exception_location(to_location(this));
    }
    TypePtr type = m_thisType->getType();
    kiwi_assert(type, "Type is null");
    return ValueBuilder(block, func->arg_begin(), type);
}
