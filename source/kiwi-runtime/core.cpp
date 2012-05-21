/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "kiwi-runtime/core.h"
#include "kiwi-runtime/gc.h"
#include "kiwi/Type.hpp"

using namespace kiwi;

namespace {
    TypePtr kiwi_icast(KiwiType type) {
        return reinterpret_cast<Type*>(type)->shared_from_this();
    }
}

// start up runtime
void kiwi_startup() {

}

// shut down runtime
void kiwi_shutdown() {

}

// dummy
void kiwi_dummy() {
}

KiwiObject kiwi_up_cast(KiwiObject obj, KiwiType type) {
    TypePtr current = kiwi_icast(obj->Data->Type);
    TypePtr derived = kiwi_icast(type);

    // check requirement of a upper cast
    if (current == derived) {
        return obj;
    }

    // allocate new object handler and store pointers
    KiwiObject parent = (KiwiObject) kiwi_malloc(sizeof(KiwiOpaqueObject));
    parent->VTable    = reinterpret_cast<KiwiVTable*>(current->getVTablePointer(derived));
    parent->AMap      = reinterpret_cast<KiwiAMap*>(current->getAMapPointer(derived));
    parent->Data      = obj->Data;
    return parent;
}

#include <unicode/ustream.h>
KIWI_RUNTIME
void kiwi_debug_pointer(void* ptr, const UChar* buffer, const int32_t length) {
    String string(buffer, length);
    KIWI_DUMP(string << ": " << ptr);
}

KIWI_RUNTIME
void kiwi_debug_integer(int64_t ptr, const UChar* buffer, const int32_t length) {
    String string(buffer, length);
    KIWI_DUMP(string << ": " << ptr);
}