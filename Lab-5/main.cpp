#include <iostream>

#include "HuffmanTree.h"
#include "Node.h"

int main() {
	HuffmanTree test;
	test.build("userFile.txt");
	test.save("TAB.txt");
	HuffmanTree loadTest;
	loadTest.load("TAB.txt");
	loadTest.save("TAB2.txt");
	return 0;
}