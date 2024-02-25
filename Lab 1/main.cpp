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
	/*std::cout << createFileWithRandomNumbers(std::string("WorkingFile.txt"), 10, 100); */

	sortFile("WorkingFile.txt");
	return 0;
}