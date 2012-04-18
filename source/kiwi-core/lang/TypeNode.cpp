#include "TypeNode.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Type.hpp"
#include <llvm/DerivedTypes.h>
#include <llvm/Module.h>

using namespace kiwi;
using namespace kiwi::lang;

TypeNode::TypeNode() { }
TypeNode::~TypeNode() { }

ConcreteTypeNode::ConcreteTypeNode(TypeRef type)
: m_type(type) { }

TypeFactory::TypeFactory(ContextRef context)
: m_context(context) { }

TypeNode* TypeFactory::getVoid()
{
    /// @todo Not implemented
    throw "Not implemented";
}

TypeNode* TypeFactory::getInt()
{
    return new ConcreteTypeNode(IntType::get32(m_context));
}

TypeNode* TypeFactory::getString()
{
    /// @todo Not implemented
    throw "Not implemented";
}

TypeNode* TypeFactory::getArray(TypeNode* type)
{
    /// @todo Not implemented
    throw "Not implemented";
}
