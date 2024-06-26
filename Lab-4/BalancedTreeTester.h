#pragma once
#include "../Lab-3/SearchTreeTester.h"

class BalancedTreeTester: public SearchTreeTester
{
  public:
    BalancedTreeTester(const bool useConsoleOutput, const bool enableAllTests = true);
    ~BalancedTreeTester() = default;

    BinaryTree* allocateTree() override;

    void check_addAndCount(const BinaryTree* tree, const int size) override;
    void check_remove(BinaryTree* tree, const int key,
        const bool result, const int size) override;
    void check_clear(const BinaryTree* tree, const int size) override;
    void check_assign(const BinaryTree* first,
        const BinaryTree* second) override;

    void check_balance(const BinaryTree*);

    void assign() override;
  private:
    bool isBalancedTree(const BinaryTree* tree);
};

