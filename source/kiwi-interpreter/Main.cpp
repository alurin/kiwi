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

    try {
        ContextPtr context = Context::create();
        context->setOptimizationLevel(1);
        context->setDebug(false);
        ModulePtr module = Module::create("user.script", context);

        Path filename;
        if (argc < 2) {
            return 1;
        }

        // parse file
        if (module->includeFile(argv[1])) {
            // build module and execute this
            return context->run(module);
        }
    } catch (Exception& ex) {
        std::cerr << ex << "\n";
    } catch (const char* ex) {
        std::cerr << ex << "\n";
    } catch (std::exception& ex) {
        std::cerr << ex.what() << "\n";
    }

    return 1;
}
