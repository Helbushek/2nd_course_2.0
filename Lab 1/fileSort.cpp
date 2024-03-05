#include "fileSort.h"


bool createEmptyFile(const std::string& fileName) {
	std::fstream fileStream(fileName, std::ios_base::out);

	if (!fileStream.is_open())
		return false;
	
	fileStream.close();
	return true;
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

	 // copied from stack overflow start

	/* Seed */
	std::random_device rd;

	/* Random number generator */
	std::default_random_engine generator(rd());

	/* Distribution on which to apply the generator */
	std::uniform_int_distribution<int> distribution(-maxNumberValue, maxNumberValue);
	 
	// copied from stack overflow end


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
bool createFilesArray(const int& filesCount, std::vector<std::fstream*>& result) {
	std::fstream* ptr = nullptr;
	std::string fileName;
	for (int i = 0; i < filesCount; ++i) {
		fileName = "fileNo" + std::to_string(i) + ".txt";
		ptr = new std::fstream(fileName);
		ptr->open(fileName, std::ios_base::out);
		if (ptr->is_open()) {
			result.push_back(ptr);
			ptr->close();
		}
		else {
			return 0;
		}
	}
	return 1;
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
			toCopy << ' '<< first;
		}
		else if (first == INT_MIN) {
			++minCount;
		}
		if (first > second) {
			++sortedPartsCounter;
			toCopy << ' '<< INT_MIN;
		}
		first = second;
		workingFile >> second;
	}
	toCopy << ' '<< second;
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

void openVector(std::vector<std::fstream*>& fileVector, std::ios_base::openmode type) {
	for (int i = 0; i < fileVector.size(); ++i) {
		fileVector[i]->open("fileNo" + std::to_string(i) + ".txt", type);
	}
}

void closeVector(std::vector<std::fstream*>& fileVector) {
	for (int i = 0; i < fileVector.size(); ++i) {
		if (fileVector[i]->is_open())
			fileVector[i]->close();
	}
}

void startSetup(interConnect& base, std::fstream& main, std::vector<std::fstream*>& fileContainer) {
	createFilesArray(base.fileCount, fileContainer);
	base.levelCount = 1;
	main.open("copy" + base.fileName, std::ios_base::in);

	for (int i = 0; i < base.fileCount-1; ++i) {
		base.ip.push_back(1);
		base.ms.push_back(1);
	}
	base.ip.push_back(0);
	base.ms.push_back(0);

	openVector(fileContainer, std::ios_base::out);
	closeVector(fileContainer);
	main.close();
}

