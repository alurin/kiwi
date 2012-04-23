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
            MutableNode* node = new InstanceMutableNode(name);
            node->setLocation(loc);
            return node;
        }

        /// returns right expression for instance node
        ExpressionNode* instanceRight(const Identifier& name, const location& loc) {
            ExpressionNode* node = new InstanceExpressionNode(name);
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
        ExpressionNode* createInt(int32_t value, const location& loc) {
            ExpressionNode* node = new IntegerConstNode(m_context, value);
            node->setLocation(loc);
            return node;
        }

        ExpressionNode* createString(const String& value, const location& loc) {
            ExpressionNode* node = new StringConstNode(m_context, value);
            node->setLocation(loc);
            return node;
        }

        ExpressionNode* createChar(const UChar& value, const location& loc) {
            ExpressionNode* node = new CharConstNode(m_context, value);
            node->setLocation(loc);
            return node;
        }

        ExpressionNode* createBool(bool value, const location& loc) {
            ExpressionNode* node = new BoolConstNode(m_context, value);
            node->setLocation(loc);
            return node;
        }

        //===--------------------------------------------------------------===//
        //    Expressions
        //===--------------------------------------------------------------===//
        ExpressionNode* createNeg(ExpressionNode* value, const location& loc) {
            ExpressionNode* node = new UnaryNode(Member::NEG, value);
            node->setLocation(loc);
            return node;
        }

        ExpressionNode* createPos(ExpressionNode* value, const location& loc) {
            ExpressionNode* node = new UnaryNode(Member::POS, value);
            node->setLocation(loc);
            return node;
        }

        ExpressionNode* createNot(ExpressionNode* value, const location& loc) {
            ExpressionNode* node = new UnaryNode(Member::NOT, value);
            node->setLocation(loc);
            return node;
        }

        ExpressionNode* createDec(ExpressionNode* value, bool post, const location& loc) {
            ExpressionNode* node = new UnaryNode(Member::DEC, value, post);
            node->setLocation(loc);
            return node;
        }

        ExpressionNode* createInc(ExpressionNode* value, bool post, const location& loc) {
            ExpressionNode* node = new UnaryNode(Member::INC, value, post);
            node->setLocation(loc);
            return node;
        }

        ExpressionNode* createAdd(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            ExpressionNode* node = new BinaryNode(Member::ADD, left, right);
            node->setLocation(loc);
            return node;
        }

        ExpressionNode* createSub(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            ExpressionNode* node = new BinaryNode(Member::SUB, left, right);
            node->setLocation(loc);
            return node;
        }

        ExpressionNode* createMul(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            ExpressionNode* node = new BinaryNode(Member::MUL, left, right);
            node->setLocation(loc);
            return node;
        }

        ExpressionNode* createDiv(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            ExpressionNode* node = new BinaryNode(Member::DIV, left, right);
            node->setLocation(loc);
            return node;
        }

        ExpressionNode* createLsh(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            ExpressionNode* node = new BinaryNode(Member::LSH, left, right);
            node->setLocation(loc);
            return node;
        }

        ExpressionNode* createRsh(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            ExpressionNode* node = new BinaryNode(Member::RSH, left, right);
            node->setLocation(loc);
            return node;
        }

        ExpressionNode* createOr(ExpressionNode* left, ExpressionNode* right, bool logic, const location& loc) {
            ExpressionNode* node = new BinaryNode(Member::OR, left, right, logic);
            node->setLocation(loc);
            return node;
        }

        ExpressionNode* createAnd(ExpressionNode* left, ExpressionNode* right, bool logic, const location& loc) {
            ExpressionNode* node = new BinaryNode(Member::AND, left, right, logic);
            node->setLocation(loc);
            return node;
        }

        ExpressionNode* createEq(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            ExpressionNode* node = new BinaryNode(Member::EQ, left, right);
            node->setLocation(loc);
            return node;
        }

        ExpressionNode* createNeq(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            ExpressionNode* node = new BinaryNode(Member::NEQ, left, right);
            node->setLocation(loc);
            return node;
        }

        ExpressionNode* createGe(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            ExpressionNode* node = new BinaryNode(Member::GE, left, right);
            node->setLocation(loc);
            return node;
        }

        ExpressionNode* createLe(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            ExpressionNode* node = new BinaryNode(Member::LE, left, right);
            node->setLocation(loc);
            return node;
        }

        ExpressionNode* createGt(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            ExpressionNode* node = new BinaryNode(Member::GT, left, right);
            node->setLocation(loc);
            return node;
        }

        ExpressionNode* createLt(ExpressionNode* left, ExpressionNode* right, const location& loc) {
            ExpressionNode* node = new BinaryNode(Member::LT, left, right);
            node->setLocation(loc);
            return node;
        }

        ExpressionNode* createAssign(MutableNode* left, ExpressionNode* right, const location& loc) {
            ExpressionNode* node = new AssignNode(left, right);
            node->setLocation(loc);
            return node;
        }

        //===--------------------------------------------------------------===//
        //    Statements
        //===--------------------------------------------------------------===//
        StatementNode* createReturn(const location& loc) {
            StatementNode* node = new ReturnStatement(scope());
            node->setLocation(loc);
            return node;
        }

        StatementNode* createReturn(ExpressionNode* result, const location& loc) {
            StatementNode* node = new ReturnStatement(scope(), result);
            node->setLocation(loc);
            return node;
        }

        StatementNode* createPrint(ExpressionNode* result, const location& loc) {
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

        /// declare call
        CallNode* call(ExpressionNode* expr, const Identifier& name);

        /// declare call
        CallNode* call(ExpressionNode* expr);

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
    };

}}

#endif
