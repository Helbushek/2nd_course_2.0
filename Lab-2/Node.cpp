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

int BinaryTree::Node::height() {
    return BinaryTree::height(this);
}

int BinaryTree::Node::balance() const {
    if (this) {
        return m_balance;
    }
    else {
        return 0;
    }
}
void BinaryTree::Node::setBalance(int key) {
    if (this) {
        m_balance = key;
    }
}

int BinaryTree::Node::_balance() {
	if (this == nullptr) {
		return 0;
	}
	if (right() == nullptr) {
		if (left() != nullptr) {
			return -left()->height();
		}
		else
			return 0;
	}
	else {
		if (left() == nullptr) {
			return right()->height();
		}
		else {
			return (right()->height() - left()->height());
		}
	}
}
