#include <iostream>
#include <time.h>
#include <Windows.h>
#include "fileSort.h"
	
int main() {
	int repeatNumber = 100;
	std::string fileName = "WorkingFile.txt";

	for (int i = 0; i < repeatNumber; ++i) {	
		createFileWithRandomNumbers(fileName, 100, 10);
		clock_t startClock = clock(), endClock;
		sortFile(fileName, 5);
		endClock = clock();
		double time = (double)(endClock - startClock) / CLOCKS_PER_SEC;
		std::cout << i << ". TIME: " << time << std::endl;
	}
	return 0;
}