#include "ExpressionNode.hpp"
#include "FunctionNode.hpp"
#include "kiwi/codegen/Emitter.hpp"
#include "kiwi/DerivedTypes.hpp"
#include <llvm/Constants.h>
#include <llvm/Function.h>
#include <llvm/GlobalVariable.h>
#include <llvm/Instructions.h>

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

StringConstNode::StringConstNode(ContextRef context, const String& value)
: m_context(context), m_value(value) { }

CharConstNode::CharConstNode(ContextRef context, const UChar& value)
: m_context(context), m_value(value) { }

CallNode::CallNode(const Identifier& method)
: m_method(method), m_hasNamed(false) {}

void CallNode::append(const Identifier& name, RightNode* value)
{
    CallArgument arg;
    arg.Name     = name;
    arg.Position = m_arguments.size();
    arg.Value    = value;
    m_arguments.push_back(arg);
    m_hasNamed = true;
}

void CallNode::append(RightNode* value)
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
        llvm::StoreInst* inst = new llvm::StoreInst(gen.getValue(), var.getValue(), gen.getBlock());
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
        llvm::StoreInst* inst = new llvm::StoreInst(gen.getValue(), var.getValue(), gen.getBlock());
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

ExpressionGen StringConstNode::emit(const StatementGen& gen)
{
    // get partial types for string
    llvm::LLVMContext& context   = gen.getContext();
    llvm::Type* charType         = llvm::IntegerType::get(context, 16);
    llvm::Type* sizeType         = llvm::IntegerType::get(context, 32);
    llvm::ArrayType* bufferType  = llvm::ArrayType::get(charType, m_value.length());
    TypeRef                 type = StringType::get(m_context);

    // generate string type
    std::vector<llvm::Type*> elements;
    elements.push_back(sizeType);
    elements.push_back(bufferType);
    llvm::StructType* stringType = llvm::StructType::create(context, llvm::makeArrayRef(elements), "string", false);

    // generate size
    llvm::Constant* size = 0;
    {
        llvm::APInt cst(32, m_value.length(), false);
        size = llvm::ConstantInt::get(context, cst);
    }

    // generate buffer
    llvm::Constant* buffer = 0;
    {
        std::vector<llvm::Constant*> bufferConst;
        for (int i = 0; i < m_value.length(); ++i)
        {
            llvm::APInt cst(16, m_value[i], false);
            llvm::ConstantInt* value = llvm::ConstantInt::get(gen.getContext(), cst);
            bufferConst.push_back(value);
        }
        buffer = llvm::ConstantArray::get(bufferType, bufferConst);
    }

    // generate string
    llvm::Constant* string = llvm::ConstantStruct::get(stringType, size, buffer, NULL);
    llvm::GlobalVariable* value  = new llvm::GlobalVariable(
        *(gen.getModule()),
        stringType,
        true,
        llvm::GlobalValue::PrivateLinkage,
        string,
        "string"
     );
    value->setUnnamedAddr(true); // Binary equal strings must be merged
    return ExpressionGen(gen, StringType::get(m_context), value);
}

ExpressionGen CharConstNode::emit(const StatementGen& gen)
{
    llvm::APInt cst(16, m_value, true);
    llvm::ConstantInt* value = llvm::ConstantInt::get(gen.getContext(), cst);
    return ExpressionGen(gen, CharType::get(m_context), value);
}

ExpressionGen CallNode::emit(const StatementGen& gen)
{
    std::vector<TypeRef>        types;
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

    TypeRef owner    = gen.getOwner();
    MethodRef method = owner->find(m_method, types);
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
