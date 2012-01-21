/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#ifndef KIWI_CONSOLE_CONSOLEHOST_HPP_INCLUDED
#define KIWI_CONSOLE_CONSOLEHOST_HPP_INCLUDED

#include "kiwi/Host.hpp"

namespace kiwi {
    namespace console {
        class ConsoleHost : public Host {
        public:
            ConsoleHost();
            
            virtual ~ConsoleHost();
        };
    }
}

#endif