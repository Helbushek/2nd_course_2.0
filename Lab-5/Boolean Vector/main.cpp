#include "BooleanVector.h"
#include <iostream>

int main() {
	BoolVector test("1000000000000000");

	test.print();
	std::cout << std::endl;

	test >>= 9;
	
	test.print();
	std::cout << std::endl;
	test <<= 9;

	test.print();
	return(0);
}