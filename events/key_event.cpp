#include "key_event.h"

#include <QKeyEvent>


KeyEvent::KeyEvent(QKeyEvent* event)
    : Event(event)
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
