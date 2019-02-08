#pragma once

#include "input_event.h"

class QKeyEvent;

class KeyEvent : public InputEvent
{
public:
    KeyEvent(QKeyEvent* event);

    int getKey() const;
    int getModifiers() const;

private:
    int key;
    int modifiers;
};
