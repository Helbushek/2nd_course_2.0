#include <assert.h>

#include "BalancedTreeTester.h"
#include "BalancedTree.h"

BalancedTreeTester::BalancedTreeTester(const bool useConsoleOutput, const bool enableAllTests)
    :SearchTreeTester(useConsoleOutput, enableAllTests)
{}

BinaryTree* BalancedTreeTester::allocateTree() {
    return new BalancedTree;
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

void BalancedTreeTester::check_addAndCount(const BinaryTree* tree, const int size) {
    SearchTreeTester::check_addAndCount(tree, size);
    assert(isBalancedTree(tree));
}

void BalancedTreeTester::check_remove(BinaryTree* tree, const int key, const bool result, const int size) {
    SearchTreeTester::check_remove(tree, key, result, size);
    assert(isBalancedTree(tree));
}

void BalancedTreeTester::check_clear(const BinaryTree* tree, const int size) {
    SearchTreeTester::check_clear(tree, size);
    assert(isBalancedTree(tree));
}

void BalancedTreeTester::check_assign(const BinaryTree* first, const BinaryTree* second) {
    SearchTreeTester::check_assign(first, second);
    assert(isBalancedTree(first));
    assert(isBalancedTree(second));
}

bool BalancedTreeTester::isBalancedTree(const BinaryTree* tree) {

    assert(SearchTreeTester::isSearchTree(tree));
    check_balance(tree);
    return true;
}

void BalancedTreeTester::check_balance(const BinaryTree* tree) {
    assert(tree->isBalanced());
}
