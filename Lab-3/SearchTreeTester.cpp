#include <assert.h>

#include "SearchTreeTester.h"
#include "SearchTree.h"

SearchTreeTester::SearchTreeTester(const bool useConsoleOutput, const bool enableAllTests)
	:BinaryTreeTester(useConsoleOutput, enableAllTests)
{}

BinaryTree* SearchTreeTester::allocateTree() {
    return new SearchTree;
}
void SearchTreeTester::check_addAndCount(const BinaryTree* tree, const int size) {
    BinaryTreeTester::check_addAndCount(tree, size);
    assert(isSearchTree(tree));
}

void SearchTreeTester::check_remove(BinaryTree* tree, const int key, const bool result, const int size) {
    BinaryTreeTester::check_remove(tree, key, result, size);
    assert(isSearchTree(tree));
}
void SearchTreeTester::check_clear(const BinaryTree* tree, const int size) 
{
    BinaryTreeTester::check_clear(tree, size);
    assert(isSearchTree(tree));
}


void SearchTreeTester::check_assign(const BinaryTree* first,
    const BinaryTree* second) 
{
    const int size = first->size();
    assert(size == second->size());

    TreeNodes firstTreeNodes = treeNodes(first);
    TreeNodes secondTreeNodes = treeNodes(second);

    for (int i = 0; i < size; ++i) {
        assert(firstTreeNodes[i] != secondTreeNodes[i]);
        assert(firstTreeNodes[i]->key() == secondTreeNodes[i]->key());
    }
}

void SearchTreeTester::assign() {
    if (!m_assignCheckEnabled) {
        return;
    }

    SearchTree tree1;

    for (int i = 0; i < m_maxSize; ++i) {
        tree1.add(i);
    }

    SearchTree tree2 = tree1; //Конструктор копирования
    check_assign(&tree1, &tree2);

    tree1 = tree1; //Присваивание самому себе
    check_assign(&tree1, &tree2); //Проверяем, что tree1 не сломалось

    tree1 = tree2; //Присваивание одинаковых по размеру деревьев
    check_assign(&tree1, &tree2);

    SearchTree tree3;
    tree1 = tree3; //Присваивание дерева меньшего размера
    check_assign(&tree1, &tree3);

    tree3 = tree2; //Присваивание дерева большего размера
    check_assign(&tree2, &tree3);
}

bool SearchTreeTester::isSearchTree(const BinaryTree* tree) {
    
    std::vector<int> nodes;
    treeKeysLnr(tree->root(), nodes);
    for (int i = 0; i < static_cast<int>(nodes.size()) - 1; ++i) {
        if (nodes[i] > nodes[i + 1]) {
            return false;
        }
    }
    return true;
}

void SearchTreeTester::treeKeysLnr(BinaryTree::Node* root, std::vector<int>& result) {
    if (root != nullptr) {
        treeKeysLnr(root->left(), result);
        result.push_back(root->key());
        treeKeysLnr(root->right(), result);
    }
}
