#include "invoke_event.h"

InvokeEvent::InvokeEvent(Function timeout, const bool repeat, const int duration, const int spent)
    : Event(Event::Invoke)
    , repeat(repeat)
    , duration(duration)
    , timeout(timeout)
    , spent(spent)
{
    if (repeat)
        action = Keep;
}

void InvokeEvent::exec(const int elapsed)
{
    spent += elapsed;
    if (spent >= duration)
    {
        timeout();

        if (duration == 0)
            spent = 0;
        else
            spent -= duration;
    }
}
