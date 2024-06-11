#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QTableWidget>
#include <QVector>
#include <QList>

#include <ui_HashTableCell.h>
#include "HashTableCell.h"
#include "HashTable.h"

class QGridLayout;

class HashTableWidget : public QWidget
{
    Q_OBJECT
  public:
    HashTableWidget(QWidget *parent = nullptr);
    HashTableWidget(QWidget *parent, const HashTableWidget &other);
    ~HashTableWidget();


    QPair<int, int> operator[](int key);
    QWidget *operator()(int, int);
    void print();

  signals:
    void sendMessage(QString message) const;
    void scroll(QRect rect) const;

  public slots:
    void addItem(int key, const QString &value);
    bool removeItem(int key);

    QPair<int, int> findItem(int key);

    bool resize(int size);
    void chooseHash(int index);

  protected:
    void paintEvent(QPaintEvent *event);

  private slots:
    void onValueChanged(HashTableCell *item);

  private:
    int *foundCell = nullptr;
    static const int connectionOffset = 50;
    static const int arrowHeadWidth = 10;
    static const int arrowHeadHeight = 10;

    HashTable<std::string> m_items;
    QGridLayout *m_layout = nullptr;
};
