#include "stdafx.h"
#include "Edge.h"
#include "GeomTools.h"

Edge::Edge(QGraphicsObject *parent)
	: Node(parent)
{
	QColor colors[4] = { QColor(255,0,0), QColor(0,255,0), QColor(0,0,255), QColor(0,0,0) };

	for (int i = 0; i < 4; i++)
	{
		_points[i] = new ControlPoint(this);
		_points[i]->setBrush(colors[i]);
	}

	nodes[1] = nodes[0] = nullptr;
	setFlag(ItemIsMovable, false);
	_bezier = false;
	_points[1]->setVisible(false);
	_points[2]->setVisible(false);

	setBrush(QBrush(Qt::NoBrush));
}

Edge::~Edge()
{}

void Edge::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setBrush(brush());
	painter->setPen(pen());
	painter->drawPath(linePath());

	//Node::paint(painter, option, widget);
}

void Edge::updateLinePath()
{
	_linePath.clear();

	QPointF points[4];

	auto source = end(Source);
	auto target = end(Target);

	if (source != nullptr && target != nullptr && 
		dynamic_cast<Edge*>(source) == nullptr &&
		dynamic_cast<Edge*>(target) == nullptr)
	{
		QPointF sourcePos, targetPos;

		auto sourceRect = source->mapToScene(source->boundingRect()).boundingRect();
		auto targetRect = target->mapToScene(target->boundingRect()).boundingRect();

		auto right = qMax(sourceRect.left(), targetRect.left());
		auto left = qMin(sourceRect.right(), targetRect.right());
		auto bottom = qMax(sourceRect.top(), targetRect.top());
		auto top = qMin(sourceRect.bottom(), targetRect.bottom());

		if (right < left)
		{
			qSwap(right, left);
		}
		if (top > bottom)
		{
			qSwap(top, bottom);
		}

		auto width = right - left;
		auto height = bottom - top;
		auto rect = QRectF(left, top, width, height);

		if (!rect.isEmpty() && !_bezier)
		{
			auto e = 1.0;
			rect = rect.adjusted(-e, -e, e, e);

			if (sourceRect.intersects(rect))
			{
				auto rect1 = sourceRect.intersected(rect);
				auto segment = rect1.bottomRight() - rect1.topLeft();
				segment /= 2.0f;
				sourcePos = rect1.topLeft() + segment;
			}
			else
			{
				sourcePos = rect.center();
			}

			if (targetRect.intersects(rect))
			{
				auto rect1 = targetRect.intersected(rect);
				auto segment = rect1.bottomRight() - rect1.topLeft();
				segment /= 2.0f;
				targetPos = rect1.topLeft() + segment;
			}
			else
			{
				targetPos = rect.center();
			}

			points[0] = mapFromScene(sourcePos);
			points[3] = mapFromScene(targetPos);
		}
		else {
			auto S = mapToItem(source, _points[1]->pos());
			auto T = mapToItem(target, _points[2]->pos());
			
			S = closestPointOnPolygonList(source->edgeConnectBoundary(), S);
			T = closestPointOnPolygonList(target->edgeConnectBoundary(), T);

			points[0] = mapFromItem(source, S);
			points[3] = mapFromItem(target, T);
		}
	}
	else if (source != nullptr && target == nullptr)
	{
		QPointF T;
		
		if (!_bezier)
			T = endPoint(Target)->pos();
		else
			T = _points[1]->pos();

		T = mapToItem(source, T);
		auto S = closestPointOnPolygonList(source->edgeConnectBoundary(), T);

		points[0] = mapFromItem(source, S);
		points[3] = endPoint(Target)->pos();
	}
	else if (source == nullptr && target != nullptr)
	{
		QPointF S;

		if (!_bezier)
			S = endPoint(Source)->pos();
		else
			S = _points[2]->pos();

		S = mapToItem(target, S);
		auto T = closestPointOnPolygonList(target->edgeConnectBoundary(), S);

		points[0] = endPoint(Source)->pos();
		points[3] = mapFromItem(target, T);
	}	
	else {
		points[0] = endPoint(Source)->pos();
		points[3] = endPoint(Target)->pos();
	}

	endPoint(Source)->setPos(points[0]);
	endPoint(Target)->setPos(points[3]);

	if (_bezier) {
		_linePath.moveTo(points[0]);
		_linePath.cubicTo(_points[1]->pos(), _points[2]->pos(), points[3]);
	}
	else {
		auto v = QVector2D(points[3] - points[0]);
		auto l = v.length();
		v.normalize();

		_points[1]->setPos(points[0] + (l * v / 3).toPointF());
		_points[2]->setPos(points[0] + (l* 2 * v / 3).toPointF());

		_linePath.moveTo(_points[0]->pos());
		_linePath.lineTo(_points[3]->pos());
	}
}

void Edge::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
	auto menu = QMenu();
	auto action = menu.addAction("Bezier");
	action->setCheckable(true);
	action->setChecked(_bezier);
	connect(action, &QAction::toggled, this, &Edge::toggleBezier);
	menu.exec(event->screenPos());
}

bool Edge::sceneEventFilter(QGraphicsItem* watched, QEvent* event)
{
	if (nodes[0] == watched or nodes[1] == watched)
	{
		if (event->type() == QEvent::GraphicsSceneMouseMove)
			update();
	}

	return Node::sceneEventFilter(watched, event);
}

void Edge::update(const QRectF& rect)
{
	updateLinePath();

	auto childRect = childrenBoundingRect();
	auto p = _points[0]->boundingRect().width() / 2;
	_boundingRect = childRect.adjusted(-p, -p, p, p);

	_edgeConnectBoundary = _linePath.toSubpathPolygons();

	prepareGeometryChange();
	QGraphicsObject::update(rect);

	updated();
}