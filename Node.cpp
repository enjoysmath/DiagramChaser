#include "stdafx.h"
#include "Node.h"

Node::Node(QGraphicsObject *parent)
	: QGraphicsObject(parent)
{
	_pen = QPen(QColor(0, 0, 255), 3.0);
	_brush = QBrush(QColor(255, 200, 0));

	setFlags(ItemIsMovable | ItemIsFocusable | ItemIsSelectable | ItemSendsGeometryChanges | ItemSendsScenePositionChanges);
	setFiltersChildEvents(true);
}

Node::~Node()
{}

void Node::update(const QRectF& rect)
{
	auto childRect = childrenBoundingRect();

	if (childRect.isEmpty())
	{
		_boundingRect = QRectF(-100, -100, 200, 200);
	}
	else {
		auto p = _padding;
		_boundingRect = childRect.adjusted(-p, -p, p, p);
	}

	QPainterPath path;
	path.addRoundedRect(_boundingRect, cornerRadius(), cornerRadius());
	_edgeConnectBoundary = path.toSubpathPolygons();

	prepareGeometryChange();
	QGraphicsObject::update(rect);

	updated();
}

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setBrush(brush());
	painter->setPen(pen());
	painter->drawRoundedRect(boundingRect(), cornerRadius(), cornerRadius());
}


QVariant Node::itemChange(GraphicsItemChange change, const QVariant& value)
{
	if (change == ItemChildAddedChange || change == ItemChildRemovedChange) 
	{
		auto child = value.value<QGraphicsItem*>();

		if (child) {
			if (change == ItemChildAddedChange)
				child->installSceneEventFilter(this);
			else
				child->removeSceneEventFilter(this);
		}
	}
	else if (change == ItemPositionHasChanged)
	{
		auto parent = parentItem();

		if (parent) {
			auto parentNode = dynamic_cast<Node*>(parent);

			if (parentNode)
			{
				parentNode->prepareGeometryChange();
				parentNode->update();
			}
		}

		auto children = childItems();

		for (int i = 0; i < children.size(); i++)
		{
			auto child = children.at(i);
			auto node = dynamic_cast<Node*>(child);
			
			if (node)
			{
				node->prepareGeometryChange();
				node->update();
			}
		}
	}
	else if (change == ItemPositionChange && scene())
	{
		QPointF newPos = value.toPointF();

		auto _scene = dynamic_cast<SnapGridScene*> (scene());

		if (QApplication::mouseButtons() == Qt::LeftButton && _scene)
		{
			int gridSize = _scene->snapGridSize();
			qreal xV = round(newPos.x() / gridSize) * gridSize;
			qreal yV = round(newPos.y() / gridSize) * gridSize;
			return QPointF(xV, yV);
		}
		else
			return newPos;
	}

	return QGraphicsObject::itemChange(change, value);
}