#include "SearchTree.h"
#include "../Lab-2/Node.h"

SearchTree::SearchTree(const SearchTree& other)
    : BinaryTree(other)
{}

SearchTree& SearchTree::operator = (const SearchTree& other)
{
	BinaryTree::operator=(other);
	return *this;
}

SearchTree SearchTree::clone(BinaryTree::Node* root) {
	SearchTree temp;
	temp.m_root = BinaryTree::_clone(root);
	return temp;
}

int SearchTree::max() const {
	if (m_root == nullptr) {

	}
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

BinaryTree::Node* SearchTree::_addNode(Node* root, int key) {
	if (!root) {
		root = new Node(key);
	}
	else if (key > root->key()) {
		root->setRight(_addNode(root->right(), key));
	}
	else if (key < root->key()) {
		root->setLeft(_addNode(root->left(), key));
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
	return nullptr;
}

BinaryTree::Node* SearchTree::_findParent(Node* root, const int key) const {
	if (root == nullptr)
		return nullptr;

	if (
		(root->right() != nullptr && root->right()->key() == key) ||
		(root->left() != nullptr && root->left()->key() == key)
		)
	{
		return root;
	}
	else {
		if (key > root->key() && root->right() != nullptr) {
			root = _findParent(root->right(), key);
		}
		else if (key < root->key() && root->left() != nullptr) {
			root = _findParent(root->left(), key);
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
		if (remove->left() != nullptr) {
			remove->setKey(bringUp(remove->left(), false));
		}
		else if (remove->right() != nullptr) {
			remove->setKey(bringUp(remove->right(), true));
		}

	}
	else if (!remove->hasChilden()) {
		if (remove == m_root) {
			delete m_root;
			m_root = nullptr;
			return true;
		}
		Node* preRemove = _findParent(m_root, key);
		if (preRemove->right() == remove) {
			preRemove->setRight(nullptr);
		}
		else if (preRemove->left() == remove) {
			preRemove->setLeft(nullptr);
		}
	}
	return true;
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
	return height;
}

void SearchTree::vectorize(Node* root, std::vector<int>& result) const {
	if (root != nullptr) {
		vectorize(root->left(), result);
		result.push_back(root->key());
		vectorize(root->right(), result);
	}
}
