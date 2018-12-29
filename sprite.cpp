#include "sprite.h"

#include "resource_manager.h"

Sprite::Sprite(Component* parent, const QString& name, const QVariantMap& properties)
    : Component(parent, name, properties)
{
}

void Sprite::paintComponent(QPainter* painter, const QRectF& sceneRect)
{
    Component::paintComponent(painter, sceneRect);

    painter->drawImage(0, 0, ResourceManager::instance().getImage(getImage()));
}
