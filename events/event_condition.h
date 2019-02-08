#pragma once

class Event;

class EventCondition
{
public:
    EventCondition();

    virtual bool match(Event* event) const = 0;
};

class KeyEventCondition : public EventCondition
{
public:
    static const int NoFilter = 0;

    KeyEventCondition(const int key, const int filter = NoFilter);

    bool match(Event* event) const override;

private:
    bool matchKey(Event* event) const;

    const int key;
    const int filter;
};

