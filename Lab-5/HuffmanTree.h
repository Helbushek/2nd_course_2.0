#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "Boolean Vector/BooleanVector.h"


class HuffmanTree {
	
public:
	class Node;
	HuffmanTree();
	~HuffmanTree() = default;

	HuffmanTree(const std::string& filePath);

	void decode(const std::string& fileName);
	void encode(const std::string& fileName);
	void import(const std::string& fileName);

	struct symbol {
		Node* code;
		int repeat;
	};

	std::string binary(unsigned x) const;
	char charFromBool(const BoolVector) const;

private:
	Node* _encode(std::fstream& file, Node*, std::vector<bool>&);
	Node* _decode(std::fstream& file, Node*, std::vector<bool>&);

	void sort(std::vector<symbol>&) const;

	std::string stringFromFile(const std::string& fileName) const;
	std::vector<symbol> getList(const std::string& fileName) const;

private:
	Node* m_root;
};