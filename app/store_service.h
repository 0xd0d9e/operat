#pragma once

#include "service.h"

#include <QString>
#include <QVariant>
#include <QVariantMap>

class StoreService : public Service
{
public:
    QVariant getValue(const QString& name, const QVariant& defaultValue = QVariant());
    void setValue(const QString& name, const QVariant& value);

    bool contains(const QString& name) const;
    QStringList getKeys() const;

private:
    StoreService();

    QVariantMap values;
};
