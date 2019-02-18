#include "event_listener.h"

#include "event.h"
#include "key_event.h"
#include "mouse_event.h"
#include "wheel_event.h"

EventListener::EventListener()
{

}

bool EventListener::onEvent(Event* event, const int elapsed)
{
    Q_UNUSED(elapsed);

    switch (event->getType())
    {
    case Event::MousePress:     return mousePress(static_cast<MouseEvent*>(event));
    case Event::MouseMove:      return mouseMove(static_cast<MouseEvent*>(event));
    case Event::MouseRelease:   return mouseRelease(static_cast<MouseEvent*>(event));
    case Event::KeyPress:       return keyPress(static_cast<KeyEvent*>(event));
    case Event::KeyRelease:     return keyRelease(static_cast<KeyEvent*>(event));
    case Event::Wheel:          return wheel(static_cast<WheelEvent*>(event));
    }
    return false;
}

bool EventListener::mousePress(MouseEvent* )
{
    return false;
}

bool EventListener::mouseMove(MouseEvent* )
{
    return false;
}

bool EventListener::mouseRelease(MouseEvent* )
{
    return false;
}

bool EventListener::keyPress(KeyEvent* )
{
    return false;
}

bool EventListener::keyRelease(KeyEvent* )
{
    return false;
}

bool EventListener::wheel(WheelEvent* )
{
    return false;
}

bool EventListener::isEnabled() const
{
    return enabled;
}

void EventListener::setEnabled(const bool newEnabled)
{
    enabled = newEnabled;
}
