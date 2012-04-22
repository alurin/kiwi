#include "ContextMeta.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Member.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Context.hpp"
#include "codegen/LlvmEmitter.hpp"
#include <llvm/DerivedTypes.h>
#include <llvm/Instruction.h>

using namespace kiwi;
using namespace kiwi::codegen;

// cosntructor
Member::Member(const TypeRef& type)
: m_ownerType(type) { }

// destructor
Member::~Member() { }