#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#include "BinaryTree.h"
#include "Node.h"

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

int BinaryTree::getKey()
{
    return m_root->key();
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

   clear(root->left());
   clear(root->right());
   delete root;
}

BinaryTree::Node* BinaryTree::root() const
{
   return m_root;
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

BinaryTree& BinaryTree::operator=(const BinaryTree &other) {
   if (other.m_root == this->m_root)
   {
       return *this;
   }
   if (!isEmpty()) {
       clear();
   }
   m_root = _clone(other.m_root);
   return *this;
}

bool BinaryTree::isIdeal() const
{
   return _isIdeal(m_root);
}

bool BinaryTree::isBalanced() const
{
   return _isBalanced(m_root);
}

bool BinaryTree::_isIdeal(Node *root) const
{
   if (root == nullptr || (!root->right() && !root->left()))
       return true;
   if (abs(size(root->left()) - size(root->right())) <= 1 && (_isIdeal(root->left()) && _isIdeal(root->right())))
   {
       return true;
   }
   return false;
}

bool BinaryTree::_isBalanced(Node *root) const
{
   if (root == nullptr || (!root->right() && !root->left()))
       return true;
   if (abs(height(root->left()) - height(root->right())) <= 1 && (_isBalanced(root->left()) && _isBalanced(root->right())))
   {
       return true;
   }
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

    cloneRoot = new BinaryTree::Node(root->key());
    cloneRoot->setLeft(_clone(root->left()));
    cloneRoot->setRight(_clone(root->right()));

    return cloneRoot;
}

BinaryTree::Node *BinaryTree::add(int key)
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
        root->setRight(_addNode(root->right(), key));
    } else {
        root->setLeft(_addNode(root->left(), key));
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

    printHorizontal(root->right(), marginLeft + levelSpacing, levelSpacing);
    std::cout << std::string(marginLeft, ' ') << root->key() << std::endl;
    printHorizontal(root->left(), marginLeft + levelSpacing, levelSpacing);
}

