/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#include "kiwi/IO/Stream.hpp"

using namespace kiwi;
using namespace kiwi::io;

InputStream::InputStream(UFILE* file) : m_file(file) {

}

OutputStream::OutputStream(UFILE* file) : m_file(file) {
    
}

InputStream::~InputStream() {
    u_fclose(m_file);
}

OutputStream::~OutputStream() {
    u_fclose(m_file);
}

InputStream* InputStream::createFromFile(UFILE* file) {
    return new InputStream(file);
}

InputStream* InputStream::createFromFile(FILE* file) {
    UFILE* ufile = u_finit(file, NULL, NULL);
    kiwi_assert(ufile && "File init is caused error");
    return new InputStream(ufile);
}

OutputStream* OutputStream::createFromFile(UFILE* file) {
    return new OutputStream(file);
}

OutputStream* OutputStream::createFromFile(FILE* file) {
    UFILE* ufile = u_finit(file, NULL, NULL);
    kiwi_assert(ufile && "File init is caused error");
    return new OutputStream(ufile);
}

size_t InputStream::read(UChar* buffer, const size_t count) {
    return u_file_read(buffer, count, m_file);
}

size_t OutputStream::write(const UChar* buffer, const size_t count) {
    return u_file_write_44(buffer, count, m_file);
}