/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <HashTableWidget.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    HashTableWidget *hashTable;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *labelKey;
    QSpinBox *spinBoxKey;
    QLabel *labelValue;
    QLineEdit *lineEditValue;
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonRemove;
    QPushButton *pushButtonFind;
    QLabel *labelTableSize;
    QSpinBox *spinBoxTableSize;
    QPushButton *pushButtonResize;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(688, 505);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 668, 409));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hashTable = new HashTableWidget(scrollAreaWidgetContents);
        hashTable->setObjectName(QString::fromUtf8("hashTable"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(hashTable->sizePolicy().hasHeightForWidth());
        hashTable->setSizePolicy(sizePolicy);
        hashTable->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(hashTable, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelKey = new QLabel(centralwidget);
        labelKey->setObjectName(QString::fromUtf8("labelKey"));

        horizontalLayout->addWidget(labelKey);

        spinBoxKey = new QSpinBox(centralwidget);
        spinBoxKey->setObjectName(QString::fromUtf8("spinBoxKey"));

        horizontalLayout->addWidget(spinBoxKey);

        labelValue = new QLabel(centralwidget);
        labelValue->setObjectName(QString::fromUtf8("labelValue"));

        horizontalLayout->addWidget(labelValue);

        lineEditValue = new QLineEdit(centralwidget);
        lineEditValue->setObjectName(QString::fromUtf8("lineEditValue"));

        horizontalLayout->addWidget(lineEditValue);

        pushButtonAdd = new QPushButton(centralwidget);
        pushButtonAdd->setObjectName(QString::fromUtf8("pushButtonAdd"));

        horizontalLayout->addWidget(pushButtonAdd);

        pushButtonRemove = new QPushButton(centralwidget);
        pushButtonRemove->setObjectName(QString::fromUtf8("pushButtonRemove"));

        horizontalLayout->addWidget(pushButtonRemove);

        pushButtonFind = new QPushButton(centralwidget);
        pushButtonFind->setObjectName(QString::fromUtf8("pushButtonFind"));

        horizontalLayout->addWidget(pushButtonFind);

        labelTableSize = new QLabel(centralwidget);
        labelTableSize->setObjectName(QString::fromUtf8("labelTableSize"));

        horizontalLayout->addWidget(labelTableSize);

        spinBoxTableSize = new QSpinBox(centralwidget);
        spinBoxTableSize->setObjectName(QString::fromUtf8("spinBoxTableSize"));
        spinBoxTableSize->setValue(10);

        horizontalLayout->addWidget(spinBoxTableSize);

        pushButtonResize = new QPushButton(centralwidget);
        pushButtonResize->setObjectName(QString::fromUtf8("pushButtonResize"));

        horizontalLayout->addWidget(pushButtonResize);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 688, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        labelKey->setText(QCoreApplication::translate("MainWindow", "Key:", nullptr));
        labelValue->setText(QCoreApplication::translate("MainWindow", "Value:", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        pushButtonRemove->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
        pushButtonFind->setText(QCoreApplication::translate("MainWindow", "Find", nullptr));
        labelTableSize->setText(QCoreApplication::translate("MainWindow", "Table size: ", nullptr));
        pushButtonResize->setText(QCoreApplication::translate("MainWindow", "Resize", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
