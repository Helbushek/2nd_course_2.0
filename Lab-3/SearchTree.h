#pragma once
#include "../Lab-2/BinaryTree.h"

class SearchTree: public BinaryTree{

public:
	SearchTree() = default;
	SearchTree(const SearchTree&);

	~SearchTree() {}

	SearchTree clone(Node* root);

	SearchTree& operator=(const SearchTree&);

	int max() const;
	int min() const;

    Node* find(const int key) const;

    bool remove(const int key);

    int height(int) const;

private:
	Node* _addNode(Node* root, int key) override;

	Node* _findParent(Node*, int) const;

	int bringUp(Node*, const bool);

	void vectorize(Node* root, std::vector<int>&) const override;
};
