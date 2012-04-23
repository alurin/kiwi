#include "kiwi/Member.hpp"

using namespace kiwi;

// cosntructor
Member::Member(Type* type)
: m_memberID((MemberID) 0), m_ownerType(type) {
}

// destructor
Member::~Member() {
}
