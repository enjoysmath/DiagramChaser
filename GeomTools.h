#pragma once

#include <QPointF>
#include <QList>
#include <QPolygonF>
#include <QLineF>
#include <QVector2D>

QPointF closestPointOnLine(const QLineF& line, const QPointF& point);
QPointF closestPointOnPolygon(const QPolygonF polygon, const QPointF& point);
QPointF closestPointOnPolygonList(const QList<QPolygonF>& polygons, const QPointF& point);