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
    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
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

    ContextRef frm = Context::create();
    if (vm.count("input-file")) {
        vector<string> files = vm["input-file"].as< vector<string> >();
        cout << "Input files are: " << files << "\n";

        ModuleRef module = Module::create("Kiwi::Script", frm);

        for (vector<string>::iterator i = files.begin(); i != files.end(); ++i) {
            module->includeFile(*i);
        }
        return 1;
    } else if (vm.count("help")) {
        cout << desc << "\n";
        return 1;
    }
    return 0;
}