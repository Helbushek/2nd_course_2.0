#include "fileSort.h"


std::fstream createEmptyFile(const std::string& fileName) {
	std::fstream fileStream(fileName);

	if (!fileStream.is_open())
		return std::fstream();
	
	return fileStream;
}

/// <summary>
/// creates file filled with random numbers
/// </summary>
/// <param name="fileName">Name of created file (will create it) </param>
/// <param name="numbersCount">Amount of numbers in file</param>
/// <param name="maxNumberValue">diaposon of random numbers generated in file</param>
/// <returns>false if couldnt open file and true if file is generated properly</returns>
bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue) {
	
	std::fstream fileStream(fileName, std::ios_base::out);

	/* Seed */
	std::random_device rd;

	/* Random number generator */
	std::default_random_engine generator(rd());

	/* Distribution on which to apply the generator */
	std::uniform_int_distribution<int> distribution(-maxNumberValue, maxNumberValue);

	for (int i = 0; i < numbersCount; ++i) {
		fileStream << distribution(generator) << " ";
	}

	fileStream.close();
	return true;
}

/// <summary>
/// creates array with fstream files, named by "fileNo#.txt" sample
/// </summary>
/// <param name="filesCount">: amount of files to be created</param>
/// <returns>vector of fstreams </returns>
std::vector<std::fstream> createFilesArray(const int& filesCount) { //
	std::vector<std::fstream> result;
	for (int i = 0; i < filesCount; ++i) {

		std::string fileName = "fileNo" + std::to_string(i) + ".txt";
		result.push_back(createEmptyFile(fileName));
	}
	return result;
}

/// <summary>
/// checks for sorted array in file, probably will not read non-integer data type
/// </summary>
/// <param name="fileName">name of file to open</param>
/// <returns>false if file if not opened or is not sorted and true if file is opened correctly and sorted</returns>
bool isFileContainsSortedArray(const std::string& fileName)  { 
	std::fstream fileStream(fileName);
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

/// <summary>
/// sorts file with 
/// </summary>
/// <param name="fileName"> name of file which will be sorted</param>
/// <param name="fileCount"> number of files that will be used during sorting</param>
/// <returns> false is something wrong and true if file is sorted</returns>
bool sortFile(const std::string& fileName, const int fileCount) {
	// I. splitting phase 

	// Need to rewrite main file to new one just to split sorted parts. 
	std::fstream workingFile(fileName); 
	std::fstream toCopy(std::string("copy" + fileName), std::ios_base::out);
	
	int first, second, minCounter=0, sortedCounter=0;
	workingFile >> first;
	while (workingFile>>second) {
		toCopy << first << ' ';
		if (first == INT_MIN) {
			++minCounter;
		}
		if (second == INT_MIN) {
			++minCounter;
		}
		if (first > second) {
			++sortedCounter;
			toCopy << INT_MIN << ' ';
		}
		first = second;
	}
	toCopy << second << ' ';
	workingFile.swap(toCopy);

	++sortedCounter;

	

	// Need an array, containing all files name, or stream names, just to be able to manipulate with them. [done]
	std::vector<std::fstream> fileContainer = createFilesArray(fileCount);


	// II. Merging phase


	return true;
}

/// <summary>
/// BOTH creates a file with random numbers and sorts it afterwards
/// </summary>
/// <param name="fileName">gives this name to file</param>
/// <param name="numbersCount">counter of numbers which will be created in file</param>
/// <param name="maxNumberValue"> diaposon of numbers which will generate in file</param>
/// <param name="fileCount">amount of files that will be used during sorting, not necessary</param>
/// <returns></returns>
int createAndSortFile(const std::string& fileName, const int numbersCount, const int maxNumberValue, const int fileCount) {
	if (!createFileWithRandomNumbers(fileName, numbersCount, maxNumberValue))
		return -1;

	int count = 0;

	while (!isFileContainsSortedArray(fileName)) {
		sortFile(fileName);
		count++;
	}
	return count;
}