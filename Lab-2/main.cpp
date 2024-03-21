#include <stdlib.h>
#include <iostream>
#include <QApplication>
#include <QDebug>

#include "TreeWidget.h"
#include "BinaryTree.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TreeWidget widget;
    widget.show();
    return app.exec();

//    BinaryTree temp;
//    int key;
//    for (int i=0; i<10; ++i) {
//        key = rand() % 50;
//        temp.addNode(key);
//    }
//    temp.printHorizontal();
//    temp.find(0);
//    temp.printHorizontal();
    //std::cout << std::endl << "MIN: " << temp.min();
    return 0;
}
