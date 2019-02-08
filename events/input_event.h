#pragma once

#include "event.h"

class InputEvent : public Event
{
public:
    explicit InputEvent(const int type);

    bool isInputEvent() const final;
};

