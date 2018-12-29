#pragma once

#include <QHash>
#include <QImage>
#include <QString>
#include <QVariantMap>

class ResourceManager
{
public:
    static ResourceManager& instance();

    void addImage(const QString& alias, const QImage& image);
    QImage getImage(const QString& alias) const;

    void setPreset(const QString& name, const QVariantMap& preset);
    QVariantMap getPreset(const QString& name) const;

private:
    ResourceManager();

    QHash<QString,QImage> images;
    QHash<QString,QVariantMap> presets;
};
