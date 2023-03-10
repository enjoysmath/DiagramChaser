#pragma once

#include <QGraphicsScene>

class SnapGridScene  : public QGraphicsScene
{
public:
	SnapGridScene(QObject *parent=nullptr);

	void drawBackground(QPainter* painter, const QRectF& rect) override;

	int snapGridSize() const { return _gridSize; }

	~SnapGridScene();

private:
	int _gridSize = 200;
};
