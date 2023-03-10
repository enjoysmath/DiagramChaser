#pragma once

#include <QGraphicsEllipseItem>

class ControlPoint  : public QGraphicsEllipseItem
{
public:
	ControlPoint(QGraphicsObject *parent=nullptr);
	~ControlPoint();

	QVariant itemChange(GraphicsItemChange change, const QVariant& value) override
	{
		if (change == ItemPositionHasChanged)
		{
			auto parent = parentItem();
			
			if (parent)
			{
				parent->update();
			}
		}

		return QGraphicsEllipseItem::itemChange(change, value);
	}
};
