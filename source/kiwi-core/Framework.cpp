#include "kiwi/Framework.hpp"

using namespace kiwi;

Framework::Framework()
{

}

FrameworkRef Framework::create()
{
    FrameworkRef ref = FrameworkRef(new Framework());
    return ref;
}