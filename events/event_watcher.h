#pragma once

#include "common/simple_function.h"
#include "components/component.h"
#include "event_condition.h"

#include <list>
#include <unordered_map>

class EventWatcher : public Component
{
public:
    DECLARE_CONSTRUCTOR(EventWatcher, Component)

    void addCondition(EventCondition* condition, SimpleFunction function);
    void addCondition(const int type, EventCondition* condition, SimpleFunction function);

private:
    void prepareEvent(Event *event, const int elapsed) override;
    void prepareEvent(const int target, Event *event);

    using Action = std::pair<EventCondition*, SimpleFunction>;

    std::unordered_map<int, std::list<Action> > actions;
};

