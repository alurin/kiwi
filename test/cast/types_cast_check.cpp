#include "test.h" // Brings in the UnitTest++ framework
#include "kiwi/Context.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/DerivedTypes.hpp"
#include "kiwi/Support/Cast.hpp"

using namespace kiwi;

template<typename T>
class type_checker {
public:
    typedef boost::shared_ptr<T> ConcreteRef;

    /// check type
    static void check(const ConcreteRef& instType) {
        TypeRef anyType = instType;

        CHECK(classof<T>(instType));
        CHECK(classof<T>(anyType));
        CHECK_EQUAL(instType, dyn_cast<T>(anyType));
    }
};

TEST(types_cast_check) // Declares a test named "sanity_check"
{
    ContextRef context = Context::create();

    type_checker<VoidType>::check(VoidType::get(context));
    type_checker<BoolType>::check(BoolType::get(context));
    type_checker<CharType>::check(CharType::get(context));
    type_checker<IntType>::check(IntType::get32(context));
    type_checker<StringType>::check(StringType::get(context));

    ModuleRef  module  = Module::create("script", context);
    type_checker<ObjectType>::check(ObjectType::create(module));
}
