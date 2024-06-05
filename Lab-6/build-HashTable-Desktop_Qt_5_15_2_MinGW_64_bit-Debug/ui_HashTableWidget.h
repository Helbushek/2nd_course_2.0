/********************************************************************************
** Form generated from reading UI file 'HashTableWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HASHTABLEWIDGET_H
#define UI_HASHTABLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HashTableWidget
{
public:

    void setupUi(QWidget *HashTableWidget)
    {
        if (HashTableWidget->objectName().isEmpty())
            HashTableWidget->setObjectName(QString::fromUtf8("HashTableWidget"));
        HashTableWidget->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(HashTableWidget->sizePolicy().hasHeightForWidth());
        HashTableWidget->setSizePolicy(sizePolicy);

        retranslateUi(HashTableWidget);

        QMetaObject::connectSlotsByName(HashTableWidget);
    } // setupUi

    void retranslateUi(QWidget *HashTableWidget)
    {
        HashTableWidget->setWindowTitle(QCoreApplication::translate("HashTableWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HashTableWidget: public Ui_HashTableWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HASHTABLEWIDGET_H
