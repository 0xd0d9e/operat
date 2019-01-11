#include "display.h"

#include "camera.h"
#include "common/debug.h"

Camera* Display::getCamera() const
{
    return camera;
}

void Display::setCamera(Camera* newCamera)
{
    camera = newCamera;
}

bool Display::contains(const QRectF& sceneRect) const
{
    return sceneRect.intersects(localToGlobal(QRectF(getPos(), camera->getFrameSize())));
}

void Display::paintComponent(QPainter* painter, const QRectF& sceneRect)
{
    if (!camera)
        return;
    Component::paintComponent(painter, sceneRect);

    camera->render(painter, sceneRect);
    painter->setPen(QPen(Qt::red, 2));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(QRectF(QPointF(), camera->getFrameSize()));
}
