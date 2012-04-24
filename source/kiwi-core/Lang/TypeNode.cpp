#include "Driver.hpp"
#include "TypeNode.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Type.hpp"

using namespace kiwi;
using namespace kiwi::lang;

TypeNode::TypeNode() {
}

TypeNode::~TypeNode() {
}

ConcreteTypeNode::ConcreteTypeNode(Type* type)
: m_type(type) {
}


QualifiedTypeNode::QualifiedTypeNode(const Identifier& name)
: m_name(name) {
}

Type* QualifiedTypeNode::get(Driver& driver) {
    Module* module = driver.getModule();
    Type*   type   = module->find(m_name);
    if (!type) {
        KIWI_ERROR_AND_EXIT("Type not found", getLocation());
    }
    return type;
}