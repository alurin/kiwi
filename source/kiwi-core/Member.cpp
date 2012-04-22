#include "ContextMeta.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Member.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Context.hpp"
#include "Codegen/LlvmEmitter.hpp"
#include <llvm/DerivedTypes.h>
#include <llvm/Instruction.h>

using namespace kiwi;
using namespace kiwi::codegen;

// cosntructor
Member::Member(Type* type)
: m_memberID((MemberID) 0), m_ownerType(type) { }

// destructor
Member::~Member() { }
