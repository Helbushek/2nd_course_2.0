#pragma once
#include <vector>

class Node;

class BinaryTree
{
public:
    class Node;

public:
    BinaryTree() = default;
    BinaryTree(const BinaryTree &other);

    ~BinaryTree();

    int getKey();

    Node* root() const;

    void clear();
    static void clear(Node* root);

    BinaryTree clone() const;
    static BinaryTree clone(Node *root);
    void operator=(const BinaryTree &other);

    bool isIdeal() const;
    bool isBalanced() const;

    Node *add(int key);

    void printHorizontal(int levelSpacing = 4) const;
    void printHorizontal(Node *root, int marginLeft, int levelSpacing) const;

    static void clearLeftChild(Node *root = nullptr);
    static void clearRightChild(Node *root = nullptr);
    static void clearChild(Node *root = nullptr);

    bool isEmpty() const;
    BinaryTree copyRightChild() const;
    BinaryTree copyLeftChild() const;

    int height() const;
    int height(int) const;
    int size() const;

    int max() const;
    int min() const;

    bool remove(const int key);

    BinaryTree find(const int key) const;

    void printList() const;

    operator std::vector<int>() const;
private:
    explicit BinaryTree(Node* root);
    Node *_addNode(Node *root, int key);
    Node *_clone() const;
    static Node *_clone(Node *root);

    int height(Node*) const;
    int size(Node*) const;

    int max(Node*) const;
    int min(Node*) const;

    bool remove(Node *root, int key);
    Node *detect(int key, Node*);

    Node *_find(const int key, Node *) const;

    void _nlrPrint(Node *) const;

    bool _isIdeal(Node *) const;
    bool _isBalanced(Node *) const;

    void vectorize(Node *root, std::vector<int>&) const;

    void bringUp(Node *root);

private:
    Node *m_root = nullptr;
};


