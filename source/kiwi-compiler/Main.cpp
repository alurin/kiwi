#include <iostream>
#include <boost/program_options.hpp>
#include "kiwi/Framework.hpp"

namespace po = boost::program_options;
using namespace kiwi;

int main(int argc, char const *argv[])
{
    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    FrameworkRef ref = Framework::create();
    return 0;
}