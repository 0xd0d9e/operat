#include "shape.h"

#include "common/debug.h"

Shape::Shape(Component* parent, const QString& name, const QVariantMap& properties)
    : Component(parent, name, properties)
{
    if (getType() == 0)
    {
        delete (int*)123;
    }
}

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
