#include <iostream>

#include "HuffmanTree.h"
#include "Node.h"

int main() {
	HuffmanTree test;
	test.build("testFile.txt");
	test.load("result.txt");
	return 0;
}