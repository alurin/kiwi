/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "Logger.hpp"
#include "location.hh"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace kiwi;
using namespace kiwi::lang;

namespace {
    typedef std::vector<std::string> StringVector;

    class LinesReader {
    public:
        LinesReader(std::istream& input) : m_input(input), m_position(-1) {
            /// Hz. This is good or not good?
            m_endFile  = input.eof();
            m_input.clear(std::ios::goodbit);
            m_position = input.tellg();
        }

        ~LinesReader() {
            if (m_position != -1) {
                m_input.seekg(m_position, std::ios::beg);
            } else if (m_endFile) {
                m_input.seekg(m_position, std::ios::end);
            }
        }

        StringVector readLines(const class location& loc);
    protected:
        std::istream&           m_input;
        std::istream::pos_type  m_position;
        bool                    m_endFile;
    };
}

SourceLogger::SourceLogger()
: m_input(0) {

}

SourceLogger::SourceLogger(std::istream* input)
: m_input(input) {
}

/// Dump error information in current error stream
void SourceLogger::error(const class location& loc, const std::string& m) {
    StringVector lines;
    if (m_input) {
        LinesReader reader(*m_input);
        lines = reader.readLines(loc);
    }

    // Write error message
    std::cerr << loc << ": " << m << std::endl;

    // Write lines from source file
    size_t current = loc.begin.line;
    size_t width   = 80 - 8;
    for (StringVector::iterator i = lines.begin(); i != lines.end(); ++i, ++current) {
        std::string line = *i;
        size_t last      = 0;
        bool first       = true;
        while (last < line.size()) {
            int lenght = std::min(line.size(), last + width);

            // print input string
            if (first) {
                std::cerr << std::setw(6) << std::setfill(' ') << current << " :";
            }
            for (size_t j = last; j < lenght; ++j) {
                std::cerr << line[j];
            }

            // print error information lines
            std::cerr << std::endl << "...... :";
            for (size_t j = last; j < lenght; ++j) {
                bool first  = loc.begin.line < current      || loc.begin.column - 1 <= j;
                bool second = current        < loc.end.line || j < loc.end.column - 1;
                std::cerr << ((first && second) ? "^" : ".");
            }
            std::cerr << std::endl;

            last += width;
            first = false;
        }
    }
}

/// read lines from stream
StringVector LinesReader::readLines(const class location& loc) {
    StringVector lines;
    if (m_position != -1 || m_endFile) {
        std::string line;
        int32_t count = 0;

        /// Move to begin of file
        m_input.clear(std::ios::goodbit);
        m_input.seekg (0, std::ios::beg);

        // collect lines
        while(m_input) {
            std::getline(m_input, line);
            count++;

            /// store line
            if (loc.begin.line <= count && count <= loc.end.line) {
                lines.push_back(line);
            } else if (count > loc.end.line) {
                break;
            }
        }
    }
    return lines;
}
