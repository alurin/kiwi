#include "TypeNode.hpp"

#include "kiwi/Module.hpp"

#include <llvm/DerivedTypes.h>
#include <llvm/Module.h>

using namespace kiwi;
using namespace kiwi::lang;

llvm::Type* TypeNode::generate(ModuleRef module)
{
    return llvm::Type::getInt32Ty(module->getModule()->getContext());
}