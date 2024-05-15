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
	pass.push_back(remove);

	while (remove) {
		if (remove->key() == key) {
			break;
		}
		if (remove->key() < key) {
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
		if (!parent || parent == remove) {
			delete m_root;
			m_root = nullptr;
			pass.clear();
            m_root->setBalance(0);
		}
		else if (parent->right() == remove) {
			delete remove;
			parent->setRight(nullptr);
			pass.pop_back();
            parent->setBalance(parent->balance() - 1);
		}
		else if (parent->left() == remove) {
			delete remove;
			parent->setLeft(nullptr);
			pass.pop_back();
            parent->setBalance(parent->balance() + 1);
		}
	}
	else {
        int temp;
        if ((remove->right() && !remove->left()) || (remove->left() && remove->right())) {
			Node* current = remove->right();
			pass.push_back(current);
			while (current->left()) {
				pass.push_back(current->left());
				current = current->left();
			}
			temp = current->key();
			_remove(current, pass);
			remove->setKey(temp);
			
			
		}
		else if (remove->left() && !remove->right()) {
			Node* current = remove->left();
			pass.push_back(current);
			while (current->right()) {
				pass.push_back(current->right());
				current = current->right();
			}
			temp = current->key();
			_remove(current, pass);
			remove->setKey(temp);
			
		}
	}
	
}

void BalancedTree::_balance(std::vector<Node*> &pass) {
    Node* current = nullptr;
	isFixed = false;

    while (!pass.empty() && !isFixed) {
        if (current)
        {
            if (pass.back()->right() == current)
            {
                pass.back()->setBalance(pass.back()->balance() - 1);
            }
            else
            {
                pass.back()->setBalance(pass.back()->balance() + 1);
            }
        }
        current = pass.back();
        pass.pop_back();

        if (current->balance() == -2) {
            if (current->left()->balance() < 1) {
                shiftRight(current);
            }
            else {
                shiftLeftRight(current);
            }
        } else if (current->balance() == 2) {
            if (current->right()->balance() > -1) {
                shiftLeft(current);
            }
            else {
                shiftRightLeft(current);
            }
        }

        if (current->balance() == -1 || current->balance() == 1) {
            isFixed = true;
        }
	}
}

SearchTree::Node* BalancedTree::_addNode(Node* root, int key) {
    if (!root) {
        isFixed = false;
        root = new Node(key);
        return root;
    }
    else if (key > root->key()) {
        root->setRight(_addNode(root->right(), key));
        if (!isFixed)
        {
            root->setBalance(root->balance() + 1);
        }
    }
    else if (key < root->key()) {
        root->setLeft(_addNode(root->left(), key));
        if (!isFixed)
        {
            root->setBalance(root->balance() - 1);
        }
    }

    if (isFixed)
    {
        return root;
    }

    if (root->balance() == -2) {
        if (root->left()->balance() < 1) {
            shiftRight(root);

        }
        else {
            shiftLeftRight(root);
        }
    } else if (root->balance() == 2) {
        if (root->right()->balance() > -1) {
            shiftLeft(root);
        }
        else {
            shiftRightLeft(root);
        }
    }

    if (root->balance() == 0) {
        isFixed = true;
    }
    return root;
}

int BalancedTree::balance() {
	return balance(m_root);
}

int BalancedTree::balance(Node* root) const
{
	root->setBalance(root->_balance());
	if (root) {
		balance(root->left());
		balance(root->right());
	}
	return root->balance();
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

	balance(root);

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

	balance(root);


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
