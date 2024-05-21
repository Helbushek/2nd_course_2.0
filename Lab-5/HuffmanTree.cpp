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


void HuffmanTree::decode(const std::string& importFile, const std::string& exportFile) {

}

void HuffmanTree::encode(const std::string& importFile, const std::string& exportFile) {
	std::fstream file(importFile, std::ios::out);

	file.seekg(0, std::ios_base::end);
	int count = file.tellg();

	char symbol;
	
	BoolVector vector(count, false);
	int i = 0;
	int tail;
	file >> tail;
	while (file) {
		file >> symbol;
		
		Node* current = m_root;
		BoolVector temp(8, false);
		int j = 0;
		while (current->left() && current->right()) {
			if (current->left()->get().code[static_cast<int>(symbol)] == 1) {
				current = current->left();
				temp[j++] = 0;
			}
			else {
				current = current->right();
				temp[j++] = 1;
			}
		}

		j = 0;
		while (j < temp.sizeOf()) {
			vector[i + j] = temp[j++];
		}

		++i;
	}

	file.close();
	file.open(exportFile, std::ios::in);

	for (int i = 0; i < vector.sizeOf()-8; i += 8) {
		file << vector.getFirst();
		vector <<= 8;
	}
	BoolVector temp(8, false);
	for (int i = 0; i < 8-tail; ++i) {
		temp[i] = vector[i];
	}
	char tempC = charFromBool(temp);
	file << tempC;
	file.close();

	return;
	
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

	while (list.size() > 1) { // MAKING TREE
		Node* first = new Node();
		*first = *list.back();
		list.pop_back();
		Node* second = new Node();
		*second = *list.back();
		list.pop_back();

		Node* summ = new Node();
		symbol temp;
		temp.code = (first->get().code | second->get().code);
		temp.repeat = (first->get().repeat + second->get().repeat);
		summ->set(temp);
		summ->setLeft(first);
		summ->setRight(second);
		auto iter = list.begin();
		for (int i = 0; i < list.size()-1; ++i) { // search through list
			if (list[i + 1]->get().repeat < summ->get().repeat) { // if next node is smaller in repeats
				list.push_back(nullptr); // grow list
				for (int j = list.size() - 1; j > i+1; --j) { // shift everything to the right untill needed place
					list[j] = list[j - 1];
				}
				list[i + 1] = summ; // on this place set the needed node
				break; // finish insertion
			}
		}
		summ = first = second = nullptr;
	}

	m_root = list.back();
	list.pop_back();
	return;
} 

void HuffmanTree::save(const std::string& fileName) {
	return;
}

void HuffmanTree::load(const std::string & fileName) {
	std::fstream file(fileName, std::ios::in);
	if (!file) {
		return;
	}

	if (m_root == nullptr) {
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
					file << static_cast<char>(i);
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

char HuffmanTree::charFromBool(BoolVector vector) const {
	int code = 0;
	int pow = 1;
	for (int i = 0; i < 8; ++i) {
		code += vector[i] * pow;
		pow *= 2;
	}
	return static_cast<char>(code);
}

 
void HuffmanTree::getList(const std::string& fileName, std::vector<HuffmanTree::Node*>& result) const  {
	std::ifstream text(fileName);
	int* TAB = new int [256];
	for (int i = 0; i < 256; ++i) {
		TAB[i] = 0;
	}

	while (text.good()) {
		char C = text.get();
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
