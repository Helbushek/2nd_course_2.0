#include <stdlib.h>
#include <iostream>
#include <QApplication>
#include <QDebug>

#include "TreeWidget.h"
#include "BinaryTree.h"

int main(int argc, char *argv[])
{
//    QApplication app(argc, argv);
//    TreeWidget widget;
//    widget.show();
//    return app.exec();

    BinaryTree temp;
    int key;
    for (int i=0; i<10; ++i) {
        key = rand() % 50;
        temp.addNode(key);
    }
    temp.printHorizontal();
    std::vector<int> vector = temp;
    std::cout << std::endl << "Vector: " << std::endl;
    for (auto i : vector)
    {
        std::cout << i << ' ';
    }
    return 0;
}
