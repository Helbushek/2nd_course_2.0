#include <iostream>
#include "fileSort.h"

int main() {
	createFileWithRandomNumbers(std::string("WorkingFile.txt"), 10, 100);
	int minCount, sortedCount = devideFile("WorkingFile.txt", minCount);
	/*std::vector<int> test{ 1, 3, 9, -1 };

	std::cout << isNotEmpty(test);

	std::vector<std::fstream*> container;
	std::fstream main;
	interConnect base{};
	base.fileCount = 4;
	base.fileName = "WorkingFile.txt";*/
	//startSetup(base, main, container);
	/*splitFile(base, main, container);
	for (int i = 0; i < base.fileCount; ++i) {
		std::cout << base.ip[i] << ' ';
	}
	std::cout << std::endl;
	for (int i = 0; i < base.fileCount; ++i) {
		std::cout << base.ms[i] << ' ';
	}*/

	sortFile("WorkingFile.txt", 4);

	return 0;
}