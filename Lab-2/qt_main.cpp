#include <stdlib.h>
#include <iostream>
#include <QApplication>
#include <QDebug>

#include "treewidget.h"
#include "BinaryTreeTester.h"

int main(int argc, char *argv[])
{
    BinaryTreeTester tester(false, true);
    tester.test(1000);

    QApplication app(argc, argv);
    TreeWidget widget;
    widget.show();
    return app.exec();
}
