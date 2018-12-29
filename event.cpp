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
    spent += elapsed;
    if (spent >= duration)
    {
        timeout();

        if (duration == 0)
            spent = 0;
        else
            spent -= duration;
        return type == Single;
    }
    return false;
}
