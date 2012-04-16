#include "kiwi/Framework.hpp"
#include "lang/Driver.hpp"
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>

using namespace kiwi;

Framework::Framework()
{

}

FrameworkRef Framework::create()
{
    FrameworkRef ref = FrameworkRef(new Framework());
    return ref;
}

void Framework::includeFile(const Path& filename)
{
    lang::Driver driver;
    driver.parseFile(filename);

    llvm::LLVMContext context;
    llvm::Module* module = new llvm::Module("Test module", context);
}