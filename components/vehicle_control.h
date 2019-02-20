#pragma once

#include "component.h"
#include "events/event_listener.h"

#include <QSet>

class KeyEvent;
class WheelEvent;

class VehicleControl
        : public Component
        , public EventListener
{
public:
    enum Mode
    {
        SimpleMoving,
        DirectionalMoving
    };
    DECLARE_CONSTRUCTOR(VehicleControl, Component)

    DECLARE_PROPERTY_D(double, speed, Speed, 100.0)
    DECLARE_PROPERTY_D(double, rotationSpeed, RotationSpeed, 3.0)
    DECLARE_PROPERTY_D(int, mode, Mode, SimpleMoving)

    void setTarget(Component* target);

private:
    DECLARE_PREPARE_EVENT(Component)

    bool keyPress(KeyEvent* event) override;
    bool keyRelease(KeyEvent* event) override;

    void update(const double time) final;

    void simpleMoving(const double time);
    void directionalMoving(const double time);

    Component* target = nullptr;
    QSet<int> keys;
};
