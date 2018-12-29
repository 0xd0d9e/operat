#pragma once

#include "shape.h"

class Grid : public Shape
{
public:
    Grid(Component* parent = nullptr, const QString& name = QString(), const QVariantMap& properties = QVariantMap());

    DECLARE_PROPERTY(double, size, Size)

    bool contains(const QRectF &sceneRect) const final;

private:
    void paintComponent(QPainter *painter, const QRectF &sceneRect) final;
};
