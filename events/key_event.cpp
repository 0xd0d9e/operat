#include "key_event.h"

#include <QKeyEvent>


KeyEvent::KeyEvent(QKeyEvent* event)
    : InputEvent(getEventType(event))
    , key(event->key())
    , modifiers(event->modifiers())
{

}

int KeyEvent::getKey() const
{
    return key;
}

int KeyEvent::getModifiers() const
{
    return modifiers;
}
