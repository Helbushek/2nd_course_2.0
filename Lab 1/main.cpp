/* �������:

- ���������
- �������
- ���������� ������ ��������� IP � MS
- ���������� ��������� ��������� IP � MS
- ��������������� ��������� �������� �� ������ 
- ������� �� � ���������� ����� �������� �� ������ (L � ������� � ��������� ���������� ���-�� ���)

*/



#include <iostream>
#include "fileSort.h"

int main() {
	//createFileWithRandomNumbers("test_sbjct.txt", 100000, 100);
	std::cout << isFileContainsSortedArray("test_sbjct.txt");
	return 0;
}