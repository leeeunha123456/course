// Copyright 2018 <Author>

#include "typing_machine.h"
#include <sstream>
#include <cassert>

static const int MAX_STRING_LENGTH = 100;
static const char NULL_CHAR = 0;
static const char CHAR_RANGE_START = 0x20;
static const char CHAR_RANGE_END = 0x7E;

TypingMachine::TypingMachine() : m_node(NULL_CHAR), m_cursor(&m_node), m_size(0) {
}

void TypingMachine::HomeKey() {
	m_cursor = &m_node;
}

void TypingMachine::EndKey() {
	while (true)
	{
		Node* nextNode = m_cursor->GetNextNode();
		if (!nextNode)
		{
			break;
		}
		m_cursor = nextNode;
	}
}

void TypingMachine::LeftKey() {
	if (m_cursor == &m_node)
	{
		return;
	}
	Node* prevNode = m_cursor->GetPreviousNode();
	if (!prevNode)
	{
		m_cursor = &m_node;
		return;
	}
	m_cursor = prevNode;
}

void TypingMachine::RightKey() {
	Node* nextNode = m_cursor->GetNextNode();
	if (!nextNode)
	{
		return;
	}
	m_cursor = nextNode;
}

bool TypingMachine::TypeKey(char key) {
	if (m_size >= MAX_STRING_LENGTH)
	{
		return false;
	}
	if (key < CHAR_RANGE_START || key > CHAR_RANGE_END)
	{
		return false;
	}
	m_cursor = m_cursor->InsertNextNode(key);
	m_size++;
	return true;
}

bool TypingMachine::EraseKey() {
	if (m_size == 0)
	{
		return false;
	}
	if (m_cursor == &m_node)
	{
		return false;
	}
	m_size--;
	Node* prevNode = m_cursor->GetPreviousNode();
	if (!prevNode)
	{
		prevNode = &m_node;
	}
	assert(prevNode);
	bool result = prevNode->EraseNextNode();
	assert(result);
	m_cursor = prevNode;
	return true;
}

std::string TypingMachine::Print(char separator) {
	std::stringstream s;

	if (&m_node == m_cursor)
	{
		s << separator;
	}

	Node* it = &m_node;
	while (it = it->GetNextNode())
	{
		s << it->GetData();
		if (it == m_cursor)
		{
			s << separator;
		}
	}
	return s.str();
}
