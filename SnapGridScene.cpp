#include "stdafx.h"
#include "SnapGridScene.h"

SnapGridScene::SnapGridScene(QObject *parent)
	: QGraphicsScene(parent)
{}

SnapGridScene::~SnapGridScene()
{}

void SnapGridScene::drawBackground(QPainter* painter, const QRectF& rect)
{
    QPen pen(Qt::black, 2.0);
    painter->setPen(pen);
    
    auto gridSize = snapGridSize();

    qreal left = int(rect.left()) - (int(rect.left()) % gridSize);
    qreal top = int(rect.top()) - (int(rect.top()) % gridSize);
    QVector<QPointF> points;

    for (qreal x = left; x < rect.right(); x += gridSize) {
        for (qreal y = top; y < rect.bottom(); y += gridSize) {
            points.append(QPointF(x, y));
        }
    }
    painter->drawPoints(points.data(), points.size());
}