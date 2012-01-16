#ifndef KIWI_ENGINE_HPP_INCLUDED
#define KIWI_ENGINE_HPP_INCLUDED

#include "llvm/LLVMContext.h"

namespace kiwi {
    /// The Engine class represents genral point for Kiwi
    ///
    /// @since 0.1
    class Engine {
    public:
        /// Engine constructor. This set up engine configuration
        Engine();

        /// Engine desctructor. This is clean up all resource requested by engine
        /// and
        ~Engine();
    }; // class Engine
} // namespace kiwi

#endif
