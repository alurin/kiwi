/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#include "kiwi/Script/Node.hpp"

using namespace kiwi;
using namespace kiwi::script;

// constructor
Node::Node(const Location& location) : m_location(location) {

}

// virtual destructor
Node::~Node() { }