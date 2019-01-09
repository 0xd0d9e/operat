#include "event_listener.h"

#include "event.h"
#include "key_event.h"
#include "mouse_event.h"
#include "wheel_event.h"

EventListener::EventListener()
{

}

void EventListener::onEvent(Event* event, const int elapsed)
{
    Q_UNUSED(elapsed);

    switch (event->getType())
    {
    case Event::MousePress:     mousePress(static_cast<MouseEvent*>(event));    break;
    case Event::MouseMove:      mouseMove(static_cast<MouseEvent*>(event));     break;
    case Event::MouseRelease:   mouseRelease(static_cast<MouseEvent*>(event));  break;
    case Event::KeyPress:       keyPress(static_cast<KeyEvent*>(event));        break;
    case Event::KeyRelease:     keyRelease(static_cast<KeyEvent*>(event));      break;
    case Event::Wheel:          wheel(static_cast<WheelEvent*>(event));         break;
    }
    return;
}

void EventListener::mousePress(MouseEvent* )
{
}

void EventListener::mouseMove(MouseEvent* )
{
}

void EventListener::mouseRelease(MouseEvent* )
{
}

void EventListener::keyPress(KeyEvent* )
{
}

void EventListener::keyRelease(KeyEvent* )
{
}

void EventListener::wheel(WheelEvent* )
{
}
