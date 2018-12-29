#pragma once

#include "component.h"

class Shape : public Component
{
public:
    enum Type
    {
        NoBody,
        Rectangle,
        Ellipse
    };

    Shape(Component* parent = nullptr, const QString& name = QString(), const QVariantMap& properties = QVariantMap());

    DECLARE_PROPERTY(QPen, pen, Pen)
    DECLARE_PROPERTY(QBrush, brush, Brush)
    DECLARE_PROPERTY(int, type, Type)
    DECLARE_PROPERTY(QRectF, rect, Rect)

    bool contains(const QRectF& sceneRect) const override;

    void paintComponent(QPainter* painter, const QRectF& sceneRect) override;
};
