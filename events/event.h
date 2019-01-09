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
    explicit Event(QEvent* event);
    virtual ~Event() = default;

    int getType() const;

    void keep();
    bool isComplete() const;

protected:
    Action action;

private:
    const int type;
};
