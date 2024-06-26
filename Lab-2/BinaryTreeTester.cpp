#include <assert.h>
#include <iostream>
#include <stdlib.h>

#include "BinaryTreeTester.h"

BinaryTreeTester::BinaryTreeTester(const bool useConsoleOutput,
                                   const bool enableAllTests)
    : m_useConsoleOutput(useConsoleOutput)
    , m_addAndCountCheckEnabled(enableAllTests)
    , m_destructorCheckEnabled(enableAllTests)
    , m_removeCheckEnabled(enableAllTests)
    , m_clearCheckEnabled(enableAllTests)
    , m_assignCheckEnabled(enableAllTests)
    , m_heightCheckEnabled(enableAllTests)
{}

void BinaryTreeTester::test(const int size)
{
    m_maxSize = size;
    addAndCount();
    destructor();
    remove();
    clear();
    assign();
    height();

    std::cout << "\n !!! Tree passed all tests, congrats! \n";
}

bool BinaryTreeTester::addAndCountCheckEnabled() const
{
    return m_addAndCountCheckEnabled;
}

bool BinaryTreeTester::destructorCheckEnabled() const
{
    return m_destructorCheckEnabled;
}

bool BinaryTreeTester::removeCheckEnabled() const
{
    return m_removeCheckEnabled;
}

bool BinaryTreeTester::clearCheckEnabled() const
{
    return m_clearCheckEnabled;
}

bool BinaryTreeTester::assignCheckEnabled() const
{
    return m_assignCheckEnabled;
}

bool BinaryTreeTester::heightCheckEnabled() const
{
    return m_heightCheckEnabled;
}

void BinaryTreeTester::setUseConsoleOutput(const bool enabled)
{
    m_useConsoleOutput = enabled;
}

void BinaryTreeTester::setAddAndCountCheckEnabled(const bool enabled)
{
    m_addAndCountCheckEnabled = enabled;
}

void BinaryTreeTester::setDestructorCheckEnabled(const bool enabled)
{
    m_destructorCheckEnabled = enabled;
}

void BinaryTreeTester::setRemoveCheckEnabled(const bool enabled)
{
    m_removeCheckEnabled = enabled;
}

void BinaryTreeTester::setClearCheckEnabled(const bool enabled)
{
    m_clearCheckEnabled = enabled;
}

void BinaryTreeTester::setAssignCheckEnabled(const bool enabled)
{
    m_assignCheckEnabled = enabled;
}

void BinaryTreeTester::setHeightCheckEnabled(const bool enabled)
{
    m_heightCheckEnabled = enabled;
}

int BinaryTreeTester::invalidKey() const
{
    return -(rand() % m_maxSize + 1);
}

BinaryTree *BinaryTreeTester::allocateTree()
{
    return new BinaryTree;
}

void BinaryTreeTester::deallocateTree(BinaryTree *tree)
{
    delete tree;
}

std::vector<int> BinaryTreeTester::generateKeys() {
    std::vector<int> ordered;
    for (int i = 0; i < m_maxSize; ++i) {
        ordered.push_back(i + 1);
    }

    std::vector<int> random;
    while (!ordered.empty()) {
        int i = rand() % ordered.size();
        random.push_back(ordered[i]);
        ordered.erase(ordered.begin() + i);
    }

    return random;
}

void BinaryTreeTester::addAndCount()
{
    if (!m_addAndCountCheckEnabled) {
        return;
    }
    BinaryTree *tree = allocateTree();
    check_addAndCount(tree, 0);
    m_keys.clear();
    m_keys = generateKeys();
    for (int i = 0 ; i < m_maxSize; ++i) {
        tree->add(m_keys[i]);
        check_addAndCount(tree, i+1);
    }
    if (m_useConsoleOutput) {
        tree->printHorizontal();
    }
    
    deallocateTree(tree);
    std::cout << "TreeTester::add and count ended. Press any key to continue...";
    getchar();
}

