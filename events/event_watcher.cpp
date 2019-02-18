#include "event_watcher.h"

#include "event.h"

void EventWatcher::addCondition(EventCondition* condition, Function function)
{
    addCondition(Event::NoEvent, condition, function);
}

void EventWatcher::addCondition(const int type, EventCondition* condition, Function function)
{
    actions[type].push_back(std::make_pair(condition, function));
}

void EventWatcher::addAction(const int type, Function function)
{
    actions[type].push_back(std::make_pair(nullptr, function));
}

bool EventWatcher::prepareEvent(Event* event, const int elapsed)
{
    Q_UNUSED(elapsed);

    if (prepareEvent(Event::NoEvent, event))
        return true;
    if (prepareEvent(event->getType(), event))
        return true;

    return false;
}

bool EventWatcher::prepareEvent(const int target, Event* event)
{
    for (Action action : actions[target])
    {
        if (!action.first || action.first->match(event))
        {
            if (action.second(event))
                return true;
        }
    }
    return false;
}
