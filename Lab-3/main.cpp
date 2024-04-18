#include <iostream>

#include "SearchTree.h"
#include "SearchTreeTester.h"

int main() {
	SearchTreeTester test(false, true);
	
	test.test(1000);
	return 0;
}