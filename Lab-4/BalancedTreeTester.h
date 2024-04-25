#pragma once
#include "../Lab-3/SearchTreeTester.h"

class BalancedTreeTester: public SearchTreeTester
{
  public:
    BalancedTreeTester(const bool useConsoleOutput, const bool enableAllTests = true);
    ~BalancedTreeTester() = default;

    BinaryTree* allocateTree() override;

    void check_balance(const BinaryTree*);

    void assign() override;
  private:
    bool isBalancedTree(const BinaryTree* tree);
};

