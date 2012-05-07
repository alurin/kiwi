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
#include "kiwi/Support/Cast.hpp"
#include <vector>

using namespace kiwi;

template<typename T, typename R>
class cast_checker {
public:
    typedef boost::shared_ptr<T> TargetPtr;
    typedef boost::shared_ptr<R> RootPtr;

    /// check type
    static void check(TargetPtr instType) {
        RootPtr anyType = instType;

        CHECK(classof<T>(instType));                 // check current class
        CHECK(classof<T>(anyType));                  // check root class
        CHECK_EQUAL(instType, dyn_cast<T>(anyType)); // check dyn_cast
    }
};

TEST(types_cast_check) // Declares a test named "types_cast_check"
{
    ContextPtr context = Context::create();

    cast_checker<VoidType, Type>::check(VoidType::get(context));
    cast_checker<BooleanType, Type>::check(BooleanType::get(context));
    cast_checker<CharType, Type>::check(CharType::get(context));
    cast_checker<IntegerType, Type>::check(IntegerType::get32(context));
    cast_checker<StringType, Type>::check(StringType::get(context));

    ModulePtr module = Module::create("script", context);
    cast_checker<ObjectType, Type>::check(ObjectType::create(module));
}

TEST(members_cast_check) // Declares a test named "members_cast_check"
{
    ContextPtr context = Context::create();
    ModulePtr  module  = Module::create("name", context);
    ObjectPtr  type    = ObjectType::create(module);

    std::vector<TypePtr> args;

    cast_checker<Field, Member>::check(type->addField("field", type));
    cast_checker<Method, Member>::check(type->addMethod("method", type, args));
    cast_checker<Method, Member>::check(type->addUnary(Member::Not, type));
    cast_checker<Method, Member>::check(type->addBinary(Member::Add, type, type));
    cast_checker<Method, Member>::check(type->addMultiary(Member::Constructor, type, args));
}
