#include "Node.h"

HuffmanTree::Node::Node() {
	m_right = nullptr;
	m_left = nullptr;
	m_code = BoolVector();
}

HuffmanTree::Node::~Node() {
	delete m_right;
	delete m_left;
}

HuffmanTree::Node::Node(const std::string& text) {
	m_right = nullptr;
	m_left = nullptr;
	m_code = BoolVector(text.c_str());
}

HuffmanTree::Node::Node(const char* text) {
	m_right = nullptr;
	m_left = nullptr;
	m_code = BoolVector(text);
}

BoolVector HuffmanTree::Node::get() const {
	return m_code;
}

void HuffmanTree::Node::set(const BoolVector& code) {
	m_code = code;
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