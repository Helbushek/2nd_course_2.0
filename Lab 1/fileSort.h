#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <ios>
#include <random>
#include <vector>

bool sortFile(const std::string& fileName, const int fileCount = 10);

bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue);

bool isFileContainsSortedArray(const std::string& fileName);

int createAndSortFile(const std::string& fileName, const int numbersCount, const int maxNumberValue);

std::ofstream createEmptyFile(const std::string& fileName);

std::vector<std::ofstream> createFilesArray(const int& filesCount);