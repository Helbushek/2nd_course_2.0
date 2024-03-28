#include <stdlib.h>
#include <iostream>
#include <QApplication>
#include <QDebug>

#include "BinaryTree.h"

int main(int argc, char *argv[])
{   
    QApplication app(argc, argv);
    TreeWidget widget;
    widget.show();
    return app.exec();
}
