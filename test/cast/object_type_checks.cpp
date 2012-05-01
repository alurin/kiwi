/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "test.h" // Brings in the UnitTest++ framework
#include "kiwi/Engine.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/DerivedTypes.hpp"
#include "kiwi/Members.hpp"
#include <vector>

using namespace kiwi;

TEST(object_methods_check) {
    Context* context = Context::create();
    Module*  module  = Module::create("script", context);
    ObjectType* type = ObjectType::create(module);
    VoidType* type1  = VoidType::get(context);
    BoolType* type2  = BoolType::get(context);

    std::vector<Type*> args;

    // create method "method" without argument
    {
        Method* created = type->addMethod("method", type1, args); // method();
        Method* method  = type->findMethod("method", args);
        CHECK_EQUAL(method, created);
    }

    // create another method with name "method" with argument
    {
        args.clear();
        args.push_back(type2);
        Method* created = type->addMethod("method", type1, args); // method();
        Method* method  = type->findMethod("method", args);
        CHECK_EQUAL(method, created);
    }
    delete context;
}

TEST(object_inheritance_check) {
    Context* context = Context::create();
    Module*  module  = Module::create("script", context);

    ObjectType* parent = ObjectType::create(module);
    ObjectType* first  = ObjectType::create(module);
    ObjectType* second = ObjectType::create(module);
    ObjectType* third  = ObjectType::create(module);
    ObjectType* any    = ObjectType::create(module);

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

    delete context;
}

TEST(object_field_override_check_after) {
    Context* context = Context::create();
    Module*  module  = Module::create("script", context);
    Type*       type = IntType::get32(context);

    ObjectType* clA  = ObjectType::create(module, "A");  // A { @a, @b }
    ObjectType* clB  = ObjectType::create(module, "B");  // B { @a, @c }
    ObjectType* clC  = ObjectType::create(module, "C");  // C : A,B { @a merge A::@a, B::@a as }


    // inherit classes before
    clC->inherit(clA);

    // add fields
    clA->addField("a", type);
    clA->addField("b", type);
    clB->addField("a", type);
    clB->addField("c", type);

    // inherit classes affter
    clC->inherit(clB);

    // merge fields
    Field* aF = clC->addField("a", type);

    clC->mergeField(aF, clA->findField("a"));
    clC->mergeField(aF, clB->findField("a"));

    CHECK(clC->findField("a"));
    CHECK(clC->findField("b"));
    CHECK(clC->findField("c"));

    CHECK(clC->findField("a")->isOverride(clA->findField("a")));
    CHECK(clC->findField("a")->isOverride(clB->findField("a")));
    CHECK(clC->findField("b")->isOverride(clA->findField("b")));
    CHECK(clC->findField("c")->isOverride(clB->findField("c")));
    // CHECK_EQUAL(3, clC->field_size());
    delete context;
}
