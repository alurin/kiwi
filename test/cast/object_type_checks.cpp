#include "test.h" // Brings in the UnitTest++ framework
#include "kiwi/Engine.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/DerivedTypes.hpp"
#include "kiwi/Members.hpp"
#include <vector>

using namespace kiwi;

TEST(object_inheritance_check) // Declares a test named "types_cast_check"
{
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
