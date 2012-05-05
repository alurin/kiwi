/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "kiwi/Exception.hpp"
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

using namespace kiwi;

#   define ANSI_COLOR_RED     "\x1b[31m"
#   define ANSI_COLOR_GREEN   "\x1b[32m"
#   define ANSI_COLOR_YELLOW  "\x1b[33m"
#   define ANSI_COLOR_BLUE    "\x1b[34m"
#   define ANSI_COLOR_MAGENTA "\x1b[35m"
#   define ANSI_COLOR_CYAN    "\x1b[36m"
#   define ANSI_COLOR_RESET   "\x1b[0m"

namespace {
    // vector of strings
    typedef std::vector<std::string> string_vector;

    // read lines from stream
    string_vector read_lines(std::istream& stream, const Location& loc, size_t& first, int extra = 2) {
        string_vector lines;
        std::string line;
        int32_t count = 0;
        first = 0;

        /// Move to begin of file
        stream.clear(std::ios::goodbit);
        stream.seekg (0, std::ios::beg);

        // collect lines
        while(stream) {
            std::getline(stream, line);
            count++;

            /// store line
            if ((loc.begin.line - extra) <= count && count <= (loc.end.line + extra + 1)) {
                if (first == 0) first = count;
                lines.push_back(line);
            } else if (count > loc.end.line) {
                break;
            }
        }
        return lines;
    }
}

// output core information about exception in stream
std::ostream& kiwi::operator<<(std::ostream& stream, const Exception& ex) {
    const Location* location  = 0;
    bool hasTwo  = false;
    bool hasEndl = false;

    // Output information about parsed file
    if (location = boost::get_error_info<exception_location>(ex)) {
        stream << ANSI_COLOR_MAGENTA << *location;

        hasEndl = true;
        hasTwo  = true;
    } else if (const std::string* filename = boost::get_error_info<exception_filename>(ex)) {
        stream << ANSI_COLOR_MAGENTA << *filename;

        hasEndl = true;
        hasTwo  = true;
    }

    // Output exception message
    if (const std::string* message = boost::get_error_info<exception_message>(ex)) {
        stream << ANSI_COLOR_RED << (hasTwo ? ": " : "") << *message;
        hasEndl = true;
    }

    if (hasEndl) stream << std::endl;

    // Output part of file around location
    if (location) {
        Location loc = *location;
        std::ifstream file(loc.filename.c_str());
        if (file.good()) {
            size_t current;
            size_t width   = 80 - 8;

            // read lines from file
            string_vector lines = read_lines(file, loc, current);

            // Write lines from source file
            for (string_vector::iterator i = lines.begin(); i != lines.end(); ++i, ++current) {
                std::string line = *i;
                size_t last      = 0;
                bool first       = true;
                bool errorLine   = (loc.begin.line <= current) && (current <= loc.end.line);

                // split line to 80 characters
                while (last < line.size()) {
                    int lenght     = std::min(line.size(), last + width);

                    // print input string
                    if (first) {
                        stream << ANSI_COLOR_CYAN << std::setw(6) << std::setfill(' ') << current << " : " << ANSI_COLOR_RESET;
                    }
                    for (size_t j = last; j < lenght; ++j) {
                        bool first  = loc.begin.line < current      || loc.begin.column - 1 <= j;
                        bool second = current        < loc.end.line || j < loc.end.column - 1;

                        if (errorLine && first && second) stream << ANSI_COLOR_GREEN;
                        stream << line[j] << ANSI_COLOR_RESET;
                    }

                    // print error information lines
                    stream << std::endl;

                    if (errorLine) {
                        stream << ANSI_COLOR_CYAN << "...... : " << ANSI_COLOR_RESET;
                        for (size_t j = last; j < lenght; ++j) {
                            bool first  = loc.begin.line < current      || loc.begin.column - 1 <= j;
                            bool second = current        < loc.end.line || j < loc.end.column - 1;

                            if (first && second)
                                stream << ANSI_COLOR_GREEN << "^" << ANSI_COLOR_RESET;
                            else
                                stream << ".";
                        }
                        stream << std::endl;
                    }
                    last += width;
                    first = false;
                }
            }
        }
    }

    return stream << ANSI_COLOR_RESET;
}

#include "../Lang/location.hh"

/// output core information about exception in stream
std::ostream& kiwi::operator<<(std::ostream& stream, const Location& location) {
    lang::position begin;
    lang::position end;

    std::string filename = location.filename;
    begin.filename = end.filename = &filename;
    begin.line   = location.begin.line;
    begin.column = location.begin.column;
    end.line     = location.end.line;
    end.column   = location.end.column;

    lang::location loc;
    loc.begin = begin;
    loc.end   = end;

    stream << loc;
}
