#include "message_service.h"

inline bool operator == (const MessageService::Handler l, const MessageService::Handler r)
{
    return l == r;
}

MessageService::MessageService()
{
}

void MessageService::send(const QString& message, const QVariant& value)
{
    for (Handler handler : handlers[message])
        handler(message, value);
}

void MessageService::addHandler(const QString& message, Handler handler)
{
    handlers[message].push_back(handler);
}

void MessageService::removeHandler(const QString& message, Handler handler)
{
    handlers[message].removeOne(handler);
}
