#pragma once
#include <vector>

class BinaryTree
{
public:
    class Node;

public:
    BinaryTree() = default;
    BinaryTree(const BinaryTree &other);

    virtual ~BinaryTree();

    int getKey();

    Node* root() const;

    void clear();
    static void clear(Node* root);

    BinaryTree clone() const;
    static BinaryTree clone(Node *root);
    BinaryTree& operator=(const BinaryTree &other);

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
    virtual int height(int) const;
    int size() const;

    int max() const;
    int min() const;

    virtual bool remove(const int key);

    virtual Node* find(const int key) const;

    void printList() const;

    virtual operator std::vector<int>() const;

protected:
    explicit BinaryTree(Node* root);
    virtual Node *_addNode(Node *root, int key);
    Node *_clone() const;
    static Node *_clone(Node *root);

    static int height(Node*);
    int size(Node*) const;

    int max(Node*) const;
    int min(Node*) const;

    bool _remove(Node *root, int key);
    Node *detect(int key, Node*);

    Node *_findParent(const int key, Node *) const;

    void _nlrPrint(Node *) const;

    bool _isIdeal(Node *) const;
    bool _isBalanced(Node *) const;

    virtual void vectorize(Node *root, std::vector<int>&) const;

    void bringUp(Node *root);

protected:
    Node *m_root = nullptr;
};