void splitFile(interConnect& base, std::fstream& main, std::vector<std::fstream*>& fileContainer) {
	startSetup(base, main, fileContainer);
	openVector(fileContainer, std::ios_base::out);
	int ip0;
	int i = 0;
	main.open("copy" + base.fileName, std::ios_base::in);
	while (!main.eof()) {
		int buf=0;
		main >> buf;
			while (buf != INT_MIN && main) {
			(*fileContainer[i]) << ' '<< buf;
			main >> buf;
		}
		(*fileContainer[i]) << ' ' << INT_MIN;
		--base.ms[i];
		if (!main) {
			closeVector(fileContainer);
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
				for (int k = 0; k < base.fileCount-1; ++k) {
					base.ms[k] = base.ip[k + 1] - base.ip[k] + ip0;
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
	closeVector(fileContainer);
}

bool skipSeparator(std::vector<std::fstream*>& container) {
	bool flag = true;
	int temp;
	for (int i = 0; i < container.size()-1; ++i) {
		(*container[i]) >> temp;
		if (temp != INT_MIN)
			flag = false;
	}
	return flag;
}

int findMin(std::vector<int>& result) {
	int min=INT_MAX, index = -1;
	for (int i = 0; i < result.size(); ++i) {
		if (result[i] <= min && result[i]!=INT_MIN) {
			min = result[i];
			index = i;
		}
	}
	return index;
}

bool hasNoNull(std::vector<int> vector) {
	bool flag = true;
	for (int i = 0; i < vector.size(); ++i) {
		if (vector[i] == 0) {
			flag = false;
		}
	}
	return flag;
}

std::vector<int> readOnce(std::vector<std::fstream*>& container) {
	std::vector<int> result;
	int temp = 0;
	for (int i = 0; i < container.size(); ++i) {
		(*container[i]) >> temp;
		result.push_back(temp);
	}
	return result;
}

void shiftRight(std::vector<std::fstream*>& vector) {
	for (int i = vector.size() - 1; i > 0; --i) {
		std::swap(vector[i], vector[i - 1]);
	}
}

void shiftRight(std::vector<int>& vector) {
	for (int i = vector.size() - 1; i > 0; --i) {
		std::swap(vector[i], vector[i - 1]);
	}
}

void mergeFile(interConnect& base, std::vector<std::fstream*> fileContainer) {
	closeVector(fileContainer);
	openVector(fileContainer, std::ios_base::in);
	//std::fstream *ptr = new std::fstream();
	//fileContainer.push_back(ptr);

	int index = base.fileCount-1, index2 = index - 1, shiftCount=0;
	int indexAfterShift = index - shiftCount, index2AfterShift = indexAfterShift - 1;


	fileContainer[index]->close();
	fileContainer[index]->open("fileNo" + std::to_string(index) + ".txt", std::ios_base::out);

	while (base.levelCount != 0) {

		std::vector<int> temp;

		while (fileContainer[index2]->peek()!=EOF) {
			while (hasNoNull(base.ms)) {
				for (int i = 0; i < base.fileCount; ++i) {
					if (i != index) {
						--base.ms[i];
					}
					else {
						++base.ms[index];
					}
				}
				
			}
			temp.clear();
			int buf;
			for (int i = 0; i < index; ++i) {
				if (base.ms[i] > 0 && i!=index) {
					--base.ms[i];
					temp.push_back(INT_MIN);
				}
				else if (base.ms[i]==0) {
					(*fileContainer[i]) >> buf;
					temp.push_back(buf);
				}
			}

			// FIXME: check what can be wrong here
			int minIndex = findMin(temp);
 			while (minIndex != -1) { // fixed
				(*fileContainer[index]) << temp[minIndex] << ' ';
				if (fileContainer[minIndex]->good()) {
					(*fileContainer[minIndex]) >> temp[minIndex];
				}
				else {
					temp[minIndex] = INT_MIN;
				}
				minIndex = findMin(temp);
				if (minIndex == -1) {
					(*fileContainer[index]) << INT_MIN << ' ';
				}
			}
					}

		// 8

		fileContainer[index]->close();
		fileContainer[index - 1]->close();

		if (indexAfterShift == -1) {
			indexAfterShift = base.fileCount - 1;
		}
		if (index2AfterShift == -1) {
			index2AfterShift = base.fileCount - 1;
		}

		fileContainer[index]->open("fileNo" + std::to_string(indexAfterShift--) + ".txt", std::ios_base::in); // good now
		fileContainer[index - 1]->open("fileNo" + std::to_string(index2AfterShift--) + ".txt", std::ios_base::out); // good now
		
		shiftRight(fileContainer);
		shiftRight(base.ms);
		shiftRight(base.ip);

		--base.levelCount;
	}

}

void deleteFiles(int numberOfFiles) {
	std::string temp;
	for (int i = 0; i < numberOfFiles; ++i) {
		temp = "fileNo" + std::to_string(i) + ".txt";
		std::remove(temp.c_str());
	}
}

/// <summary>
/// sorts file with 
/// </summary>
/// <param name="fileName"> name of file which will be sorted</param>
/// <param name="fileCount"> number of files that will be used during sorting</param>
/// <returns> false is something wrong and true if file is sorted</returns>
bool sortFile(const std::string& fileName, int fileCount) {
	std::string resultName = "result.txt";
	std::remove(resultName.c_str());

	// I. splitting phase 
	int minCount;
	int splitedParts = devideFile(fileName, minCount);
	
	interConnect base{};
	
	base.fileCount = fileCount;
	base.fileName = fileName;
	
	std::fstream main;
	std::vector<std::fstream*> fileContainer;
	
	splitFile(base, main, fileContainer);
	
	// II. Merging phase
	
	int fileShifts = base.levelCount;
	
	mergeFile(base, fileContainer);
	
	main.close();
	main.open("copy" + fileName, std::ios_base::out);
	
	for (int i = 0; i < minCount; ++i) {
		main << ' ' << INT_MIN;
	}
	
	closeVector(fileContainer);

	int resultIndex = fileCount - fileShifts;
	while (resultIndex < 0) {
		resultIndex += fileCount;
	}
	fileContainer[resultIndex]->open("fileNo" + std::to_string(resultIndex) + ".txt", std::ios_base::in);
	
	main.close();
	main.open("copy" + fileName);
	
	for (int i = 0; i < minCount; ++i) {
		main << ' ' << INT_MIN;
	}
	
	int buf;
	
	(*fileContainer[resultIndex]) >> buf;
	
	while (buf!=INT_MIN && fileContainer[resultIndex]->good()) {
		main << ' ' << buf;
		(*fileContainer[resultIndex]) >> buf;
	}
	
	fileContainer[resultIndex]->close();
	
	main.close();
	
	std::string temp = "copy" + fileName;
	
	std::rename(temp.c_str(), resultName.c_str());
	
	deleteFiles(fileCount);
	
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