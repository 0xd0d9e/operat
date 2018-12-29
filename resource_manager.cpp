#include "resource_manager.h"

ResourceManager& ResourceManager::instance()
{
    static ResourceManager resourceManager;
    return resourceManager;
}

void ResourceManager::addImage(const QString& alias, const QImage& image)
{
    Q_ASSERT(!image.isNull());
    images[alias] = image;
}

QImage ResourceManager::getImage(const QString& alias) const
{
    return images.value(alias);
}

void ResourceManager::setPreset(const QString& name, const QVariantMap& preset)
{
    presets[name] = preset;
}

QVariantMap ResourceManager::getPreset(const QString& name) const
{
    return presets.value(name);
}

ResourceManager::ResourceManager()
{
}
