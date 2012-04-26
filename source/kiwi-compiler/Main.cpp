/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "kiwi/Engine.hpp"
#include "kiwi/Module.hpp"
#include <boost/program_options.hpp>
#include <iostream>

using namespace kiwi;
namespace po = boost::program_options;

void printVersion() {
    std::cout << KIWI_NAME        << " v"               << KIWI_VERSION_STRING  << std::endl;
    std::cout << KIWI_VENDOR_NAME << "; Copyright (C) " << KIWI_COPYRIGHT_YEARS << std::endl;
}

int main(int argc, char const *argv[]) {
    int  opt = 0;

    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("version", "dump version")
        ("optimization,O", po::value<int>(&opt)->default_value(0), "optimization level [0-3]")
        ("debug", "debug parser and scanner")
        ("ir-dump", "dump generated LLVM module")
        ("input-file", po::value< std::vector< std::string > >(), "input file")
    ;

    // Add position for files
    po::positional_options_description p;
    p.add("input-file", -1);

    // Load options from console
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).
          options(desc).positional(p).run(), vm);
    po::notify(vm);

    /// Run application
    ContextEngine engine;
    Context* context = engine.get();
    context->setOptimizationLevel(opt);
    context->setDebug(vm.count("debug"));

    if (vm.count("input-file")) {
        std::vector< std::string > files = vm["input-file"].as< std::vector< std::string > >();

        try {
            // create script module
            Module* module = Module::create("Kiwi::Script", context);
            for (std::vector< std::string >::iterator i = files.begin(); i != files.end(); ++i) {
                module->includeFile(*i);
            }

            // build module and dump or execute
            module->build();
            if (vm.count("ir-dump")) {
                module->dump();
            } else {
                return module->run();
            }
        } catch (const char* ex) {
            std::cerr << ex << "\n";
            return 1;
        }
    } else if (vm.count("help")) {
        std::cout << desc << "\n";
    } else if (vm.count("version")) {
        printVersion();
        return 0;
    }

    return 0;
}
