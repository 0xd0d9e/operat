#pragma once

class QEvent;

class Event
{
public:
    enum Type
    {
        NoEvent = 0,
        Invoke,

        MousePress,
        MouseRelease,
        MouseMove,
        Wheel,

        KeyPress,
        KeyRelease,

        UserType = 5000
    };

    enum Action
    {
        Complete,
        Keep
    };

    explicit Event(const int type);
    virtual ~Event() = default;

    virtual bool isInputEvent() const;

    int getType() const;

    void keep();
    bool isComplete() const;

protected:
    Action action;

private:
    const int type;
};

Event::Type getEventType(QEvent* event);
