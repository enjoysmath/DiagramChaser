#include "stdafx.h"
#include "ControlPoint.h"

ControlPoint::ControlPoint(QGraphicsObject *parent)
	: QGraphicsEllipseItem(parent)
{
	setFlags(ItemSendsGeometryChanges | ItemSendsScenePositionChanges | ItemIsMovable | ItemIsFocusable);
	setRect(QRectF(-10, -10, 20, 20));
	setPen(QPen(QColor(232, 180, 10), 2.0));
	setBrush(QBrush(QColor(255, 255, 0)));
}



ControlPoint::~ControlPoint()
{}
