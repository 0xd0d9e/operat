#pragma once

#include "component.h"

class Camera;

class Display : public Component
{
public:
    DECLARE_CONSTRUCTOR(Display, Component)

    Camera* getCamera() const;
    void setCamera(Camera* camera);

    bool contains(const QRectF &sceneRect) const;

    void paintComponent(QPainter *painter, const QRectF &sceneRect);

private:
    Camera* camera = nullptr;
};

