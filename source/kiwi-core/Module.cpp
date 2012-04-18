#include "kiwi/Context.hpp"
#include "kiwi/Module.hpp"

#include "lang/Driver.hpp"
#include "lang/FunctionNode.hpp"

#include "llvm/Module.h"

using namespace kiwi;

Module::Module(const Identifier& name, const ContextRef& context)
: m_name(name), m_context(context), m_module(0)
{
    m_module = new llvm::Module(name, context->getContext());
}

ModuleRef Module::create(const Identifier& name, const ContextRef& ref)
{
    ModuleRef module = ModuleRef(new Module(name, ref));
    return module;
}

void Module::includeFile(const Path& filename)
{
    lang::Driver driver(m_context.lock());
    if (driver.parseFile(filename)) {
        /// @todo build examples
        for (std::vector<lang::FunctionNode*>::const_iterator i = driver.func_begin(); i != driver.func_end(); ++i)
        {
            (*i)->generate(shared_from_this());
        }
    }
    m_module->dump();
}