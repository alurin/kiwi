#ifndef KIWI_IO_STREAM_HPP_INCLUDED
#define KIWI_IO_STREAM_HPP_INCLUDED

#include "kiwi/String.hpp"
#include <unicode/ustdio.h>

namespace kiwi {
    namespace io {
        /// The Stream class represpent binary stream
        class Stream { };

        /// Input stream class
        class InputStream  : public Stream {
        public:
            /// Create input stream from file
            static InputStream* createFromFile(FILE* file);

            /// Create input stream from file
            static InputStream* createFromFile(UFILE* file);

            /// Read from stream
            ///
            /// @param buffer Buffer is filled
            /// @param count The number of characters to read from file
            /// @return Actual count of readed characters
            size_t read(UChar* buffer, size_t count);

            virtual ~InputStream();
        protected:
            UFILE* m_file;

            InputStream(UFILE* file);
        };

        /// Output stream class
        class OutputStream : public Stream {
        public:
            /// Create output stream from file
            static OutputStream* createFromFile(FILE* file);

            /// Create output stream from file
            static OutputStream* createFromFile(UFILE* file);

            virtual ~OutputStream();
        protected:
            UFILE* m_file;

            OutputStream(UFILE* file);
        };
    }
}

#endif