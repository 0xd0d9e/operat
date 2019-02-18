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
    DECLARE_CONSTRUCTOR(VehicleControl, Component)

    DECLARE_PROPERTY_D(double, speed, Speed, 100.0)

    void setTarget(Component* target);

private:
    DECLARE_PREPARE_EVENT(Component)

    bool keyPress(KeyEvent* event) override;
    bool keyRelease(KeyEvent* event) override;

    void update(const double time) final;

    Component* target = nullptr;
    QSet<int> keys;
};
