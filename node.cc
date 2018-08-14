// Copyright 2018 <Author>

#include "node.h"

Node::Node(char data) : m_next(nullptr), m_prev(nullptr), m_data(data) {
}

char Node::GetData() {
    return m_data;
}

Node* Node::GetPreviousNode() {
    return m_prev;
}

Node* Node::GetNextNode() {
    return m_next;
}

Node* Node::InsertPreviousNode(char data) {
    Node* node = new Node(data);
    node->m_prev = m_prev;
    node->m_next = this;
    if (m_prev)
    {
        m_prev->m_next = node;
    }
    m_prev = node;
    return node;
}

Node* Node::InsertNextNode(char data) {
    Node* node = new Node(data);
    node->m_prev = this;
    node->m_next = m_next;
    if (m_next)
    {
        m_next->m_prev = node;
    }
    m_next = node;
    return node;
}

bool Node::ErasePreviousNode() {
    if (!m_prev)
    {
        return false;
    }
    EraseNode(m_prev);
    return true;
}

bool Node::EraseNextNode() {
    if (!m_next)
    {
        return false;
    }
    EraseNode(m_next);
    return true;
}

void Node::EraseNode(Node* node)
{
    Node* prev = node->m_prev;
    Node* next = node->m_next;
    if (prev)
    {
        prev->m_next = next;
    }
    if (next)
    {
        next->m_prev = prev;
    }
    delete node;
}

