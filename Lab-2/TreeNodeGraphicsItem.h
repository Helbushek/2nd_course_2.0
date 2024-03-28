#pragma once
#include <QGraphicsSimpleTextItem>

class TreeNodeGraphicsItem: public QGraphicsSimpleTextItem
{
public:
	TreeNodeGraphicsItem(const QString &text = "", QGraphicsItem *parent = nullptr);

    int fontSize();
    QColor textColor();
    QColor borderColor();
    QColor fillColor();

//    QPointF pos() const;

//    void setPos(qreal X, qreal Y);
	void setFontSize(int);
	void setTextColor(QColor &);
	void setBorderColor(QColor &);
	void setFillColor(QColor &);

	QRectF boundingRect() const;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
	QColor m_textColor = Qt::black;
	QColor m_borderColor = Qt::black;
	QColor m_fillColor = Qt::white;
};

