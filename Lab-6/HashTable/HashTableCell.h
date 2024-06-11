#pragma once

#include <QWidget>
#include <QObject>

namespace Ui {
class HashTableCell;
}

class HashTableCell : public QWidget
{
    Q_OBJECT

        public:
          explicit HashTableCell(QWidget *parent = nullptr);

          HashTableCell(QWidget *parent, const HashTableCell &other);
          HashTableCell operator=(const HashTableCell &other);

          ~HashTableCell();

          QString value() const;
          int key() const;

        public slots:
          void setKey(int key);
          void setValue(const QString &value);

        signals:
          void valueChanged(HashTableCell* item);

private:

    Ui::HashTableCell *ui;
};

