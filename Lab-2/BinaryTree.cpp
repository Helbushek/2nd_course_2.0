#include <assert.h>
#include <stdlib.h>
#include <iostream>

#include "BinaryTree.h"

BinaryTree::BinaryTree(const BinaryTree &other)
{
    m_root = other._clone();
}

BinaryTree::BinaryTree(Node* root) {
    if(isEmpty()) {
    m_root = root;
    } else {
    clear();
    m_root = root;
    }
}

BinaryTree::~BinaryTree()
{
    clear();
}

void BinaryTree::clear()
{
   clear(m_root);
   m_root = nullptr;
}

void BinaryTree::clear(Node* root)
{
   if(root==nullptr) {
       return;
   }

   clear(root->getLeft());
   clear(root->getRight());
   delete root;
}

BinaryTree BinaryTree::clone() const
{
    return clone(m_root);
}

BinaryTree BinaryTree::clone(Node *root)
{
   BinaryTree tree;
   tree.m_root = _clone(root);
   return tree;
}

void BinaryTree::operator=(const BinaryTree &other) {
   if (!isEmpty()) {
       clear();
   }
   m_root = other.clone().m_root;
}

bool BinaryTree::isIdeal() const
{
    return false;
}

bool BinaryTree::isBalanced() const
{
    return false;
}

BinaryTree::Node *BinaryTree::_clone() const
{
    return _clone(m_root);
}

BinaryTree::Node *BinaryTree::_clone(Node *root)
{
    Node *cloneRoot = nullptr;
    if (root == nullptr) {
       return cloneRoot;
    }

    cloneRoot = new Node(root->getKey());
    cloneRoot->setLeft(_clone(root->getLeft()));
    cloneRoot->setRight(_clone(root->getRight()));

    return cloneRoot;
}

BinaryTree::Node *BinaryTree::addNode(int key)
{
    if (m_root) {
        return _addNode(m_root, key);
    } else {
        return m_root = new Node(key);
    }
}

BinaryTree::Node *BinaryTree::_addNode(Node *root, int key)
{
    if (!root) {
        root = new Node(key);
    } else if (rand()%2) {
        root->setRight(_addNode(root->getRight(), key));
    } else {
        root->setLeft(_addNode(root->getLeft(), key));
    }

    return root;
}

void BinaryTree::printHorizontal(int levelSpacing) const
{
    printHorizontal(m_root, 0, levelSpacing);
}

void BinaryTree::printHorizontal(Node *root, int marginLeft, int levelSpacing) const
{
    if (root == nullptr) {
        return;
    }

    printHorizontal(root->getRight(), marginLeft + levelSpacing, levelSpacing);
    std::cout << std::string(marginLeft, ' ') << root->getKey() << std::endl;
    printHorizontal(root->getLeft(), marginLeft + levelSpacing, levelSpacing);
}

void BinaryTree::clearLeftChild(Node *root){
    if (root == nullptr || root->getLeft()==nullptr) {
        return;
    }
    else {
        clear(root->getLeft());
        root->setLeft(nullptr);
    }
}
void BinaryTree::clearRightChild(Node *root){
    if (root == nullptr || root->getRight()==nullptr) {
        return;
    }
    else {
        clear(root->getRight());
        root->setRight(nullptr);
    }
}
void BinaryTree::clearChild(Node *root){
    clearLeftChild(root);
    clearRightChild(root);
}

bool BinaryTree::isEmpty() const {
    if(m_root == nullptr) {
        return true;
    }
    else return false;
}

BinaryTree BinaryTree::copyRightChild() const{
    return m_root->getRight();
}
BinaryTree BinaryTree::copyLeftChild() const{
    return m_root->getLeft();
}

int BinaryTree::height() const {
    return height(m_root);
}

int BinaryTree::height(Node* root) const {
    if (root->getRight() == nullptr && root->getLeft() == nullptr) {
        return 1;
    }
    if (root->getRight()==nullptr) {
        return height(root->getLeft())+1;
    }
    if (root->getLeft()==nullptr) {
        return height(root->getRight())+1;
    }
    return std::max(height(root->getRight()), height(root->getLeft()))+1;
}

int BinaryTree::power() const {
    return power(m_root);
}
int BinaryTree::power(Node* root) const {
    if (root->getRight() == nullptr && root->getLeft() == nullptr) {
        return 1;
    }
    if (root->getRight()==nullptr) {
        return power(root->getLeft())+1;
    }
    if (root->getLeft()==nullptr) {
        return power(root->getRight())+1;
    }
    return power(root->getRight())+power(root->getLeft())+1;
}

int BinaryTree::max() const {
    return max(m_root);
}
int BinaryTree::max(Node* root) const {
    if (root->getRight() == nullptr && root->getLeft() == nullptr) {
        return root->getKey();
    }
    if (root->getRight()==nullptr) {
        return std::max(max(root->getLeft()), root->getKey());
    }
    if (root->getLeft()==nullptr) {
        return std::max(max(root->getRight()), root->getKey());
    }
    return std::max(std::max(max(root->getRight()), max(root->getLeft())), root->getKey());
}

int BinaryTree::min() const {
    return min(m_root);
}
int BinaryTree::min(Node* root) const {
    if (root->getRight() == nullptr && root->getLeft() == nullptr) {
        return root->getKey();
    }
    if (root->getRight()==nullptr) {
        return std::min(min(root->getLeft()), root->getKey());
    }
    if (root->getLeft()==nullptr) {
        return std::min(min(root->getRight()), root->getKey());
    }
    return std::min(std::min(min(root->getRight()), min(root->getLeft())), root->getKey());
}

BinaryTree BinaryTree::find(const int key) const {
    return _find(key, m_root);
}
BinaryTree::Node* BinaryTree::_find(const int key, Node* root) const {
    if (root==nullptr) {
        return nullptr;
    }
    if (root->getKey()==key) {
        return root;
    }
    else {
        Node* searchRight = _find(key, root->getRight());
        Node* searchLeft = _find(key, root->getLeft());
        if (searchRight!=nullptr) {
            return searchRight;
        }
        else if (searchLeft!=nullptr) {
            return searchLeft;
        }
        else
            return nullptr;
    }
}

bool BinaryTree::remove(const int key) {
    if (find(key).m_root!=nullptr) {
        remove(find(key).m_root);
        return true;
    }
    else
        return false;
}

void BinaryTree::remove(Node* root) {
    if (root->getRight() == nullptr && root->getLeft() == nullptr) {
        delete root;
        return;
    }
    else if (root->getRight()!=nullptr) {
        root->setKey(root->getRight()->getKey());
        remove(root->getRight());
        return;
    }
    else if (root->getLeft()!=nullptr) {
        root->setKey(root->getLeft()->getKey());
        remove(root->getLeft());
        return;
    }
}

BinaryTree::Node::Node(int key, Node* left, Node* right)
    : m_key(key)
    , m_left(left)
    , m_right(right)
{}

int BinaryTree::Node::getKey() const
{
    return m_key;
}

void BinaryTree::Node::setKey(int key)
{
    m_key = key;
}

BinaryTree::Node* BinaryTree::Node::getLeft() const
{
    return m_left;
}

BinaryTree::Node* BinaryTree::Node::getRight() const
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

BinaryTree::Node::operator BinaryTree() {
    return BinaryTree(*this);
}
