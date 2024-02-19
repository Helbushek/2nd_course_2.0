#pragma once
#include <string>

bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue);

bool isFileContainsSortedArray(const std::string& fileName);

bool sortFile(const std::string& fileName);	

int createAndSortFile(const std::string& fileName, const int numbersCount, const int maxNumberValue);