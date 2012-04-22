#ifndef KIWI_LANG_FACTORY_INTERNAL
#define KIWI_LANG_FACTORY_INTERNAL

#include "kiwi/DerivedTypes.hpp"
#include "StatementNode.hpp"
#include "ExpressionNode.hpp"
#include "FunctionNode.hpp"
#include "TypeNode.hpp"
#include "location.hh"
#include <vector>
#include <stack>

namespace kiwi {
    typedef boost::shared_ptr<class Context> ContextRef;
namespace lang {

    /// Factory for nodes
    class NodeFactory {
    public:
        ~NodeFactory();

        //===--------------------------------------------------------------===//
        //    Functions
        //===--------------------------------------------------------------===//
        /// returns current function
        FunctionNode* func();

        /// declare function
        FunctionNode* func(const Identifier& name, TypeNode* type);

        /// end current function
        FunctionNode* funcEnd();

        //===--------------------------------------------------------------===//
        //    Functions
        //===--------------------------------------------------------------===//
        FieldNode* field(const Identifier& name, TypeNode* type);

        //===--------------------------------------------------------------===//
        //    Scopes
        //===--------------------------------------------------------------===//
        /// returns current scope
        ScopeNode* scope();

        /// begin new scope
        ScopeNode* scopeBegin();

        /// end current scope
        ScopeNode* scopeEnd();

        //===--------------------------------------------------------------===//
        //    Variables
        //===--------------------------------------------------------------===//
        // returns left expression for named node
        LeftNode* left(const Identifier& name, const location& loc);

        /// returns right expression for named node
        RightNode* right(const Identifier& name, const location& loc);

        // returns left expression for instance node
        LeftNode* instanceLeft(const Identifier& name, const location& loc) {
            LeftNode* node = new InstanceLeftNode(name);
            node->setLocation(loc);
            return node;
        }

        /// returns right expression for instance node
        RightNode* instanceRight(const Identifier& name, const location& loc) {
            RightNode* node = new InstanceRightNode(name);
            node->setLocation(loc);
            return node;
        }

        //===--------------------------------------------------------------===//
        //    Types
        //===--------------------------------------------------------------===//
        TypeNode* createVoidTy(const location& loc) {
            TypeNode* node = new ConcreteTypeNode(VoidType::get(m_context));
            node->setLocation(loc);
            return node;
        }

        TypeNode* createIntTy(const location& loc) {
            TypeNode* node = new ConcreteTypeNode(IntType::get32(m_context));
            node->setLocation(loc);
            return node;
        }

        TypeNode* createBoolTy(const location& loc) {
            TypeNode* node = new ConcreteTypeNode(BoolType::get(m_context));
            node->setLocation(loc);
            return node;
        }

        TypeNode* createStringTy(const location& loc) {
            TypeNode* node = new ConcreteTypeNode(StringType::get(m_context));
            node->setLocation(loc);
            return node;
        }

        TypeNode* createCharTy(const location& loc) {
            TypeNode* node = new ConcreteTypeNode(CharType::get(m_context));
            node->setLocation(loc);
            return node;
        }

        TypeNode* createArrayTy(TypeNode* type, const location& loc) {
            throw "Not implemented";
        }

        //===--------------------------------------------------------------===//
        //    Constants
        //===--------------------------------------------------------------===//
        RightNode* createInt(int32_t value, const location& loc)
        {
            RightNode* node = new IntegerConstNode(m_context, value);
            node->setLocation(loc);
            return node;
        }

        RightNode* createString(const String& value, const location& loc)
        {
            RightNode* node = new StringConstNode(m_context, value);
            node->setLocation(loc);
            return node;
        }

        RightNode* createChar(const UChar& value, const location& loc)
        {
            RightNode* node = new CharConstNode(m_context, value);
            node->setLocation(loc);
            return node;
        }

        RightNode* createBool(bool value, const location& loc)
        {
            RightNode* node = new BoolConstNode(m_context, value);
            node->setLocation(loc);
            return node;
        }

        //===--------------------------------------------------------------===//
        //    Expressions
        //===--------------------------------------------------------------===//
        RightNode* createNeg(RightNode* value, const location& loc)
        {
            RightNode* node = new UnaryNode(Member::NEG, value);
            node->setLocation(loc);
            return node;
        }

        RightNode* createPos(RightNode* value, const location& loc)
        {
            RightNode* node = new UnaryNode(Member::POS, value);
            node->setLocation(loc);
            return node;
        }

