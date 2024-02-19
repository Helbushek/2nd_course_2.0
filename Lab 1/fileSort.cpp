#include "fileSort.h"
#include <iostream>
#include <fstream>
#include <ios>
#include <random>


bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue) {
	std::ofstream fileStream(fileName);

	if (!fileStream.is_open()) 
		return false;

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

bool sortFile(const std::string& fileName) {

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