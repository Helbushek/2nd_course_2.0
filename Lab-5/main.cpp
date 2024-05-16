#include <iostream>

#include "HuffmanTree.h"
#include "Node.h"

int main() {
	HuffmanTree test;
	std::string temp("testFile.txt");
	test.encode(temp);
	//HuffmanTree::Node* temp = new HuffmanTree::Node(test.binary(static_cast<int>('!')));
	//std::cout << temp->get();
	//std::cout << test.charFromBool(temp->get());
	return 0;
}