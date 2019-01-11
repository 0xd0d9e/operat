#pragma once

#include "service.h"

#include <QString>
#include <QVariant>

#include <functional>

class MessageService : public Service
{
public:
    using Handler = std::function<void (const QString&, const QVariant&)>;

    MessageService();

public:
    void send(const QString& message, const QVariant& value);
    void addHandler(const QString& message, Handler handler);
    void removeHandler(const QString& message, Handler handler);

private:
    QHash<QString, QList<Handler> > handlers;

};

