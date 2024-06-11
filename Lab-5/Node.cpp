#include "Node.h"

HuffmanTree::Node::Node() {
	m_right = nullptr;
	m_left = nullptr;
	m_body.code = BoolVector(256, false);
	m_body.repeat = 0;
}

HuffmanTree::Node::~Node() {}

HuffmanTree::Node::Node(const char* text) {
	m_right = nullptr;
	m_left = nullptr;
	m_body.code = BoolVector();
	m_body.repeat = 0;
}

HuffmanTree::symbol HuffmanTree::Node::get() const {
	return m_body;
}

void HuffmanTree::Node::set(symbol body) {
	m_body = body;
}

void HuffmanTree::Node::setLeft(Node* root) {
	m_left = root;
}
void HuffmanTree::Node::setRight(Node* root) {
	m_right = root;
}

HuffmanTree::Node* HuffmanTree::Node::left() const {
	return m_left;
}
HuffmanTree::Node* HuffmanTree::Node::right() const {
	return m_right;
}