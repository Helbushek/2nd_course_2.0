#include <iostream>

#include "SearchTree.h"
#include "BinaryTree.h"
#include "random"

int main() {

	SearchTree temp;
	for (int i = 0; i < 10; ++i) {
		temp.add(rand() % 10);
	}

	temp.printHorizontal();

	std::cout << "\n\n";

	SearchTree temp2;

	temp2 = temp;

	temp2.printHorizontal();

	return 0;
}