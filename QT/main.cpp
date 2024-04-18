#include <stdlib.h>
#include <iostream>
#include <QApplication>
#include <QDebug>

#include "treewidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TreeWidget widget;
    widget.show();
    return app.exec();
}
