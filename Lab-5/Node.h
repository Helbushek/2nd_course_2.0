#pragma once
#include <string>

#include "HuffmanTree.h"
#include "Boolean Vector/BooleanVector.h"

class HuffmanTree::Node {
public:
	Node();
	~Node();

	Node(const char*);

	symbol get() const;
	void set(symbol);

	void setLeft(Node*);
	void setRight(Node*);

	Node* left() const;
	Node* right() const;

private:
	Node* m_right;
	Node* m_left;
	HuffmanTree::symbol m_body;
};