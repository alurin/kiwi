#include "kiwi/Context.hpp"
#include "kiwi/Module.hpp"
using namespace kiwi;

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

// A helper function to simplify the main part.
template<class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    copy(v.begin(), v.end(), ostream_iterator<T>(cout, " "));
    return os;
}

int main(int argc, char const *argv[])
{
    int  opt     = 0;

    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("optimization,O", po::value<int>(&opt)->default_value(0), "optimization level [0-3]")
        ("debug", "debug parser and scanner")
        ("ir-dump", "dump generated LLVM module")
        ("input-file", po::value< vector<string> >(), "input file")
    ;

    // Add position for files
    po::positional_options_description p;
    p.add("input-file", -1);

    // Load options from console
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).
          options(desc).positional(p).run(), vm);
    po::notify(vm);

    ContextRef context = Context::create();
    context->setOptimizationLevel(opt);
    context->setDebug(vm.count("debug"));

    if (vm.count("input-file")) {
        vector<string> files = vm["input-file"].as< vector<string> >();

        try {
            // create script module
            ModuleRef module = Module::create("Kiwi::Script", context);
            for (vector<string>::iterator i = files.begin(); i != files.end(); ++i) {
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
        cout << desc << "\n";
        return 1;
    }
    return 0;
}