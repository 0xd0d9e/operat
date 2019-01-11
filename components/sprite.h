#pragma once

#include "component.h"

class Sprite : public Component
{
public:
    DECLARE_CONSTRUCTOR(Sprite, Component)

    DECLARE_PROPERTY(QString, image, Image)
    DECLARE_PROPERTY(QPointF, origin, Origin)

    void paintComponent(QPainter *painter, const QRectF &sceneRect) override;

private:
    QPointF calcOrigin(const QSizeF& size) const;
};
