#include "kiwi/Codegen/Object.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/DerivedTypes.hpp"
#include <llvm/Constants.h>
#include <llvm/Function.h>
#include <llvm/GlobalVariable.h>
#include <llvm/Instructions.h>

using namespace kiwi;
using namespace kiwi::codegen;

/// Emit string constant
ExpressionGen StringEmitter::emit(const String& value)
{
    // get partial types for string
    TypeRef type = StringType::get(m_context);
    llvm::LLVMContext& context = m_context.getContext();
    llvm::Type* charType = llvm::IntegerType::get(context, 16);
    llvm::Type* sizeType = llvm::IntegerType::get(context, 32);
    llvm::ArrayType* bufferType = llvm::ArrayType::get(charType, m_value.length());

    // generate string type
    std::vector<llvm::Type*> elements;
    elements.push_back(sizeType);
    elements.push_back(bufferType);
    llvm::StructType* stringType = llvm::StructType::create(context, llvm::makeArrayRef(elements), "string", false);

    // generate size
    llvm::Constant* size = 0;
    {
        llvm::APInt cst(32, m_value.length(), false);
        size = llvm::ConstantInt::get(context, cst);
    }

    // generate buffer
    llvm::Constant* buffer = 0;
    {
        std::vector<llvm::Constant*> bufferConst;
        for (int i = 0; i < m_value.length(); ++i)
        {
            llvm::APInt cst(16, m_value[i], false);
            llvm::ConstantInt* value = llvm::ConstantInt::get(gen.getContext(), cst);
            bufferConst.push_back(value);
        }
        buffer = llvm::ConstantArray::get(bufferType, bufferConst);
    }

    // generate string
    llvm::Constant* string = llvm::ConstantStruct::get(stringType, size, buffer, NULL);
    llvm::GlobalVariable* value  = new llvm::GlobalVariable(
        *(gen.getModule()),
        stringType,
        true,
        llvm::GlobalValue::PrivateLinkage,
        string,
        "string"
     );
    value->setUnnamedAddr(true); // Binary equal strings must be merged
    return ExpressionGen(gen, StringType::get(m_context), value);
}
