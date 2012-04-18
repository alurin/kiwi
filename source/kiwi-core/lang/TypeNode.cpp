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