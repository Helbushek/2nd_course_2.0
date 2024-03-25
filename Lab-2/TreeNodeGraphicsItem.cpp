#include <QPainter>
#include <QtMath>
#include "TreeNodeGraphicsItem.h"

TreeNodeGraphicsItem::TreeNodeGraphicsItem(const QString &text, QGraphicsItem *parent)
	: QGraphicsSimpleTextItem(text, parent)
	{
	}

int TreeNodeGraphicsItem::fontSize()
	{
	return font().pointSize();
	}

QColor TreeNodeGraphicsItem::textColor()
	{
	return m_textColor;
	}

QColor TreeNodeGraphicsItem::borderColor()
	{
	return m_borderColor;
	}

QColor TreeNodeGraphicsItem::fillColor()
	{
	return m_fillColor;
	}

void TreeNodeGraphicsItem::setTextColor(QColor &color)
	{
	m_textColor = color;
	update();
	}

void TreeNodeGraphicsItem::setBorderColor(QColor &color)
	{
	m_borderColor = color;
	update();
	}

void TreeNodeGraphicsItem::setFillColor(QColor &color)
	{
	m_textColor = color;
	update();
	}

void TreeNodeGraphicsItem::setFontSize(int size)
	{
	QFont font = this->font();
	font.setPointSize(size);
	this->setFont(font);
	}

QRectF TreeNodeGraphicsItem::TreeNodeGraphicsItem::boundingRect() const
	{
	QRectF rect	  = QGraphicsSimpleTextItem::boundingRect();
	int oldWidth  = rect.width();
	int oldHeight = rect.height();
	rect.setWidth(oldWidth * sqrt(2));
	rect.setHeight(oldHeight * sqrt(2));
	return rect;
}

void TreeNodeGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QRectF rect	  = QGraphicsSimpleTextItem::boundingRect();
	QRectF circleRect = boundingRect();
	circleRect.setHeight(qMax(circleRect.height(), circleRect.width()));
	circleRect.setWidth(circleRect.height());
	rect.moveTo((circleRect.width() - rect.width()) / 2,
				(circleRect.height() - rect.height()) / 2);

	painter->drawEllipse(circleRect);
	painter->setFont(font());
	painter->drawText(rect, text());

}
