#include "line.h"

#include <QDebug>

#include <cmath>

inline bool isNan(const QPointF& p)
{
    return std::isnan(p.x()) || std::isnan(p.y());
}

bool Line::contains(const QRectF& sceneRect) const
{
    return sceneRect.intersects(QRectF(getP1(), getP2()));
}

void Line::paintComponent(QPainter* painter, const QRectF& sceneRect)
{
    Component::paintComponent(painter, sceneRect);

    const QPointF p1 = getP1();
    const QPointF p2 = getP2();
    if (p1.isNull() || p2.isNull() || isNan(p1) || isNan(p2))
        return;
    painter->setPen(getPen());
    painter->drawLine(p1, p2);
}
