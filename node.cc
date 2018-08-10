// Copyright 2018 <Author>

#include "node.h"

Node::Node(char data) : m_next(this), m_prev(this), m_data(data) {
}

char Node::GetData() {
	return m_data;
}

Node* Node::GetPreviousNode() {
	if (m_prev->isEnd())
	{
		return nullptr;
	}
	return m_prev;
}

Node* Node::GetNextNode() {
	if (m_next->isEnd())
	{
		return nullptr;
	}
	return m_next;
}

Node* Node::InsertPreviousNode(char data) {
	Node* node = new Node(data);
	Node* prev = m_prev;
	Node* next = this;
	node->m_prev = m_prev;
	node->m_next = this;
	m_prev->m_next = node;
	m_prev = node;
	return node;
}

Node* Node::InsertNextNode(char data) {
	Node* node = new Node(data);
	node->m_prev = this;
	node->m_next = m_next;
	m_next->m_prev = node;
	m_next = node;
	return node;
}

bool Node::ErasePreviousNode() {
	if (isEnd())
	{
		return false;
	}
	return EraseNode(m_prev);
}

bool Node::EraseNextNode() {
	return EraseNode(m_next);
}

bool Node::EraseNode(Node* node)
{
	if (node->isEnd())
	{
		return false;
	}
	Node* prev = node->m_prev;
	Node* next = node->m_next;
	prev->m_next = next;
	next->m_prev = prev;
	delete node;
	return true;
}

bool Node::isEnd() const
{
	return m_data == 0;
}