#include <ios>
#include <bitset>
#include <algorithm>
#include <string>
#include <fstream>

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


bool HuffmanTree::decode(const std::string& inputFileName, const std::string& outputFileName) {
	if (m_root == nullptr) {
		return false;
	}

	std::fstream inputData(inputFileName, std::ios::in | std::ios::binary);

	char* tempErrorMessage = new char[200];

	if (errno) {
		strerror_s(tempErrorMessage, 200, errno);
		std::cerr << "Alert! Error occured in [HuffmanTree::decode] during [opening " << inputFileName << " ] : " << tempErrorMessage << "\n";
		return -1;
	}

	std::fstream outputData(outputFileName, std::ios::out | std::ios::binary | std::ios::in | std::ios::trunc);
	/*if (!outputData.is_open()) {
		outputData.open(outputFileName, std::ios::out);
		outputData.close();
		outputData.open(outputFileName, std::ios::out | std::ios::binary | std::ios::in | std::ios::trunc);
	}*/

	if (errno) {
		strerror_s(tempErrorMessage, 200, errno);
		std::cerr << "Alert! Error occured in [HuffmanTree::decode] during [opening " << outputFileName << " ] : " << tempErrorMessage << "\n";
		return -1;
	}

	delete[] tempErrorMessage;

	int tail;
	tail = static_cast<int>(inputData.get() - '0');

	unsigned char symbol;
	std::string string;
	BoolVector code(8, false);
	Node* current = nullptr;
	int i = -1;
	while (inputData.peek()!=EOF || (inputData.peek() == EOF && i>0 && i<8-tail)) {
		if (i == -1) {
			symbol = inputData.get();
			string = binary(symbol);
			std::reverse(string.begin(), string.end());
			code = BoolVector(string.c_str());
			i = 0;
		}

		current = m_root;
		while (current->left() || current->right()) {
			if (inputData.peek()!=EOF) {
				if (code[i] == 0 && current->left()) {
					current = current->left();
				}
				else if (code[i] == 1 && current->right()){
					current = current->right();
				}
				++i;
			}
			else {
				if (current->left() && code[i] == 0 && i < 8 - tail) {
					current = current->left();
				}
				else if (current->right() && code[i] == 1 && i < 8 - tail) {
					current = current->right();
				}
				++i;
			}

			if (i >= 8 && inputData.peek()!=EOF) {
				symbol = inputData.get();
				string = binary(symbol);
				std::reverse(string.begin(), string.end());
				code = BoolVector(string.c_str());
				i = i % 8;
			}
		}
		if (current == m_root) { ++i; }
		int j = 0;
		while (!current->get().code[j++]==1);
		outputData.put(static_cast<unsigned char>(j-1));
	}

	inputData.close();
	outputData.close();

	return true;
}

double HuffmanTree::encode(const std::string& importFile, const std::string& exportFile) {
	if (m_root == nullptr) {
		return -1;
	}

	std::fstream firstFile(importFile, std::ios::in | std::ios::binary);

	char* tempErrorMessage = new char [200];

	if (errno) {
		strerror_s(tempErrorMessage, 200, errno);
		std::cerr << "Alert! Error occured in [HuffmanTree::encode] during [opening " << importFile << " ] : " << tempErrorMessage << "\n";
		return -1;
	}

	std::fstream secondFile(exportFile, std::ios::out | std::ios::binary | std::ios::in | std::ios::trunc);
	if (!secondFile.is_open()) {
		secondFile.open(exportFile, std::ios::out);
		secondFile.close();
		secondFile.open(exportFile, std::ios::out | std::ios::binary | std::ios::in | std::ios::trunc);
	}

	if (errno) {
		strerror_s(tempErrorMessage, 200, errno);
		std::cerr << "Alert! Error occured in [HuffmanTree::encode] during [opening " << exportFile << " ] : " << tempErrorMessage << "\n";
		return -1;
	}

	delete[] tempErrorMessage;
	
	Node* current;
	unsigned char symbol;
	int j = 0;
	secondFile.put('0');
	int countUncrypted = 0, countCrypted = 0, tail=0;
	BoolVector temp(8, false);
	while (firstFile.peek()!=EOF) {
		symbol = firstFile.get();
		++countUncrypted;

		current = m_root;
		
		while (current->left() || current->right()) {
			if (current->left()->get().code[static_cast<int>(symbol)] == 1) {
				current = current->left();
				temp[j++] = 0;
			}
			else if (current->right()->get().code[static_cast<int>(symbol)]==1) {
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
		if (current == m_root) { ++j; }
		if (j < 8 && firstFile.peek()==EOF) {
			tail = (8 - j)%8;
			secondFile.put(temp.getFirst());
		}
		else if (j<8) {
			continue;
		}
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

	_build(list);
} 

void HuffmanTree::_build(std::vector<Node*>& list) {
	Node* first, * second, * summ;
	symbol temp;
	while (list.size() > 1) {
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
		for (int i = list.size() - 1; i > 0; --i) {
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

void HuffmanTree::load(const std::string& fileName) {
	std::fstream file(fileName, std::ios::in | std::ios::binary | std::ios::out);

	if (m_root) {
		clear();
	}

	char* tempErrorMessage = new char[200];

	if (errno) {
		strerror_s(tempErrorMessage, 200, errno);
		std::cerr << "Alert! Error occured in [HuffmanTree::load] during [opening " << fileName << " ] : " << tempErrorMessage << "\n";
		return;
	}

	delete[] tempErrorMessage;
	std::vector<Node*> list;
	unsigned char temp = file.peek();
	while (file.peek() != EOF) {
		int code;
		code = file.get();
		unsigned char vertSlash = file.get();
		if (vertSlash != '|') {
			exit(-1);
		}
		int repeat;
		file >> repeat;

		Node* temp = new Node();
		HuffmanTree::symbol symbol;
		symbol.repeat = repeat;
		BoolVector tempBool(256, false);
		tempBool[code] = 1;
		symbol.code = tempBool;
		temp->set(symbol);
		list.push_back(temp);
		code = file.get();
	}
	
	_build(list);
	return;
}

void HuffmanTree::save(const std::string & fileName) {
	

	std::fstream file(fileName, std::ios::out | std::ios::binary);

	if (!m_root) {
		return;
	}

	char* tempErrorMessage = new char[200];

	if (errno) {
		strerror_s(tempErrorMessage, 200, errno);
		std::cerr << "Alert! Error occured in [HuffmanTree::save] during [opening " << fileName << " ] : " << tempErrorMessage << "\n";
		return;
	}

	delete[] tempErrorMessage;

	_export(file, m_root);

	file.close();
}

void HuffmanTree::_export(std::fstream& file, Node* root) {
	if (root->left()) {
		_export(file, root->left());
	}
	if (!root->left() && !root->right()) {
		BoolVector temp = root->get().code;
		for (int i = 0; i < 256; ++i) {
			if (temp[i] == true) {
				file << static_cast<unsigned char>(i);
				break;
			}
		}

		file << '|' << root->get().repeat << '\n';
		return;
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
	for (int i = s.size(); i < 8; ++i) s.push_back('0');
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

	char* tempErrorMessage = new char[200];

	if (errno) {
		strerror_s(tempErrorMessage, 200, errno);
		std::cerr << "Alert! Error occured in [HuffmanTree::load] during [opening " << fileName << " ] : " << tempErrorMessage << "\n";
		return;
	}

	int* TAB = new int [256];
	for (int i = 0; i < 256; ++i) {
		TAB[i] = 0;
	}

	while (text.peek()!=EOF) {
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
