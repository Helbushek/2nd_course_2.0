#include "Node.h"

// NODE ZONE BELOW \|\|\|

BinaryTree::Node::Node(int key, Node* left, Node* right)
    : m_key(key)
      , m_left(left)
      , m_right(right)
{}

int BinaryTree::Node::key() const
{
    return m_key;
}

void BinaryTree::Node::setKey(int key)
{
    m_key = key;
}

BinaryTree::Node* BinaryTree::Node::left() const
{
    return m_left;
}

BinaryTree::Node* BinaryTree::Node::right() const
{
    return m_right;
}

void BinaryTree::Node::setLeft(Node* left)
{
    m_left = left;
}

void BinaryTree::Node::setRight(Node* right)
{
    m_right = right;
}

bool BinaryTree::Node::hasChilden()
{
    if (this == nullptr)
    {
        return false;
    }
    else {
        return ((m_right != nullptr) || (m_left != nullptr));
    }
}
