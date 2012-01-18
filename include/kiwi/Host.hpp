/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#ifndef KIWI_HOST_HPP_INCLUDED
#define KIWI_HOST_HPP_INCLUDED

#include "kiwi/IO/Stream.hpp"

namespace kiwi {
    /// The Host class is abstract class for host environment
    class Host {
    public:
        /// Virtual destructor
        virtual ~Host();

        /// Returns input stream
        io::InputStream*  getInputStream()  const {
            return m_inputStream;
        }

        /// Returns output stream
        io::OutputStream* getOutputStream() const {
            return m_outputStream;
        }

        /// Returns error stream
        io::OutputStream* getErrorStream()  const {
            return m_errorStream;
        }
    protected:
        /// Input stream
        io::InputStream*  m_inputStream;
        
        /// Output stream
        io::OutputStream* m_outputStream;
        
        /// Error stream
        io::OutputStream* m_errorStream;

        /// Protected constructor
        Host();
    };
}

#endif