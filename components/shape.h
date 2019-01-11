#pragma once

#include "component.h"
#include "common/style.h"

class Shape : public Component
{
public:
    enum Type
    {
        NoBody,
        Rectangle,
        Ellipse
    };

    DECLARE_CONSTRUCTOR(Shape, Component)

    DECLARE_PROPERTY(Style, style, Style)
    DECLARE_PROPERTY(int, type, Type)
    DECLARE_PROPERTY(QRectF, rect, Rect)

    bool contains(const QRectF& sceneRect) const override;

    void paintComponent(QPainter* painter, const QRectF& sceneRect) override;
};
