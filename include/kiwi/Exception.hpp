/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_EXCEPTION_INCLUDED
#define KIWI_EXCEPTION_INCLUDED

#include "kiwi/types.hpp"
#include <boost/exception/all.hpp>
#include <boost/format.hpp>
#include <ostream>

namespace kiwi {
    /// Information about exception: current nam of file
    typedef boost::error_info<struct tag_message, std::string>  exception_message;

    /// Information about exception: current nam of file
    typedef boost::error_info<struct tag_filename, std::string> exception_filename;

    /// Base exception class for all Kiwi core exceptions
    class Exception : virtual public boost::exception, public virtual std::exception {
    };

    /// Base exception class for all language excception, e.g. not found variables
    class LangException : public virtual Exception {
    public:
        const char* what() const throw() {
            return boost::diagnostic_information_what(*this);
        }
    };

    /// Copy past from Bison
    class Position {
    public:
        Position()
        : line(0), column(0) {
        }

        Position(uint32_t line, uint32_t column)
        : line(line), column(column) {
        }
    public:
        /// Current line number.
        uint32_t line;
        /// Current column number.
        uint32_t column;
    };

    /// Copy past from Bison
    class Location {
    public:
        Location() {
        }

        Location(const std::string& filename, const Position& begin, const Position& end)
        : filename(filename), begin(begin), end(end) {
        }
    public:
        /// File name to which this location region refers.
        std::string filename;
        /// Beginning of the located region.
        Position begin;
        /// End of the located region.
        Position end;
    };

    /// Information about exception: current line of file
    typedef boost::error_info<struct tag_fileline, Location> exception_location;

    /// output core information about exception in stream
    std::ostream& operator<<(std::ostream& stream, const Exception& ex);

    /// output core information about exception in stream
    std::ostream& operator<<(std::ostream& stream, const Location& location);

    #define exception_format(_format, _args) exception_message(boost::str(boost::format(_format) % _args ))
}

#endif
