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
            throw "Not implemented";
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

        //===--------------------------------------------------------------===//
        //    Expressions
        //===--------------------------------------------------------------===//
        RightNode* createNeg(RightNode* value, const location& loc)
        {
            RightNode* node = new UnaryNode(UnaryOperator::NEG, value);
            node->setLocation(loc);
            return node;
        }

        RightNode* createPos(RightNode* value, const location& loc)
        {
            RightNode* node = new UnaryNode(UnaryOperator::POS, value);
            node->setLocation(loc);
            return node;
        }

        RightNode* createNot(RightNode* value, const location& loc)
        {
            RightNode* node = new UnaryNode(UnaryOperator::NOT, value);
            node->setLocation(loc);
            return node;
        }

        RightNode* createDec(RightNode* value, bool post, const location& loc)
        {
            RightNode* node = new UnaryNode(UnaryOperator::DEC, value, post);
            node->setLocation(loc);
            return node;
        }

        RightNode* createInc(RightNode* value, bool post, const location& loc)
        {
            RightNode* node = new UnaryNode(UnaryOperator::INC, value, post);
            node->setLocation(loc);
            return node;
        }

        RightNode* createAdd(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(BinaryOperator::ADD, left, right);
            node->setLocation(loc);
            return node;
        }

        RightNode* createSub(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(BinaryOperator::SUB, left, right);
            node->setLocation(loc);
            return node;
        }

        RightNode* createMul(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(BinaryOperator::MUL, left, right);
            node->setLocation(loc);
            return node;
        }

        RightNode* createDiv(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(BinaryOperator::DIV, left, right);
            node->setLocation(loc);
            return node;
        }

        RightNode* createLsh(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(BinaryOperator::LSH, left, right);
            node->setLocation(loc);
            return node;
        }

        RightNode* createRsh(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(BinaryOperator::RSH, left, right);
            node->setLocation(loc);
            return node;
        }

        RightNode* createOr(RightNode* left, RightNode* right, bool logic, const location& loc)
        {
            RightNode* node = new BinaryNode(BinaryOperator::OR, left, right, logic);
            node->setLocation(loc);
            return node;
        }

        RightNode* createAnd(RightNode* left, RightNode* right, bool logic, const location& loc)
        {
            RightNode* node = new BinaryNode(BinaryOperator::AND, left, right, logic);
            node->setLocation(loc);
            return node;
        }

        RightNode* createEq(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(BinaryOperator::EQ, left, right);
            node->setLocation(loc);
            return node;
        }

        RightNode* createNeq(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(BinaryOperator::NEQ, left, right);
            node->setLocation(loc);
            return node;
        }

        RightNode* createGe(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(BinaryOperator::GE, left, right);
            node->setLocation(loc);
            return node;
        }

        RightNode* createLe(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(BinaryOperator::LE, left, right);
            node->setLocation(loc);
            return node;
        }

        RightNode* createGt(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(BinaryOperator::GT, left, right);
            node->setLocation(loc);
            return node;
        }

        RightNode* createLt(RightNode* left, RightNode* right, const location& loc)
        {
            RightNode* node = new BinaryNode(BinaryOperator::LT, left, right);
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
    protected:
        ContextRef                  m_context;
        std::stack<FunctionNode*>   m_funcs;
        std::stack<ScopeNode*>      m_scopes;
        std::vector<FunctionNode*>  m_functions;
    };

}}

#endif
