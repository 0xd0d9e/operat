#pragma once

#include "shape.h"

class Label : public Shape
{
public:
    Label(Component* parent = nullptr, const QString& name = QString(), const QVariantMap& properties = QVariantMap());

    DECLARE_PROPERTY(QStringList, text, Text)

    void paintComponent(QPainter *painter, const QRectF &sceneRect) override;
};
