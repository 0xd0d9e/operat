#include "event.h"

#include <QEvent>
#include <QHash>

inline Event::Type getEventType(QEvent* event)
{
    const QHash<QEvent::Type, Event::Type> eventMap =
    {
        {QEvent::MouseButtonPress, Event::MousePress},
        {QEvent::MouseButtonRelease, Event::MouseRelease},
        {QEvent::MouseMove, Event::MouseMove},
        {QEvent::KeyPress, Event::KeyPress},
        {QEvent::KeyRelease, Event::KeyRelease},
        {QEvent::Wheel, Event::Wheel},
    };
    return eventMap[event->type()];
}

Event::Event(const int type)
    : action(Complete)
    , type(type)
{
}

Event::Event(QEvent* event)
    : action(Complete)
    , type(getEventType(event))
{

}

int Event::getType() const
{
    return type;
}

void Event::keep()
{
    action = Keep;
}

bool Event::isComplete() const
{
    return action == Complete;
}

