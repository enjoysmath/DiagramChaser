#pragma once

#include "SnapGridScene.h"
#include "Edge.h"



class DiagramEditorScene  : public SnapGridScene
{
public:
	DiagramEditorScene(QObject *parent=nullptr);
	~DiagramEditorScene();

	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

protected:
	Edge* edgeBeingPlaced = nullptr;
	Edge::End endBeingPlaced;
	ControlPoint* controlPointBeingMoved = nullptr;
	bool edgeJustPlaced = false;
};
