#pragma once
#include "BinaryTree.h"

class BinaryTree::Node
{
  public:
    Node(int key = 0, Node* left = nullptr, Node* right = nullptr);
    ~Node() = default;

    int key() const;
    void setKey(int key);

    bool hasChilden();

    Node* left() const;
    Node* right() const;
    void setLeft(Node* left);
    void setRight(Node* right);

  private:
    int m_key;
    Node* m_left;
    Node* m_right;
};