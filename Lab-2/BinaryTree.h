#pragma once
#include <vector>
#include <QWidget>

#include "treewidget.h"
class BinaryTree
{
public:
    class Node;

public:
    BinaryTree() = default;
    BinaryTree(const BinaryTree &other);

    ~BinaryTree();

    int getKey();

    void clear();
    static void clear(Node* root);

    BinaryTree clone() const;
    static BinaryTree clone(Node *root);
    void operator=(const BinaryTree &other);

    bool isIdeal() const;
    bool isBalanced() const;

    Node *addNode(int key);

    void printHorizontal(int levelSpacing = 4) const;
    void printHorizontal(Node *root, int marginLeft, int levelSpacing) const;

    void print(TreeWidget* parent=nullptr) const;
    void print(Node *root, int leftBorderPos, int rightBorderPos, int yPos = 0, TreeWidget* parent=nullptr) const;

    static void clearLeftChild(Node *root = nullptr);
    static void clearRightChild(Node *root = nullptr);
    static void clearChild(Node *root = nullptr);

    bool isEmpty() const;

    BinaryTree copyRightChild() const;
    BinaryTree copyLeftChild() const;

    int height() const;
    int height(int) const;
    int power() const;

    int max() const;
    int min() const;

    bool remove(const int key);

    BinaryTree find(const int key) const;

    void printList() const;

    operator std::vector<int>();
private:
    BinaryTree(Node* root);
    Node *_addNode(Node *root, int key);
    Node *_clone() const;
    static Node *_clone(Node *root);

    int height(Node*) const;
    int power(Node*) const;

    int max(Node*) const;
    int min(Node*) const;

    bool remove(Node* root);

    Node *_find(const int key, Node *) const;

    void _printList(Node *) const;

    bool _isIdeal(Node *) const;
    bool _isBalanced(Node *) const;

    void vectorize(Node *root, std::vector<int>&) const;

private:
    Node *m_root = nullptr;
};

class BinaryTree::Node
{
public:
    Node(int key = 0, Node* left = nullptr, Node* right = nullptr);
    ~Node() = default;

    int getKey() const;
    void setKey(int key);

    Node* getLeft() const;
    Node* getRight() const;
    void setLeft(Node* left);
    void setRight(Node* right);

    operator BinaryTree();

private:
    int m_key = 0;
    Node* m_left = nullptr;
    Node* m_right = nullptr;

};
