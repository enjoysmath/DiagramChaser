#pragma once

#include "Node.h"
#include <QGraphicsObject>
#include "Edge.h"
#include "ControlPoint.h"

class Edge  : public Node
{
public:
	enum End { Source, Target };

	Edge(QGraphicsObject *parent=nullptr);
	~Edge();

	void setEnd(End end, Node* node)
	{
		if (nodes[end] != node)
		{
			if (nodes[end]) {
				disconnect(nodes[end], &Node::updated, 0, 0);
				nodes[end]->removeSceneEventFilter(this);
			}
			nodes[end] = node;

			if (node)
			{
				connect(node, &Node::updated, this, [this]() { update(); });
				node->installSceneEventFilter(this);
			}
			update();
		}
	}

	Node* end(End end) { return nodes[end]; }

	ControlPoint* endPoint(End end) {
		if (end == Source)
			return _points[0];
		else
			return _points[3];
	}

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

	QPainterPath linePath() const { return _linePath;  }

	void updateLinePath();

	void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

	bool sceneEventFilter(QGraphicsItem* watched, QEvent* event) override;

	void update(const QRectF& rect=QRectF());

	void toggleBezier(bool en)
	{
		if (en != _bezier)
		{
			_points[1]->setVisible(en);
			_points[2]->setVisible(en);
			_bezier = en;
			update();
		}
	}

private:
	Node* nodes[2];
	Edge* edgeBeingPlaced = nullptr;
	ControlPoint* _points[4];
	QPainterPath _linePath;
	bool _bezier = false;
};
