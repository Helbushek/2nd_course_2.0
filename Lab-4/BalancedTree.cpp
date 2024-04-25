#include "BalancedTree.h"
#include "../Lab-2/Node.h"

BalancedTree::BalancedTree()
	:SearchTree()
{}

BalancedTree::BalancedTree(const BalancedTree& other)
	:SearchTree(other)
{}

BalancedTree& BalancedTree::operator=(const BalancedTree& other)
{
	SearchTree::operator=(other);
	return *this;
}

BalancedTree BalancedTree::copyLeftChild() const {
	BalancedTree temp;
	temp.m_root = SearchTree::copyLeftChild().root();
	return temp;
}

BalancedTree BalancedTree::copyRightChild() const {
	BalancedTree temp;
	temp.m_root = SearchTree::copyRightChild().root();
	return temp;
}

bool BalancedTree::remove(const int key) {
	Node* remove = m_root;
	std::vector<Node*> pass;
	pass.push_back(m_root);

	while (!remove && remove->key() != key) {
		if (remove->key() > key) {
			pass.push_back(remove->right());
			remove = remove->right();
		}
		else {
			pass.push_back(remove->left());
			remove = remove->left();
		}
	}

	if (!remove) {
		return false;
	}
	
	_remove(remove, pass);
	_balance(pass);
	return true;
}

void BalancedTree::_remove(Node* remove, std::vector<Node*>& pass) {
	Node* parent = _findParent(m_root, remove->key());
	
	if (!remove->hasChilden()) {
		if (!parent) {
			delete m_root;
			m_root = nullptr;
		}
		else if (parent->right() == remove) {
			parent->right() == nullptr;
		}
		else if (parent->left() == remove) {
			parent->left() == nullptr;
		}
	}
	else {
		if (remove->right() && !remove->left()) {
			Node* current = remove;
			while (current->right()) {
				pass.push_back(current->right());
				current = current->right();
			}
			remove->setKey(current->key());
			_remove(current, pass);
		}
		else if (remove->left() && !remove->right()) {
			Node* current = remove;
			while (current->left()) {
				pass.push_back(current->left());
				current = current->left();
			}
			remove->setKey(current->key());
			_remove(current, pass);
		}
		else if (remove->left() && remove->right()) {
			Node* current = remove->left();
			pass.push_back(remove->left());
			while (current->right()) {
				pass.push_back(current->right());
				current = current->right();
			}
			remove->setKey(current->key());
			_remove(current, pass);
		}
	}
	
}

void BalancedTree::_balance(std::vector<Node*> &pass) {
	Node* current;
	bool isFixed = false;
	while (!pass.empty()) {
		current = pass.back();
		pass.pop_back();

		while (1) {
			if (current->balance() == 0) {
				break;
			}
			if (current->balance() == -1 || current->balance() == 1) {
				isFixed = true;
				break;
			}
			if (current->balance() == -2) {
				if (current->left()->balance() < 1) {
					shiftRight(current);
					continue;
				}
				else {
					shiftLeftRight(current);
					continue;
				}
			}
			if (current->balance() == 2) {
				if (current->right()->balance() > -1) {
					shiftLeft(current);
					continue;
				}
				else {
					shiftRightLeft(current);
					continue;
				}
			}
		}
	}
}

SearchTree::Node* BalancedTree::_addNode(Node* root, int key) {
	bool isFixed = false;
	return _addBalanceNode(root, key, isFixed);
}

SearchTree::Node* BalancedTree::_addBalanceNode(Node* root, int key, bool& isFixed) {
	if (!root) {
		root = new Node(key);
	}
	else if (key > root->key()) {
		root->setRight(_addBalanceNode(root->right(), key, isFixed));
	}
	else if (key < root->key()) {
		root->setLeft(_addBalanceNode(root->left(), key, isFixed));
	}

	
	isFixed = false;
	while (1) {
		if (root->balance() == 0) {
			break;
		};
		if (root->balance() == -1 || root->balance() == 1) {
			return root;
		}
		if (root->balance() == -2 || root->balance() == 2) {
			if (root->balance() == -2) {
				if (root->left()->balance() < 1) {
					shiftRight(root);

				}
				else {
					shiftLeftRight(root);
				}
				continue;
			}
			if (root->balance() == 2) {
				if (root->right()->balance() > -1) {
					shiftLeft(root);
				}
				else {
					shiftRightLeft(root);
				}
				continue;
			}
		}
	}
	isFixed = true;
	
	return root;
}

int BalancedTree::balance(int key) const {
	return balance(find(key));
}

int BalancedTree::balance(Node* root) const{
	if (m_root == nullptr) {
		return 0;
	}
	if (root == nullptr) {
		return balance(m_root);
	}
	if (root->right() == nullptr) {
		if (root->left() != nullptr) {
			return -root->left()->height();
		}
		else
			return 0;
	}
	else {
		if (root->left() == nullptr) {
			return root->right()->height();
		}
		else {
			return (root->right()->height() - root->left()->height());
		}
	}
}

void BalancedTree::shiftRight(Node* root) {
	Node* bot;
	bot = root->left();
	if (bot) {
		root->setLeft(bot->left());
		bot->setLeft(bot->right());
		bot->setRight(root->right());
		root->setRight(bot);

		int temp = bot->key();
		bot->setKey(root->key());
		root->setKey(temp);
	}
}
void BalancedTree::shiftLeft(Node* root) {
	Node* bot;
	bot = root->right();
	if (bot) {
		root->setRight(bot->right());
		bot->setRight(bot->left());
		bot->setLeft(root->left());
		root->setLeft(bot);

		int temp = bot->key();
		bot->setKey(root->key());
		root->setKey(temp);
	}
}

void BalancedTree::shiftLeftRight(Node* root) {
	Node* bot = root->left();
	if (bot) {
		shiftLeft(bot);
		shiftRight(root);
	}
}
void BalancedTree::shiftRightLeft(Node* root) {
	Node* bot = root->right();
	if (bot) {
		shiftRight(bot);
		shiftLeft(root);
	}
}