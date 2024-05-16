#include <ios>
#include <bitset>
#include <algorithm>

#include "HuffmanTree.h"
#include "Node.h"

HuffmanTree::HuffmanTree() {
	m_root = new Node();
}

HuffmanTree::HuffmanTree(const std::string& filePath) {
	m_root = new Node();
}

std::string HuffmanTree::stringFromFile(const std::string& fileName) const{
	std::fstream file;
	file.open(fileName.c_str(), std::ios::in|std::ios::binary);
	std::string result;
	if (file) {
		file >> result;
	}
	return result;
}

void HuffmanTree::decode(const std::string& fileName) {
	std::fstream result(fileName, std::ios::in);
	


}

HuffmanTree::Node* HuffmanTree::_decode(std::fstream& file, Node* root, std::vector<bool>& route) {

	if (root->left() == nullptr && root->right() == nullptr) {
		for (auto i = route.begin(); i != route.end(); ++i) {
			file << *i << ' ';
		}
		file << "| " << charFromBool(root->get()) << "\n";
		route.pop_back();
		return root;
	}
	if (root->left() != nullptr) {
		route.push_back(false);
		_encode(file, root->left(), route);
	}
	if (root->right() != nullptr) {
		route.push_back(true);
		_encode(file, root->right(), route);
	}
}


void HuffmanTree::encode(const std::string& fileName) {
	import(fileName);
	std::string encoded = "encoded" + fileName;

	std::fstream result(encoded, std::ios::out);
	std::vector<bool> route;
	_encode(result, m_root, route);
	return;
} 



HuffmanTree::Node* HuffmanTree::_encode(std::fstream& file, Node* root, std::vector<bool>& route) {

	if (root->left() == nullptr && root->right() == nullptr) {
		for (auto i = route.begin(); i != route.end(); ++i) {
			file << *i << ' ';
		}
		file << "| " << charFromBool(root->get()) << "\n";
		route.pop_back();
		return root;
	}
	if (root->left() != nullptr) {
		route.push_back(false);
		_encode(file, root->left(), route);
	}
	if (root->right() != nullptr) {
		route.push_back(true);
		_encode(file, root->right(), route);
	}
}

void HuffmanTree::import(const std::string& fileName) {
	std::vector<symbol> list = getList(fileName);

	while (list.size()>1) {
		symbol first = list.back();
		list.pop_back();
		symbol second = list.back();
		list.pop_back();

		symbol summ;
		summ.code = new Node();
		summ.code->set(first.code->get() | second.code->get());
		summ.code->setLeft(first.code);
		summ.code->setRight(second.code);
		summ.repeat = (first.repeat + second.repeat);
		list.push_back(summ);
		sort(list);	
	}
	
	m_root = list.back().code;
	list.clear();
	return;
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

char HuffmanTree::charFromBool(BoolVector vector) const {
	int code = 0;
	int pow = 1;
	for (int i = 0; i < 8; ++i) {
		code += vector[i] * pow;
		pow *= 2;
	}
	return static_cast<char>(code);
}

 
std::vector<HuffmanTree::symbol> HuffmanTree::getList(const std::string& fileName) const  {
	
	std::string text = stringFromFile(fileName);
	std::vector<symbol> result;
	
	int* TAB = new int [256];
	for (int i = 0; i < 255; ++i) {
		TAB[i] = 0;
	}

	const char* temp = text.c_str();
	for (int i = 0; i < text.length(); ++i) {
		TAB[temp[i]] += 1;
	}

	for (int i = 0; i < 255; ++i) {
		if (TAB[i] != 0) {
			symbol symbol;
			symbol.repeat = TAB[i];
			char tempC = static_cast<char>(int(i));
			symbol.code = new Node(binary(tempC));
			result.push_back(symbol);
		}
	}

	sort(result);
	return result;
}

void HuffmanTree::sort(std::vector<symbol>& result) const {
	if (result.empty()) {
		return;
	}  for (size_t i = 1; i < result.size(); i++) {
		symbol key = result[i];
		size_t j = i - 1;  
		while (j < result.size() && result[j].repeat < key.repeat) {
			result[j + 1] = result[j];
			j--;
		}  
		result[j + 1] = key;
	}

}
