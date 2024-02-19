/* Функции:

- Разбиение
- Слияние
- Нахождение первой генерации IP и MS
- Нахождение следующих генераций IP и MS
- Переопределение фиктивных отрезков по файлам 
- Собрать всё в сортировку через слежение за слоями (L в слиянии и разбиении одинаковое кол-во раз)

*/



#include <iostream>
#include "fileSort.h"

int main() {
	//createFileWithRandomNumbers("test_sbjct.txt", 100000, 100);
	std::cout << isFileContainsSortedArray("test_sbjct.txt");
	return 0;
}