#pragma once

#include "components/component.h"

class Event;
class MouseEvent;
class KeyEvent;
class WheelEvent;

class EventListener
{
public:
    EventListener();

    void onEvent(Event *event, const int elapsed);

    virtual void mousePress(MouseEvent* event);
    virtual void mouseMove(MouseEvent* event);
    virtual void mouseRelease(MouseEvent* event);

    virtual void keyPress(KeyEvent* event);
    virtual void keyRelease(KeyEvent* event);

    virtual void wheel(WheelEvent* event);
};

#define DECLARE_PREPARE_EVENT(Super) void prepareEvent(Event *event, const int elapsed) override \
        { onEvent(event, elapsed); Super::prepareEvent(event, elapsed); }
