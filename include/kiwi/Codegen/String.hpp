#ifndef KIWI_CODEGEN_STRING_INTERNAL
#define KIWI_CODEGEN_STRING_INTERNAL

#include "kiwi/Codegen/Expression.hpp"

namespace kiwi {
    typedef boost::shared_ptr<StringType> StringTy;
namespace codegen {
    /// Emitter for standart operation with objects
    class StringEmitter {
    public:
        /// constructor
        StringEmitter(StringTy);

        /// emit constant string
        ExpressionGen emit(const String& value);
    protected:
        ContextWeak m_context;
    };

}} // namespace kiwi::codegen

#endif
