#pragma once

#include <QGraphicsObject>
#include "SnapGridScene.h"
// TODO DEBUG REMOVE:
#include <QDebug>


class Node  : public QGraphicsObject
{
	Q_OBJECT

public:
	Node(QGraphicsObject *parent=nullptr);
	~Node();

	QRectF boundingRect() const override { return _boundingRect;  }

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	void update(const QRectF& rect = QRectF());

	float cornerRadius() const { 
		if (_cornerRadius < 0)
		{
			auto rect = boundingRect();
			return (rect.width() + rect.height()) / 4;
		}
		return _cornerRadius;  
	}
	
	void setCornerRadius(float rad) 
	{
		if (rad != _cornerRadius) {
			_cornerRadius = rad; 
			update();
		}
	}

	float padding() const { return _padding; }

	void setPadding(float pad)
	{
		if (pad != _padding)
		{
			_padding = pad;
			update();
		}
	}

	QBrush brush() const { return _brush; }
	QPen pen() const { return _pen; }

	void setBrush(const QBrush& brush)
	{
		if (brush != _brush)
		{
			_brush = brush;
			update();
		}
	}

	void setPen(const QPen& pen)
	{
		if (pen != _pen)
		{
			_pen = pen;
			update();
		}
	}

	QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

	const QList<QPolygonF> edgeConnectBoundary() const { return _edgeConnectBoundary;  }

signals:
	void updated();

protected:
	QRectF _boundingRect = QRectF();
	float _padding = 20;
	float _cornerRadius = 30;
	QPen _pen;
	QBrush _brush;
	QList<QPolygonF> _edgeConnectBoundary;
};
