#pragma once

class BinaryTree
{
public:
    class Node;

public:
    BinaryTree() = default;
    BinaryTree(const BinaryTree &other);

    ~BinaryTree();

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

    static void clearLeftChild(Node *root = nullptr);
    static void clearRightChild(Node *root = nullptr);
    static void clearChild(Node *root = nullptr);

    bool isEmpty() const;

    BinaryTree copyRightChild() const;
    BinaryTree copyLeftChild() const;

    int height() const;
    int power() const;

    int max() const;
    int min() const;

    bool remove(const int key);

    BinaryTree find(const int key) const;
private:
    BinaryTree(Node* root);
    Node *_addNode(Node *root, int key);
    Node *_clone() const;
    static Node *_clone(Node *root);

    int height(Node*) const;
    int power(Node*) const;

    int max(Node*) const;
    int min(Node*) const;

    void remove(Node* root);

    Node* _find(const int key, Node*) const;
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
