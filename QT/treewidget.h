#pragma once

#include <QWidget>

#include "../Lab-2/BinaryTree.h"
#include "../Lab-2/Node.h"
#include "../Lab-3/SearchTree.h"
#include "../Lab-4/BalancedTree.h"

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

    void updateHeight();

    void updatePower();
  public slots:

    void addKey(int key);
    void removeKey(int key);
    void findKey(int key);
    void rebuildTree(int);
    void changeFontSize(int);
    void addRandKey();

protected:
    void resizeEvent(QResizeEvent *event) override;

  private:
    QPointF _drawTree(BinaryTree::Node *root, int leftBorderPos, int rightBorderPos, int yPos);
    void _redrawTree();
    void _updateSceneRect();

  private:
    int m_foundNumber = 0;
    std::vector<int> m_alt_tree;
    BinaryTree::Node* foundNode = nullptr;
    int m_fontSize = 42;
    Ui::TreeWidget *ui;
    QGraphicsScene *m_scene = nullptr;
    BinaryTree *m_tree;
};
