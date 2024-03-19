#pragma once

#include <QWidget>

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

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void _updateSceneRect();

private:
    Ui::TreeWidget *ui;
    QGraphicsScene *m_scene = nullptr;
};
