#pragma once

#include "component.h"

#include <QPen>

class Grid : public Component
{
public:
    DECLARE_CONSTRUCTOR(Grid, Component)

    DECLARE_PROPERTY(double, size, Size)
    DECLARE_PROPERTY(QPen, pen, Pen)
    DECLARE_PROPERTY(QRectF, rect, Rect)

    bool contains(const QRectF &sceneRect) const final;

private:
    void paintComponent(QPainter *painter, const QRectF &sceneRect) final;
};
