#include "kiwi/Framework.hpp"
#include "lang/Driver.hpp"

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
    lang::Driver driver;
    driver.parseFile(filename);
}