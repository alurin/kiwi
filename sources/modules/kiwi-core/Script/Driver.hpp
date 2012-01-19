/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#ifndef KIWI_SCRIPT_DRIVER_HPP_INCLUDED
#define	KIWI_SCRIPT_DRIVER_HPP_INCLUDED

#include "kiwi/Types.hpp"
#include "kiwi/Script/RootNode.hpp"
#include <stack>
#include <string>
#include <vector>

namespace kiwi {
    class Engine;

    namespace script {
        class Lexer;

        /**
         * Class for instance of language analyse driver
         *
         * @since 0.1
         * @todo Error handling
         */
        class DriverImpl {
        public:
            /**
             * Driver constructor
             */
            DriverImpl(Engine* engine);

            /**
             * Destroy driver and clear all used symbols
             *
             * @todo Memory allocation and deallocation!!! Memory leak!!!!
             */
            virtual ~DriverImpl();

            /// Returns owner engine
            Engine* getEngine() const { 
                return m_engine;
            }
            
            //===----------------------------------------------------------------===//
            // Driver debug & trace
            //===----------------------------------------------------------------===//

            /**
             * Invoke the scanner and parser for a stream.
             *
             * @param in        input stream
             * @param sname     stream name for error messages
             * @return          true if successfully parsed
             */
            RootNode* parseStream(std::istream& in,
                              const String& sname = "stream input");

            //===----------------------------------------------------------------===//
            // Driver debug & trace
            //===----------------------------------------------------------------===//

            /// Get stream name
            String getStreamName() const {
                return m_streamName;
            }

            /// Returns stream name in utf-8 encoding
            Path getStreamNameUTF8() const;
        protected:
            /// Owner engine
            Engine* m_engine;

            /// Stream name
            String m_streamName;

            /// Cached stream name in utf-8 encoding
            mutable Path m_streamNameUTF8;

            /// Current lexer
            Lexer* m_lexer;
        };
    }
}

#endif	/* DRIVER_HPP */
