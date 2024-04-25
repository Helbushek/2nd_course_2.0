#include <random>
#include <iostream>

#include "BalancedTree.h"

int main() {
	BalancedTree temp;
	for (int i = 0; i < 10; ++i) {
		temp.add(rand()%100);
	}
	temp.printHorizontal();

	temp.remove(34);
	temp.remove(0);

	temp.printHorizontal();
	return 0;
}