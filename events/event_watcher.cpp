#include "event_watcher.h"

#include "event.h"

void EventWatcher::addCondition(EventCondition* condition, SimpleFunction function)
{
    addCondition(Event::NoEvent, condition, function);
}

void EventWatcher::addCondition(const int type, EventCondition* condition, SimpleFunction function)
{
    actions[type].push_back(std::make_pair(condition, function));
}

void EventWatcher::prepareEvent(Event* event, const int elapsed)
{
    prepareEvent(Event::NoEvent, event);
    prepareEvent(event->getType(), event);
}

void EventWatcher::prepareEvent(const int target, Event* event)
{
    for (Action action : actions[target])
    {
        if (action.first->match(event))
            action.second();
    }
}
