#include "fileSort.h"


std::fstream createEmptyFile(const std::string& fileName) {
	std::fstream fileStream(fileName);

	if (!fileStream.is_open())
		return std::fstream();
	
	fileStream.close();
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
	fileStream.close();
	return true;
}

int devideFile(const std::string& fileName, int& minCount) {
	std::fstream workingFile(fileName, std::ios_base::in);
	std::fstream toCopy(std::string("copy" + fileName), std::ios_base::out);

	minCount = 0;
	int first, second, sortedPartsCounter = 0;
	workingFile >> first >> second;
	while (workingFile) {
		if (first != INT_MIN) {
			toCopy << first << ' ';
		}
		else if (first == INT_MIN) {
			++minCount;
		}
		if (first > second) {
			++sortedPartsCounter;
			toCopy << INT_MIN << ' ';
		}
		first = second;
		workingFile >> second;
	}
	toCopy << second << ' ';
	workingFile.swap(toCopy);

	workingFile.close();
	toCopy.close();
	return sortedPartsCounter+1;
}

int sumVector(std::vector<int> vector) {
	int sum = 0;
	for (auto i : vector) {
		sum += i;
	}
	return sum;
}

void openVector(std::vector<std::fstream> fileVector, std::ios_base::openmode type) {
	for (int i = 0; i < fileVector.size(); ++i) {
		fileVector[i].open("fileNo" + std::to_string(i) + ".txt", type);
	}
}

struct interConnect {
	interConnect(void) 
		:fileCount{}
		, fileName{}
		, levelCount{}
		, main{}
		, ip{}
		, ms{}
		, fileContainer{}
	{ return; }
	const int fileCount;
	const std::string fileName;
	int levelCount;
	std::fstream main;
	std::vector<int> ip;
	std::vector<int> ms;
	std::vector<std::fstream> fileContainer;
};

void startSetup(interConnect &base) {
	base.fileContainer = createFilesArray(base.fileCount);
	
	base.levelCount = 1;
	base.main.open("copy" + base.fileName);

	for (int i = 0; i < base.fileCount; ++i) {
		base.ip.push_back(1);
		base.ms.push_back(1);
	}
	base.ip.push_back(0);
	base.ms.push_back(0);

	openVector(base.fileContainer, std::ios_base::out);
}

void splitFile(interConnect& base) {
	startSetup(base);
	
	int ip0;
	int i = 0;
	while (!base.main) {
		int buf;
		base.main >> buf;
		while (buf != INT_MIN) {
			base.fileContainer[i] << buf << ' ';
			base.main >> buf;
		}
		base.fileContainer[i] << INT_MIN << ' ';
		--base.ms[i];
		if (!base.main) {
			continue;
		}
		if (base.ms[i] < base.ms[i + 1]) {
			++i;
			continue;
		} else {
			if (base.ms[i]==0) {
				++base.levelCount;
				ip0 = base.ip[0];
				i = 0;
				for (int k = 0; k < base.fileCount - 1; ++k) {
					base.ms[k] = base.ms[k + 1] - base.ip[k] + ip0;
					base.ip[k] = base.ip[k + 1] + ip0;
				}
				continue;
			}
			else {
				i = 0;
				continue;
			}
		}
	}
}

void mergeFile(interConnect& base) {

}

/// <summary>
/// sorts file with 
/// </summary>
/// <param name="fileName"> name of file which will be sorted</param>
/// <param name="fileCount"> number of files that will be used during sorting</param>
/// <returns> false is something wrong and true if file is sorted</returns>
bool sortFile(const std::string& fileName, const int fileCount) {
	// I. splitting phase 
	int minCount;
	int splitedParts = devideFile(fileName, minCount);
	interConnect base;
	splitFile(base);
	

	// II. Merging phase
	mergeFile(base);

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