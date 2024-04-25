#include <assert.h>

#include "BalancedTreeTester.h"
#include "BalancedTree.h"

BalancedTreeTester::BalancedTreeTester(const bool useConsoleOutput, const bool enableAllTests)
    :SearchTreeTester(useConsoleOutput, enableAllTests)
{}

BinaryTree* BalancedTreeTester::allocateTree() {
    return new BalancedTree;
}
void BalancedTreeTester::check_addAndCount(const BinaryTree* tree, const int size) {
    assert(tree->size() == size);
}
void BalancedTreeTester::check_remove(BinaryTree* tree, const int key,
                                    const bool result, const int size) {
    assert(tree->remove(key) == result);
    assert(tree->size() == size);
    assert(isBalancedTree(tree));
}
void BalancedTreeTester::check_clear(const BinaryTree* tree, const int size)
{
    assert(tree->size() == size);
}


void BalancedTreeTester::check_assign(const BinaryTree* first,
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

void BalancedTreeTester::assign() {
    if (!m_assignCheckEnabled) {
        return;
    }

    BalancedTree tree1;

    for (int i = 0; i < m_maxSize; ++i) {
        tree1.add(i);
    }

    BalancedTree tree2 = tree1; //����������� �����������
    check_assign(&tree1, &tree2);

    check_balance(&tree1);
    check_balance(&tree2);
    tree1 = tree1; //������������ ������ ����
    check_assign(&tree1, &tree2); //���������, ��� tree1 �� ���������

    tree1 = tree2; //������������ ���������� �� ������� ��������
    check_assign(&tree1, &tree2);
    check_balance(&tree1);
    check_balance(&tree2);

    BalancedTree tree3;
    tree1 = tree3; //������������ ������ �������� �������
    check_assign(&tree1, &tree3);
    check_balance(&tree3);

    tree3 = tree2; //������������ ������ �������� �������
    check_assign(&tree2, &tree3);
    check_balance(&tree2);
}

bool BalancedTreeTester::isBalancedTree(const BinaryTree* tree) {

    std::vector<int> nodes;
    treeKeysLnr(tree->root(), nodes);
    for (int i = 0; i < static_cast<int>(nodes.size()) - 1; ++i) {
        if (nodes[i] > nodes[i + 1]) {
            return false;
        }
    }
    check_balance(tree);
    return true;
}

void BalancedTreeTester::treeKeysLnr(BinaryTree::Node* root, std::vector<int>& result) {
    if (root != nullptr) {
        treeKeysLnr(root->left(), result);
        result.push_back(root->key());
        treeKeysLnr(root->right(), result);
    }
}

void BalancedTreeTester::check_balance(const BinaryTree* tree) {
    assert(tree->isBalanced());
}
