#pragma once

#include <functional>

class Event
{
public:
    enum Type
    {
        Single,
        Regular
    };

    using Function = std::function<void ()>;

    Event(Function timeout, const Type type = Single, const int duration = 0, const int spent = 0);

    /// return true if event complete
    bool prepare(const int elapsed);

private:
    Type type;
    int duration;
    Function timeout;
    int spent;
};