void BinaryTreeTester::check_addAndCount(const BinaryTree *tree, const int size)
{
    assert(tree->size() == size);
}

void BinaryTreeTester::destructor()
{
    if (!m_destructorCheckEnabled) {
        return;
    }
    const int runsCount = 200;
	for (int i = 0; i < runsCount; i++)
    {
        BinaryTree* tree = allocateTree();
        for (int i = 0 ; i < m_maxSize; ++i) {
            tree->add(i);
        }
        if (m_useConsoleOutput) {
            tree->printHorizontal();
        }
		deallocateTree(tree);
    }
    std::cout << "TreeTester::destructor ended. Press any key to continue...";
    getchar();
	
}

void BinaryTreeTester::remove()
{
    if (!m_removeCheckEnabled) {
        return;
    }

    BinaryTree* tree = allocateTree();
    m_keys.clear();
    check_remove(tree, invalidKey(), false, m_keys.size());
    
    m_keys.clear();
    m_keys = generateKeys();
    for (int i = 0; i < m_maxSize; ++i) {
        tree->add(m_keys[i]);
        
        check_addAndCount(tree, i + 1);
    }

    while (!m_keys.empty()) {
        
        int removedNodeIndex = rand() % static_cast<int>(m_keys.size());

        check_remove(tree, invalidKey(), false, m_keys.size());
        check_remove(tree, m_keys[removedNodeIndex], true, static_cast<int>(m_keys.size()) - 1);
        m_keys.erase(m_keys.begin() + removedNodeIndex);

        if (m_useConsoleOutput) {
            tree->printHorizontal();
        }
    }

    

    check_remove(tree, invalidKey(), false, m_keys.size());
	deallocateTree(tree);
    std::cout << "TreeTester::remove ended. Press any key to continue...";
    getchar();
}

void BinaryTreeTester::check_remove(BinaryTree *tree, const int key,
                                    const bool result, const int size)
{
    assert(tree->remove(key) == result);
    assert(tree->size() == size);
}

void BinaryTreeTester::clear()
{
    if (!m_clearCheckEnabled) {
        return;
    }

	BinaryTree* tree = allocateTree();
	for (int i = 0; i < 200; i++)
    {
        for (int i = 0 ; i < m_maxSize; ++i) {
            tree->add(i);
        }
        if (m_useConsoleOutput) {
            tree->printHorizontal();
        }
		tree->clear();
		check_clear(tree, 0);
    }
    deallocateTree(tree);
    std::cout << "TreeTester::clear ended. Press any key to continue...";
    getchar();
}

void BinaryTreeTester::check_clear(const BinaryTree *tree, const int size)
{
    assert(tree->size() == size);
}

void BinaryTreeTester::assign()
{
    if (!m_assignCheckEnabled) {
        return;
    }

    BinaryTree tree1;
    
    for (int i = 0 ; i < m_maxSize; ++i) {
        tree1.add(i);
    }

    BinaryTree tree2 = tree1; //Конструктор копирования
    check_assign(&tree1, &tree2);

    tree1 = tree1; //Присваивание самому себе
    check_assign(&tree1, &tree2); //Проверяем, что tree1 не сломалось

    tree1 = tree2; //Присваивание одинаковых по размеру деревьев
    check_assign(&tree1, &tree2);

    BinaryTree tree3;
    tree1 = tree3; //Присваивание дерева меньшего размера
    check_assign(&tree1, &tree3);

    tree3 = tree2; //Присваивание дерева большего размера
    check_assign(&tree2, &tree3);

    std::cout << "TreeTester::assign ended. Press any key to continue...";
    getchar();
}

void BinaryTreeTester::check_assign(const BinaryTree *first,
                                    const BinaryTree *second)
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

