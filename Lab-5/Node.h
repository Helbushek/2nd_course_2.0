#pragma once
#include <string>

#include "HuffmanTree.h"
#include "Boolean Vector/BooleanVector.h"

class HuffmanTree::Node {
public:
	Node();
	~Node();

	Node(const std::string& text);
	Node(const char*);

	BoolVector get() const;
	void set(const BoolVector&);

	void setLeft(Node*);
	void setRight(Node*);

	Node* left() const;
	Node* right() const;

private:
	Node* m_right;
	Node* m_left;
	BoolVector m_code;
};