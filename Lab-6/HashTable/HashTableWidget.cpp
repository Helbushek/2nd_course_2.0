#include <QMainWindow>
#include <QLineEdit>
#include <QPainter>
#include <QpaintEvent>
#include <QMargins>
#include <QDebug>
#include <QtMath>
#include <QLayoutItem>
#include <QPair>
#include <QPolygonF>
#include <QColor>
#include <iostream>
#include <QProcess>

#include "HashTable.h"
#include "HashTableWidget.h"
#include "HashTableCell.h"

HashTableWidget::HashTableWidget(QWidget *parent) : QWidget(parent), m_layout(new QGridLayout)
{
    setLayout(m_layout);
    QMargins margins = m_layout->contentsMargins();
    margins.setRight(margins.right() + connectionOffset);
    m_layout->setContentsMargins(margins);
    m_layout->setHorizontalSpacing(connectionOffset);
}

HashTableWidget::HashTableWidget(QWidget *parent, const HashTableWidget &other) : HashTableWidget(parent)
{
    if (foundCell)
    {
        delete foundCell;
    }
    foundCell = new int(*other.foundCell);


    m_items = other.m_items;
}

HashTableWidget::~HashTableWidget()
{
    resize(0);
}

void HashTableWidget::addItem(int key, const QString &value)
{
    if (m_items.size() == 0)
    {
        sendMessage("size is 0");
        return;
    }
    coordinates find = m_items.findItem(key);
    if (find.x != -1 || find.y != -1)
    {
        sendMessage("failure: add item allready exists");
        QWidget widget(m_layout->itemAtPosition(find.x, find.y)->widget());
        QRect rect(widget.x(), widget.y(), widget.width(), widget.height());
        if (foundCell)
        {
            delete foundCell;
            foundCell = nullptr;
        }
        foundCell = new int(key);
        scroll(rect);
        update();
        return;
    }
    coordinates add = m_items.addItem(key, value.toStdString());
    HashTableCell *temp = new HashTableCell(this);
    temp->setKey(key);
    temp->setValue(value);
    connect(temp, &HashTableCell::valueChanged, this, &HashTableWidget::onValueChanged);
    m_layout->addWidget(temp, add.y, add.x);
    sendMessage("success: add");
    update();
}

bool HashTableWidget::removeItem(const int key)
{
    if (!m_items.size())
    {
        return false;
    }

    std::string message = m_items.removeItem(key);
    sendMessage(QString::fromStdString(message));
    return true;
}

QPair<int, int> HashTableWidget::findItem(int key)
{
    coordinates find = m_items.findItem(key);
    if (find.x == -1 || find.y == -1)
    {
        sendMessage("failure find: no such item");
        if (foundCell)
        {
            delete foundCell;
            foundCell = nullptr;
        }
        update();
        return QPair<int, int>(-1, -1);
    }
    else
    {
        QString message = "success find: " + QString::number(find.x) + " | " + QString::number(find.y);
        sendMessage(message);
        if (foundCell)
        {
            delete foundCell;
            foundCell = nullptr;
        }
        foundCell = new int(key);
        update();
        return QPair<int, int>(find.x, find.y);
    }
}

QPair<int, int> HashTableWidget::operator[](int key)
{
    return findItem(key);
}

bool HashTableWidget::resize(int size)
{
    QLayoutItem *item;
    while ((item = m_layout->takeAt(0)) != NULL)
    {
        delete item->widget();
        delete item;
    }
    m_items.resize(size);

    for (int i = 0; i < m_items.size(); ++i)
    {
        for (int j = 0; j < m_items.at(i)->size(); ++j)
        {
            HashTableCell *temp = new HashTableCell(this);
            coordinates cords;
            cords.x = i;
            cords.y = j;
            temp->setKey(m_items(cords)->key);
            temp->setValue(QString::fromStdString(m_items(cords)->value));
            m_layout->addWidget(temp, i, j);
        }
    }

    sendMessage("success: resize");
    return true;
}

void HashTableWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);

    for (int j = 0; j < m_items.size(); ++j)
    {
        for (int i = 0; i < m_items.at(j)->size(); ++i)
        {
            QWidget *item = m_layout->itemAtPosition(j, i)->widget();
            coordinates cords;
            cords.x = j;
            cords.y = i;
            if (foundCell && m_items(cords)->key == *foundCell)
            {
                painter.setPen(Qt::green);
                painter.drawRect(item->x() - 1, item->y() - 1, item->width() + 2, item->height() + 2);
                painter.setPen(Qt::black);
            }
            if (i < static_cast<int>(m_items.at(j)->size()) - 1)
            {
                QPoint itemBorder(item->x() + item->width(), item->y() + (item->height() / 2));

                painter.drawLine(itemBorder.x(), itemBorder.y(), itemBorder.x() + connectionOffset, itemBorder.y());
                QPolygonF arrow;
                QPoint point1 = QPoint(itemBorder.x() + connectionOffset, itemBorder.y());
                QPoint point2 =
                    QPoint(itemBorder.x() + connectionOffset - arrowHeadWidth, itemBorder.y() + arrowHeadHeight);
                QPoint point3 =
                    QPoint(itemBorder.x() + connectionOffset - arrowHeadWidth, itemBorder.y() - arrowHeadHeight);
                arrow << point1 << point2 << point3;

                painter.drawPolygon(arrow);
            }
        }
    }
}

int HashTableWidget::onValueChanged(HashTableCell *item)
{
    qDebug() << item->value();
}

void HashTableWidget::print()
{
    m_items.print();
}

void HashTableWidget::chooseHash(int index)
{
    sendMessage(QString::fromStdString(m_items.chooseHash(index)));
    resize(m_items.size());
}

QWidget *HashTableWidget::operator()(int first, int second)
{
  return m_layout->itemAtPosition(first, second)->widget();
}

