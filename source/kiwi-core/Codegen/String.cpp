#include "kiwi/Codegen/String.hpp"
#include "kiwi/Context.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/DerivedTypes.hpp"
#include <llvm/Constants.h>
#include <llvm/Function.h>
#include <llvm/GlobalVariable.h>
#include <llvm/Instructions.h>

using namespace kiwi;
using namespace kiwi::codegen;

StringEmitter::StringEmitter(StringType* stringTy)
: m_stringTy(stringTy) { }

/// Emit string constant
ExpressionGen StringEmitter::emit(const StatementGen& gen, const String& value)
{
    // get partial types for string
    llvm::LLVMContext& context = m_stringTy->getModule()->getContext()->getContext();
    llvm::Type* charType = llvm::IntegerType::get(context, 16);
    llvm::Type* sizeType = llvm::IntegerType::get(context, 32);
    llvm::ArrayType* bufferType = llvm::ArrayType::get(charType, value.length());

    // generate string type
    std::vector<llvm::Type*> elements;
    elements.push_back(sizeType);
    elements.push_back(bufferType);
    llvm::StructType* stringType = llvm::StructType::create(context, llvm::makeArrayRef(elements), "string", false);

    // generate size
    llvm::Constant* size = 0;
    {
        llvm::APInt cst(32, value.length(), false);
        size = llvm::ConstantInt::get(context, cst);
    }

    // generate buffer
    llvm::Constant* buffer = 0;
    {
        std::vector<llvm::Constant*> bufferConst;
        for (int i = 0; i < value.length(); ++i)
        {
            llvm::APInt cst(16, value[i], false);
            llvm::ConstantInt* value = llvm::ConstantInt::get(context, cst);
            bufferConst.push_back(value);
        }
        buffer = llvm::ConstantArray::get(bufferType, bufferConst);
    }

    // generate string
    llvm::Constant* string = llvm::ConstantStruct::get(stringType, size, buffer, NULL);
    llvm::GlobalVariable* result  = new llvm::GlobalVariable(
        *(gen.getModule()),
        stringType,
        true,
        llvm::GlobalValue::PrivateLinkage,
        string,
        "string"
     );
    result->setUnnamedAddr(true); // Binary equal strings must be merged
    return ExpressionGen(gen, m_stringTy, result);
}
