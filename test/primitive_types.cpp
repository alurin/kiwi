/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "test.h" // Brings in the UnitTest++ framework
#include "kiwi/Context.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/DerivedTypes.hpp"
#include "kiwi/Members.hpp"
#include <vector>

using namespace kiwi;

TEST(integer_primitive_type_test)
{
    ContextPtr context = Context::create();
    IntegerPtr type    = IntegerType::get32(context);

    CHECK(type->findUnary(Member::Print).get());
}

TEST(string_primitive_type_test)
{

}
