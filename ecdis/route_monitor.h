#pragma once

#include "route_calculator.h"
#include "voyage_state.h"

#include <components/component.h>

class Line;
class Route;

class RouteMonitor : public Component
{
public:
    DECLARE_CONSTRUCTOR(RouteMonitor, Component)

    DECLARE_PROPERTY_CD(bool, enabled, Enabled, onEnabledChanged, false)

    void setRoute(Route* route);
    void setShip(Component* ship);

    void update(const double time) final;

private:
    void init() final;
    void initilizeVoyage();

    void onEnabledChanged(const bool enabled);

    Route* route;
    Component* ship;

    VoyageState state;
    RouteCalculator* calculator;

    Line* traverseLine;
    Line* targetLine;
};

