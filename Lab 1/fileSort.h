#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <ios>
#include <random>
#include <vector>
#include <xiosbase>
/// <summary>
/// amount of files that will be used during sorting
/// </summary>
const int FILE_COUNT = 10;

struct interConnect {
	interConnect(void) = default;
	int fileCount = 0;
	std::string fileName;
	int levelCount = 0;
	std::vector<int> ip;
	std::vector<int> ms;

};

bool createEmptyFile(const std::string& fileName);

bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue);

bool createFilesArray(const int& filesCount, std::vector<std::fstream*>&);

bool isFileContainsSortedArray(const std::string& fileName);

int divideFile(const std::string& fileName, int& minCount);

int sumVector(std::vector<int> vector);

void openVector(std::vector<std::fstream*>& fileVector, std::ios_base::openmode type);

void closeVector(std::vector<std::fstream*>& fileVector);

void startSetup(interConnect& base, std::fstream& main, std::vector<std::fstream*>& fileContainer);

void splitFile(interConnect& base, std::fstream& main, std::vector<std::fstream*>& fileContainer);

int findMin(std::vector<int>& result);

bool hasNoNull(std::vector<int> vector);

void mergeFile(interConnect& base, std::vector<std::fstream*> fileContainer);

bool sortFile(const std::string& fileName, const int fileCount = FILE_COUNT);

int createAndSortFile(const std::string& fileName, const int numbersCount, const int maxNumberValue, const int fileCount = FILE_COUNT);



