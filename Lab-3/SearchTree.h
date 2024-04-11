#pragma once
#include "../Lab-2/BinaryTree.h"

class SearchTree: public BinaryTree{

public:
	SearchTree() = default;
	SearchTree(const SearchTree&);

	virtual ~SearchTree() {}

	SearchTree clone(Node* root);

	void operator=(const SearchTree&);

	int max() const;
	int min() const;

    virtual Node* add(int key);

    virtual Node* find(const int key) const;

    virtual bool remove(const int key);

    virtual int height(int) const;

    virtual operator std::vector<int>() const;

private: 
	Node* _addNode(Node*, int);

	void _remove(Node*, int);

	Node* _find(Node*, int) const;

	int bringUp(Node*, const bool);

	void vectorize(Node* root, std::vector<int>&) const;
};
