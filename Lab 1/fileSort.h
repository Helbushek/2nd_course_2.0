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

bool createEmptyFile(const std::string& fileName);

bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue);

void createFilesArray(const int& filesCount);

bool isFileContainsSortedArray(const std::string& fileName);

bool sortFile(const std::string& fileName, const int fileCount = FILE_COUNT);

int createAndSortFile(const std::string& fileName, const int numbersCount, const int maxNumberValue, const int fileCount = FILE_COUNT);



