#include "sprite.h"

#include "app/resource_manager.h"
#include "app/service_manager.h"

void Sprite::paintComponent(QPainter* painter, const QRectF& sceneRect)
{
    Component::paintComponent(painter, sceneRect);

    auto resourceManager = ServiceManager::ask<ResourceManager>();
    const QImage image = resourceManager->getImage(getImage());
    painter->drawImage(calcOrigin(image.size()), image);
}

QPointF Sprite::calcOrigin(const QSizeF& size) const
{
    const QPointF origin = getOrigin();
    return origin.isNull()
            ? QPointF()
            : QPointF(size.width() * origin.x(), size.height() * origin.y());
}
