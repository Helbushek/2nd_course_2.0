#pragma once
#include "../Lab-3/SearchTree.h"

class BalancedTree : public SearchTree {
public:
	BalancedTree();
	BalancedTree(const BalancedTree& other);

	int balance(int key=0) const;

	~BalancedTree() = default;

	BalancedTree& operator=(const BalancedTree& other);

	BalancedTree copyLeftChild() const;
	BalancedTree copyRightChild() const;

	bool remove(const int key) override;
	

private:
	Node* _addNode(Node* root, int key) override;
	Node* _addBalanceNode(Node* root, int key, bool& isFixed);
	int balance(Node* root) const;
	void _balance(std::vector<Node*>& pass);

	void _remove(Node*, std::vector<Node*>& pass);

	void shiftRight(Node*);
	void shiftLeft(Node*);

	void shiftLeftRight(Node*);
	void shiftRightLeft(Node*);
};