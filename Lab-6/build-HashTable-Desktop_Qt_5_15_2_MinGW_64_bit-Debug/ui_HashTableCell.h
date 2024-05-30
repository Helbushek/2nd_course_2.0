/********************************************************************************
** Form generated from reading UI file 'HashTableCell.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HASHTABLECELL_H
#define UI_HASHTABLECELL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HashTableCell
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelKey;
    QLabel *labelKeyValue;
    QLabel *labelValue;
    QLineEdit *lineEditValue;

    void setupUi(QWidget *HashTableCell)
    {
        if (HashTableCell->objectName().isEmpty())
            HashTableCell->setObjectName(QString::fromUtf8("HashTableCell"));
        HashTableCell->resize(205, 44);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(HashTableCell->sizePolicy().hasHeightForWidth());
        HashTableCell->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(HashTableCell);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinimumSize);
        gridLayout->setVerticalSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        labelKey = new QLabel(HashTableCell);
        labelKey->setObjectName(QString::fromUtf8("labelKey"));

        horizontalLayout->addWidget(labelKey);

        labelKeyValue = new QLabel(HashTableCell);
        labelKeyValue->setObjectName(QString::fromUtf8("labelKeyValue"));

        horizontalLayout->addWidget(labelKeyValue);

        labelValue = new QLabel(HashTableCell);
        labelValue->setObjectName(QString::fromUtf8("labelValue"));

        horizontalLayout->addWidget(labelValue);

        lineEditValue = new QLineEdit(HashTableCell);
        lineEditValue->setObjectName(QString::fromUtf8("lineEditValue"));
        lineEditValue->setMaxLength(32770);

        horizontalLayout->addWidget(lineEditValue);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(HashTableCell);

        QMetaObject::connectSlotsByName(HashTableCell);
    } // setupUi

    void retranslateUi(QWidget *HashTableCell)
    {
        HashTableCell->setWindowTitle(QCoreApplication::translate("HashTableCell", "Form", nullptr));
        labelKey->setText(QCoreApplication::translate("HashTableCell", "Key:", nullptr));
        labelKeyValue->setText(QString());
        labelValue->setText(QCoreApplication::translate("HashTableCell", "Value:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HashTableCell: public Ui_HashTableCell {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HASHTABLECELL_H
