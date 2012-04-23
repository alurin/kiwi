#ifndef KIWI_LANG_LOGGER_INTERNAL
#define KIWI_LANG_LOGGER_INTERNAL

#include "kiwi/Config.hpp"
#include <istream>

namespace kiwi {
namespace lang {
    /// Better loger for compile procesess for source code
    class SourceLogger {
    public:
        /// Stream
        SourceLogger();

        /// Stream
        SourceLogger(std::istream* input);

        /// Dump error information in current error stream
        void error(const class location& l, const std::string& m);
    protected:
        std::istream* m_input;
    }; // class UnaryEmitter


} // namespace codegen
} // namespace kiwi

#endif
