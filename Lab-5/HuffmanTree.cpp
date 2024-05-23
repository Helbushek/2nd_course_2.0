#include <ios>
#include <bitset>
#include <algorithm>

#include "HuffmanTree.h"
#include "Node.h"

HuffmanTree::HuffmanTree() {
	m_root = nullptr;
}

HuffmanTree::HuffmanTree(const std::string& filePath) {
	build(filePath);
}

HuffmanTree::~HuffmanTree() {
	clear();
}

void HuffmanTree::clear()
{
	clear(m_root);
	m_root = nullptr;
}

void HuffmanTree::clear(Node* root)
{
	if (root == nullptr) {
		return;
	}

	clear(root->left());
	clear(root->right());
	delete root;
}


bool HuffmanTree::decode(const std::string& importFile, const std::string& exportFile) {
	if (m_root == nullptr) {
		return false;
	}

	std::fstream readFile(importFile, std::ios::in | std::ios::binary);
	int tail;
	readFile >> tail;
	std::fstream writeFile(exportFile, std::ios::out | std::ios::binary);

	unsigned char temp;
	std::string code;

	readFile >> temp;
	code = binary(temp);
	int i = 0;
	while (readFile) {
		
		Node* current = m_root;
		while (current->left() && current->right()) {
			int leftOver = 0;
			if (!readFile.good()) {
				leftOver = tail;
			}
			if (i > 7-leftOver) {
				if (!readFile) {
					break;
				}
				if (leftOver == 0) {
					readFile >> temp;
					code = binary(temp);
					i = 0;
				}
			}
			if (code[i++] == '0') {
				current = current->left();
			}
			else {
				current = current->right();
			}
		}
		BoolVector binary = current->get().code;
		int j = 0;
		while (binary[j++] != 1) {}
		writeFile << static_cast<unsigned char>(j-1);

	}

	readFile.close();
	writeFile.close();

	return true;
}

double HuffmanTree::encode(const std::string& importFile, const std::string& exportFile) {
	if (m_root == nullptr) {
		return -1;
	}

	std::fstream firstFile(importFile, std::ios::in | std::ios::binary);
	std::fstream secondFile(exportFile, std::ios::out | std::ios::binary | std::ios::in);
	
	Node* current;
	unsigned char symbol;
	int i = 0, j = 0;
	secondFile.put('0');
	int countUncrypted = 0, countCrypted = 0, tail=0;
	BoolVector temp(8, false);
	while (!firstFile.eof()) {
		symbol = firstFile.get();
		++countUncrypted;

		current = m_root;
		
		while (current->left() && current->right()) {
			if (current->left()->get().code[static_cast<int>(symbol)] == 1) {
				current = current->left();
				temp[j++] = 0;
			}
			else {
				current = current->right();
				temp[j++] = 1;
			}
			if (j == 8) {
				secondFile.put(temp.getFirst());
				++countCrypted;
				j = 0;
				temp.setAll(false);
			}
		}
		if (j < 8 && firstFile.eof()) {
			tail = 8 - j;
			secondFile.put(temp.getFirst());
		}
		else if (j<8) {
			continue;
		}

		++i;
	}
	current = nullptr;

	firstFile.close();

	secondFile.seekp(0, std::ios::beg);
	secondFile.put(tail+'0');

	secondFile.close();

	double compression = ((countCrypted *1.) / countUncrypted*1.) * 100.;
	if (compression == 0) {
		return -1;
	}
	return compression;
}


std::string HuffmanTree::stringFromFile(const std::string& fileName) const{
	std::fstream file;
	file.open(fileName.c_str(), std::ios::in|std::ios::binary);
	std::string result;
	while (file) {
		file >> result;
		result += ' ';
	}
	file.close();
	return result;
}


void HuffmanTree::build(const std::string& fileName) {
	if (m_root != nullptr) {
		return;
	}
	std::vector<Node*> list;
	getList(fileName, list);

	Node* first, *second, *summ;
	symbol temp;
	while (list.size() > 1) { // MAKING TREE
		first = list.back();
		list.pop_back();
		second = list.back();
		list.pop_back();

		summ = new Node();
		
		temp.code = (first->get().code | second->get().code);
		temp.repeat = (first->get().repeat + second->get().repeat);
		summ->set(temp);
		summ->setLeft(first);
		summ->setRight(second);

		list.push_back(nullptr);
		if (list.size() == 1) {
			list[0] = summ;
		}
		for (int i=list.size()-1; i>0; --i) {
			if (list[i - 1]->get().repeat >= summ->get().repeat) {
				list[i] = summ;
				break;
			}
			if (i == 1 && list[i - 1]->get().repeat < summ->get().repeat) {
				list[i] = list[i - 1];
				list[0] = summ;
				break;
			}
			list[i] = list[i - 1];
		}
	}
	
	m_root = list.back();
	list.pop_back();
	return;
} 

void HuffmanTree::save(const std::string& fileName) {
	return;
}

void HuffmanTree::load(const std::string & fileName) {
	std::fstream file(fileName, std::ios::in | std::ios::binary);
	if (!file || !m_root) {
		return;
	}

	_export(file, m_root);

	file.close();
}

void HuffmanTree::_export(std::fstream& file, Node* root) {
	if (!root->left() && !root->right()) {
		BoolVector temp = root->get().code;
		for (int i = 0; i < 256; ++i) {
			if (temp[i] == true) {
				if (i < 33) {
					file << i;
				}
				else {
					file << static_cast<unsigned char>(i);
				}
				break;
			}
		}

		file << " | " << root->get().repeat << "\n";
		return;
	}
	if (root->left()) {
		_export(file, root->left());
	}
	if (root->right()) {
		_export(file, root->right());
	}
}

std::string HuffmanTree::binary(unsigned x) const
{
	std::string s;
	do
	{
		s.push_back('0' + (x & 1));
	} while (x >>= 1);
	std::reverse(s.begin(), s.end());
	return s;
}

unsigned char HuffmanTree::charFromBool(BoolVector vector) const {
	int code = 0;
	int pow = 1;
	for (int i = 0; i < 8; ++i) {
		code += vector[i] * pow;
		pow *= 2;
	}
	return static_cast<unsigned char>(code);
}

 
void HuffmanTree::getList(const std::string& fileName, std::vector<HuffmanTree::Node*>& result) const  {
	std::fstream text(fileName, std::ios::in | std::ios::binary);
	int* TAB = new int [256];
	for (int i = 0; i < 256; ++i) {
		TAB[i] = 0;
	}

	while (text.good()) {
		unsigned char C = text.get();
		TAB[static_cast<int>(C)] += 1;
	}

	for (int i = 0; i < 256; ++i) {
		if (TAB[i] != 0) {
			symbol symbol;
			symbol.repeat = TAB[i];
			symbol.code = BoolVector(256, false);
			symbol.code[i] = true;
			Node* temp = new Node();
			temp->set(symbol);
			result.push_back(temp);
			temp = nullptr;
			delete temp;
		}
	}
	sort(result);

	return;
}

void HuffmanTree::sort(std::vector<Node*>& result) const {
	if (result.empty()) {
		return;
	}  for (size_t i = 1; i < result.size(); i++) {
		Node* key = new Node();
		*key = *result[i];
		size_t j = i - 1;  
		while (j < result.size()-1 && result[j]->get().repeat < key->get().repeat) {
			*result[j + 1] = *result[j];
			j--;
		}  
		*result[j + 1] = *key;
		delete key;
	}

}
