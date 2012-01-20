/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#include "kiwi/Script/Node.hpp"

using namespace kiwi;
using namespace kiwi::script;

// Location constructor
Location::Location(const String& streamName) : m_streamName(streamName) {

}

// Node constructor
Node::Node(const Location& location) : m_location(location) {

}

// Node virtual destructor
Node::~Node() { }
