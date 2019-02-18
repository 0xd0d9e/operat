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

    bool onEvent(Event *event, const int elapsed);

    virtual bool mousePress(MouseEvent* event);
    virtual bool mouseMove(MouseEvent* event);
    virtual bool mouseRelease(MouseEvent* event);

    virtual bool keyPress(KeyEvent* event);
    virtual bool keyRelease(KeyEvent* event);

    virtual bool wheel(WheelEvent* event);

    bool isEnabled() const;
    void setEnabled(const bool enabled);

private:
    bool enabled = true;
};

#define DECLARE_PREPARE_EVENT(Super) bool prepareEvent(Event *event, const int elapsed) override \
        { if (!isEnabled()) return false; \
          if (onEvent(event, elapsed)) return true; \
          return Super::prepareEvent(event, elapsed); }
