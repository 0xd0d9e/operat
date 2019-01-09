#pragma once

#include "component.h"

class Sprite : public Component
{
public:
    Sprite(Component* parent = nullptr, const QString& name = QString(), const QVariantMap& properties = QVariantMap());

    DECLARE_PROPERTY(QString, image, Image)

    void paintComponent(QPainter *painter, const QRectF &sceneRect) override;
};