BinaryTreeTester::TreeNodes BinaryTreeTester::treeNodes(const BinaryTree *tree)
{
    TreeNodes nodes;
	
    TreeNodes nodesToProcess;
	nodesToProcess.push_back(tree->root());
	while (!nodesToProcess.empty()) {
        BinaryTree::Node *node = nodesToProcess.front();
		if (node != nullptr) {
            nodesToProcess.push_back(node->left());
            nodesToProcess.push_back(node->right());
			nodes.push_back(node);
        }
        nodesToProcess.erase(nodesToProcess.begin());
	}
	
	return nodes;
}

void BinaryTreeTester::height()
{
    if (!m_heightCheckEnabled) {
        return;
    }

    height_trivialCases();
    height_longOnlyLeftSubtree();
    height_longOnlyRightSubtree();
    height_longOnlyLeftAndRightSubtrees();
    height_longRandomZigzagSubtrees();
    std::cout << "TreeTester::height ended. Press any key to continue...";
    getchar();
}

void BinaryTreeTester::check_height(const BinaryTree &tree, const int height)
{
    assert(tree.height() == height);
}

void BinaryTreeTester::height_trivialCases()
{
    BinaryTree tree;
    check_height(tree, 0);
    
    tree.add(0);
    check_height(tree, 1);
    if (m_useConsoleOutput) {
        tree.printHorizontal();
    }

}

void BinaryTreeTester::height_longOnlyLeftSubtree()
{
    BinaryTree longTree;
    longTree.add(0);
    BinaryTree::Node *runner = longTree.root();
    for (int i = 1; i < m_maxSize; ++i) {
        runner->setLeft(new BinaryTree::Node(i));
        runner = runner->left();
        check_height(longTree, i + 1);
    }
    if (m_useConsoleOutput) {
        longTree.printHorizontal();
    }
}

void BinaryTreeTester::height_longOnlyRightSubtree()
{
    BinaryTree longTree;
    longTree.add(0);
    BinaryTree::Node *runner = longTree.root();
    for (int i = 1; i < m_maxSize; ++i) {
        runner->setRight(new BinaryTree::Node(i));
        runner = runner->right();
        check_height(longTree, i + 1);
    }
    if (m_useConsoleOutput) {
        longTree.printHorizontal();
    }
}

void BinaryTreeTester::height_longOnlyLeftAndRightSubtrees()
{
    BinaryTree longTree;
    longTree.add(0);
    BinaryTree::Node *leftRunner = longTree.root();
    BinaryTree::Node *rightRunner = longTree.root();
    for (int i = 1; i < m_maxSize/2; ++i) {
        leftRunner->setLeft(new BinaryTree::Node(i));
        leftRunner = leftRunner->left();
        check_height(longTree, i + 1);
        
        rightRunner->setRight(new BinaryTree::Node(i));
        rightRunner = rightRunner->right();
        check_height(longTree, i + 1);
    }
    if (m_useConsoleOutput) {
        longTree.printHorizontal();
    }
}

void BinaryTreeTester::height_longRandomZigzagSubtrees()
{
    BinaryTree longTree;
    longTree.add(0);
    BinaryTree::Node *leftRunner = longTree.root();
    BinaryTree::Node *rightRunner = longTree.root();

    leftRunner->setLeft(new BinaryTree::Node(1));
    leftRunner = leftRunner->left();
    rightRunner->setRight(new BinaryTree::Node(1));
    rightRunner = rightRunner->right();

    for (int i = 2; i < m_maxSize/2; ++i) {
        if (rand() % 2 == 0) 
        {
            leftRunner->setLeft(new BinaryTree::Node(i));
            leftRunner = leftRunner->left();
        }
        else 
        {
            leftRunner->setRight(new BinaryTree::Node(i));
            leftRunner = leftRunner->right();
        }
        check_height(longTree, i + 1);

        if (rand() % 2 == 0)
        {
            rightRunner->setLeft(new BinaryTree::Node(i));
            rightRunner = rightRunner->left();
        }
        else 
        {
            rightRunner->setRight(new BinaryTree::Node(i));
            rightRunner = rightRunner->right();
        }
        check_height(longTree, i + 1);
    }
    if (m_useConsoleOutput) {
        longTree.printHorizontal();
    }
}
