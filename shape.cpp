#include "shape.h"

#include "debug.h"

Shape::Shape(Component* parent, const QString& name, const QVariantMap& properties)
    : Component(parent, name, properties)
{
}

bool Shape::contains(const QRectF& sceneRect) const
{
    return sceneRect.intersects(getRect());
}

void Shape::paintComponent(QPainter* painter, const QRectF& sceneRect)
{
    Component::paintComponent(painter, sceneRect);

    painter->setPen(properties["pen"].value<QPen>());
    painter->setBrush(properties["brush"].value<QBrush>());

    switch (properties["type"].toInt())
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
