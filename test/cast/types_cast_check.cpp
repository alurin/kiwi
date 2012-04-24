#include "test.h" // Brings in the UnitTest++ framework
#include "kiwi/Engine.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/DerivedTypes.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Support/Cast.hpp"
#include <vector>

using namespace kiwi;

template<typename T, typename R>
class cast_checker {
public:
    /// check type
    static void check(T* instType) {
        R* anyType = instType;

        CHECK(classof<T>(instType));                 // check current class
        CHECK(classof<T>(anyType));                  // check root class
        CHECK_EQUAL(instType, dyn_cast<T>(anyType)); // check dyn_cast
    }
};

TEST(types_cast_check) // Declares a test named "types_cast_check"
{
    Context* context = Context::create();

    cast_checker<VoidType, Type>::check(VoidType::get(context));
    cast_checker<BoolType, Type>::check(BoolType::get(context));
    cast_checker<CharType, Type>::check(CharType::get(context));
    cast_checker<IntType, Type>::check(IntType::get32(context));
    cast_checker<StringType, Type>::check(StringType::get(context));

    Module* module = Module::create("script", context);
    cast_checker<ObjectType, Type>::check(ObjectType::create(module));
    delete context;
}

TEST(members_cast_check) // Declares a test named "members_cast_check"
{
    Context* context = Context::create();
    Module*  module  = Module::create("name", context);
    ObjectType* type = ObjectType::create(module);

    std::vector<Type*> args;

    cast_checker<Field, Member>::check(type->add("field", type));
    cast_checker<Method, Member>::check(type->add("method", type, args));
    cast_checker<UnaryOperator, Member>::check(type->add(Member::Not, type, 0));
    cast_checker<BinaryOperator, Member>::check(type->add(Member::Add, type, type, 0));
    delete context;
}
