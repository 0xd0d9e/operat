#include "shape.h"

#include "common/debug.h"

bool Shape::contains(const QRectF& sceneRect) const
{
    return sceneRect.intersects(localToGlobal(getRect()));
}

void Shape::paintComponent(QPainter* painter, const QRectF& sceneRect)
{
    Component::paintComponent(painter, sceneRect);

    getStyle().apply(painter);

    switch (getType())
    {
    case Rectangle:
        painter->drawRect(getRect());
        break;

    case Ellipse:
        painter->drawEllipse(getRect());
        break;

    default:
        break;
    }
}
