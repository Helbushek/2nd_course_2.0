#include <stdlib.h>
#include <QGraphicsScene>
#include <QColor>

#include "ui_TreeWidget.h"
#include "TreeNodeGraphicsItem.h"
#include "treewidget.h"

TreeWidget::TreeWidget(QWidget *parent):
    QWidget(parent),
    ui(new Ui::TreeWidget),
    m_scene(new QGraphicsScene(this))
{

    srand(time(0));
    ui->setupUi(this);
    ui->graphicsView->setScene(m_scene);
    m_tree = new BinaryTree();
    ui->lcdNumberFound->display(0);
    connect(ui->pushBUttonAdd, &QPushButton::clicked, this, [this] { addKey(ui->spinBox->value()); });

    connect(ui->pushButtonRemove, &QPushButton::clicked, this, [this] { removeKey(ui->spinBox->value()); });

    connect(ui->pushButtonFind, &QPushButton::clicked, this, [this] { findKey(ui->spinBox->value()); });

    connect(ui->pushButtonRand, &QPushButton::clicked, this, [this] { addRandKey(); });

    connect(ui->fontSlider, &QSlider::sliderMoved, this, [this] { changeFontSize(ui->fontSlider->value()); });

    connect(ui->pushButtonClear, &QPushButton::clicked, this, [this] {
        m_tree->clear();
        _redrawTree();
    });

    connect(ui->typeComboBox, &QComboBox::currentTextChanged, this,
            [this] { rebuildTree(ui->typeComboBox->currentIndex()); });

    connect(ui->spinBoxMin, QOverload<int>::of(&QSpinBox::valueChanged), this, [this] {
        ui->spinBox->setRange(ui->spinBoxMin->value(), ui->spinBoxMax->value());
    }); // shifting the max and min ranges of main spin box and random number generation

    connect(ui->spinBoxMax, QOverload<int>::of(&QSpinBox::valueChanged), this, [this] { ui->spinBox->setRange(ui->spinBoxMin->value(), ui->spinBoxMax->value());
    });

}

void TreeWidget::addKey(int key)
{
    m_tree->add(key);
    _redrawTree();
}
void TreeWidget::addRandKey()
{
    int iterationNumber = ui->spinBoxRand->value();
    if (iterationNumber <= 0)
    {
        iterationNumber = 1;
    }
    for (int i = 0; i < iterationNumber; ++i)
    {
        int key = rand() % (ui->spinBox->maximum() - ui->spinBox->minimum() + 1) + ui->spinBox->minimum();
        m_tree->add(key);
    }
    _redrawTree();
}
void TreeWidget::removeKey(int key)
{
    m_tree->remove(key);
    m_alt_tree.erase(std::find(m_alt_tree.begin(), m_alt_tree.end(), key));
    _redrawTree();
}
void TreeWidget::findKey(int key)
{
    if (foundNode == nullptr)
    {
        foundNode = new BinaryTree::Node();
    }
    if (m_tree->find(key) != nullptr)
        foundNode->setKey(m_tree->find(key)->key());
    else
    {
        foundNode = nullptr;
    }
    _redrawTree();
}

void TreeWidget::rebuildTree(int index)
{
    std::vector<int> temp(*m_tree);
    delete m_tree;
    if (index == 0)
    {
        m_tree = new BinaryTree();
    }
    if (index == 1)
    {
        m_tree = new SearchTree();
    }


    for (int i = 0; i < static_cast<int>(temp.size()); ++i)
    {
        m_tree->add(temp[i]);
    }
    _redrawTree();
}
void TreeWidget::changeFontSize(int size)
{
    m_fontSize = size;
    _redrawTree();
}


void TreeWidget::_redrawTree()
{
    m_foundNumber = 0;
    m_scene->clear();
    updateHeight();
    updatePower();
    _drawTree(m_tree->root(), 0, m_scene->width(), 0);
    ui->lcdNumberFound->display(m_foundNumber);
}

void TreeWidget::updateHeight()
{
    ui->heightNumber->display(m_tree->height());
    return;
}

void TreeWidget::updatePower()
{
    ui->sizeNumber->display(m_tree->size());
    return;
}

QPointF TreeWidget::_drawTree(BinaryTree::Node *root, int leftBorderPos, int rightBorderPos, int yPos)
{
    if (root == nullptr)
    {
        return QPointF();
    }

    int xPos = (leftBorderPos + rightBorderPos) / 2;
    TreeNodeGraphicsItem *item = new TreeNodeGraphicsItem(QString::number(root->key()));


    item->setFontSize(m_fontSize);

    if (foundNode != nullptr && root->key() == foundNode->key())
    {
        ++m_foundNumber;
        item->setFillColor(Qt::green);
        item->update();
    }

    m_scene->addItem(item);
    item->setPos(xPos - item->boundingRect().width() / 2, yPos);


    QPointF center = item->pos() + QPointF(item->boundingRect().center());

    QPointF leftCenter = _drawTree(root->left(), leftBorderPos, xPos, yPos + 100);
    QPointF rightCenter = _drawTree(root->right(), xPos, rightBorderPos, yPos + 100);

    if (!leftCenter.isNull())
    {
        auto line = m_scene->addLine(QLineF(center, leftCenter));
        line->setZValue(-1);
    }

    if (!rightCenter.isNull())
    {
        auto line = m_scene->addLine(QLineF(center, rightCenter));
        line->setZValue(-1);
    }
    return center;
}

TreeWidget::~TreeWidget()
{
    delete ui;
    delete m_tree;
}

void TreeWidget::show()
{

    QWidget::show();
    _updateSceneRect();

}

void TreeWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    _updateSceneRect();
    _redrawTree();
}

void TreeWidget::_updateSceneRect()
{
    m_scene->setSceneRect(0, 0,
                          ui->graphicsView->viewport()->width(),
                          ui->graphicsView->viewport()->height()
                          //        qMax(int(m_scene->width()), ui->graphicsView->viewport()->width()),
                          //        qMax(int(m_scene->height()), ui->graphicsView->viewport()->height())
                          );
    _redrawTree();
}
