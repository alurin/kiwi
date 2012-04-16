#include "kiwi/Framework.hpp"
#include "lang/Driver.hpp"
#include "lang/Expression.hpp"

using namespace kiwi;

Framework::Framework()
{

}

FrameworkRef Framework::create()
{
    FrameworkRef ref = FrameworkRef(new Framework());
    return ref;
}

void Framework::includeFile(const Path& filename)
{
    CalcContext context;
    example::Driver driver(context);
    driver.parseFile(filename);
}