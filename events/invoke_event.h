#pragma once

#include "event.h"

#include <functional>

class InvokeEvent : public Event
{
public:
    using Function = std::function<void ()>;

    /// Create func call  event
    /// \a timeout - func for call (don't delete owner component)
    /// \a repeat - repeat event, if false - singleshot event
    /// \a duration - call timeout
    /// \a spent - time before first shot
    InvokeEvent(Function timeout,
                const bool repeat = false,
                const int duration = 0,
                const int spent = 0);

    /// return true if event complete
    void exec(const int elapsed);

private:
    bool repeat;
    int duration;
    Function timeout;
    int spent;
};
