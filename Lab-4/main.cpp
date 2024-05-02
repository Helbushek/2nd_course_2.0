#include <random>
#include <iostream>

#include "BalancedTree.h"
#include "BalancedTreeTester.h"

int main() {
	SearchTreeTester temp1(false, true);
	BalancedTreeTester temp(false, true);
	
	temp1.test(1000);
	temp.test(1000);
	return 0;
}