#include "SearchTree.h"
#include "../Lab-2/Node.h"

SearchTree::SearchTree(const SearchTree& other)
    : BinaryTree(other)
{}

void SearchTree::operator = (const SearchTree& other)
{
	BinaryTree::operator=(other);
}

SearchTree SearchTree::clone(BinaryTree::Node* root) {
	SearchTree temp;
	temp.m_root = BinaryTree::_clone(root);
	return temp;
}

int SearchTree::max() const {
	Node* current = m_root;
	while (current->right()!=nullptr) {
		current = current->right();
	}
	return current->key();
}
int SearchTree::min() const {
	Node* current = m_root;
	while (current->left() != nullptr) {
		current = current->left();
	}
	return current->key();
}

BinaryTree::Node* SearchTree::add(int key) {
	if (m_root) {
		return _addNode(m_root, key);
	}
	else {
		return m_root = new Node(key);
	}
}

BinaryTree::Node* SearchTree::_addNode(Node* root, int key) {

	if (!root) {
		root = new Node(key);
	}
	else if (key>root->key()) {
		root->setRight(_addNode(root->right(), key));
	}
	else if (key<root->key()) {
		root->setLeft(_addNode(root->left(), key));
	}
	else {
		return nullptr;
	}

	return root;
}

BinaryTree::Node* SearchTree::find(const int key) const {
	Node* current = m_root;
	while (current != nullptr) {
		if (key == current->key()) {
			return current;
		}
		else if (key > current->key()) {
			current = current->right();
			continue;
		}
		else if (key < current->key()) {
			current = current->left();
			continue;
		}
	}
	return current;
}

BinaryTree::Node* SearchTree::_find(Node* root ,const int key) const {
	if (root == nullptr)
		return nullptr;

	if  (
		(root->right() != nullptr && root->right()->key() == key) ||
		(root->left() != nullptr && root->left()->key() == key)
		)
	{
		return root;
	}
	else {
		if (key > root->key() && root->right() != nullptr) {
			root = _find(root->right(), key);
		}
		else if (key < root->key() && root->left() != nullptr) {
			root = _find(root->left(), key);
		}
		return root;
	}
}

bool SearchTree::remove(const int key) {
	Node* remove = find(key);
	if (remove == nullptr) {
		return false;
	}
	if (remove->hasChilden()) {
		_remove(remove, key);
		
	}
	else if (!remove->hasChilden()) {
		Node* preRemove = _find(m_root, key);
		if (preRemove->right() == remove) {
			preRemove->setRight(nullptr);
		}
		else if (preRemove->left() == remove) {
			preRemove->setLeft(nullptr);
		}
	}
	return true;
}

void SearchTree::_remove(Node* root, int key) {
	if (root->left() != nullptr) {
		root->setKey(bringUp(root->left(), false));
	}
	else if (root->right() != nullptr) {
		root->setKey(bringUp(root->right(), true));
	}
}

int SearchTree::bringUp(Node* root, const bool state) {
	if (state == false) {
		Node* current = root;
		int key;
		while (current->right() != nullptr) {
			current = current->right();
		}
		key = current->key();
		remove(key);
		return key;
	}
	else {
		Node* current = root;
		int key;
		while (current->left() != nullptr) {
			current = current->left();
		}
		key = current->key();
		remove(key);
		return key;
	}
}

int SearchTree::height(int key) const {
	Node* current = m_root;
	int height = 1;
	while (current != nullptr) {
		if (key == current->key()) {
			return height;
		}
		else if (key > current->key()) {
			current = current->right();
		}
		else if (key < current->key()) {
			current = current->left();
		}
	}
	if (current == nullptr) {
		return -1;
	}
}

SearchTree::operator std::vector<int>() const {
	std::vector<int> result;
	vectorize(m_root, result);
	return result;
}

void SearchTree::vectorize(Node* root, std::vector<int>& result) const {
	if (root != nullptr) {
		vectorize(root->left(), result);
		result.push_back(root->key());
		vectorize(root->right(), result);
	}
}