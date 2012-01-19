/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#include "kiwi/String.hpp"
#include "kiwi/Engine.hpp"
#include "kiwi/Script/Driver.hpp"
#include "ConsoleHost.hpp"

#include <boost/program_options.hpp>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace kiwi;
using namespace kiwi::console;
using namespace kiwi::script;
namespace po = boost::program_options;

int main(int argc, char** argv)
{
    po::variables_map vm;
    /// Collect options for engine
    {
        // Declare the supported options.
        po::options_description desc("Options for Kiwi language compiler and interpreter", 120);
        desc.add_options()
              ("help", "show help message")
              ("version", "show version information")
#if KIWI_DEBUG
              ("debug-driver", "show debug information for script driver")
#endif
              ("input-file", po::value< Path > (), "file for parsing and executing")
              ;

        po::positional_options_description p;
        p.add("input-file", -1);

#if KIWI_WIN32
        std::vector< std::string > args = split_winmain(lpCmdLine);
        store(command_line_parser(args).options(desc).run(), vm);
#else
        po::store(po::command_line_parser(argc, argv).
                  options(desc).positional(p).run(), vm);
#endif
        po::notify(vm);

        /// Output version if need
        if (vm.count("version")) {
            std::cout << KIWI_NAME << " " << KIWI_VERSION_STRING << "\n";
            return EXIT_SUCCESS;
        }

        /// Output version if need
        if (vm.count("help")) {
            std::cout << KIWI_NAME << " " << KIWI_VERSION_STRING << "\n"
                      << KIWI_VENDOR_NAME << ". Copyright (C) " << KIWI_COPYRIGHT_YEARS << ". " << KIWI_COPYRIGHT_LICENSE << ".\n\n"
                      << desc;
            return EXIT_SUCCESS;
        }
        
        #if KIWI_DEBUG
            Driver::setDebugMode(vm.count("help"));
        #endif
    }

    /// Create engine and start process
    {
        ConsoleHost host;
        Engine engine(&host);

//        // Backend* backend = new vm::VmBackend();
//        // Frontend* frontend = new console::ConsoleFrontend();
//        // Engine engine(backend, frontend);
//
//        /// Trace driver actions??
//#ifdef KIWI_DEBUG
//        //test_primary_types(engine.getContext());
//        engine.setDriverDebug(vm.count("debug-driver"));
//#endif

//        try {
            if (vm.count("input-file")) {
                Path path = vm["input-file"].as< Path > ();
                return Driver::parseFile(&engine, path) ? EXIT_SUCCESS : EXIT_FAILURE;
            } else {
                std::cerr << "Do not specify input files. Run with --help for information about options\n";
                return EXIT_FAILURE;
            }
//        } catch (Exception* ex) {
//            ex->dump(std::cerr);
//            return EXIT_FAILURE;
//        }
    }
}

