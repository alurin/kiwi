/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
/*
 * This file includes the magic necessary in order to get your unit tests
 * that you create with UnitTest++ to automatically run. There should
 * never be a reason to modify this file. For an example unit test,
 * see "sanity_check.cpp". For a reference on creating tests, see "test.h".
 *
 */
#include "test.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <iostream>
#include <sstream>
#include "kiwi/Engine.hpp"

void run_script(std::string filename, int32_t olevel);

int main(int argc, char* argv[]) {
    kiwi::EngineGuard guard;
    return UnitTest::RunAllTests();
}
