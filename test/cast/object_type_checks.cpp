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

TEST(object_methods_check) {
    ContextPtr context  = Context::create();
    ModulePtr  module   = Module::create("script", context);
    ObjectPtr type      = ObjectType::create(module);
    VoidPtr type1       = VoidType::get(context);
    BooleanPtr type2    = BooleanType::get(context);

    std::vector<TypePtr> args;

    // create method "method" without argument
    {
        FieldPtr created = type->addField("field1", type1);
        FieldPtr method  = type->findField("field1");
        CHECK_EQUAL(created, method);
    }

    // create method "method" without argument
    {
        MethodPtr created = type->addMethod("method", type1, args);
        MethodPtr method  = type->findMethod("method", args);
        CHECK_EQUAL(created, method);
    }

    // create another method with name "method" with argument
    {
        args.clear();
        args.push_back(type2);
        MethodPtr created = type->addMethod("method", type1, args);
        MethodPtr method  = type->findMethod("method", args);
        CHECK_EQUAL(created, method);
    }
}

TEST(object_inheritance_check) {
    ContextPtr context = Context::create();
    ModulePtr  module  = Module::create("script", context);

    ObjectPtr parent = ObjectType::create(module);
    ObjectPtr first  = ObjectType::create(module);
    ObjectPtr second = ObjectType::create(module);
    ObjectPtr third  = ObjectType::create(module);
    ObjectPtr any    = ObjectType::create(module);

    first->inherit(parent);
    third->inherit(first);
    third->inherit(second);

    // first child of parent
    CHECK(first->isInherit(parent));

    // third type inherit direct from first and second, and indirect from first
    CHECK(third->isInherit(parent));
    CHECK(third->isInherit(first));
    CHECK(third->isInherit(second));

    // not one type inherit from any
    CHECK(!parent->isInherit(any));
    CHECK(!first->isInherit(any));
    CHECK(!second->isInherit(any));
    CHECK(!third->isInherit(any));


    // types must be castable to parents (Liskov substitution principle)
    CHECK(first->isCastableTo(parent));
    CHECK(third->isCastableTo(parent));
    CHECK(third->isCastableTo(first));
    CHECK(third->isCastableTo(second));
    CHECK(!third->isCastableTo(any));
}

TEST(object_field_override_check_after) {
    ContextPtr context = Context::create();
    ModulePtr  module  = Module::create("script", context);
    TypePtr       type = IntegerType::get32(context);

    ObjectPtr clA  = ObjectType::create(module, "A");  // A { @a, @b }
    ObjectPtr clB  = ObjectType::create(module, "B");  // B { @a, @c }
    ObjectPtr clC  = ObjectType::create(module, "C");  // C : A,B { @a merge A::@a, B::@a as }

    // inherit classes affter
    clC->inherit(clA);

    // add fields
    clA->addField("a", type);
    clA->addField("b", type);
    clB->addField("a", type);
    clB->addField("c", type);

    // inherit classes affter
    clC->inherit(clB);

    // merge fields
    FieldPtr aF = clC->addField("a", type);

    clC->mergeField(aF, clA->findField("a"));
    clC->mergeField(aF, clB->findField("a"));

    CHECK(clC->findField("a"));
    CHECK(clC->findField("b"));
    CHECK(clC->findField("c"));

    CHECK(clC->findField("a")->isOverride(clA->findField("a")));
    CHECK(clC->findField("a")->isOverride(clB->findField("a")));
    CHECK(clC->findField("b")->isOverride(clA->findField("b")));
    CHECK(clC->findField("c")->isOverride(clB->findField("c")));
    CHECK_EQUAL(3, clC->field_size());
}
