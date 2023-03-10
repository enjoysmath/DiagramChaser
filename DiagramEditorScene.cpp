#include "stdafx.h"
#include "DiagramEditorScene.h"
#include "Node.h"
#include "ControlPoint.h"


DiagramEditorScene::DiagramEditorScene(QObject *parent)
	: SnapGridScene(parent)
{}

DiagramEditorScene::~DiagramEditorScene()
{}

void DiagramEditorScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		auto item = itemAt(event->scenePos(), QTransform());

		if (item)
		{
			auto node = dynamic_cast<Node*>(item);

			if (node)
			{
				auto edge = new Edge();
				addItem(edge);
				edge->setEnd(Edge::Source, node);
				auto scenePos = edge->mapFromScene(event->scenePos());
				edge->endPoint(Edge::Source)->setPos(scenePos);
				edge->endPoint(Edge::Target)->setPos(scenePos);
				edgeBeingPlaced = edge;
				endBeingPlaced = Edge::Target;
			}
		}
		else 
		{
			auto node = new Node();
			addItem(node);
			node->setPos(event->scenePos());
			node->setBrush(QBrush(Qt::red));
			auto node1 = new Node();
			node1->setParentItem(node);
			node1->setBrush(QBrush(Qt::yellow));
			node1->update();
			node->update();
		}
		

	}
}

void DiagramEditorScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	if (edgeBeingPlaced)
	{
		ControlPoint* controlPoint = edgeBeingPlaced->endPoint(endBeingPlaced);
		controlPoint->setPos(controlPoint->pos() + event->scenePos() - event->lastScenePos());
		edgeBeingPlaced->update();

		return;
	}
	else if (controlPointBeingMoved)
	{
		auto delta = event->scenePos() - event->lastScenePos();
		controlPointBeingMoved->setPos(controlPointBeingMoved->pos() + delta);

		auto parent = controlPointBeingMoved->parentItem();

		if (parent)
		{
			auto edge = dynamic_cast<Edge*>(parent);

			if (edge)
			{
				edge->update();
			}
		}

		return;
	}

	SnapGridScene::mouseMoveEvent(event);
}

void DiagramEditorScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (edgeBeingPlaced)
	{
		auto underMouse = items(event->scenePos());
		
		foreach(QGraphicsItem * item, underMouse)
		{
			if (item != edgeBeingPlaced)
			{
				auto node = dynamic_cast<Node*>(item);

				if (node)
				{
					edgeBeingPlaced->setEnd(endBeingPlaced, node);
					edgeBeingPlaced = nullptr;
					return;
				}
			}
		}

		removeItem(edgeBeingPlaced);
		delete edgeBeingPlaced;
		edgeBeingPlaced = nullptr;
		edgeJustPlaced = true;

		return;
	}
	else {
		if (controlPointBeingMoved == nullptr) {
			auto underMouse = items(event->scenePos());

			foreach(QGraphicsItem * item, underMouse)
			{
				auto controlPoint = dynamic_cast<ControlPoint*>(item);

				if (controlPoint)
				{
					auto parent = controlPoint->parentItem();
					
					if (parent)
					{
						auto edge = dynamic_cast<Edge*>(parent);
						
						if (edge)
						{
							if (controlPoint == edge->endPoint(Edge::Source) ||
								controlPoint == edge->endPoint(Edge::Target))
							{
								SnapGridScene::mousePressEvent(event);
								return;
							}
						}
					}

					controlPointBeingMoved = controlPoint;
					foreach(QGraphicsView * view, views())
					{
						view->setDragMode(QGraphicsView::NoDrag);
					}
					return;
				}
			}
		}
	}

	SnapGridScene::mousePressEvent(event);
}

void DiagramEditorScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	if (edgeJustPlaced)
	{
		edgeJustPlaced = false;
	}
	else if (controlPointBeingMoved)
	{
		controlPointBeingMoved = nullptr;
		foreach(QGraphicsView * view, views())
		{
			view->setDragMode(QGraphicsView::RubberBandDrag);
		}
	}
	else {
		auto underMouse = items(event->scenePos());

		foreach(QGraphicsItem * item, underMouse)
		{
			auto controlPoint = dynamic_cast<ControlPoint*>(item);

			if (controlPoint)
			{
				auto edge = dynamic_cast<Edge*>(controlPoint->parentItem());

				if (edge)
				{
					if (controlPoint == edge->endPoint(Edge::Source))
					{
						edgeBeingPlaced = edge;
						endBeingPlaced = Edge::Source;
						edge->setEnd(endBeingPlaced, nullptr);
					}
					else if (controlPoint == edge->endPoint(Edge::Target)) {
						edgeBeingPlaced = edge;
						endBeingPlaced = Edge::Target;
						edge->setEnd(endBeingPlaced, nullptr);
					}
					else {
					}

					return;
				}
			}
		}
	}

	SnapGridScene::mouseReleaseEvent(event);
}