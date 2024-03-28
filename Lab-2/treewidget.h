#pragma once

#include <QWidget>

#include "BinaryTree.h"

class QGraphicsScene;

namespace Ui {
class TreeWidget;
}

class TreeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TreeWidget(QWidget *parent = nullptr);
    ~TreeWidget();

    void show();

  public slots:

    void addKey(int key);
    void removeKey(int key);

protected:
    void resizeEvent(QResizeEvent *event) override;

  private:
    QPointF _drawTree(BinaryTree::Node *root, int leftBorderPos, int rightBorderPos, int yPos);
    void _redrawTree();
    void _updateSceneRect();

private:
    int m_fontSize = 42;
    Ui::TreeWidget *ui;
    QGraphicsScene *m_scene = nullptr;
    BinaryTree *m_tree;
};
