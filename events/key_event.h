#pragma once

#include "event.h"

class QKeyEvent;

class KeyEvent : public Event
{
public:
    KeyEvent(QKeyEvent* event);

    int getKey() const;
    int getModifiers() const;

private:
    int key;
    int modifiers;
};
