/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "kiwi/Engine.hpp"
#include "kiwi/Module.hpp"
#include <iostream>

using namespace kiwi;

int main(int argc, char const *argv[]) {
    ContextEngine engine;
    Context* context = engine.get();
    context->setOptimizationLevel(1);
    context->setDebug(false);
    Module* module = Module::create("user.script", context);

    Path filename;
    if (argc == 1) {
        return 1;
    }

    try {
        // parse file
        if (module->includeFile(argv[1])) {
            // build module and execute this
            module->build();
            return module->run();
        }
        return 1;
    } catch (const char* ex) {
        std::cerr << ex << "\n";
        return 1;
    }
}
