#include <iostream>

#include "HuffmanTree.h"
#include "Node.h"

int main() {
	HuffmanTree test;
	test.encode("userFile.txt", "encodedFile.txt");
	test.save("TAB.txt");
	test.decode("encodedFile.txt", "decodedFile.txt");
	return 0;
}