#include "event_condition.h"

#include "key_event.h"

EventCondition::EventCondition()
{

}

KeyEventCondition::KeyEventCondition(const int key, const int filter)
    : key(key)
    , filter(filter)
{

}

bool KeyEventCondition::match(Event* event) const
{
    return (filter != NoFilter && event->getType() == filter && matchKey(event))
        || (event->getType() == Event::KeyPress && matchKey(event))
        || (event->getType() == Event::KeyRelease && matchKey(event));
}

bool KeyEventCondition::matchKey(Event* event) const
{
    return static_cast<KeyEvent*>(event)->getKey() == key;
}
