#include "BinaryTreeTester.h"
#include <random>
#include <iostream>


int main() {
	BinaryTree test;
	for (int i = 0; i < 10; ++i) {
		test.add(rand() % 10);
	}

	test.printHorizontal();

	std::vector<int> temp(test);

	for (int i = 0; i < temp.size(); ++i) {
		std::cout << temp[i] << ' ';
	}
}
