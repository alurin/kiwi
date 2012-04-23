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
    class Context;
namespace lang {

    /// Factory for nodes
    class NodeFactory {
    public:
        // destructor
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
            return inject(new UnaryNode(Member::NEG, value), loc);
        }

        ExpressionNode* createPos(ExpressionNode* value, const location& loc) {
            return inject(new UnaryNode(Member::POS, value), loc);
        }

        ExpressionNode* createNot(ExpressionNode* value, const location& loc) {
            return inject(new UnaryNode(Member::NOT, value), loc);
        }

        ExpressionNode* createDec(ExpressionNode* value, bool post, const location& loc) {
            return inject(new UnaryNode(Member::DEC, value, post), loc);
        }

        ExpressionNode* createInc(ExpressionNode* value, bool post, const location& loc) {
            return inject(new UnaryNode(Member::INC, value, post), loc);
        }

        ExpressionNode* createAdd(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::ADD, left, right), loc);
        }

        ExpressionNode* createSub(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::SUB, left, right), loc);
        }

        ExpressionNode* createMul(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::MUL, left, right), loc);
        }

        ExpressionNode* createDiv(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::DIV, left, right), loc);
        }

        ExpressionNode* createLsh(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::LSH, left, right), loc);
        }

        ExpressionNode* createRsh(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::RSH, left, right), loc);
        }

        ExpressionNode* createOr(ExpressionNode* left, ExpressionNode* right, bool logic, const location& loc) {
            return inject(new BinaryNode(Member::OR, left, right, logic), loc);
        }

        ExpressionNode* createAnd(ExpressionNode* left, ExpressionNode* right, bool logic, const location& loc) {
            return inject(new BinaryNode(Member::AND, left, right, logic), loc);
        }

        ExpressionNode* createEq(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::EQ, left, right), loc);
        }

        ExpressionNode* createNeq(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::NEQ, left, right), loc);
        }

        ExpressionNode* createGe(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::GE, left, right), loc);
        }

        ExpressionNode* createLe(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::LE, left, right), loc);
        }

        ExpressionNode* createGt(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::GT, left, right), loc);
        }

        ExpressionNode* createLt(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            return inject(new BinaryNode(Member::LT, left, right), loc);
        }

        ExpressionNode* createAssign(MutableNode* left, ExpressionNode* right, const location& loc) {
            return inject(new AssignNode(left, right), loc);
        }

        //===--------------------------------------------------------------===//
        //    Statements
        //===--------------------------------------------------------------===//
        StatementNode* createExpr(ExpressionNode* expr) {
            return inject(new ExpressionStatementNode(scope(), expr), expr->getLocation());
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

        //===--------------------------------------------------------------===//
        //    Calls
        //===--------------------------------------------------------------===//

        /// returns current call
        CallNode* call();

        /// declare call
        CallNode* call(const Identifier& name, const location& loc);

        /// declare call
        CallNode* call(ExpressionNode* expr, const Identifier& name, const location& loc);

        /// declare call
        CallNode* call(ExpressionNode* expr, const location& loc);

        /// end current call
        CallNode* callEnd();

        //===--------------------------------------------------------------===//
        //    Other staff
        //===--------------------------------------------------------------===//

        // constructor
        NodeFactory(Context* context, Type* thisType)
        : m_context(context), m_this(thisType) { }

        // returns begin of functions vector
        std::vector<FunctionNode*>::const_iterator func_begin() const {
            return m_functions.begin();
        }

        // returns end of functions vector
        std::vector<FunctionNode*>::const_iterator func_end() const {
            return m_functions.end();
        }

        // returns begin of fields vector
        std::vector<FieldNode*>::const_iterator field_begin() const {
            return m_fields.begin();
        }

        // returns end of fields vector
        std::vector<FieldNode*>::const_iterator field_end() const {
            return m_fields.end();
        }
    protected:
        /// Current context
        Context* m_context;

        /// This type
        Type* m_this;

        /// Stack of current parse functions
        std::stack<FunctionNode*> m_funcs;

        /// Stack of current parse scopes
        std::stack<ScopeNode*> m_scopes;

        /// Stack of current parse calls
        std::stack<CallNode*> m_calls;

        /// List of parsed functions
        std::vector<FunctionNode*> m_functions;

        /// List of parsed fields
        std::vector<FieldNode*> m_fields;

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
