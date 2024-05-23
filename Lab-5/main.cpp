#include <iostream>

#include "HuffmanTree.h"
#include "Node.h"

int main() {
	HuffmanTree test;
	test.build("testFile.txt");
	//test.load("result.txt");
	test.encode("testFile.txt", "result.txt");
	return 0;
}