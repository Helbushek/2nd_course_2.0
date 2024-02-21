#include "fileSort.h"

std::ofstream createEmptyFile(const std::string& fileName) {
	std::ofstream fileStream(fileName);

	if (!fileStream.is_open())
		return std::ofstream();
	
	return fileStream;
}

bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue) {
	
	std::ofstream fileStream = createEmptyFile(fileName);

	/* Seed */
	std::random_device rd;

	/* Random number generator */
	std::default_random_engine generator(rd());

	/* Distribution on which to apply the generator */
	std::uniform_int_distribution<int> distribution(-maxNumberValue, maxNumberValue);

	for (int i = 0; i < numbersCount; ++i) {
		fileStream <<  distribution(generator) << " ";
	}

	fileStream.close();
	return true;
}

bool isFileContainsSortedArray(const std::string& fileName) {
	std::ifstream fileStream(fileName);
	if (!fileStream.is_open())
		return false;

	int val1, val2;
	fileStream >> val2;
	while (!fileStream.eof()) {
		val1 = val2;
		fileStream >> val2;
		if (val1 > val2) 
			return false;
	}
	return true;
}

std::vector<std::ofstream> createFilesArray(const int& filesCount) {
	std::vector<std::ofstream> result;
	for (int i = 0; i < filesCount; ++i) {

		std::string fileName = "fileNo" + std::to_string(i) + ".txt";
		result.push_back(createEmptyFile(fileName));
	}
	return result;
}

bool sortFile(const std::string& fileName, const int fileCount) {
	// I. splitting phase 

	// Need an array, containing all files name, or stream names, just to be able to manipulate with them.
	std::vector<std::ofstream> fileContainer = createFilesArray(fileCount);

	for (int i = 0; i < fileCount; ++i) {
		
	}

	// II. Merging phase


	return true;
}

int createAndSortFile(const std::string& fileName, const int numbersCount, const int maxNumberValue) {
	if (!createFileWithRandomNumbers(fileName, numbersCount, maxNumberValue))
		return -1;

	int count = 0;

	while (!isFileContainsSortedArray(fileName)) {
		sortFile(fileName);
		count++;
	}
	return count;
}