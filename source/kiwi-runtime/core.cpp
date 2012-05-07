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

struct KiwiObject {
    KiwiVTable* VTable;
    KiwiAMap*   AMap;
    KiwiData*   Data;
};

struct KiwiData {
    KiwiType*   Type;   ///< type for data
    void*       Buffer; ///< buffer with data
};

// start up runtime
void kiwi_startup() {

}

// shut down runtime
void kiwi_shutdown() {

}

// dummy
void kiwi_dummy() {
}

KiwiObject* kiwi_dyn_cast(KiwiData* data, KiwiType* type) {
    Type* current = reinterpret_cast<Type*>(data->Type);
    Type* derived = reinterpret_cast<Type*>(type);

    // alloca new object handler
    KiwiObject* object = (KiwiObject*) kiwi_malloc(sizeof(KiwiObject));

    // store new object handler
    object->VTable = reinterpret_cast<KiwiVTable*>(current->getVTablePointer(derived->shared_from_this()));
    object->AMap   = reinterpret_cast<KiwiAMap*>(current->getAMapPointer(derived->shared_from_this()));
    object->Data   = data;

    return object;
}
