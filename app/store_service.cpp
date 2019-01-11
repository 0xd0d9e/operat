#include "store_service.h"

#include "message_service.h"
#include "service_manager.h"

StoreService::StoreService()
{
}

QVariant StoreService::getValue(const QString& name, const QVariant& defaultValue)
{
    return values.value(name, defaultValue);
}

void StoreService::setValue(const QString& name, const QVariant& value)
{
    QVariant& currentValue = values[name];
    if (currentValue == value)
        return;

    currentValue = value;
    ServiceManager::ask<MessageService>()->send(name, value);
}

bool StoreService::contains(const QString& name) const
{
    return values.contains(name);
}

QStringList StoreService::getKeys() const
{
    return QStringList(values.keys());
}
