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

    int balance() const;
    int _balance();
    void setBalance(int);

    Node* left() const;
    Node* right() const;
    void setLeft(Node* left);
    void setRight(Node* right);

    int height();
    //int balance();

  private:
    int m_key;
    Node* m_left;
    Node* m_right;
    int m_balance = 0;
};
