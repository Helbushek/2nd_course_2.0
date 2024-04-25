#include <random>
#include <iostream>

#include "BalancedTree.h"
#include "BalancedTreeTester.h"

int main() {
	BalancedTreeTester temp(false, true);

	temp.test(500);
	return 0;
}