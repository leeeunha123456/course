// Copyright 2018 <Author>

#include "typing_machine.h"
#include <sstream>
#include <cassert>

static const int MAX_STRING_LENGTH = 100;
static const char NULL_CHAR = 0;
static const char CHAR_RANGE_START = 0x20;
static const char CHAR_RANGE_END = 0x7E;

TypingMachine::TypingMachine()
    : m_start(new Node(NULL_CHAR)),
      m_cursor(m_start), m_size(0) {
    m_end = m_start->InsertNextNode(NULL_CHAR);
}

TypingMachine::~TypingMachine() {
    while (m_start->EraseNextNode()) {
        // do nothing
    }
    delete m_start;
}

void TypingMachine::HomeKey() {
    m_cursor = m_start;
}

void TypingMachine::EndKey() {
    m_cursor = m_end->GetPreviousNode();
}

void TypingMachine::LeftKey() {
    if (m_cursor == m_start)
    {
        return;
    }
    m_cursor = m_cursor->GetPreviousNode();
}

void TypingMachine::RightKey() {
    Node* nextNode = m_cursor->GetNextNode();
    if (nextNode == m_end)
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
    if (m_cursor == m_start)
    {
        return false;
    }
    Node* next = m_cursor->GetNextNode();
    assert(next);
    bool result = next->ErasePreviousNode();
    assert(result);
    m_cursor = next->GetPreviousNode();
    m_size--;
    return true;
}

std::string TypingMachine::Print(char separator) {
    std::stringstream s;

    if (m_start == m_cursor && separator != 0) {
        s << separator;
    }

    Node* node;
    for (node=m_start->GetNextNode(); node!=m_end; node = node->GetNextNode()) {
        s << node->GetData();
        if (node == m_cursor && separator != 0) {
            s << separator;
        }
    }
    return s.str();
}
