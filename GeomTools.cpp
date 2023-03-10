#include "stdafx.h"
#include "GeomTools.h"

QPointF closestPointOnLine(const QLineF& line, const QPointF& point)
{
	auto P1 = line.p1();
	auto P2 = line.p2();
	QPointF A, B;

	if (QVector2D(P1 - point).lengthSquared() >
		QVector2D(P2 - point).lengthSquared())
	{
		A = P2;
		B = P1;
	}
	else {
		A = P1;
		B = P2;
	}

	auto v = QVector2D(B - A);
	v.normalize();
	auto t = QVector2D(point - A);

	v.normalize();
	auto vt = QVector2D::dotProduct(v, t);

	if (vt < 0)
		return A;

	return A + (v * vt).toPointF();
}

QPointF closestPointOnPolygon(const QPolygonF polygon, const QPointF& point)
{
	QPointF minPoint = polygon.at(0);
	double minDist = QVector2D(minPoint - point).lengthSquared();

	for (qsizetype i = 1; i < polygon.count(); i++)
	{
		QPointF t0 = polygon.at(i - 1);
		QPointF t1 = polygon.at(i);

		QPointF test = closestPointOnLine(QLineF(t0, t1), point);

		auto dist = QVector2D(test - point).lengthSquared();

		if (dist < minDist)
		{
			minDist = dist;
			minPoint = test;
		}
	}

	return minPoint;
}

QPointF closestPointOnPolygonList(const QList<QPolygonF>& polygons,
	const QPointF& point)
{
	QPointF minPoint = closestPointOnPolygon(polygons.at(0), point);
	double minDist = QVector2D(minPoint - point).lengthSquared();

	for (qsizetype i = 1; i < polygons.count(); i++)
	{
		QPolygonF polygon = polygons.at(i);

		auto test = closestPointOnPolygon(polygon, point);
		auto dist = QVector2D(test - point).lengthSquared();

		if (minDist > dist)
		{
			minDist = dist;
			minPoint = test;
		}
	}

	return minPoint;
}