#include "test.h" // Brings in the UnitTest++ framework
#include "kiwi/Context.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/DerivedTypes.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Support/Cast.hpp"
#include <vector>

using namespace kiwi;

template<typename T>
class member_checker {
public:
    typedef boost::shared_ptr<T> ConcreteRef;

    /// check type
    static void check(const ConcreteRef& instType) {
        MemberRef anyType = instType;

        CHECK(classof<T>(instType));
        CHECK(classof<T>(anyType));
        CHECK_EQUAL(instType, dyn_cast<T>(anyType));
    }
};

TEST(members_cast_check) // Declares a test named "sanity_check"
{
    ContextRef context = Context::create();
    ModuleRef  module  = Module::create("name", context);
    ObjectTy   type    = ObjectType::create(module);

    std::vector<ArgumentRef> args;

    member_checker<Field>::check(type->add("field", type));
    member_checker<Method>::check(type->add("method", type, args));
    member_checker<UnaryOperator>::check(type->add(Member::NOT, type, 0));
    member_checker<BinaryOperator>::check(type->add(Member::ADD, type, type, 0));
}
