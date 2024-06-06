#include "HashTableCell.h"
#include "ui_HashTableCell.h"
#include <QLineEdit>
#include <QDebug>

HashTableCell::HashTableCell(QWidget *parent) : QWidget(parent), ui(new Ui::HashTableCell)
{
    ui->setupUi(this);

    connect(ui->lineEditValue, &QLineEdit::editingFinished, this, [this]() { valueChanged(this); });

}

HashTableCell::~HashTableCell()
{
    delete ui;
}

QString HashTableCell::value() const
{
    return ui->lineEditValue->text();
}

int HashTableCell::key() const
{
    return ui->labelKeyValue->text().toInt();
}

void HashTableCell::setKey(int key)
{
    ui->labelKeyValue->setText(QString::number(key));
}

void HashTableCell::setValue(const QString &value)
{
    ui->lineEditValue->setText(value);
}

HashTableCell::HashTableCell(QWidget *parent, const HashTableCell &other) : HashTableCell(parent)
{
    this->setKey(other.key());
    this->setValue(other.value());
}

HashTableCell HashTableCell::operator=(const HashTableCell &other)
{}
