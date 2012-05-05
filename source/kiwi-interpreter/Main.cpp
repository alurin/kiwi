/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "kiwi/ManagedStatic.hpp"
#include "kiwi/Context.hpp"
#include "kiwi/Exception.hpp"
#include "kiwi/Module.hpp"
#include <iostream>

using namespace kiwi;

int main(int argc, char const *argv[]) {
    kiwi::ManagedStatic guard;
    ContextPtr context = Context::create();
    context->setOptimizationLevel(1);
    context->setDebug(false);
    ModulePtr module = Module::create("user.script", context);

    Path filename;
    if (argc < 2) {
        return 1;
    }

    try {
        // parse file
        if (module->includeFile(argv[1])) {
            // build module and execute this
            return context->run(module);
        }
        return 1;
    } catch (Exception& ex) {
        std::cerr << ex << "\n";
    } catch (const char* ex) {
        std::cerr << ex << "\n";
        return 1;
    }
}
