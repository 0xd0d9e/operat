#pragma once

#include "component.h"

#include <QPointF>
#include <QPen>

class Line : public Component
{
public:
    DECLARE_CONSTRUCTOR(Line, Component)

    DECLARE_PROPERTY(QPen, pen, Pen)
    DECLARE_PROPERTY(QPointF, p1, P1)
    DECLARE_PROPERTY(QPointF, p2, P2)

    bool contains(const QRectF& sceneRect) const override;

    void paintComponent(QPainter* painter, const QRectF& sceneRect) override;
};
