#include "test.h" // Brings in the UnitTest++ framework
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost::algorithm;

#define TEST_EXE                "../../bin/kiwic "
#define TEST_RESOURCE_PATH      "../../test/resource/"
#define TEST_RESOURCE_INPUT     ".kiwi"
#define TEST_RESOURCE_OUTPUT    ".out"
#define LINE_BREAK              \
"\n================================================================================\n"

/// Execute string and return actual result
std::string test_script_exec(std::string command) {
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::stringstream lines;
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe)) {
            lines << buffer;
        }
    }
    pclose(pipe);
    return lines.str();
}

/// Load expected result
std::string test_script_load(std::string filename) {
    std::ifstream infile(filename.c_str());
    if (!infile) {
        return "";
    }
    std::stringstream lines;
    std::string line;
    while (infile) {
        std::getline(infile, line);
        lines << line << "\n";
    }
    infile.close();
    return lines.str();
}

/// Run script as external process!!!
bool run_script(std::string filename, int32_t olevel) {
    std::string input  = (TEST_RESOURCE_PATH + filename + TEST_RESOURCE_INPUT);
    std::string output = (TEST_RESOURCE_PATH + filename + TEST_RESOURCE_OUTPUT);

    // prepare application for run
    std::stringstream ss;
    ss << TEST_EXE << input << " " << "-O" << olevel << " 2>&1";

    // check strings
    std::string expected = test_script_load(output);
    std::string actual   = test_script_exec(ss.str());

    /// last new lines and spaces not valid
    trim(expected);
    trim(actual);

    if (expected != actual) {
        std::cerr
                << "Execute script: "  << filename << TEST_RESOURCE_INPUT << " with -O" << olevel << "\n"
                << "Expected output: " << LINE_BREAK
                << expected            << LINE_BREAK
                << "Actual output: "   << LINE_BREAK
                << actual              << LINE_BREAK;
        CHECK(expected == actual);
        return false;
    }
    return true;
}

// Define test for parsing scripts
#define TEST_SCRIPT(name) \
    TEST(name) { \
        for (int olevel = 0; olevel < 4; ++olevel) { \
            if (!run_script(#name, olevel)) return; \
        } \
    }
