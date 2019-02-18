#pragma once

#include "components/component.h"
#include "event_condition.h"

#include <list>
#include <unordered_map>

class EventWatcher : public Component
{
public:
    using Function = std::function<bool (Event*)>;

    DECLARE_CONSTRUCTOR(EventWatcher, Component)

    void addCondition(EventCondition* condition, Function function);
    void addCondition(const int type, EventCondition* condition, Function function);
    void addAction(const int type, Function function);

private:
    bool prepareEvent(Event *event, const int elapsed) override;
    bool prepareEvent(const int target, Event *event);

    using Action = std::pair<EventCondition*, Function>;

    std::unordered_map<int, std::list<Action> > actions;
};

