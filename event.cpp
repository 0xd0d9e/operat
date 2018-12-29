#include "event.h"

Event::Event(Function timeout, const Type type, const int duration, const int spent)
    : type(type)
    , duration(duration)
    , timeout(timeout)
    , spent(spent)
{

}

bool Event::prepare(const int elapsed)
{
    if (duration == 0)
    {
        timeout();
        return type == Single;
    }

    spent += elapsed;
    if (spent >= duration)
    {
        timeout();
        spent -= duration;
        return type == Single;
    }
    return false;
}
