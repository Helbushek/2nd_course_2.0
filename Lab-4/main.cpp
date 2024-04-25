#include <random>
#include <iostream>

#include "BalancedTree.h"
#include "BalancedTreeTester.h"

int main() {
	BalancedTreeTester temp(false, true);
	temp.setHeightCheckEnabled(false);

	temp.test(100);
	return 0;
}