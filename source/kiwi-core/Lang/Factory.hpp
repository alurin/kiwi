/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_LANG_FACTORY_INTERNAL
#define KIWI_LANG_FACTORY_INTERNAL

#include "kiwi/DerivedTypes.hpp"
#include "StatementNode.hpp"
#include "ExpressionNode.hpp"
#include "FunctionNode.hpp"
#include "TypeNode.hpp"
#include "CompoundNode.hpp"
#include "location.hh"
#include <vector>
#include <stack>

namespace kiwi {
    class Context;
namespace lang {

    /// Factory for nodes
    class NodeFactory {
    public:
        // destructor
        virtual ~NodeFactory();

        //===--------------------------------------------------------------===//
        //    Classes
        //===--------------------------------------------------------------===//
        /// returns current function
        CompoundNode* classTop();

        /// declare function
        CompoundNode* classBegin(const Identifier& name, const location& loc);

        /// end current function
        CompoundNode* classEnd();

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
        FieldNode* field(const Identifier& name, TypeNode* type) {
            return new FieldNode(name, type);
        }

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
        MutableNode* left(const Identifier& name, const location& loc);

        /// returns right expression for named node
        ExpressionNode* right(const Identifier& name, const location& loc);

        // returns left expression for instance node
        MutableNode* instanceLeft(const Identifier& name, const location& loc) {
            return inject(new InstanceMutableNode(name), loc);
        }

        /// returns right expression for instance node
        ExpressionNode* instanceRight(const Identifier& name, const location& loc) {
            return inject(new InstanceExpressionNode(name), loc);
        }

        //===--------------------------------------------------------------===//
        //    Types
        //===--------------------------------------------------------------===//
        TypeNode* createVoidTy(const location& loc) {
            return inject(new ConcreteTypeNode(VoidType::get(m_context)), loc);
        }

        TypeNode* createIntTy(const location& loc) {
            return inject(new ConcreteTypeNode(IntType::get32(m_context)), loc);
        }

        TypeNode* createBoolTy(const location& loc) {
            return inject(new ConcreteTypeNode(BoolType::get(m_context)), loc);
        }

        TypeNode* createStringTy(const location& loc) {
            return inject(new ConcreteTypeNode(StringType::get(m_context)), loc);
        }

        TypeNode* createCharTy(const location& loc) {
            return inject(new ConcreteTypeNode(CharType::get(m_context)), loc);
        }

        TypeNode* createQualifiedTy(const Identifier& qualified, const location& loc) {
            return inject(new QualifiedTypeNode(qualified), loc);
        }

        TypeNode* createArrayTy(TypeNode* type, const location& loc) {
            throw "Not implemented";
        }

        //===--------------------------------------------------------------===//
        //    Constants
        //===--------------------------------------------------------------===//
        ExpressionNode* createInt(int32_t value, const location& loc) {
            return inject(new IntegerConstNode(m_context, value), loc);
        }

        ExpressionNode* createString(const String& value, const location& loc) {
            return inject(new StringConstNode(m_context, value), loc);
        }

        ExpressionNode* createChar(const UChar& value, const location& loc) {
            return inject(new CharConstNode(m_context, value), loc);
        }

        ExpressionNode* createBool(bool value, const location& loc) {
            return inject(new BoolConstNode(m_context, value), loc);
        }

        ExpressionNode* createThis(const location& loc);

        //===--------------------------------------------------------------===//
        //    Expressions
        //===--------------------------------------------------------------===//
        ExpressionNode* createNeg(ExpressionNode* value, const location& loc) {
            return inject(new UnaryNode(Member::Neg, value), loc);
        }

        ExpressionNode* createPos(ExpressionNode* value, const location& loc) {
            return inject(new UnaryNode(Member::Pos, value), loc);
        }

        ExpressionNode* createNot(ExpressionNode* value, const location& loc) {
            return inject(new UnaryNode(Member::Not, value), loc);
        }

        ExpressionNode* createDec(ExpressionNode* value, bool post, const location& loc) {
            return inject(new UnaryNode(Member::Dec, value, post), loc);
        }

        ExpressionNode* createInc(ExpressionNode* value, bool post, const location& loc) {
            return inject(new UnaryNode(Member::Inc, value, post), loc);
        }

        ExpressionNode* createAdd(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::Add, left, right), loc);
        }

