#include <QGraphicsScene>

#include "TreeWidget.h"
#include "ui_TreeWidget.h"
#include "TreeNodeGraphicsItem.h"

TreeWidget::TreeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TreeWidget),
    m_scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
	ui->graphicsView->setScene(m_scene);
	auto item = new TreeNodeGraphicsItem("90wwww");
	item->setFontSize(16);
	m_scene->addItem(item);
}

TreeWidget::~TreeWidget()
{
    delete ui;
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
}

void TreeWidget::_updateSceneRect()
{
    m_scene->setSceneRect(0, 0,
                          ui->graphicsView->viewport()->width(),
                          ui->graphicsView->viewport()->height()
                          //        qMax(int(m_scene->width()), ui->graphicsView->viewport()->width()),
                          //        qMax(int(m_scene->height()), ui->graphicsView->viewport()->height())
                          );
}
