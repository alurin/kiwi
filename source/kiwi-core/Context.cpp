#include "ContextMeta.hpp"
#include "kiwi/Context.hpp"
#include "kiwi/Module.hpp"
#include "RuntimeModule.hpp"
#include <llvm/LLVMContext.h>

using namespace kiwi;

Context::Context()
: m_context(0), m_meta(new ContextMeta()), m_optimizationLevel(1), m_debug(false)
{

}

Context::~Context() {
    delete m_context;
    delete m_meta;
}

Context* Context::create()
{
    Context* context = new Context();
    context->initializate();
    return context;
}

void Context::initializate()
{
    m_context = new llvm::LLVMContext();

    Module* module = Module::create("system", this);
    m_meta->boolTy = BoolType::create(module);
    m_meta->int32Ty = IntType::create(module, 32, false);
    m_meta->voidTy = VoidType::create(module);
    m_meta->charTy = CharType::create(module);
    m_meta->stringTy = StringType::create(module);

    initRuntimeModule(module);
}
