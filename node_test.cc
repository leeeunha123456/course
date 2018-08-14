// Copyright 2018 Minkyu Jo

#include "node.h"
#include "node_test.h"
#include "test.h"

#include <memory>

struct NodeDeleter
{
    void operator () (Node* node) {
        if (!node) {
            return;
        }

        Node* n;
        while (n = node->GetPreviousNode()) {
            node->ErasePreviousNode();
        }

        while (n = node->GetNextNode()) {
            node->EraseNextNode();
        }

        delete node;
    }
};

using NodePtr = std::unique_ptr<Node, NodeDeleter>;

class NodeConstructorTestSuite
{
private:
  static void SingleNodeTest() {
    Node *node = new Node('A');
    ASSERT_TRUE(node->GetData() == 'A');
    ASSERT_TRUE(node->GetPreviousNode() == nullptr);
    ASSERT_TRUE(node->GetNextNode() == nullptr);
    delete node;
  }

  static void InsertNextNodeTest() {
      NodePtr node(new Node('A'));

      Node* nextNext = node->InsertNextNode('B');
      ASSERT_TRUE(node->GetPreviousNode() == nullptr);
      ASSERT_TRUE(node->GetNextNode() == nextNext);
      ASSERT_TRUE(nextNext->GetPreviousNode() == node.get());
      ASSERT_TRUE(nextNext->GetNextNode() == nullptr);

      Node* next = node->InsertNextNode('C');
      ASSERT_TRUE(node->GetNextNode() == next);
      ASSERT_TRUE(next->GetPreviousNode() == node.get());
      ASSERT_TRUE(next->GetNextNode() == nextNext);
      ASSERT_TRUE(nextNext->GetPreviousNode() == next);
      ASSERT_TRUE(nextNext->GetNextNode() == nullptr);
  }

  static void InsertPreviousNodeTest() {
      NodePtr node(new Node('A'));

      Node* prevPrev = node->InsertPreviousNode('B');
      ASSERT_TRUE(node->GetPreviousNode() == prevPrev);
      ASSERT_TRUE(node->GetNextNode() == nullptr);
      ASSERT_TRUE(prevPrev->GetPreviousNode() == nullptr);
      ASSERT_TRUE(prevPrev->GetNextNode() == node.get());

      Node* prev = node->InsertPreviousNode('C');
      ASSERT_TRUE(node->GetNextNode() == nullptr);
      ASSERT_TRUE(node->GetPreviousNode() == prev);
      ASSERT_TRUE(prev->GetPreviousNode() == prevPrev);
      ASSERT_TRUE(prev->GetNextNode() == node.get());
      ASSERT_TRUE(prevPrev->GetPreviousNode() == nullptr);
      ASSERT_TRUE(prevPrev->GetNextNode() == prev);
  }

  static void ErasePreviousNodeTest() {
      NodePtr node(new Node('A'));
      ASSERT_FALSE(node->ErasePreviousNode());

      Node* prev = node->InsertPreviousNode('B');
      ASSERT_TRUE(node->ErasePreviousNode());
      ASSERT_TRUE(node->GetPreviousNode() == nullptr);

      Node* prevPrev = node->InsertPreviousNode('B');
      prev = node->InsertPreviousNode('C');
      ASSERT_TRUE(node->ErasePreviousNode());
      ASSERT_TRUE(node->GetPreviousNode() == prevPrev);
      ASSERT_TRUE(prevPrev->GetNextNode() == node.get());
  }

  static void EraseNextNodeTest() {
      NodePtr node(new Node('A'));
      ASSERT_FALSE(node->EraseNextNode());

      Node* next = node->InsertNextNode('B');
      ASSERT_TRUE(node->EraseNextNode());
      ASSERT_TRUE(node->GetNextNode() == nullptr);

      Node* nextNext = node->InsertNextNode('B');
      next = node->InsertNextNode('C');
      ASSERT_TRUE(node->EraseNextNode());
      ASSERT_TRUE(node->GetNextNode() == nextNext);
      ASSERT_TRUE(nextNext->GetPreviousNode() == node.get());
  }

public:
  static void RunTest() {
    SingleNodeTest();
    InsertPreviousNodeTest();
    InsertNextNodeTest();
    ErasePreviousNodeTest();
    EraseNextNodeTest();
    // add more..
  }
};

class SomeOtherTestSuite
{
private:

public:
  static void RunTest() {
    // add more..
  }
};

void NodeTest() {
  NodeConstructorTestSuite::RunTest();
  // add more..
}
