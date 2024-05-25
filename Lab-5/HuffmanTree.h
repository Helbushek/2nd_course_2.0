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
	~HuffmanTree();

	void clear();
	void clear(Node*);

	HuffmanTree(const std::string& filePath);

	bool decode(const std::string& importFile, const std::string& exportFile);

	double encode(const std::string& importFile, const std::string& exportFile);

	void build(const std::string& fileName);

	void save(const std::string& fileName);

	void load(const std::string& fileName);

	struct symbol {
		BoolVector code;
		int repeat;
	};

	std::string binary(unsigned x) const;
	unsigned char charFromBool(const BoolVector) const;

private:

	void _build(std::vector<Node*>& list);

	void _export(std::fstream&, Node*);

	void sort(std::vector<Node*>&) const;

	std::string stringFromFile(const std::string& fileName) const;
	void getList(const std::string& fileName, std::vector<Node*>&) const;

private:
	Node* m_root;
};