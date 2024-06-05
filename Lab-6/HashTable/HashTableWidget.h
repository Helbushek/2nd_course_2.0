#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QTableWidget>
#include <QVector>
#include <QList>

#include <ui_HashTableCell.h>
#include "HashTableCell.h"
#include "HashFunction.h"

class QGridLayout;

class HashTableWidget : public QWidget
{
    Q_OBJECT
  public:
    HashTableWidget(QWidget *parent = nullptr);
    ~HashTableWidget();

  signals:
    void sendMessage(QString message) const;

  public slots:
    void addItem(int key, const QString &value);
    bool removeItem(int key);
    QRect findItem(int key);
    bool resize(int size);
    bool chooseHash(int index);

  protected:
    void paintEvent(QPaintEvent *event);

  private slots:
    int onValueChanged(HashTableCell *item);

  private:
    int* foundCell = nullptr;
    HashFunction *m_hash = new HashFunctionOne();
    int m_hash_index = 0;
    static const int connectionOffset = 50;
    static const int arrowHeadWidth = 3;
    static const int arrowHeadHeight = 3;

    QVector<QList<HashTableCell*>*> m_items;
    QGridLayout *m_layout = nullptr;
};