        ExpressionNode* createSub(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::Sub, left, right), loc);
        }

        ExpressionNode* createMul(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::Mul, left, right), loc);
        }

        ExpressionNode* createDiv(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::Div, left, right), loc);
        }

        ExpressionNode* createLsh(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::Lsh, left, right), loc);
        }

        ExpressionNode* createRsh(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::Rsh, left, right), loc);
        }

        ExpressionNode* createOr(ExpressionNode* left, ExpressionNode* right, bool logic, const location& loc) {
            return inject(new BinaryNode(Member::Or, left, right, logic), loc);
        }

        ExpressionNode* createAnd(ExpressionNode* left, ExpressionNode* right, bool logic, const location& loc) {
            return inject(new BinaryNode(Member::And, left, right, logic), loc);
        }

        ExpressionNode* createEq(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::Eq, left, right), loc);
        }

        ExpressionNode* createNeq(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::Neq, left, right), loc);
        }

        ExpressionNode* createGe(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::Ge, left, right), loc);
        }

        ExpressionNode* createLe(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::Le, left, right), loc);
        }

        ExpressionNode* createGt(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::Gt, left, right), loc);
        }

        ExpressionNode* createLt(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::Lt, left, right), loc);
        }

        ExpressionNode* createAssign(MutableNode* left, ExpressionNode* right, const location& loc) {
            return inject(new AssignNode(left, right), loc);
        }

        //===--------------------------------------------------------------===//
        //    Statements
        //===--------------------------------------------------------------===//
        StatementNode* createExpr(ExpressionNode* expr) {
            if (expr)
                return inject(new ExpressionStatementNode(scope(), expr), expr->getLocation());
            return 0;
        }
        StatementNode* createReturn(const location& loc) {
            return inject(new ReturnStatement(scope()), loc);
        }

        StatementNode* createReturn(ExpressionNode* result, const location& loc) {
            return inject(new ReturnStatement(scope(), result), loc);
        }

        StatementNode* createPrint(ExpressionNode* result, const location& loc) {
            return inject(new PrintStatement(scope(), result), loc);
        }

        StatementNode* createCond(ExpressionNode* cond, StatementNode* trueStmt, StatementNode* falseStmt, const location& loc) {
            return inject(new ConditionalNode(scope(), cond, trueStmt, falseStmt), loc);
        }

        StatementNode* createInit(VariableNode* var, const location& loc) {
            return inject(new InitStatement(scope(), var), loc);
        }

        //===--------------------------------------------------------------===//
        //    Calls
        //===--------------------------------------------------------------===//

        /// returns current call
        CallableNode* call();

        /// declare call
        CallableNode* call(const Identifier& name, const location& loc);

        /// declare call
        CallableNode* call(ExpressionNode* expr, const Identifier& name, const location& loc);

        /// declare call to constructor
        CallableNode* newBegin(TypeNode* type, const location& loc);

        // begin new subtraction
        CallableNode* subBegin(ExpressionNode* expr, const location& loc);

        /// end current call
        CallableNode* callEnd(const location& loc);

        //===--------------------------------------------------------------===//
        //    Other staff
        //===--------------------------------------------------------------===//
        /// return context
        Context* getContext() const {
            return m_context;
        }

        /// returns module
        Module* getModule() const;

        /// returns iterator for compounds: begin
        std::vector<CompoundNode*>::const_iterator begin() const {
            return m_compounds.begin();
        }

        /// returns iterator for compounds: end
        std::vector<CompoundNode*>::const_iterator end() const {
            return m_compounds.end();
        }

        // return count of compounds
        size_t size() const {
            return m_compounds.size();
        }

        // prepare script level nodes
        void prepareScript(const location& loc);
    protected:
        /// Current context
        Context* m_context;

        /// This type
        Type* m_this;

        /// Stack of current parse functions
        std::stack<CompoundNode*> m_classes;

        /// Stack of current parse functions
        std::stack<FunctionNode*> m_funcs;

        /// Stack of current parse scopes
        std::stack<ScopeNode*> m_scopes;

        /// Stack of current parse calls
        std::stack<CallableNode*> m_calls;

        /// List of parsed classes
        std::vector<CompoundNode*> m_compounds;

        // constructor
        NodeFactory(Context* context, Type* thisType);

        //===--------------------------------------------------------------===//
        //    Utils
        //===--------------------------------------------------------------===//
        template<typename NodeT>
        NodeT* inject(NodeT* node, const location& loc) {
            node->setLocation(loc);
            return node;
        }
    };

}}

#endif
