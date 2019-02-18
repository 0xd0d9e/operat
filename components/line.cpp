#include "line.h"

bool Line::contains(const QRectF& sceneRect) const
{
    return sceneRect.intersects(QRectF(getP1(), getP2()));
}

void Line::paintComponent(QPainter* painter, const QRectF& sceneRect)
{
    Component::paintComponent(painter, sceneRect);

    painter->setPen(getPen());
    painter->drawLine(getP1(), getP2());
}