        RightNode* createNot(RightNode* value, const location& loc)
        {
            RightNode* node = new UnaryNode(Member::NOT, value);
            node->setLocation(loc);
            return node;
        }

        RightNode* createDec(RightNode* value, bool post, const location& loc)
        {
            RightNode* node = new UnaryNode(Member::DEC, value, post);
            node->setLocation(loc);
            return node;
        }

        RightNode* createInc(RightNode* value, bool post, const location& loc)
        {
            RightNode* node = new UnaryNode(Member::INC, value, post);
            node->setLocation(loc);
            return node;
        }

        RightNode* createAdd(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(Member::ADD, left, right);
            node->setLocation(loc);
            return node;
        }

        RightNode* createSub(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(Member::SUB, left, right);
            node->setLocation(loc);
            return node;
        }

        RightNode* createMul(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(Member::MUL, left, right);
            node->setLocation(loc);
            return node;
        }

        RightNode* createDiv(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(Member::DIV, left, right);
            node->setLocation(loc);
            return node;
        }

        RightNode* createLsh(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(Member::LSH, left, right);
            node->setLocation(loc);
            return node;
        }

        RightNode* createRsh(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(Member::RSH, left, right);
            node->setLocation(loc);
            return node;
        }

        RightNode* createOr(RightNode* left, RightNode* right, bool logic, const location& loc)
        {
            RightNode* node = new BinaryNode(Member::OR, left, right, logic);
            node->setLocation(loc);
            return node;
        }

        RightNode* createAnd(RightNode* left, RightNode* right, bool logic, const location& loc)
        {
            RightNode* node = new BinaryNode(Member::AND, left, right, logic);
            node->setLocation(loc);
            return node;
        }

        RightNode* createEq(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(Member::EQ, left, right);
            node->setLocation(loc);
            return node;
        }

        RightNode* createNeq(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(Member::NEQ, left, right);
            node->setLocation(loc);
            return node;
        }

        RightNode* createGe(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(Member::GE, left, right);
            node->setLocation(loc);
            return node;
        }

        RightNode* createLe(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(Member::LE, left, right);
            node->setLocation(loc);
            return node;
        }

        RightNode* createGt(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(Member::GT, left, right);
            node->setLocation(loc);
            return node;
        }

        RightNode* createLt(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(Member::LT, left, right);
            node->setLocation(loc);
            return node;
        }

        RightNode* createAssign(LeftNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new AssignNode(left, right);
            node->setLocation(loc);
            return node;
        }

        //===--------------------------------------------------------------===//
        //    Statements
        //===--------------------------------------------------------------===//
        StatementNode* createReturn(const location& loc)
        {
            StatementNode* node = new ReturnStatement(scope());
            node->setLocation(loc);
            return node;
        }

        StatementNode* createReturn(RightNode* result, const location& loc)
        {
            StatementNode* node = new ReturnStatement(scope(), result);
            node->setLocation(loc);
            return node;
        }

        StatementNode* createPrint(RightNode* result, const location& loc)
        {
            StatementNode* node = new PrintStatement(scope(), result);
            node->setLocation(loc);
            return node;
        }

        //===--------------------------------------------------------------===//
        //    Calls
        //===--------------------------------------------------------------===//

        /// returns current call
        CallNode* call();

        /// declare call
        CallNode* call(const Identifier& name);

        /// end current call
        CallNode* callEnd();

        //===--------------------------------------------------------------===//
        //    Other staff
        //===--------------------------------------------------------------===//

        // constructor
        NodeFactory(ContextRef context)
        : m_context(context) { }

        // returns begin of functions vector
        std::vector<FunctionNode*>::const_iterator func_begin() const
        {
            return m_functions.begin();
        }

        // returns end of functions vector
        std::vector<FunctionNode*>::const_iterator func_end() const
        {
            return m_functions.end();
        }

        // returns begin of fields vector
        std::vector<FieldNode*>::const_iterator field_begin() const
        {
            return m_fields.begin();
        }

        // returns end of fields vector
        std::vector<FieldNode*>::const_iterator field_end() const
        {
            return m_fields.end();
        }
    protected:
        ContextRef                  m_context;
        std::stack<FunctionNode*>   m_funcs;
        std::stack<ScopeNode*>      m_scopes;
        std::stack<CallNode*>       m_calls;
        std::vector<FunctionNode*>  m_functions;
        std::vector<FieldNode*>     m_fields;
    };

}}

#endif
