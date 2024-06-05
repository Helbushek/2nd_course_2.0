#include "HashTableWidget.h"
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
#include "HashFunction.h"


HashTableWidget::HashTableWidget(QWidget *parent)
    : QWidget(parent)
      , m_layout(new QGridLayout)
{
    setLayout(m_layout);
    QMargins margins = m_layout->contentsMargins();
    margins.setRight(margins.right() + connectionOffset);
    m_layout->setContentsMargins(margins);
    m_layout->setHorizontalSpacing(connectionOffset);
}

HashTableWidget::~HashTableWidget()
{
    resize(0);
}

void HashTableWidget::addItem(int key, const QString &value)
{
    if (!m_items.size())
    {
        sendMessage("size is 0");
        return;
    }

    int row = m_hash->hash(key, m_items.size());
    HashTableCell *temp = new HashTableCell();
    temp->setKey(key);
    temp->setValue(value);
    m_items[row]->push_back(temp);
    connect(temp, &HashTableCell::valueChanged, this, &HashTableWidget::onValueChanged);
    m_layout->addWidget((*m_items[row])[m_items[row]->size()-1], row, m_items[row]->size()-1);
    sendMessage("success: add");
}

bool HashTableWidget::removeItem(const int key)
{
    if (!m_items.size())
    {
        return false;
    }

    int row = m_hash->hash(key, m_items.size());
    for (int i = 0; i < m_items[row]->size(); ++i)
    {
        if ((*m_items[row])[i]->key() == key)
        {
            m_items[row]->removeAt(i);
            resize(m_items.size());
            sendMessage("success: remove");
            return true;
        }
    }
    sendMessage("failure: no such item");
    return false;
}

QRect HashTableWidget::findItem(int key)
{
    int i = m_hash->hash(key, m_items.size());
    for (int j = 0; j < m_items[i]->size(); ++j)
        if ((*m_items[i])[j]->key() == key)
        {
            sendMessage(QString::number(i) + ", " + QString::number(j));
            QRect temp = QRect((*m_items[i])[j]->x() + ((*m_items[i])[j]->width() + connectionOffset),
                               (*m_items[i])[j]->y(), (*m_items[i])[j]->width(), (*m_items[i])[j]->height());
            sendMessage("success: find");
            delete foundCell;
            foundCell = new int(key);
            return temp;
    }

    sendMessage("failure: no such item");
    delete foundCell;
    return QRect(-1,-1, 0, 0);
}

bool HashTableWidget::resize(int size)
{
    update();
    if (size < 0)
    {
        return false;
        sendMessage("invalid size: size should be 0 or more");
    }
    QVector<QPair<int, QString>> temp;
    for (int i = 0; i < m_items.size(); ++i)
    {
        for (int j = 0; j < m_items[i]->size(); ++j)
        {
        QPair<int, QString> tempCell;
        tempCell.first = (*m_items[i])[j]->key();
        tempCell.second = (*m_items[i])[j]->value();
        temp.push_back(tempCell);
        }
    }
    for (int i = m_items.size() - 1; i >= size; --i)
    {
        delete m_items[i];
    }

    QLayoutItem* item;
    while ( ( item = m_layout->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }

    m_items.resize(size);
    for (int i = 0; i < size; ++i)
    {
        m_items[i] = new QList<HashTableCell *>();
    }

    for (int i = 0; i < temp.size(); ++i)
    {
        addItem(temp[i].first, temp[i].second);
    }
    return true;
    sendMessage("success: resize");
}

bool HashTableWidget::chooseHash(int index)
{
    if (index < 0 || index > 2)
    {
        return false;
    }
    else
    {
        update();
        if (m_hash_index != index && m_hash)
        {
            delete m_hash;
        }
        m_hash_index = index;
        switch (index)
        {
        case 0: {
            m_hash = new HashFunctionOne();
            resize(m_items.size());
            sendMessage("success: hashOne");
            return true;
        }
        case 1: {
            m_hash = new HashFunctionTwo();
            resize(m_items.size());
            sendMessage("success: hashTwo");
            return true;
        }
        case 2: {
            m_hash = new HashFunctionThree();
            resize(m_items.size());
            sendMessage("success: hashThree");
            return true;
        }
        }
    }

}

void HashTableWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);

    for (auto &list : m_items)
    {
        for (int i = 0; i < list->size(); ++i)
        {
            HashTableCell *item = list->at(i);
            if (foundCell && item->key() == *foundCell)
            {
                QPainter green(this);
                green.setPen(QColorConstants::Green);
                green.drawRect(item->x()-1, item->y()-1, item->width()+2, item->height()+2);
            }
            if (i < list->size() - 1)
            {
                QPoint itemBorder(item->x() + item->width(), item->y() + (item->height() / 2));

                painter.drawLine(itemBorder.x(), itemBorder.y(), itemBorder.x()+connectionOffset, itemBorder.y());
                QPolygonF arrow;
                QPoint point1 = QPoint(itemBorder.x() + connectionOffset, itemBorder.y());
                QPoint point2 = QPoint(itemBorder.x() + connectionOffset-arrowHeadWidth, itemBorder.y() + arrowHeadHeight);
                QPoint point3 = QPoint(itemBorder.x() + connectionOffset-arrowHeadWidth, itemBorder.y() - arrowHeadHeight);
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

