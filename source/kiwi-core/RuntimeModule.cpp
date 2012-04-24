#include "kiwi/Module.hpp"
#include "kiwi/DerivedTypes.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Support/Array.hpp"
#include "RuntimeModule.hpp"

// #include <llvm/ADT/ArrayRef.h>
// #include <llvm/Constants.h>
// #include <llvm/Function.h>
// #include <llvm/InstrTypes.h>
// #include <llvm/Instructions.h>
// #include <llvm/Module.h>

using namespace kiwi;

void kiwi::initRuntimeModule(Module* module) {
    StringType*     string    = StringType::get(module->getContext());
    IntType*        integer   = IntType::get32(module->getContext());

    // ObjectType*     aPoint    = ObjectType::create      (module, "AbstractPoint");
    // InterfaceType*  params    = InterfaceType::create   (module, "Params");
    // ObjectType*     envParams = ObjectType::create      (module, "EnvironmentParams");
    // ObjectType*     appParams = ObjectType::create      (module, "ProgrammParams");

    // params->add(Member::Substraction, string, makeArray(string, 0));                        /// [name];
    // params->add("get", string, makeArray(string, 0));                                       /// .get(name);
    // params->add("get", string, makeArray(string, string, 0));                               /// .get(name, default);

    // envParams->implement(params);
    // envParams->add(Member::Substraction, string, makeArray(string, 0), "kiwi_env_get");        /// [name];
    // envParams->add("get", string, makeArray(string, 0),                "kiwi_env_get");        /// .get(name);
    // envParams->add("get", string, makeArray(string, string, 0),        "kiwi_env_default");    /// .get(name, default);

    // appParams->implement(params);
    // appParams->add(Member::Substraction, string, makeArray(string, 0), "kiwi_arg_get");        /// [index];
    // appParams->add("get", string, makeArray(integer, 0),               "kiwi_arg_get");        /// .get(index);

    // pointType->add("getEnv",  envParams, makeArray<Type*>(0));  /// Get envirtoment arguments
    // pointType->add("getArgs", appParams, makeArray<Type*>(0));  /// Get console arguments

    /*
        llvm::Module*       llvmModule = mod->getModule();
        llvm::LLVMContext& context = llvmModule->getContext();
        llvm::Type*       voidType = llvm::Type::getVoidTy(context);
        llvm::Type*        intType = llvm::IntegerType::get(context, 32);
        llvm::Type*       charType = llvm::IntegerType::get(context, 16);
        llvm::Type*       boolType = llvm::IntegerType::get(context, 1);
        llvm::Type*     bufferType = charType->getPointerTo();
        llvm::Function* printInt    = llvm::dyn_cast<llvm::Function>(llvmModule->getOrInsertFunction("kiwi_print_integer", voidType, intType, NULL));
        llvm::Function* printBool   = llvm::dyn_cast<llvm::Function>(llvmModule->getOrInsertFunction("kiwi_print_bool",    voidType, boolType, NULL));
        llvm::Function* printChar   = llvm::dyn_cast<llvm::Function>(llvmModule->getOrInsertFunction("kiwi_print_char",    voidType, charType, NULL));
        llvm::Function* printString = llvm::dyn_cast<llvm::Function>(llvmModule->getOrInsertFunction("kiwi_print_string",  voidType, bufferType, intType, NULL));
    */
}