void BinaryTree::clearLeftChild(Node *root){
    if (root == nullptr || root->left()==nullptr) {
        return;
    }
    else {
        clear(root->left());
        root->setLeft(nullptr);
    }
}
void BinaryTree::clearRightChild(Node *root){
    if (root == nullptr || root->right()==nullptr) {
        return;
    }
    else {
        clear(root->right());
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

BinaryTree BinaryTree::copyRightChild() const
{
    BinaryTree temp = clone(m_root->right());
    return temp;
}
BinaryTree BinaryTree::copyLeftChild() const{

    BinaryTree temp = clone(m_root->left());
    return temp;
}

int BinaryTree::height() const {
    return height(m_root);
}

int BinaryTree::height(int key) const
{
    BinaryTree temp(find(key));
    if (temp.isEmpty())
        return -1;
    return height(temp.m_root);
}

int BinaryTree::height(Node* root) {
    if (root == nullptr)
    {
        return 0;
    }
    return std::max(height(root->right()), height(root->left()))+1;
}

int BinaryTree::size() const {
    return size(m_root);
}
int BinaryTree::size(Node* root) const {
    if (root == nullptr)
    {
        return 0;
    }
    return size(root->right())+size(root->left())+1;
}

int BinaryTree::max() const {
    return max(m_root);
}
int BinaryTree::max(Node* root) const {
    if (root == nullptr)
    {
        return 0;
    }
    if (root->right() == nullptr && root->left() == nullptr) {
        return root->key();
    }
    if (root->right()==nullptr) {
        return std::max(max(root->left()), root->key());
    }
    if (root->left()==nullptr) {
        return std::max(max(root->right()), root->key());
    }
    return std::max(std::max(max(root->right()), max(root->left())), root->key());
}

int BinaryTree::min() const {
    return min(m_root);
}
int BinaryTree::min(Node* root) const {
    if (root == nullptr)
    {
        return 0;
    }
    if (root->right() == nullptr && root->left() == nullptr) {
        return root->key();
    }
    if (root->right()==nullptr) {
        return std::min(min(root->left()), root->key());
    }
    if (root->left()==nullptr) {
        return std::min(min(root->right()), root->key());
    }
    return std::min(std::min(min(root->right()), min(root->left())), root->key());
}

BinaryTree::Node* BinaryTree::find(const int key) const
{
    return _findParent(key, m_root);
}
BinaryTree::Node* BinaryTree::_findParent(const int key, Node* root) const {
    if (root==nullptr) {
        return nullptr;
    }
    if (root->key()==key) {
        return root;
    }
    else
    {
        Node *node = _findParent(key, root->right());
        if (node == nullptr)
        {
            node = _findParent(key, root->left());
        }
        return node;
    }
}
void BinaryTree::bringUp(Node *root)
{
    Node *current = root;
    while (current->hasChilden())
    {

        Node *next = current->right();
        if (next == nullptr)
        {
            next = current->left();
        }

        // bring next key to current
        current->setKey(next->key());

        // check if next has children
        if (next->hasChilden()) // if yes make current = next and repeat
        {
            current = next;
            continue;
        }
        else
        { // if no delete it and make nullptr
            if (current->right() == next)
            {
                current->setRight(nullptr);
            }
            else
            {
                current->setLeft(nullptr);
            }
            delete next;
            current = nullptr;
            continue;
        }
    }
}

bool BinaryTree::remove(const int key)
{
    if (m_root == nullptr)
    {
        return false;
    }
    if (!m_root->hasChilden() && m_root->key() == key)
    {
        delete m_root;
        m_root = nullptr;
        return true;
    }
    else if (m_root->key() == key)
    {
        bringUp(m_root);
        return true;
    }
    Node *sub_founded = detect(key, m_root);
    if (sub_founded != nullptr)
    {
        _remove(sub_founded, key);
        return true;
    }
    else return false;
}

BinaryTree::Node* BinaryTree::detect(int key, Node* root) {
    if (root==nullptr) {
        return nullptr;
    }
    if (
        (root->right()!=nullptr && root->right()->key()==key) ||
        (root->left()!=nullptr && root->left()->key()==key) )
    {
        return root;
    }
    else {
        Node *node = detect(key, root->right());
        if (node == nullptr)
        {
            node = detect(key, root->left());
        }
        return node;
    }
}

bool BinaryTree::_remove(Node* root, int key) {
    if (root == nullptr)
    {
        return true;
    }
    if (!root->hasChilden()) {
        return false;
    }
    else
    {
        if (root->right()!=nullptr && !root->right()->hasChilden() && root->right()->key()==key)
        {
            delete root->right();
            root->setRight(nullptr);
            return false;
        }
        else if (root->right() != nullptr && root->right()->hasChilden() && root->right()->key() == key)
        {
            bringUp(root->right());
        }
        else if ((root->left() != nullptr && !root->left()->hasChilden()) && root->left()->key()==key)
        {
            delete root->left();
            root->setLeft(nullptr);
            return false;
        }
        else if (root->left() != nullptr && root->left()->hasChilden() && root->left()->key() == key)
        {
            bringUp(root->left());
        }
        else
            return false;
    }
}

void BinaryTree::printList() const
{
    _nlrPrint(m_root);
}

void BinaryTree::_nlrPrint(Node *root) const
{
    if (root->right() == nullptr && root->left() == nullptr)
    {
        std::cout << root->key() << ' ';
    }
    else
    {
        if (root->left())
            _nlrPrint(root->left());
        if (root->right())
        {
            _nlrPrint(root->right());
        }
    }
}

void BinaryTree::vectorize(Node *root, std::vector<int> &result) const
{
    if (root != nullptr) {
        vectorize(root->left(), result);
        result.push_back(root->key());
        vectorize(root->right(), result);
    }
}

BinaryTree::operator std::vector<int>() const
{
    std::vector<int> result;
    vectorize(m_root, result);
    return result;
}

