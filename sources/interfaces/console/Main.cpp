#include "kiwi/String.hpp"
#include "kiwi/Engine.hpp"
#include "ConsoleHost.hpp"

#include <boost/program_options.hpp>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace kiwi;
using namespace kiwi::console;
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

        bool isExit = vm.count("help") || vm.count("version");
#if KIWI_DEBUG
        bool isVersion = vm.count("help") || vm.count("version");
#else
        bool isVersion = vm.count("help") || vm.count("version") || !vm.count("input-file");
#endif
        bool isHelp = vm.count("help");

        /// Output version if need
        if (isVersion) {
            std::cout << KIWI_NAME << " " << KIWI_VERSION_STRING << "\n";
        }
        if (isHelp) {
            std::cout << KIWI_VENDOR_NAME << ". Copyright (C) " << KIWI_COPYRIGHT_YEARS << ". " << KIWI_COPYRIGHT_LICENSE << ".\n\n"
                      << desc;
        }
        if (isExit) {
            return EXIT_SUCCESS;
        }
    }

    /// Create engine and start process
    {
        ConsoleHost host;
        Engine engine;
//
//        // Backend* backend = new vm::VmBackend();
//        // Frontend* frontend = new console::ConsoleFrontend();
//        // Engine engine(backend, frontend);
//
//        /// Trace driver actions??
//#ifdef KIWI_DEBUG
//        //test_primary_types(engine.getContext());
//        engine.setDriverDebug(vm.count("debug-driver"));
//#endif
//
//        try {
//            if (vm.count("input-file")) {
//                Path path = vm["input-file"].as< Path > ();
//                return engine.requireFile(path) ? EXIT_SUCCESS : EXIT_FAILURE;
//            } else {
//                std::cerr << "Не задан файл для исполнения. Запустите приложение с параметром --help для получения информации о параметрах\n";
//                return EXIT_FAILURE;
//            }
//        } catch (Exception* ex) {
//            ex->dump(std::cerr);
//            return EXIT_FAILURE;
//        }
    }
}

